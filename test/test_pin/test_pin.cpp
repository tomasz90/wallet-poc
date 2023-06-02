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
    switch (c) {
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

void should_increment_first_digit() {
    Pin::setMode(PinMode::SET);

    int digit = getDigitAt(0);
    int expectedDigit = digit < 9 ? digit + 1 : 0;

    Pin::incrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_first_digit() {
    Pin::setMode(PinMode::SET);

    int digit = getDigitAt(0);
    int expectedDigit = digit > 0 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = getDigitAt(0);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_increment_next_digit() {
    Pin::setMode(PinMode::SET);

    Pin::setOneDigit();

    int digit = getDigitAt(1);
    int expectedDigit = digit < 9 ? digit + 1 : -1;

    Pin::incrementCurrentDigit();
    digit = getDigitAt(1);

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_next_digit() {
    Pin::setMode(PinMode::SET);

    Pin::setOneDigit();

    int digit = getDigitAt(1);
    int expectedDigit = digit > -1 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = getDigitAt(1);

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

void should_throws_exception_when_not_all_digits_are_initialized_when_save_pin() {
    Pin::setMode(PinMode::CONFIRM);
    Pin::setOneDigit();

    try {
        Pin::savePin();
        TEST_FAIL_MESSAGE("Expected exception, but was not thrown");
    } catch (std::runtime_error &e) {
        TEST_PASS();
    }
}

void should_return_false_when_pin_mismatch() {
    Pin::setMode(PinMode::SET);

    while (getDigitAt(0) == -1) {
        Pin::incrementCurrentDigit();
    }

    int digit0 = getDigitAt(0);

    Pin::setOneDigit();
    Pin::setOneDigit();
    Pin::setOneDigit();
    Pin::setOneDigit();

    Pin::setMode(PinMode::CONFIRM);


    while (getDigitAt(0) == digit0) {
        Pin::incrementCurrentDigit();
    }

    Pin::setOneDigit();
    Pin::setOneDigit();
    Pin::setOneDigit();
    Pin::setOneDigit();

    TEST_ASSERT_FALSE(Pin::savePin());
}

void should_save_pin() {
    Pin::setMode(PinMode::SET);

    while (getDigitAt(0) == -1) {
        Pin::incrementCurrentDigit();
    }

    int digit0 = getDigitAt(0);
    Pin::setOneDigit();

    int digit1 = getDigitAt(1);
    Pin::setOneDigit();

    int digit2 = getDigitAt(2);
    Pin::setOneDigit();

    int digit3 = getDigitAt(3);
    Pin::setOneDigit();

    TEST_ASSERT_TRUE(Pin::savePin());

    Pin::setMode(PinMode::CONFIRM);


    while (getDigitAt(0) != digit0) {
        Pin::incrementCurrentDigit();
    }

    Pin::setOneDigit();

    while (getDigitAt(1) != digit1) {
        Pin::incrementCurrentDigit();
    }
    Pin::setOneDigit();

    while (getDigitAt(2) != digit2) {
        Pin::incrementCurrentDigit();
    }
    Pin::setOneDigit();

    while (getDigitAt(3) != digit3) {
        Pin::incrementCurrentDigit();
    }

    Pin::setOneDigit();

    TEST_ASSERT_TRUE(Pin::savePin());
}

void setup() {
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(should_initiate_with_proper_values);
    RUN_TEST(should_increment_first_digit);
    RUN_TEST(should_decrement_first_digit);
    RUN_TEST(should_increment_next_digit);
    RUN_TEST(should_decrement_next_digit);
    RUN_TEST(shouldSetOneDigit);
    RUN_TEST(shouldUnsetOneDigit);
    RUN_TEST(should_throws_exception_when_not_all_digits_are_initialized_when_save_pin);
    RUN_TEST(should_return_false_when_pin_mismatch);
    RUN_TEST(should_save_pin);

    UNITY_END();
}

void loop() {}