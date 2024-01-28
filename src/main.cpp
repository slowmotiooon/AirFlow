#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200); //设置串口通信，波特率为115200
  pinMode(LED_BUILTIN,OUTPUT);

  SerialBT.begin("esppppppp32");  //启动蓝牙终端
  SerialBT.setPin("1234");  //设置配对码
  
}

void loop() {
  String cmdBuffer;  //来自蓝牙串口的字符串命令
  int cmdval = 0; //命令中的整形数据

  //SerialBT的available函数指的是什么：
  //在其它蓝牙设备向esp32输入蓝牙信息后，esp32会把接收到的信息放入缓冲区，
  //当缓冲区的字符长度不为0时，avaliable为true，否则为false。
  while(SerialBT.available()){
    Serial.write(SerialBT.read());  //读取SerialBT获取到的内容，并在串口监视器中输出

  }

  while(Serial.available()){
    SerialBT.write(Serial.read());
  }
}

