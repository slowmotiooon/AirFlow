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
    cmdBuffer +=char(SerialBT.read());  //读取SerialBT中的内容，并且存放到cmdBuffer中，便于后续操作。

  }
  //Serial的available函数也同理。
  while(Serial.available()){
    SerialBT.write(Serial.read());
  }

  if(cmdBuffer.length()){
    String commandType; //存储的命令类型

    //遍历cmdBuffer，分割命令类型和命令参数；
    for(int i = 0;i<cmdBuffer.length();i++){
      if(isalpha(cmdBuffer[i])){
        commandType+=cmdBuffer[i];
      }
      if(isdigit(cmdBuffer[i])){
        cmdval = cmdval*10+cmdBuffer[i]-'0';
      }
    }

    Serial.print("Command: ");
    Serial.print(commandType);
    Serial.print(" Value: ");
    Serial.print(cmdval, DEC);
    Serial.print('\n');



    // LED响应
    // Serial.print(cmdBuffer);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN,LOW);
  }
}

