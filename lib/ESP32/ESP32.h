#pragma once

#include <Arduino.h>
#include <Ticker.h>
#include <Device.h>

#define PWM_PIN_A 33
#define ADC_PIN_A 35
#define POWER 25
#define LAUNCH 26
#define PURGE 27

const uint8_t MOTOR_LEDC_CHANNEL = 2; // 设置PWM通信频道
const uint8_t pwmResolution = 10; // 设置PWM分辨率
const uint32_t pwmFreq = 1000; // 设置PWM基础频率

bool InitIO(); // 初始化引脚读写
//void TimerStart(void (*func)(void));
//void TimerEnd();