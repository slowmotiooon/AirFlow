#pragma once
#include <Arduino.h>
#include <BluetoothSerial.h>
#include <IO.h>

extern BluetoothSerial SerialBT;

void outputViaBT(String target);

int command(String cmdType,int cmdval);