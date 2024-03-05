#include <cmd.h>

//由于SerialBT库中并没有输出字符串的函数，于是我就写了一个。
void outputViaBT(String target){
    //遍历字符串，用于输出
    for(int i = 0;i<target.length();i++){
        Serial.print(target[i]);    //在串口中输出
        SerialBT.write(target[i]);  //在蓝牙中输出
    }
    Serial.print("\n");
    SerialBT.write('\n');
}

//设置LED开关
int setLED(int ledVal){
    outputViaBT("LED is set to ");
    if(ledVal==1){
        digitalWrite(LED_BUILTIN,HIGH);
        Serial.print("HIGH");
        SerialBT.write(char(ledVal+48));
        return 1;
    }
    else if(ledVal==0){
        digitalWrite(LED_BUILTIN,LOW);
        Serial.print("LOW");
        SerialBT.write(char(ledVal+48));
        return 0;
    }
    else{
        outputViaBT("error.");
        return -1;
    }
}

// SerialBT的available函数指的是什么：
// 在其它蓝牙设备向esp32输入蓝牙信息后，esp32会把接收到的信息放入缓冲区，
// 当缓冲区的字符长度不为0时，available为true，否则为false。

//从蓝牙设备中获得命令信息
String getBTCommand(){
    String commandBuffer; //用于接收命令
    while(SerialBT.available()){
        commandBuffer+=char(SerialBT.read());   // 读取SerialBT中的内容，并且存放到cmdBuffer中，便于后续操作。
    }
    return commandBuffer;
}

//处理命令
//返回值：1表示存在指令并开始执行；
//      0表示指令不存在
int executeCommand(const String& commandBuffer){
    String commandType; //命令类型
    int commandValue = 0;   //命令中的整数部分

    //分离命令中的类型和整数部分
    for (int i = 0; i < commandBuffer.length(); i++)
    {
        if (isalpha(commandBuffer[i]))
        {
            commandType += commandBuffer[i];
        }
        if (isdigit(commandBuffer[i]))
        {
            commandValue = commandValue * 10 + commandBuffer[i] - '0';
        }
    }

    //处理命令
    if (commandType.equals("setLED")){
        if(setLED(commandValue) == -1) return -1;
        return 1;
    }
    else if (commandType.equals("power")){
        defaultDevice.setPower(commandValue);
        return 1;
    }
    else if (commandType.equals("launch")){
        defaultDevice.setLaunch(commandValue);
        return 1;
    }
    else if (commandType.equals("purge")){
        defaultDevice.setPurge(commandValue);
        return 1;
    }
    else if (commandType.equals("getInfo")){
        return 1;
    }
    else if (commandType.startsWith("setRate ")){
        return 1;
    }
    else if (commandType.startsWith("setVolume ")){
        return 1;
    }
    else if (commandType.startsWith("setTime ")){
        return 1;
    }
    else if (commandType.startsWith("setFactor ")){
        return 1;
    }
    else if (commandType.startsWith("setRange ")){
        return 1;
    }
    else return 0;
}

/*
 * command类接收蓝牙输入命令转换为IO与timer命令
 *
 * power on/off
 * launch on/off
 * purge on/off
 * getinfo 包括瞬时流量，剩余时间，已经输入的容量，当前的阀控态，电源态，当前设置的时间、流速、体积、转换系数、满量程流速
 * （待机态每秒调用一次，启动时每100ms调用一次）
 *
 * setRate double 设置流速
 * setVolume double 设置容积
 * setTime double 设置时间
 * setFactor double 设置气体转换系数
 * setRange int 设置满量程流速
 */
