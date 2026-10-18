#pragma once
#include <stdint.h>

#define USB_VID 0x303A
#define USB_PID 0x1001
#define USB_MANUFACTURER "Gecko"
#define USB_PRODUCT "Gecko Lite W"

// No external UART or I2C peripherals. USB uses the native USB interface.
static const uint8_t TX = 255;
static const uint8_t RX = 255;
static const uint8_t SDA = 255;
static const uint8_t SCL = 255;
// TFT on HSPI. SDA/SCL printed on this display refer to SPI MOSI/CLK.
#define TFT_SCLK 12
#define TFT_MOSI 11
#define TFT_MISO -1
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_BL -1 // BL is wired directly to 3.3 V; no PWM brightness control.
#define TFT_DISPON 0x29
#define TFT_DISPOFF 0x28

// SD on FSPI, independent of the display. Also the default user SPI bus.
#define SDCARD_SCK 14
#define SDCARD_MOSI 13
#define SDCARD_MISO 16
#define SDCARD_CS 15
#define SPI_SCK_PIN SDCARD_SCK
#define SPI_MOSI_PIN SDCARD_MOSI
#define SPI_MISO_PIN SDCARD_MISO
#define SPI_SS_PIN SDCARD_CS
static const uint8_t SS = SDCARD_CS;
static const uint8_t MOSI = SDCARD_MOSI;
static const uint8_t MISO = SDCARD_MISO;
static const uint8_t SCK = SDCARD_SCK;

// Controls are active-low with pull-ups; joystick COM goes to GND.
#define JOY_UP_PIN 4
#define JOY_DOWN_PIN 5
#define JOY_LEFT_PIN 6
#define JOY_RIGHT_PIN 7
#define JOY_PRESS_PIN 21
#define SET_BTN_PIN 17
#define BACK_RST_BTN_PIN 18
#define BTN_ALIAS "OK"
#define ANALOG_BAT_PIN 1
#define ANALOG_BAT_MULTIPLIER 2.0f // 100k upper / 100k lower divider.
#define BUZZ_PIN 38
