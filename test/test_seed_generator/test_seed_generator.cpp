#include <Arduino.h>
#include <unity.h>
#include <cstring>
#include "util/SeedGenerator.h"


void should_have_12_words() {

    SeedGenerator::createMnemonic();
    TEST_ASSERT_EQUAL(12, SeedGenerator::mnemonic.size());
}

void should_return_different_seeds() {

    SeedGenerator::createMnemonic();
    std::string wordList1 = SeedGenerator::mnemonic.to_string();

    SeedGenerator::createMnemonic();
    std::string wordList2 = SeedGenerator::mnemonic.to_string();

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