//
// Created by Tomasz Kulig on 26/05/2023.
//
#include "Adafruit_SSD1306.h"
#include "uitl.h"
#include "display.h"
#include "display_choice.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

namespace Util {

    void initDisplay() {
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            Serial.println(F("SSD1306 allocation failed"));
            while (true);
        }
        delay(200);

        display.clearDisplay();
        Display::begin(display);
        DisplayChoice::begin(display);
    }
}
