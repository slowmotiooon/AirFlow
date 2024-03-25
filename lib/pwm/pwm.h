#pragma once
#include <Arduino.h>
#include "../IO/IO.h"

const int pwmResolution = 10; //设置PWM分辨率
const int pwmFreq = 1000;

void pwmInit();