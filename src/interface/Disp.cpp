#include "Disp.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BOX_WIDTH 50
#define BOX_HEIGHT 20

#define BOX_Y_START 43
#define BOX_Y_CURSOR 49
#define TEXT_SIZE 1
#define PIN_SIZE 2

#define SEED_WORD_Y_POSITION 24

const int SCREEN_CENTER = SCREEN_WIDTH / 2 - 1;

const int SCREEN_LEFT_HALF_CENTER = SCREEN_CENTER - (SCREEN_WIDTH / 4);
const int SCREEN_RIGHT_HALF_CENTER = SCREEN_CENTER + (SCREEN_WIDTH / 4);

const int BOX_X_1_START = SCREEN_LEFT_HALF_CENTER - (BOX_WIDTH / 2);
const int BOX_X_2_START = SCREEN_RIGHT_HALF_CENTER - (BOX_WIDTH / 2);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Disp::Disp() {
    lastTextBlinked = 0;
    blink = false;
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
    display.clearDisplay();
}

void Disp::setText(const string &text, uint8_t toLine) {
    clearText(toLine);
    display.setTextSize(TEXT_SIZE);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Disp::drawTransaction(const string &chainId, const string &to, const string &value) {
    clearTextCenter();
    display.setTextSize(TEXT_SIZE);
    display.setTextColor(WHITE);

    display.setCursor(3, 3);
    display.println(("chainId: " + chainId).c_str());

    display.setCursor(3, 13);
    display.println(("to: " + to).c_str());

    display.setCursor(3, 23);
    display.println(("val: " + value).c_str());
    display.display();
}

void Disp::setTextAtCenter(const string &text, uint8_t y) {
    //todo: have this in mind, it prevents delay from displaying text
    lastTextBlinked = 0;
    clearTextCenter();
    display.setTextSize(TEXT_SIZE);
    display.setTextColor(WHITE);
    setCursorRelativeToCenter(text, SCREEN_CENTER, y);
    display.println(text.c_str());
}

void Disp::blinkTextWarningAtCenter(const string &text) {
    clearTextCenter();
    uint16_t _delay = 300;
    setTextAtCenter(text, SEED_WORD_Y_POSITION);
    display.display();
    delay(_delay);
    clearTextCenter();
    disp();
    delay(_delay);

    setTextAtCenter(text, SEED_WORD_Y_POSITION);
    disp();
    delay(_delay);
    clearTextCenter();
    disp();
    delay(_delay);

    setTextAtCenter(text, SEED_WORD_Y_POSITION);
    disp();
    delay(_delay);
    clearTextCenter();
    disp();
}

void Disp::blinkTextWithSign(const string &text, uint8_t toLine) {
    string text2;
    text2.assign(text);
    text2.append(" >");
    animateText(text, text2, toLine);
}

void Disp::blinkTextWithSign(const string &text) {
    blinkTextWithSign(text, SCREEN_TEXT_MENU_BORDER_POSITION);
}

void Disp::drawTwoBoxes(const string &text1, const string &text2, bool rightHighlighted) {
    clearMenu();
    drawLeftBox(text1, !rightHighlighted);
    drawRightBox(text2, rightHighlighted);
    display.display();
}

void Disp::drawOnlyLeftBox(const string &text) {
    clearMenu();
    drawLeftBox(text, true);
    display.display();
}

void Disp::drawOnlyRightBox(const string &text) {
    clearMenu();
    drawRightBox(text, true);
    display.display();
}

void Disp::drawLeftBox(const string &text, bool highlighted) {
    if (highlighted) {
        display.fillRect(BOX_X_1_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.drawRect(BOX_X_1_START + 1, BOX_Y_START + 1, BOX_WIDTH - 2, BOX_HEIGHT - 2, BLACK);
        display.setTextColor(BLACK);

    } else {
        display.drawRect(BOX_X_1_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.setTextColor(WHITE);
    }

    setCursorRelativeToCenter(text, SCREEN_LEFT_HALF_CENTER, BOX_Y_CURSOR);
    display.setTextSize(TEXT_SIZE);
    display.println(text.c_str());
}

void Disp::drawRightBox(const string &text, bool highlighted) {
    if (highlighted) {
        display.fillRect(BOX_X_2_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.drawRect(BOX_X_2_START + 1, BOX_Y_START + 1, BOX_WIDTH - 2, BOX_HEIGHT - 2, BLACK);
        display.setTextColor(BLACK);
    } else {
        display.drawRect(BOX_X_2_START, BOX_Y_START, BOX_WIDTH, BOX_HEIGHT, WHITE);
        display.setTextColor(WHITE);
    }

    setCursorRelativeToCenter(text, SCREEN_RIGHT_HALF_CENTER, BOX_Y_CURSOR);
    display.setTextSize(TEXT_SIZE);
    display.println(text.c_str());
}

void Disp::drawOneBox(const string &text, uint8_t width) {
    clearMenu();
    uint8_t begin = SCREEN_CENTER - (width / 2);
    display.fillRect(begin, BOX_Y_START, width, BOX_HEIGHT, WHITE);
    display.drawRect(begin + 1, BOX_Y_START + 1, width - 2, BOX_HEIGHT - 2, BLACK);

    setCursorRelativeToCenter(text, SCREEN_CENTER, BOX_Y_CURSOR);
    display.setTextColor(BLACK);
    display.setTextSize(TEXT_SIZE);
    display.println(text.c_str());
    display.display();
}

void Disp::setCursorRelativeToCenter(const string &text, uint8_t textCenter, uint8_t y) {
    uint8_t halfTextWidth = ((text.length() * 6)) / 2;
    display.setCursor(textCenter - halfTextWidth, y);
}

void Disp::drawPin(const string &pin) {
    clearMenu();
    display.setCursor(23, 40);
    display.setTextColor(WHITE);
    display.setTextSize(PIN_SIZE);
    display.println(pin.c_str());
    display.display();
}

void Disp::animateText(const string &text1, const string &text2, uint8_t toLine) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastTextBlinked < 500) return;
    string text = blink ? text1 : text2;
    setText(text, toLine);
    lastTextBlinked = currentMillis;
    blink = !blink;
}

void Disp::clearText(uint8_t toLine) {
    display.fillRect(0, 0, SCREEN_WIDTH, toLine, BLACK);
}

void Disp::clearTextCenter() {
    uint8_t begin = 20;
    display.fillRect(0, begin, SCREEN_WIDTH, SCREEN_TEXT_MENU_BORDER_POSITION - begin, BLACK);
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

void Disp::disp() {
    display.display();
}
