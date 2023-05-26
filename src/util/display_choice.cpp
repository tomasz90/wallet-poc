#include "display_choice.h"
#include "uitl.h"

Adafruit_SSD1306 DisplayChoice::display;
DisplayChoice::DisplayChoice() = default;

void DisplayChoice::begin(Adafruit_SSD1306 &_display) {
    display = _display;
}

void DisplayChoice::drawNo() {
    display.fillRect(5, 43, 50, 20, WHITE);
    display.drawRect(6, 44, 48, 18, BLACK);

    display.drawRect(73, 43, 50, 20, WHITE);

    display.setCursor(25, 49);
    display.setTextColor(BLACK);
    display.println("NO");

    display.setTextColor(WHITE);
    display.setCursor(89, 49);
    display.println("YES");
    display.display();
}

void DisplayChoice::drawYes() {

    display.drawRect(5, 43, 50, 20, WHITE);

    display.fillRect(73, 43, 50, 20, WHITE);
    display.drawRect(74, 44, 48, 18, BLACK);

    display.setTextColor(BLACK);
    display.setCursor(89, 49);
    display.println("YES");

    display.setCursor(25, 49);
    display.setTextColor(WHITE);
    display.println("NO");
    display.display();
}
