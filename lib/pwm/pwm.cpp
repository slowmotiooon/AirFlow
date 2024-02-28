#include "pwm.h"

void pwmInit(){
    ledcSetup(MOTOR_LEDC_CHANNEL,pwmFreq,pwmResolution);
    ledcAttachPin(LED_BUILTIN, MOTOR_LEDC_CHANNEL);
}