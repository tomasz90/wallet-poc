#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "seed/SeedVerifier.h"


void should_have_12_words() {

    SeedVerifier::createMnemonic();
    TEST_ASSERT_EQUAL(12, SeedVerifier::mnemonic.size());
}

void should_return_different_seeds() {

    SeedVerifier::createMnemonic();
    std::string wordList1 = SeedVerifier::mnemonic.to_string();

    SeedVerifier::createMnemonic();
    std::string wordList2 = SeedVerifier::mnemonic.to_string();

    bool areDifferent = std::strcmp(wordList1.c_str(), wordList2.c_str()); // wired behavior, strcmp returns 0 if equal

    TEST_ASSERT_EQUAL(true, areDifferent);
}

void setup() {
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(should_return_different_seeds);
    UNITY_END();
}

void loop() {}