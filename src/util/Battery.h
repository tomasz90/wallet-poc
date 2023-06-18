#ifndef BATTERY_H
#define BATTERY_H

#include <cstdint>
#include <esp32-hal-adc.h>
#define BATTERY_MAX_VOLTAGE 6.6
#define RESOLUTION 4096

class Battery {
    public:
    explicit Battery(uint8_t pin): pin(pin) {};
    int getStatus() {
        uint32_t rawVoltage = analogRead(pin);
        double voltage = rawVoltage * BATTERY_MAX_VOLTAGE / RESOLUTION;
        int level = getLevel(voltage);
        return level;
    }

private:
    uint8_t pin;
    float levels[10] = {3.91, 3.83, 3.74, 3.67, 3.61, 3.58, 3.55, 3.51, 3.47, 3.29};
    int getLevel(float voltage) {
        for (int i = 0; i < sizeof levels; i++) {
            if (voltage >= levels[i]) {
                return 100 - i * 10;
            }
        }
        return 0;
    }
};
#endif //BATTERY_H
