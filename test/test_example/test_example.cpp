#include <Arduino.h>
#include <unity.h>

#define BUILTIN_LED 23

void should_equal() {
    TEST_ASSERT_EQUAL(true, true);
}

void setup() {
    pinMode(BUILTIN_LED, OUTPUT);
    UNITY_BEGIN();
    RUN_TEST(should_equal);
    UNITY_END();
}

void loop() {
    digitalWrite(BUILTIN_LED, HIGH);
    delay(1);
    digitalWrite(BUILTIN_LED, LOW);
    delay(200);
}