#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <Arduino.h>
#include "Bluetooth.h"
#include "util/DataHolder.h"

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristicSender = NULL;
BLECharacteristic *pCharacteristicSenderAddress = NULL;
BLECharacteristic *pCharacteristicReceiver = NULL;

Bluetooth::Bluetooth(BLEServerCallbacks *_nav, DataHolder *_dataHolder) {
    dataHolder = _dataHolder;
    // Create the BLE Device
    BLEDevice::init("ESP32");

    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(_nav);

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

void Bluetooth::sendAddress() {
    pCharacteristicSenderAddress->setValue("0x51c50Fe7392F8D3D570A8068314c4331ECbC8b52");
    pCharacteristicSenderAddress->notify();
}

bool Bluetooth::receivedTx() {
    auto receiverValue = pCharacteristicReceiver->getValue();
    if (receiverValue.length() > 0) {
        dataHolder->tx = new EthTx(receiverValue);
        // received, so reset value for now
        pCharacteristicReceiver->setValue("");
        return true;
    }
    return false;
}

void Bluetooth::signTx() {
    Serial.println("Sending transaction");
    char *buffer;
    dataHolder->tx->sign(buffer);
    pCharacteristicSender->setValue(buffer);
    pCharacteristicSender->notify();
    delete[] buffer;
    delete dataHolder->tx;
}

void Bluetooth::declineTx() {
    delete dataHolder->tx;
}
