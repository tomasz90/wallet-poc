#include "display.h"
#include "Adafruit_SSD1306.h"

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 Display::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool Display::blink;
unsigned long Display::previousMillis;

void Display::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        while (true);
    }
    delay(200);
}

void Display::setText(const std::string& text) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    display.println(text.c_str());
    display.display();
}

void Display::animateText(const std::string& _text) {
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
