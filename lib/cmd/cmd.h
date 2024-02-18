#pragma once
#include <Arduino.h>
#include <BluetoothSerial.h>

extern BluetoothSerial SerialBT;

void outputViaBT(String target);

int command(String cmdType,int cmdval);