#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "util/SeedGenerator.h"
#include "util/Pin.h"

int getDigitAt(uint8_t index) {
    char c = Pin::getPinString()[index * 2];
    return c == '<' ? -1 : c - '0';
}

DigitState getDigitStateAt(uint8_t index) {
    char c = Pin::getPinString()[index * 2];
    switch(c) {
        case '*':
            return DigitState::UN_INIT;
        case '$':
            return DigitState::SET;
        default:
            return DigitState::INIT;
    }
}

void should_initiate_with_proper_values() {
    Pin::setMode(PinMode::SET);
    bool hiddenPin = Pin::getPinString().substr(1) == " * * *";

    TEST_ASSERT_EQUAL(Pin::isFirstDigit(), true);
    TEST_ASSERT_EQUAL(hiddenPin, true);
    TEST_ASSERT_EQUAL(getDigitStateAt(0), DigitState::INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(1), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(2), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(3), DigitState::UN_INIT);
}

void should_increment_digit_mode_SET() {
    Pin::setMode(PinMode::SET);

    int digit = getDigitAt(0);
    int expectedDigit = digit < 9 ? digit + 1 : 0;

    Pin::incrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_digit_mode_SET() {
    Pin::setMode(PinMode::SET);

    int digit = getDigitAt(0);
    int expectedDigit = digit > 0 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_increment_digit_mode_CONFIRM() {
    Pin::setMode(PinMode::CONFIRM);

    int digit = getDigitAt(0);
    int expectedDigit = digit < 9 ? digit + 1 : -1;

    Pin::incrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_digit_mode_CONFIRM() {
    Pin::setMode(PinMode::CONFIRM);

    int digit = getDigitAt(0);
    int expectedDigit = digit > -1 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void shouldSetOneDigit() {
    Pin::setMode(PinMode::SET);
    Pin::setOneDigit();

    TEST_ASSERT_EQUAL(getDigitStateAt(0), DigitState::SET);
    TEST_ASSERT_EQUAL(getDigitStateAt(1), DigitState::INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(2), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(3), DigitState::UN_INIT);
}

void shouldUnsetOneDigit() {
    Pin::setMode(PinMode::SET);
    Pin::setOneDigit();

    TEST_ASSERT_EQUAL(getDigitStateAt(0), DigitState::SET);
    TEST_ASSERT_EQUAL(getDigitStateAt(1), DigitState::INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(2), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(3), DigitState::UN_INIT);

    Pin::unsetOneDigit();

    TEST_ASSERT_EQUAL(getDigitStateAt(0), DigitState::INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(1), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(2), DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(getDigitStateAt(3), DigitState::UN_INIT);
}


void setup() {
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(should_initiate_with_proper_values);
    RUN_TEST(should_increment_digit_mode_SET);
    RUN_TEST(should_decrement_digit_mode_SET);
    RUN_TEST(should_increment_digit_mode_CONFIRM);
    RUN_TEST(should_decrement_digit_mode_CONFIRM);
    RUN_TEST(shouldSetOneDigit);
    RUN_TEST(shouldUnsetOneDigit);

    UNITY_END();
}

void loop() {}