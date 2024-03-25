#include "pwm.h"

void pwmInit(){
    ledcSetup(MOTOR_LEDC_CHANNEL,pwmFreq,pwmResolution);
    ledcAttachPin(33, MOTOR_LEDC_CHANNEL);
}