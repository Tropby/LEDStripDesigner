#include <Arduino.h>

#include "https.h"
#include "sdreader.h"

#include <FastLED.h>

#define EST_LED_COUNT 600
#define SECTOR_SIZE (((int)(EST_LED_COUNT * 3.0 / 512.0 + 0.5)) * 512)

#define LED_COUNT (SECTOR_SIZE / 3 + 1)

CRGB ledBuffer[LED_COUNT];

#define INPUT_1 GPIO_NUM_4      /*  */
#define INPUT_2 GPIO_NUM_35     /*  */
#define INPUT_3 GPIO_NUM_34     /*  */
#define INPUT_4 GPIO_NUM_36     /*  */

#define LED_1 GPIO_NUM_27       /* WLAN Connected */
#define LED_2 GPIO_NUM_16       /* Status (AN/AUS) */
#define LED_3 GPIO_NUM_17       /*  */

#define OUTPUT_1 GPIO_NUM_26    /*  */

void setup()
{
    // Wait until voltage is stable
    delay(3000);

    Serial.begin(115200);
    Serial.println("Startup!");
    delay(1000);

    // Inputs from Relais
    pinMode(INPUT_1, INPUT_PULLUP);
    pinMode(INPUT_2, INPUT_PULLUP);
    pinMode(INPUT_3, INPUT_PULLUP);
    pinMode(INPUT_4, INPUT_PULLUP);

    // Output Relais
    pinMode(OUTPUT_1, OUTPUT);

    // Output LEDs
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);

    delay(1000);

    while (!initSD())
    {
        Serial.println("Can not init SD-Card!");
        delay(1000);
    }

    while (!readConfig(ssid, password))
    {
        Serial.println("Can not read config!");
        delay(1000);
    }

    initWiFi();

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
