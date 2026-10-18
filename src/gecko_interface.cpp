#include "core/display.h"
#include <globals.h>
#include <interface.h>
#include <Preferences.h>

namespace {
constexpr uint16_t defaultFullMv = 4200;
constexpr uint16_t defaultEmptyMv = 3300;
uint16_t batteryFullMv = defaultFullMv;
uint16_t batteryEmptyMv = defaultEmptyMv;
int batteryCachedPercent = -1;
uint32_t batterySampledAt = 0;

bool validFullMv(uint16_t mv) { return mv >= 3600 && mv <= 4400; }
bool validBatteryRange(uint16_t full, uint16_t empty) {
    return validFullMv(full) && empty >= 2500 && empty <= 3900 && full >= empty + 200;
}

float readBatteryMv() {
    uint32_t totalMv = 0;
    analogReadMilliVolts(ANALOG_BAT_PIN);
    for (int i = 0; i < 16; ++i) totalMv += analogReadMilliVolts(ANALOG_BAT_PIN);
    return (totalMv / 16.0f) * ANALOG_BAT_MULTIPLIER;
}

bool saveBatteryRange(uint16_t full, uint16_t empty) {
    if (!validBatteryRange(full, empty)) return false;
    Preferences prefs;
    if (!prefs.begin("gecko-battery", false)) return false;
    // Store both endpoints in one NVS value so they cannot be partially updated.
    const uint32_t range = (static_cast<uint32_t>(full) << 16) | empty;
    const bool saved = prefs.putUInt("range-mv", range) == sizeof(uint32_t);
    prefs.end();
    if (saved) {
        batteryFullMv = full;
        batteryEmptyMv = empty;
        batteryCachedPercent = -1;
    }
    return saved;
}

constexpr uint32_t debounceMs = 40;
constexpr uint32_t repeatDelayMs = 400;
constexpr uint32_t repeatIntervalMs = 120;
constexpr uint32_t restartHoldMs = 3000;

struct Button {
    uint8_t pin;
    bool raw = false;
    bool pressed = false;
    bool justPressed = false;
    bool justReleased = false;
    uint32_t changedAt = 0;
    uint32_t pressedAt = 0;
    uint32_t repeatedAt = 0;

    void update(uint32_t now) {
        justPressed = justReleased = false;
        const bool reading = digitalRead(pin) == LOW;
        if (reading != raw) {
            raw = reading;
            changedAt = now;
        }
        if (raw != pressed && now - changedAt >= debounceMs) {
            pressed = raw;
            justPressed = pressed;
            justReleased = !pressed;
            if (pressed) pressedAt = repeatedAt = now;
        }
    }

    bool navigationEvent(uint32_t now) {
        if (justPressed) return true;
        if (pressed && now - pressedAt >= repeatDelayMs && now - repeatedAt >= repeatIntervalMs) {
            repeatedAt = now;
            return true;
        }
        return false;
    }
};

enum ButtonIndex { Up, Down, Left, Right, Select, Set, Back };
Button buttons[] = {
    {JOY_UP_PIN}, {JOY_DOWN_PIN}, {JOY_LEFT_PIN}, {JOY_RIGHT_PIN},
    {JOY_PRESS_PIN}, {SET_BTN_PIN}, {BACK_RST_BTN_PIN},
};
bool waitForRelease = false;
volatile bool selectHeld = false;
} // namespace

void _setup_gpio() {
    // Deselect both peripherals before either SPI controller is started.
    pinMode(TFT_CS, OUTPUT);
    digitalWrite(TFT_CS, HIGH);
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);
    for (const auto &button : buttons) pinMode(button.pin, INPUT_PULLUP);
    pinMode(BUZZ_PIN, OUTPUT);
    digitalWrite(BUZZ_PIN, LOW);
    pinMode(ANALOG_BAT_PIN, INPUT);
    analogSetPinAttenuation(ANALOG_BAT_PIN, ADC_11db);
    Preferences prefs;
    if (prefs.begin("gecko-battery", true)) {
        const uint32_t fallback = (static_cast<uint32_t>(defaultFullMv) << 16) | defaultEmptyMv;
        const uint32_t saved = prefs.getUInt("range-mv", fallback);
        const uint16_t full = saved >> 16;
        const uint16_t empty = saved & 0xFFFF;
        if (validBatteryRange(full, empty)) {
            batteryFullMv = full;
            batteryEmptyMv = empty;
        }
        prefs.end();
    }
}

void _setBrightness(uint8_t brightval) {
    // BL is hardwired to 3.3 V. Blank/wake the panel without claiming PWM control.
    static bool displayOn = true;
    const bool turnOn = brightval != 0;
    if (displayOn != turnOn) {
        tft.writecommand(turnOn ? TFT_DISPON : TFT_DISPOFF);
        displayOn = turnOn;
    }
}

void InputHandler() {
    const uint32_t now = millis();
    bool anyPressed = false;
    for (auto &button : buttons) {
        button.update(now);
        anyPressed |= button.pressed;
    }
    const bool selecting = buttons[Select].pressed || buttons[Set].pressed;
    const bool selectionStarted = selecting && !selectHeld;
    selectHeld = selecting;

    // The first input after display sleep only wakes it, until all keys release.
    if (waitForRelease) {
        if (!anyPressed) waitForRelease = false;
        return;
    }
    if (anyPressed && wakeUpScreen()) {
        waitForRelease = true;
        return;
    }
    if (buttons[Back].pressed && now - buttons[Back].pressedAt >= restartHoldMs) {
        noTone(BUZZ_PIN);
        ESP.restart();
        return;
    }

    UpPress |= buttons[Up].navigationEvent(now);
    DownPress |= buttons[Down].navigationEvent(now);
    PrevPress |= buttons[Left].navigationEvent(now);
    NextPress |= buttons[Right].navigationEvent(now);
    // One event per press; file-browser holds use the separate physical state.
    SelPress |= selectionStarted;
    EscPress |= buttons[Back].justReleased;
    AnyKeyPress |= anyPressed || buttons[Back].justReleased;
}

bool isSelectHeld() { return selectHeld; }

int getBattery() {
    const uint32_t now = millis();
    if (batteryCachedPercent >= 0 && now - batterySampledAt < 1000) return batteryCachedPercent;

    // Linear interpolation between measured endpoints; not a fuel-gauge charge curve.
    const float percent = (readBatteryMv() - batteryEmptyMv) * 100.0f / (batteryFullMv - batteryEmptyMv);
    // Report 5% steps, keeping 0 reserved for devices without a battery.
    // A 2-point margin beyond the rounding midpoint prevents boundary flicker.
    constexpr int step = 5;
    constexpr float hysteresis = 2.0f;
    const int rounded = constrain(static_cast<int>(percent / step + 0.5f) * step, step, 100);
    if (batteryCachedPercent < 0 ||
        percent >= batteryCachedPercent + step / 2.0f + hysteresis ||
        percent <= batteryCachedPercent - step / 2.0f - hysteresis) {
        batteryCachedPercent = rounded;
    }
    batterySampledAt = now;
    return batteryCachedPercent;
}

static uint16_t sampleBatteryReference() {
    // Sample a fresh reference over time, not the cached percentage.
    float total = 0;
    for (int i = 0; i < 8; ++i) {
        total += readBatteryMv();
        delay(25);
    }
    return static_cast<uint16_t>(total / 8.0f + 0.5f);
}

bool calibrateBatteryFull() { return saveBatteryRange(sampleBatteryReference(), batteryEmptyMv); }
bool calibrateBatteryEmpty() { return saveBatteryRange(batteryFullMv, sampleBatteryReference()); }
bool resetBatteryCalibration() { return saveBatteryRange(defaultFullMv, defaultEmptyMv); }

// No charger-status signal or power-switch circuit is connected.
bool isCharging() { return false; }
