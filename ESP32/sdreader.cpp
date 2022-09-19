#include <SD.h>

#include "sdreader.h"
#include <ArduinoJson.h>

File currentAnimationFile;

bool initSD()
{
    Serial.println("Try to init SD Card");
    if (!SD.begin())
    {
        Serial.println("Failed to initilize SD Card!");
        return false;
    }
    Serial.println("Initilatized SD Card");

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return false;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if (cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if (cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
}

boolean readConfig(char *ssid, char *password)
{
    File config;
    config = SD.open("/config.json", FILE_READ);

    if(!config)
    {
        Serial.printf("Can not open config.json!\n");
        return false;
    }

    if( !config.available() )
    {
        Serial.printf("config.json not available!\n");
        return false;
    }

    StaticJsonDocument<200> doc;
    deserializeJson(doc, config.readString());

    strcpy(ssid, doc["ssid"]);
    strcpy(password, doc["password"]);

    Serial.println(ssid);
    Serial.println(password);

    return true;
}

size_t readFile(char *buffer, size_t maxSize)
{
    if( !currentAnimationFile.available() )
    {
        currentAnimationFile.seek(0, fs::SeekMode::SeekSet);
    }

    return currentAnimationFile.readBytes(buffer, maxSize);
}

boolean openFile(const char * filename)
{
    Serial.print("Opening filename: ");
    Serial.println(filename);

    if (currentAnimationFile )
        currentAnimationFile.close();

    currentAnimationFile = SD.open(filename, FILE_READ);
    if (currentAnimationFile )
        return true;
    return false;
}
