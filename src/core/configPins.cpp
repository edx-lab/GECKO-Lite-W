#include "configPins.h"
#include "esp_mac.h"
#include "sd_functions.h"
#include <globals.h>
String getMacAddress() {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    char macStr[18];
    snprintf(
        macStr,
        sizeof(macStr),
        "%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0],
        mac[1],
        mac[2],
        mac[3],
        mac[4],
        mac[5]
    );

    return String(macStr);
}

void BruceConfigPins::fromJson(JsonObject obj) {
    int count = 0;
    String mac = getMacAddress();

    if (obj[mac].isNull()) return saveFile();

    JsonObject root = obj[mac].as<JsonObject>();

    if (!root["rot"].isNull()) {
        rotation = root["rot"].as<int>();
    } else {
        count++;
        log_e("Fail");
    }

    if (!root["bleName"].isNull()) {
        bleName = root["bleName"].as<String>();
    } else {
        count++;
        log_e("Fail");
    }

    if (!root["iButton"].isNull()) {
        int val = root["iButton"].as<int>();
        if (val < GPIO_NUM_MAX) iButton = val;
        else log_w("iButton pin not set");
    } else {
        count++;
        log_e("Fail");
    }

    if (!root["SDCard_Pins"].isNull()) {
        SPIPins def = SDCARD_bus;
        SDCARD_bus.fromJson(root["SDCard_Pins"].as<JsonObject>());
        if (SDCARD_bus.sck == GPIO_NUM_NC && def.sck != GPIO_NUM_NC) {
            SDCARD_bus = def;
            count++;
        }
    } else {
        count++;
        log_e("Fail");
    }
    // DO NOT UPDATE THESE VALIES, THEY ARE USED INTERNALLY BY THE SYSTEM,
    // THEY NEVER CHANGE EXCEPT FOR CARDPUTER/CARDPUTER ADV environment
    // if (!root["sys_i2c"].isNull()) {
    //     sys_i2c.fromJson(root["sys_i2c"].as<JsonObject>());
    // } else {
    //     count++;
    //     log_e("Fail");
    // }
    if (!root["i2c_bus"].isNull()) {
#if defined(SOC_HP_I2C_NUM) && SOC_HP_I2C_NUM < 2 && SYS_I2C_SDA >= 0 && SYS_I2C_SCL >= 0
        log_e("I2C Pins cannot be changed on this board, using default values");
        i2c_bus = sys_i2c;
#else
        i2c_bus.fromJson(root["i2c_bus"].as<JsonObject>());
#endif
    } else {
        count++;
        log_e("Fail");
    }
    if (!root["uart_bus"].isNull()) {
        uart_bus.fromJson(root["uart_bus"].as<JsonObject>());
    } else {
        count++;
        log_e("Fail");
    }
    validateConfig();
    if (count > 0) saveFile();
}

void BruceConfigPins::toJson(JsonObject obj) const {
    JsonObject root = obj[getMacAddress()].to<JsonObject>();

    root["rot"] = rotation;
    root["bleName"] = bleName;
    root["iButton"] = iButton;

    JsonObject _SD = root["SDCard_Pins"].to<JsonObject>();
    SDCARD_bus.toJson(_SD);

    JsonObject _si2c = root["sys_i2c"].as<JsonObject>();
    sys_i2c.toJson(_si2c);
    JsonObject _di2c = root["i2c_bus"].to<JsonObject>();
    i2c_bus.toJson(_di2c);
    JsonObject _uart = root["uart_bus"].to<JsonObject>();
    uart_bus.toJson(_uart);
}

void BruceConfigPins::loadFile(JsonDocument &jsonDoc, bool checkFS) {
    FS *fs;
    if (checkFS) {
        if (!getFsStorage(fs)) return;
    } else {
        if (checkLittleFsSize()) fs = &LittleFS;
        else return;
    }

    if (!fs->exists(filepath)) return createFile();

    File file;
    file = fs->open(filepath, FILE_READ);
    if (!file) {
        log_e("Config pins file not found. Using default values");
        return;
    }

    if (deserializeJson(jsonDoc, file)) {
        log_e("Failed to read config pins file, using default configuration");
        return;
    }
    file.close();

    serializeJsonPretty(jsonDoc, Serial);
}

void BruceConfigPins::fromFile(bool checkFS) {
    JsonDocument jsonDoc;
    loadFile(jsonDoc, checkFS);

    if (!jsonDoc.isNull()) fromJson(jsonDoc.as<JsonObject>());
    jsonDoc.clear();
}

void BruceConfigPins::createFile() {
    JsonDocument jsonDoc;
    toJson(jsonDoc.to<JsonObject>());
    serializeJsonPretty(jsonDoc, Serial);

    // Open file for writing
    FS *fs = &LittleFS;
    File file = fs->open(filepath, FILE_WRITE);
    if (!file) {
        log_e("Failed to open config file");
        file.close();
        return;
    };

    // Serialize JSON to file
    if (serializeJsonPretty(jsonDoc, file) < 5) log_e("Failed to write config file");
    else log_i("config file written successfully");

    file.close();
    jsonDoc.clear();

    // don't try to mount SD Card if not previously mounted
    if (sdcardMounted) copyToFs(LittleFS, SD, filepath, false);
}

void BruceConfigPins::saveFile() {
    JsonDocument jsonDoc;
    loadFile(jsonDoc);

    if (jsonDoc.isNull()) return createFile();

    jsonDoc.remove(getMacAddress());
    toJson(jsonDoc.as<JsonObject>());

    // Open file for writing
    FS *fs = &LittleFS;
    File file = fs->open(filepath, FILE_WRITE);
    if (!file) {
        log_e("Failed to open config file");
        return;
    };

    // Serialize JSON to file
    if (serializeJsonPretty(jsonDoc, file) < 5) log_e("Failed to write config file");
    else log_i("config file written successfully");

    file.close();
    jsonDoc.clear();
    // don't try to mount SD Card if not previously mounted
    if (sdcardMounted) copyToFs(LittleFS, SD, filepath, false);
}

void BruceConfigPins::factoryReset() {
    FS *fs = &LittleFS;
    fs->rename(String(filepath), "/bak." + String(filepath).substring(1));
    // don't try to mount SD Card if not previously mounted
    if (sdcardMounted) SD.rename(String(filepath), "/bak." + String(filepath).substring(1));
}

void BruceConfigPins::validateConfig() {
    validateRotationValue();
    validateSpiPins(SDCARD_bus);
    validateI2CPins(sys_i2c);
    validateI2CPins(i2c_bus);
    validateUARTPins(uart_bus);
}

void BruceConfigPins::setSDCardPins(SPIPins value) {
    SDCARD_bus = value;
    validateSpiPins(SDCARD_bus);
    saveFile();
}

void BruceConfigPins::setSpiPins(SPIPins value) {
    validateSpiPins(value);
    saveFile();
}

void BruceConfigPins::setI2CPins(I2CPins value) {
    validateI2CPins(value);
    saveFile();
}

void BruceConfigPins::setUARTPins(UARTPins value) {
    validateUARTPins(value);
    saveFile();
}
void BruceConfigPins::validateSpiPins(SPIPins value) {
    if (value.sck < 0 || value.sck > GPIO_PIN_COUNT) value.sck = GPIO_NUM_NC;
    if (value.miso < 0 || value.miso > GPIO_PIN_COUNT) value.miso = GPIO_NUM_NC;
    if (value.mosi < 0 || value.mosi > GPIO_PIN_COUNT) value.mosi = GPIO_NUM_NC;
    if (value.cs < 0 || value.cs > GPIO_PIN_COUNT) value.cs = GPIO_NUM_NC;
    if (value.io0 < 0 || value.io0 > GPIO_PIN_COUNT) value.io0 = GPIO_NUM_NC;
    if (value.io2 < 0 || value.io2 > GPIO_PIN_COUNT) value.io2 = GPIO_NUM_NC;
}

void BruceConfigPins::validateI2CPins(I2CPins value) {
    if (value.sda < 0 || value.sda > GPIO_PIN_COUNT) value.sda = GPIO_NUM_NC;
    if (value.scl < 0 || value.scl > GPIO_PIN_COUNT) value.scl = GPIO_NUM_NC;
}

void BruceConfigPins::validateUARTPins(UARTPins value) {
    if (value.rx < 0 || value.rx > GPIO_PIN_COUNT) value.rx = GPIO_NUM_NC;
    if (value.tx < 0 || value.tx > GPIO_PIN_COUNT) value.tx = GPIO_NUM_NC;
}

void BruceConfigPins::setRotation(int value) {
    rotation = value;
    validateRotationValue();
    saveFile();
}

void BruceConfigPins::validateRotationValue() {
    if (rotation < 0 || rotation > 3) rotation = 1;
}

void BruceConfigPins::setBleName(String value) {
    bleName = value;
    saveFile();
}

void BruceConfigPins::setiButtonPin(int value) {
    if (value < GPIO_NUM_MAX) {
        iButton = value;
        saveFile();
    } else log_e("iButton: Gpio pin not set, incompatible with this device\n");
}

