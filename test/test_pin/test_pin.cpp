#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "util/SeedGenerator.h"
#include "util/Pin.h"

void should_initiate_with_proper_values() {
    Pin::setMode(PinMode::SET);
    bool hiddenPin = Pin::getPinString().substr(1) == " * * *";

    TEST_ASSERT_EQUAL(Pin::isFirstDigit(), true);
    TEST_ASSERT_EQUAL(hiddenPin, true);
    TEST_ASSERT_EQUAL(Pin::testStateCombination()[0], DigitState::INIT);
    TEST_ASSERT_EQUAL(Pin::testStateCombination()[1], DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(Pin::testStateCombination()[2], DigitState::UN_INIT);
    TEST_ASSERT_EQUAL(Pin::testStateCombination()[3], DigitState::UN_INIT);
}

void should_increment_digit_mode_SET() {
    Pin::setMode(PinMode::SET);

    int digit = Pin::testRawCombination()[0];
    int expectedDigit = digit < 9 ? digit + 1 : 0;

    Pin::incrementCurrentDigit();
    digit = Pin::testRawCombination()[0];

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_digit_mode_SET() {
    Pin::setMode(PinMode::SET);

    int digit = Pin::testRawCombination()[0];
    int expectedDigit = digit > 0 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = Pin::testRawCombination()[0];

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_increment_digit_mode_CONFIRM() {
    Pin::setMode(PinMode::SET);

    int digit = Pin::testRawCombination()[0];
    int expectedDigit = digit < 9 ? digit + 1 : -1;

    Pin::incrementCurrentDigit();
    digit = Pin::testRawCombination()[0];

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}

void should_decrement_digit_mode_CONFIRM() {
    Pin::setMode(PinMode::SET);

    int digit = Pin::testRawCombination()[0];
    int expectedDigit = digit > -1 ? digit - 1 : 9;

    Pin::decrementCurrentDigit();
    digit = Pin::testRawCombination()[0];

    TEST_ASSERT_EQUAL(expectedDigit, digit);
}


void setup() {
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(should_initiate_with_proper_values);
    RUN_TEST(should_increment_digit_mode_SET);
    RUN_TEST(should_decrement_digit_mode_SET);
    RUN_TEST(should_increment_digit_mode_CONFIRM);
    RUN_TEST(should_decrement_digit_mode_CONFIRM);
    UNITY_END();
}

void loop() {}