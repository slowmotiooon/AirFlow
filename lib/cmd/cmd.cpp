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

int command(String cmdType,int cmdval){
    if(cmdType.equals("setLED")){
        if(setLED(cmdval)==-1) return -1;
    }

    if(cmdType.equals("getPower")){
        getPower();
    }
    return -1;

}