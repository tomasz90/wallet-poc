#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "EthTx.h"
#include "BluetoothCallbacks.h"
#include "Bluetooth.h"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristicSender = NULL;
BLECharacteristic *pCharacteristicSenderAddress = NULL;
BLECharacteristic *pCharacteristicReceiver = NULL;

BluetoothCallbacks *bc = new BluetoothCallbacks();

EthTx *tx;

void Bluetooth::begin() {
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(bc);

    // Create the BLE Services
    BLEService *pServiceAddress = pServer->createService(SERVICE_ADDRESS_UUID);
    BLEService *pService = pServer->createService(SERVICE_UUID);

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
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_ADDRESS_UUID);
    pAdvertising->addServiceUUID(SERVICE_UUID);

    pServer->startAdvertising();
}

void Bluetooth::sendAddressIfOnConnectedCalled() {
    if (bc->deviceConnected) {
        if (bc->onConnectCalled) {
            bc->onConnectCalled = false;
            delay(2000);
            pCharacteristicSenderAddress->setValue("0x51c50Fe7392F8D3D570A8068314c4331ECbC8b52");
            pCharacteristicSenderAddress->notify();
        }
    }
}

bool Bluetooth::receivedTx() {
    bool received = false;
    if (bc->deviceConnected) {
        auto receiverValue = pCharacteristicReceiver->getValue();
        if (receiverValue.length() > 0) {
            tx = new EthTx(receiverValue);
            // received, so reset value for now
            pCharacteristicReceiver->setValue("");
            received = true;
        }
    }
    return received;
}

void Bluetooth::signTx() {
    if (bc->deviceConnected) {
        Serial.println("Sending transaction");
        char *buffer;
        tx->sign(buffer);
        delete tx;
        pCharacteristicSender->setValue(buffer);
        pCharacteristicSender->notify();
    } else {
        Serial.println("Not connected");
    }
}

void Bluetooth::declineTx() {
    delete tx;
}
