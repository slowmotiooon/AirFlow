#include <Arduino.h>
#include <BluetoothSerial.h>
#include <cmd.h>
#include <IO.h>
#include "../lib/pwm/pwm.h"

BluetoothSerial SerialBT; //创建蓝牙服务器对象
Device defaultDevice;   //创建默认设备对象
hw_timer_t *timer = nullptr; // 设置硬件计时器
int interruptCounter = 0;

TaskHandle_t th_p[1];   //定义句柄

void pwmTask(void *pVoid) {
    while (1) {
        ledcWrite(MOTOR_LEDC_CHANNEL, interruptCounter);
        delay(1);
    }
}

//回调函数，在计时器的触发时刻执行
void IRAM_ATTR timerEvent() {
    //outputViaBT(defaultDevice.getDeviceInfo()); //将获得的设备信息上传到蓝牙终端
}

hw_timer_t *TimerStart(hw_timer_t *hwTimer) {
    // 设置计时器属性
    // 第一个参数指定了计时器编号。esp32中共有4个计时器。其中0，1是80MHz的，2，3是1MHz的。
    // 第二个参数设置分频数，每间隔多少次单位记一次时。
    // 第三个参数设定是否是累加模式
    hwTimer = timerBegin(0, 80, true);

    // 绑定回调函数
    // 第一个是计时器
    // 第二个参数是回调函数
    // 第三个是设置是否重复调用
    timerAttachInterrupt(hwTimer, &timerEvent, true);

    // 设置回调函数触发时间
    // 第一个参数是（绑定好回调函数的）计时器
    // 第二个参数是设置触发间隔， 1000000，指一秒钟触发一次
    timerAlarmWrite(hwTimer, Device::getUpdateFrequency(), true);

    // 启动
    timerAlarmEnable(hwTimer);

    return hwTimer;
}

void setup() {
    Serial.begin(9600); // 设置串口通信，波特率为115200
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(POWER,OUTPUT);
    pinMode(LAUNCH,OUTPUT);
    pinMode(PURGE,OUTPUT);
    pwmInit();
    SerialBT.begin("esppppppp32"); // 启动蓝牙终端
    SerialBT.setPin("1234");       // 设置配对码
    timer = TimerStart(timer);

    //xTaskCreatePinnedToCore(pwmTask, "pwmTask", 4096, nullptr, 3, &th_p[0], 0);
}

void loop() {
    //Serial.print("Start receiving message from Bluetooth devices on core ");
    //Serial.println(xPortGetCoreID());
    String commandBuffer = getBTCommand();

    // Serial的available函数也同理。
//    while (Serial.available()) {
//        SerialBT.write(Serial.read());
//    }

    if (commandBuffer.length()) {
        if (!executeCommand(commandBuffer)) {
            outputViaBT("Unknown command: " + commandBuffer);
        }
    }
    delay(1);
}
