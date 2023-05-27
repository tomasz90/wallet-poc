#include "display.h"
#include "Adafruit_SSD1306.h"
#include "Fonts/FreeMono9pt7b.h"
#include "Fonts/FreeMonoBold9pt7b.h"
#include "Fonts/FreeSerif9pt7b.h"
#include "Fonts/Org_01.h"
#include "Fonts/Picopixel.h"
#include "uitl.h"
#include "pin.h"

Adafruit_SSD1306 Disp::display;
bool Disp::blink;
bool Disp::firstTime;
unsigned long Disp::lastTextBlinked;

void Disp::begin(Adafruit_SSD1306 &_display) {
    display = _display;
    display.clearDisplay();
}

void Disp::setText(const std::string &text) {
    clearText();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Disp::blinkTextWithSign(const std::string &text) {
    std::string text2;
    text2.assign(text);
    text2.append(" >");
    animateText(text, text2);
}

void Disp::drawNo() {
    clearMenu();
    display.fillRect(5, 43, 50, 20, WHITE);
    display.drawRect(6, 44, 48, 18, BLACK);

    display.drawRect(73, 43, 50, 20, WHITE);

    display.setCursor(25, 49);
    display.setTextColor(BLACK);
    display.setTextSize(1);
    display.println("NO");

    display.setTextColor(WHITE);
    display.setCursor(89, 49);
    display.println("YES");
    display.display();
}

void Disp::drawYes() {
    clearMenu();
    display.drawRect(5, 43, 50, 20, WHITE);

    display.fillRect(73, 43, 50, 20, WHITE);
    display.drawRect(74, 44, 48, 18, BLACK);

    display.setTextColor(BLACK);
    display.setTextSize(1);
    display.setCursor(89, 49);
    display.println("YES");

    display.setCursor(25, 49);
    display.setTextColor(WHITE);
    display.println("NO");
    display.display();
}

void Disp::drawPin() {
    clearMenu();
    display.setCursor(23, 40);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.println(Pin::getPinString());
    display.display();
}

void Disp::animateText(const std::string &text1, const std::string &text2) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastTextBlinked < 500 && !firstTime) return;
    firstTime = false;
    std::string text = blink ? text1 : text2;
    setText(text);
    lastTextBlinked = currentMillis;
    blink = !blink;
}

void Disp::clearText() {
    display.fillRect(0, 0, 128, 40, BLACK);
}

void Disp::clearMenu() {
    display.fillRect(0, 38, 128, 26, BLACK);
}

void Disp::clear() {
    display.clearDisplay();
    display.display();
}
