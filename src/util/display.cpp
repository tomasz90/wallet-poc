#include "display.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 Display::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

std::string Display::_word;
unsigned long Display::previousMillis;
bool Display::blink;

Display::Display() = default;

void Display::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
}

void Display::setText(std::string text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 30);
    display.println(text.c_str());
    display.display();
}

void Display::animateText() {
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
