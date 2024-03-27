#ifndef LED_H
#define LED_H

#include <cstdint>

class Led {
public:
    Led(uint8_t pin, uint8_t channel, uint8_t flashTime, uint32_t brightness);
    void flash() const;
private:
    uint8_t channel;
    uint8_t flashTime;
    uint32_t brightness;
};

#endif //LED_H
