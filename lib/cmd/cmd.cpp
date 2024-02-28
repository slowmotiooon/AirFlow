#include <cmd.h>

//由于SerialBT库中并没有输出字符串的函数，于是我就写了一个。
void outputViaBT(String target){
    //遍历字符串，用于输出
    for(int i = 0;i<target.length();i++){
        Serial.print(target[i]);    //在串口中输出
        //Serial.println(i);
        SerialBT.write(target[i]);  //在蓝牙中输出
    }
    return;
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

//获取电源状态
int getPower(){
    if(digitalRead(POWER)==HIGH){
        outputViaBT("power:ON;");
        return 1;
    }
    else{
        outputViaBT("power:OFF");
        return 0;
    }
}

int command(String cmd){
    if (cmd.equals("setLED")){
        if(setLED(cmdval)==-1) return -1;
    }
    else if (cmd.equals("power on")){
    }
    else if (cmd.equals("power off")){
    }
    else if (cmd.equals("launch on")){
    }
    else if (cmd.equals("launch off")){
    }
    else if (cmd.equals("purge on")){
    }
    else if (cmd.equals("purge off")){
    }
    else if (cmd.equals("getinfo")){
    }
    else if (cmd.startsWith("setRate ")){
    }
    else if (cmd.startsWith("setVolume ")){
    }
    else if (cmd.startsWith("setTime ")){
    }
    else if (cmd.startsWith("setFactor ")){
    }
    else if (cmd.startsWith("setRange ")){
    }
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
