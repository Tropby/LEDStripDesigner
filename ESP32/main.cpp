#include <Arduino.h>

#include "https.h"
#include "sdreader.h"

#include <FastLED.h>

#define EST_LED_COUNT 600
#define SECTOR_SIZE (((int)(EST_LED_COUNT * 3.0 / 512.0 + 0.5)) * 512)

#define LED_COUNT (SECTOR_SIZE / 3 + 1)

CRGB ledBuffer[LED_COUNT];

void setup()
{
    Serial.begin(115200);
    Serial.println("Startup!");
    initSD();

    readConfig(ssid, password);

    initWiFi();
    Serial.println("OPEN FILE TEST.ALC!");
    openFile("/test.ALC");

    FastLED.addLeds<WS2812B, 2>(ledBuffer, LED_COUNT);
}

boolean serialMode = false;
void loop()
{
    handleHTTPS();

    while (Serial.available())
    {
        uint8_t b = Serial.read();
        if (b == 0x02)
        {
            uint8_t *buffer = (uint8_t *)ledBuffer;
            for (int i = 0; i < SECTOR_SIZE; i++)
            {
                while (!Serial.available())
                    ;

                b = Serial.read();
                *buffer = b;
                buffer++;
            }
            uint8_t crc = Serial.read();
            serialMode = true;
        }
    }

    if (!serialMode)
    {
        readFile((char *)ledBuffer, SECTOR_SIZE);
        delay(10);
    }

    FastLED.show();
}
