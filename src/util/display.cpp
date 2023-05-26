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
unsigned long Display::lastChange;

void Display::begin(Adafruit_SSD1306 &_display) {
    display = _display;
}

void Display::setText(const std::string &text) {
    clearText();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Display::clearText() {
    display.fillRect(0, 0, 128, 43, BLACK);
}

void Display::animateText(const std::string &text1, const std::string &text2) {
    delay(20);
    unsigned long currentMillis = millis();
    if (currentMillis - lastChange < 500) return;
    std::string text = blink ? text1 : text2;
    setText(text);
    lastChange = currentMillis;
    blink = !blink;
}
