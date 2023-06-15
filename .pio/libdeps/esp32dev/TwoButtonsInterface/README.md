# Two Buttons Interface


Library handles events when pressing buttons. It supports single clicks and simultaneous clicks of two buttons. It also contains debouncer. It is useful to create simple projects with graphical interface when buttons are used to navigate through a menu. I was not able to find similar library (that handles simultaneous clicks) so I created this one.

Set up is very simple just create two button objects - they need a pin number and mode IN_PULLUP or IN_PULLDOWN - this is based on your wiring, if you connect button to 3.3V - then IN_PULLDOWN, when to ground then IN_PULLUP.

Then buttons need to be passed to ButtonHandler, you also need to create callbacks for actions pressed1, pressed2, pressedBoth.
Inside loop buttonhandler will be listening for button events. Additionally, user can specify different than default debounce time.

Same example in dir examples.

#### PLEASE NOTE: actual callbacks are executed when button is released - this is necessary to be able to handle simultanous click.

```c++

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
```
