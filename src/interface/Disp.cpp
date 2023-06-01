#include "Disp.h"
#include "Adafruit_SSD1306.h"
#include "util/Pin.h"

bool Disp::blink;
unsigned long Disp::lastTextBlinked;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void Disp::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
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

void Disp::drawTwoBoxes(const char text1[], const char text2[], bool firstHighlighted) {
    clearMenu();
    bool textColor1 = 0;
    bool textColor2 = 1;

    if(firstHighlighted) {
        display.drawRect(73, 43, 50, 20, WHITE);

        display.fillRect(5, 43, 50, 20, WHITE);
        display.drawRect(6, 44, 48, 18, BLACK);
    } else {
        textColor1 = 1;
        textColor2 = 0;

        display.drawRect(5, 43, 50, 20, WHITE);

        display.fillRect(73, 43, 50, 20, WHITE);
        display.drawRect(74, 44, 48, 18, BLACK);
    }

    display.setCursor(25, 49);
    display.setTextColor(textColor1);
    display.setTextSize(1);
    display.println(text1);

    display.setTextColor(textColor2);
    display.setCursor(89, 49);
    display.println(text2);
    display.display();
}

void Disp::drawOneBox(const std::string &text, uint8_t width) {
    clearMenu();
    uint8_t begin = (128 - width) / 2;
    display.fillRect(begin, 43, width, 20, WHITE);
    display.drawRect(begin + 1, 44, width - 2, 18, BLACK);

    uint8_t position = 64 - ((text.size() * 5) / 2);
    display.setCursor(position, 49);
    display.setTextColor(BLACK);
    display.setTextSize(1);
    display.println(text.c_str());
    display.display();
}

void Disp::drawPin() {
    clearMenu();
    display.setCursor(23, 40);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.println(Pin::getPinString().c_str());
    display.display();
}

void Disp::animateText(const std::string &text1, const std::string &text2) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastTextBlinked < 500) return;
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

// TODO: not used, but keep it for now
//void Disp::clear() {
//    display.clearDisplay();
//    display.display();
//}
