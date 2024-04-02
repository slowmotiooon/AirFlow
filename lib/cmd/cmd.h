#pragma once
#include <Arduino.h>
#include <Device.h>

extern Device* defaultDevice;

String toString(std::string str);

int executeCommand(const String& commandBuffer);