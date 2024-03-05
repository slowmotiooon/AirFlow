#pragma once
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <IO.h>
#include "../Device/Device.h"

extern BluetoothSerial SerialBT;
extern Device defaultDevice;

void outputViaBT(String target);

int executeCommand(const String& commandBuffer);

String getBTCommand();