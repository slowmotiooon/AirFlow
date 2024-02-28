#pragma once
#include <Arduino.h>
#include <IO.h>

const int MOTOR_PWM = 0;

int pwmResolution = 10; //设置PWM分辨率
int pwmFreq = 1000;

void pwmInit(){
    pinMode(MOTOR_PWM,OUTPUT);
}