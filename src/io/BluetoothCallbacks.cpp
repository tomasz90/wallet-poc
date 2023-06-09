#include <Arduino.h>
#include "BluetoothCallbacks.h"
#include "util/Nav.h"

void BluetoothCallbacks::onConnect(BLEServer *pServer) {
    Serial.println("connected");
    Nav::onBtConnected();
    deviceConnected = true;
    onConnectCalled = true;
};

void BluetoothCallbacks::onDisconnect(BLEServer *pServer) {
    Serial.println("disconnected");
    Nav::onBtDisconnected();
    pServer->startAdvertising(); // restart advertising
    deviceConnected = false;
    onConnectCalled = false;
}