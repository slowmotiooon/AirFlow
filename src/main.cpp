#include <Arduino.h>
#include <Ticker.h>
#include <BluetoothSerial.h>
#include <cmd.h>

BluetoothSerial SerialBT; //创建蓝牙服务器对象
Device* defaultDevice = new Device(); //创建默认设备对象
Ticker reporter; // 传输设备内容的计时器

// TaskHandle_t th_p[1]; // 定义多线程句柄
// pwm线程函数
//void pwmTask(void *pVoid) {
//    while (1) {
//        delay(10000);
//    }
//}

void report(){outputViaBT(defaultDevice->toString());}

void setup() {
    InitIO(); // 初始化ESP32串口读写
    Serial.begin(9600); // 设置串口通信，波特率为9600
    SerialBT.begin("esppppppp32"); // 启动蓝牙终端
    SerialBT.setPin("1234"); // 设置配对码
    reporter.attach(5, report);
    // xTaskCreatePinnedToCore(pwmTask, "pwmTask", 4096, nullptr, 3, &th_p[0], 0);
}

void loop() {
    // 接收蓝牙信息模块
    String commandBuffer = getBTCommand();
    if (commandBuffer.length()) {
        if (!executeCommand(commandBuffer)) {
            outputViaBT("Command fail: " + commandBuffer);
        }
    }
}
