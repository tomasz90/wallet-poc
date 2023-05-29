#include <esp32-hal-gpio.h>
#include "Led.h"

Led::Led(uint8_t pin, uint8_t channel, uint8_t flashTime, uint32_t brightness)
        : channel(channel), flashTime(flashTime), brightness(brightness) {
    pinMode(pin, OUTPUT);
    ledcSetup(0, 5000, 8);  // Set PWM frequency and resolution
    ledcAttachPin(pin, 0);
}

void Led::flash() const {
    ledcWrite(channel, brightness);
    delay(flashTime);
    ledcWrite(0, 0);
}
