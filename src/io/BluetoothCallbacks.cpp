#include <Arduino.h>
#include "BluetoothCallbacks.h"

void BluetoothCallbacks::onConnect(BLEServer *pServer) {
    Serial.println("connected");
    deviceConnected = true;
};

void BluetoothCallbacks::onDisconnect(BLEServer *pServer) {
    Serial.println("disconnected");
    deviceConnected = false;
}