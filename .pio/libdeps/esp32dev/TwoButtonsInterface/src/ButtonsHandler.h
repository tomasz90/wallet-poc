#include <Arduino.h>
#include "Button.h"

#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

class ButtonsHandler {

public:
    ButtonsHandler(Button button1, Button button2);

    void setCallbacks(
            std::function<void()> _onPressedButton1,
            std::function<void()> _onPressedButton2,
            std::function<void()> _onPressedBoth
    );
    void setDebounceTime(unsigned int time);
    void poll();

private:
    Button button1;
    Button button2;
    bool bothClicked = false;
    unsigned int debounceTime = 20;

    std::function<void()> onPressedButton1;
    std::function<void()> onPressedButton2;
    std::function<void()> onPressedBoth;

    bool pollState(Button &button) const;
    void resetState(Button &button) const;
    bool isPressed(Button &button) const;
    bool wasPressed(Button &button) const;
    bool isReleased(Button &button) const;
};

#endif //BUTTON_HANDLER_H