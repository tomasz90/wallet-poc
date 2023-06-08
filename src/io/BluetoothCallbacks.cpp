#include <Arduino.h>
#include "BluetoothCallbacks.h"

void BluetoothCallbacks::onConnect(BLEServer *pServer) {
    Serial.println("connected");
    deviceConnected = true;
    onConnectCalled = true;
};

void BluetoothCallbacks::onDisconnect(BLEServer *pServer) {
    Serial.println("disconnected");
    pServer->startAdvertising(); // restart advertising
    Serial.println("start advertising");
    deviceConnected = false;
    onConnectCalled = false;
}