#pragma once
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <IO.h>

extern BluetoothSerial SerialBT;

void outputViaBT(String target);

int executeCommand(const String& commandBuffer);

String getBTCommand();