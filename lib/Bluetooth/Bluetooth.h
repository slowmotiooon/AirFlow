#pragma once

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <cmd.h>

#define SERVICE_UUID "c60cb46e-1145-4d9e-a6e0-30874ed841c6"
#define CHARACTERISTIC_UUID_RX "e36c2a19-29e0-4c92-8c33-108db2b10305"
#define CHARACTERISTIC_UUID_TX "4564eccc-b13b-4885-93e2-9efb0ebc54d5"


extern BLEServer* pServer;
extern BLECharacteristic* pTxCharacteristic;
extern bool deviceConnected;


class ServerCallback : public BLEServerCallbacks{
    void onConnect(BLEServer* pServer){
        deviceConnected = true;
    }

    void onDisconnect(BLEServer* pServer){
        deviceConnected = false;
    }
};

void BLEOutput(String s);

class MyCallbacks:public BLECharacteristicCallbacks{
    void onWrite(BLECharacteristic* pCharacteristic);
};


void BLEInit();