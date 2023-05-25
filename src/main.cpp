#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "bip39/bip39.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define BUTTON 35

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

BIP39::word_list passphrase;
int wordIndex = -1;
std::string _word;
unsigned long previousMillis;
bool blink;
unsigned long previousMillisButton;

bool active = true;

void setText(std::string text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 30);
    display.println(text.c_str());
    display.display();
}

void animateText(unsigned long currentMillis) {
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
    passphrase = BIP39::generate_mnemonic();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
    setText("Hello!");
}

void loop() {
    bool clicked = digitalRead(BUTTON);
    unsigned long currentMillis = millis();
    active = currentMillis - previousMillisButton > 500;
    if (clicked && active) {
        previousMillisButton = currentMillis;
        wordIndex++;
        _word = passphrase.getWordAt(wordIndex);
        std::string humanIndex = std::to_string(wordIndex + 1).append(". ");
        _word.insert(0, humanIndex);
    }
    if (wordIndex > 11) {
        setText("Done!");
    } else if (wordIndex != -1) {
        animateText(currentMillis);
    }
}
