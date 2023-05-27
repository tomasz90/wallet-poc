#include "display.h"
#include "Adafruit_SSD1306.h"
#include "Fonts/FreeMono9pt7b.h"
#include "Fonts/FreeMonoBold9pt7b.h"
#include "Fonts/FreeSerif9pt7b.h"
#include "Fonts/Org_01.h"
#include "Fonts/Picopixel.h"
#include "uitl.h"

Adafruit_SSD1306 Display::display;
bool Display::blink;
unsigned long Display::lastTextBlinked;
unsigned long Display::needsUpdate;

void Display::begin(Adafruit_SSD1306 &_display) {
    display = _display;
    display.clearDisplay();
}

void Display::setText(const std::string &text) {
    clearText();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Display::blinkTextWithSign(const std::string &text) {
    std::string text2;
    text2.assign(text);
    text2.append(" >");
    animateText(text, text2);
}

void Display::drawNo() {
    clearBoxes();
    needsUpdate = false;
    display.fillRect(5, 43, 50, 20, WHITE);
    display.drawRect(6, 44, 48, 18, BLACK);

    display.drawRect(73, 43, 50, 20, WHITE);

    display.setCursor(25, 49);
    display.setTextColor(BLACK);
    display.println("NO");

    display.setTextColor(WHITE);
    display.setCursor(89, 49);
    display.println("YES");
}

void Display::drawYes() {
    clearBoxes();
    display.drawRect(5, 43, 50, 20, WHITE);

    display.fillRect(73, 43, 50, 20, WHITE);
    display.drawRect(74, 44, 48, 18, BLACK);

    display.setTextColor(BLACK);
    display.setCursor(89, 49);
    display.println("YES");

    display.setCursor(25, 49);
    display.setTextColor(WHITE);
    display.println("NO");
}

void Display::animateText(const std::string &text1, const std::string &text2) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastTextBlinked < 500) return;
    std::string text = blink ? text1 : text2;
    setText(text);
    lastTextBlinked = currentMillis;
    blink = !blink;
}

void Display::clearText() {
    display.fillRect(0, 0, 128, 43, BLACK);
}

void Display::clearBoxes() {
    display.fillRect(0, 43, 128, 23, BLACK);
}

void Display::clearDisplay() {
    display.clearDisplay();
}
