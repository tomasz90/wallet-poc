#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Tx.h"
#include "BluetoothCallbacks.h"
#include "Bluetooth.h"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristicSender = NULL;
BLECharacteristic *pCharacteristicReceiver = NULL;
BLE2902 *pBLE2902;

BluetoothCallbacks* bc = new BluetoothCallbacks();

char *buffer;
Tx *tx;

unsigned long lastMillis = 0;

#define SERVICE_UUID  "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SENDER_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define RECEIVER_UUID "03d2fde6-1615-461d-897b-6b0220bdd335"

void Bluetooth::begin() {
    pinMode(0, INPUT);
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(bc);

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristicSender = pService->createCharacteristic(SENDER_UUID, BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristicReceiver = pService->createCharacteristic(RECEIVER_UUID, BLECharacteristic::PROPERTY_WRITE);

    pBLE2902 = new BLE2902();
    pBLE2902->setNotifications(true);
    pCharacteristicSender->addDescriptor(pBLE2902);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    Serial.println("Waiting a client connection to notify...");

    pServer->startAdvertising();
    Serial.println("start advertising");
}

void Bluetooth::poll() {
    if (bc->deviceConnected) {
        auto receiverValue = pCharacteristicReceiver->getValue();
        if (receiverValue.length() > 0) {
            tx = new Tx(receiverValue);

            Serial.println(tx->nonce);
            Serial.println(std::to_string(tx->gasPrice).c_str());
            Serial.println(tx->gasLimit);
            Serial.println(tx->destinationAddress.c_str());
            Serial.println(tx->value.c_str());
            Serial.println(tx->data.c_str());

            // received, so reset value for now
            pCharacteristicReceiver->setValue("");
        }

        bool pressed = !digitalRead(0);
        if (pressed && millis() - lastMillis > 1000) {
            tx->sign(buffer);
            pCharacteristicSender->setValue(buffer);
            pCharacteristicSender->notify();
            lastMillis = millis();
        }
    }
}