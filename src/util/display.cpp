#include "display.h"
#include "Adafruit_SSD1306.h"
#include "Fonts/FreeMono9pt7b.h"
#include "Fonts/FreeMonoBold9pt7b.h"
#include "Fonts/FreeSerif9pt7b.h"
#include "Fonts/Org_01.h"
#include "Fonts/Picopixel.h"
#include "uitl.h"
#include "display_choice.h"

Adafruit_SSD1306 Display::display;
bool Display::blink;
unsigned long Display::previousMillis;

void Display::begin(Adafruit_SSD1306 &_display) {
    display = _display;
}

void Display::setText(const std::string &text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Display::animateText(const std::string &_text) {
    delay(20);
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > 500) {
        previousMillis = currentMillis;
        std::string text;
        text.assign(_text);
        if (blink) text.append(" >");
        setText(text);
        blink = !blink;
    }
}
