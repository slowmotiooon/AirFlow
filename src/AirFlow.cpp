#include <Arduino.h>
#include <Ticker.h>
#include <Bluetooth.h>
#include <cmd.h>

Device* defaultDevice = new Device(); //创建默认设备对象
Ticker reporter; // 传输设备内容的计时器

BLEServer* pServer = nullptr;
BLECharacteristic* pTxCharacteristic = nullptr;
bool deviceConnected = false;


// TaskHandle_t th_p[1]; // 定义多线程句柄
// pwm线程函数
//void pwmTask(void *pVoid) {
//    while (1) {
//        delay(10000);
//    }
//}

void IRAM_ATTR report(){
    uint8_t x[20];
    defaultDevice->toU8(x);
    Serial.println(reinterpret_cast<const char *>(x));
    BLEOutput(x, 14);
//    for(int i = 0;i<14;i++){
//        Serial.print(char(x[i]));
//    }
//    Serial.println();
}

void setup() {
    InitIO(); // 初始化ESP32串口读写
    Serial.begin(115200); // 设置串口通信，波特率为115200
    BLEInit();
    reporter.attach(0.5, report);
    //xTaskCreatePinnedToCore(pwmTask, "pwmTask", 4096, nullptr, 3, &th_p[0], 0);
}

void loop() {
    if(deviceConnected){

    }
    else{
        delay(500);
        pServer->getAdvertising()->start();
        Serial.println("start broadcasting.");
    }
    delay(10);
}
