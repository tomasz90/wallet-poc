#include "Disp.h"
#include "Adafruit_SSD1306.h"
#include "util/Pin.h"

bool Disp::blink;
unsigned long Disp::lastTextBlinked;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BOX_WIDTH 50
#define BOX_HEIGHT 20

#define BOX_Y_START 43
#define SCREEN_TEXT_MENU_BORDER_POSITION 40
#define BOX_Y_CURSOR 49
#define TEXT_SIZE 1
#define PIN_SIZE 2


const int SCREEN_CENTER = SCREEN_WIDTH / 2 - 1;

const int SCREEN_FIRST_HALF_CENTER = SCREEN_CENTER - (SCREEN_WIDTH / 4);
const int SCREEN_SECOND_HALF_CENTER = SCREEN_CENTER + (SCREEN_WIDTH / 4);

const int BOX_X_1_START = SCREEN_FIRST_HALF_CENTER - (BOX_WIDTH / 2);
const int BOX_X_2_START = SCREEN_SECOND_HALF_CENTER - (BOX_WIDTH / 2);

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
    display.setTextSize(TEXT_SIZE);
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

void Disp::drawTwoBoxes(const std::string &text1, const std::string &text2, bool firstHighlighted) {
    clearMenu();
    bool textColor1 = 0;
    bool textColor2 = 1;

    if (firstHighlighted) {
        display.drawRect(BOX_X_2_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.fillRect(BOX_X_1_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.drawRect(BOX_X_1_START + 1, BOX_Y_START + 1, BOX_WIDTH - 2, BOX_HEIGHT - 2, BLACK);
    } else {
        textColor1 = 1;
        textColor2 = 0;

        display.drawRect(BOX_X_1_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.fillRect(BOX_X_2_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.drawRect(BOX_X_2_START + 1, BOX_Y_START + 1, BOX_WIDTH - 2, BOX_HEIGHT - 2, BLACK);
    }

    uint8_t text1Position = calculateCursorPosition(text1, SCREEN_FIRST_HALF_CENTER);
    display.setCursor(text1Position, BOX_Y_CURSOR);
    display.setTextColor(textColor1);
    display.setTextSize(TEXT_SIZE);
    display.println(text1.c_str());

    uint8_t text2Position = calculateCursorPosition(text2, SCREEN_SECOND_HALF_CENTER);
    display.setTextColor(textColor2);
    display.setCursor(text2Position, BOX_Y_CURSOR);
    display.println(text2.c_str());
    display.display();
}

void Disp::drawOneBox(const std::string &text, uint8_t width) {
    clearMenu();
    uint8_t begin = SCREEN_CENTER - (width / 2);
    display.fillRect(begin, BOX_Y_START, width, BOX_HEIGHT, WHITE);
    display.drawRect(begin + 1, BOX_Y_START + 1, width - 2, BOX_HEIGHT - 2, BLACK);

    uint8_t position = calculateCursorPosition(text, SCREEN_CENTER);
    display.setCursor(position, BOX_Y_CURSOR);
    display.setTextColor(BLACK);
    display.setTextSize(TEXT_SIZE);
    display.println(text.c_str());
    display.display();
}

uint8_t Disp::calculateCursorPosition(
        const std::string &text,
        uint8_t textCenter
) {
    uint8_t halfTextWidth = ((text.length() * 6)) / 2;
    return textCenter - halfTextWidth;
}

void Disp::drawPin() {
    clearMenu();
    display.setCursor(23, 40);
    display.setTextColor(WHITE);
    display.setTextSize(PIN_SIZE);
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
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_TEXT_MENU_BORDER_POSITION, BLACK);
}

void Disp::clearMenu() {
    display.fillRect(
            0,
            SCREEN_TEXT_MENU_BORDER_POSITION,
            SCREEN_WIDTH,
            SCREEN_HEIGHT - SCREEN_TEXT_MENU_BORDER_POSITION,
            BLACK
    );
}

// TODO: not used, but keep it for now
//void Disp::clear() {
//    display.clearDisplay();
//    display.display();
//}
