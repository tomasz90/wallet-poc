#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "util/seed.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define BUTTON 35

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

BIP39::word_list passphrase;
int wordIndex = -1;
std::string _word;
unsigned long previousMillis;
unsigned long lastButtonTime = 0;
bool blink;

void IRAM_ATTR nextWord() {
    unsigned long buttonTime = millis();
    if (buttonTime - lastButtonTime > 700) {
        lastButtonTime = buttonTime;
        wordIndex++;
        std::string humanIndex = std::to_string(wordIndex + 1).append(". ");
        _word = passphrase.getWordAt(wordIndex);
        _word.insert(0, humanIndex);
    }
}

void setText(std::string text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 30);
    display.println(text.c_str());
    display.display();
}

void animateText() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis > 500) {
        previousMillis = currentMillis;
        std::string word;
        word.assign(_word);
        if (blink) word.append(" >");
        setText(word);
        blink = !blink;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON, INPUT);
    attachInterrupt(BUTTON, nextWord, RISING);
    passphrase = Seed::createMnemonic();
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
    setText("Hello!");
}

void loop() {
    if (wordIndex > 11) {
        setText("Done!");
    } else if (wordIndex != -1) {
        animateText();
    }
}
