#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "Tx.h"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristicSender = NULL;
BLECharacteristic *pCharacteristicReceiver = NULL;
BLE2902 *pBLE2902;

bool deviceConnected = false;
bool oldDeviceConnected = false;
char *buffer;
Tx *tx;

unsigned long lastMillis = 0;

#define SERVICE_UUID  "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SENDER_UUID   "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define RECEIVER_UUID "03d2fde6-1615-461d-897b-6b0220bdd335"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        Serial.println("connected");
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer) {
        Serial.println("disconnected");
        deviceConnected = false;
    }
};

void setup() {
    Serial.begin(115200);
    pinMode(0, INPUT);
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

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
    BLEDevice::startAdvertising();
    Serial.println("Waiting a client connection to notify...");
}

void loop() {
    if (deviceConnected) {
        auto receiverValue = pCharacteristicReceiver->getValue();
        if (receiverValue.length() > 0) {
            tx = new Tx(receiverValue);

            Serial.println(tx->nonce);
            Serial.println(tx->gasLimit);
            Serial.println(tx->destinationAddress.c_str());
            Serial.println(tx->value.c_str());
            Serial.println(tx->data.c_str());

            // received, so reset value for now
            pCharacteristicReceiver->setValue("");
        }

        bool pressed = !digitalRead(0);
        if (pressed && millis() - lastMillis > 1000) {
            tx->serialize(buffer);
            pCharacteristicSender->setValue(buffer);
            pCharacteristicSender->notify();
            lastMillis = millis();
        }
        delay(50);
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
}