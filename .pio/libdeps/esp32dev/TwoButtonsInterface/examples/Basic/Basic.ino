#include <Arduino.h>
#include "ButtonsHandler.h"

#define NEXT_BUTTON 12
#define PREVIOUS_BUTTON 13

Button button1(PREVIOUS_BUTTON, IN_PULLDOWN);
Button button2(NEXT_BUTTON, IN_PULLDOWN);

ButtonsHandler buttonsHandler(button1, button2);

void pressed1() { Serial.println("Button1 pressed"); }

void pressed2() { Serial.println("Button2 pressed"); }

void pressedBoth() { Serial.println("Both pressed"); }


void setup() {
    Serial.begin(115200);
    buttonsHandler.setCallbacks(pressed1,pressed2,pressedBoth);
}

void loop() {
    buttonsHandler.poll();
}