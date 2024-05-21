#include "ESP32.h"

// 初始化引脚读写 临时放在device里面，到时候搬到ESP类去
bool InitIO() {
    //pinMode(LED_BUILTIN, OUTPUT);
    pinMode(POWER,OUTPUT);
    pinMode(LAUNCH,OUTPUT);
    pinMode(PURGE,OUTPUT);
    pinMode(ADC_PIN_A,INPUT);

    ledcSetup(MOTOR_LEDC_CHANNEL,pwmFreq,pwmResolution); // 设置PWM频道的分辨率，基础频率
    ledcAttachPin(PWM_PIN_A, MOTOR_LEDC_CHANNEL); //将PWM_PIN_A引脚（GPIO33）绑定到PWM频道上

    analogReadResolution(pwmResolution);
    analogSetAttenuation(ADC_11db);
    return true;
}

//// 硬件计时器代码
//void TimerStart(void (*func)(void)) {
//    // 如果计时器正在运行，则停止
//    if(timerAlarmEnabled(timer))TimerEnd();
//
//    // 设置计时器属性
//    timer = timerBegin(
//            0,       // 指定计时器编号，0、1 分辨率80MHz，2、3 分辨率1MHz
//            80,     // 设置计数周期为1us：当前最小分辨率80MHz，每80时钟周期更新一次计数周期
//            true); // 是否为累加模式
//
//    // 绑定回调函数
//    timerAttachInterrupt(
//            timer,
//            *func, // 绑定的函数
//            true); // 是否允许重复调用
//
//    // 设置回调函数触发时间
//    timerAlarmWrite(
//            timer,
//            1000000, // 触发回调函数的技术周期间隔，设为1s
//            true);
//
//    // 启动
//    timerAlarmEnable(timer);
//}
//
//void TimerEnd(){
//    timerEnd(timer);
//    timer = nullptr;
//}
