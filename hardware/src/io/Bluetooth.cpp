#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Bluetooth.h"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristicSender = NULL;
BLECharacteristic* pCharacteristicSenderAddress = NULL;
BLECharacteristic* pCharacteristicReceiver = NULL;

Bluetooth::Bluetooth(BLEServerCallbacks* nav) {
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(nav);

    // Create the BLE Services
    BLEService* pServiceAddress = pServer->createService(SERVICE_ADDRESS_UUID);
    BLEService* pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic
    pCharacteristicSenderAddress = pServiceAddress->createCharacteristic(SENDER_ADDRESS_UUID,
                                                                         BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristicSender = pService->createCharacteristic(SENDER_UUID, BLECharacteristic::PROPERTY_NOTIFY);
    pCharacteristicReceiver = pService->createCharacteristic(RECEIVER_UUID, BLECharacteristic::PROPERTY_WRITE);

    auto pBLE2902Address = new BLE2902();
    pBLE2902Address->setNotifications(true);
    pCharacteristicSenderAddress->addDescriptor(pBLE2902Address);

    auto pBLE2902 = new BLE2902();
    pBLE2902->setNotifications(true);
    pCharacteristicSender->addDescriptor(pBLE2902);

    // Start the service
    pServiceAddress->start();
    pService->start();

    // Start advertising
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_ADDRESS_UUID);
    pAdvertising->addServiceUUID(SERVICE_UUID);
}

void Bluetooth::startAdvertising() {
    pServer->startAdvertising();
}

void Bluetooth::sendAddress(const string &address) {
    pCharacteristicSenderAddress->setValue(address);
    pCharacteristicSenderAddress->notify();
}

void Bluetooth::resetBuffer() {
    pCharacteristicReceiver->setValue("");
}

string Bluetooth::receiveData() {
    string s = pCharacteristicReceiver->getValue();
    if(s.length() > 0) {
        resetBuffer();
    }
    return s;
}

void Bluetooth::sendTx(char* buffer) {
    Serial.println("Sending transaction");
    pCharacteristicSender->setValue(buffer);
    pCharacteristicSender->notify();
    delete[] buffer;
}
