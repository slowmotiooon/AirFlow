#include "Device.h"

//device的默认构造函数，设置所有程序均为关闭状态。
Device::Device() {
    power = false;
    launch = false;
    purge = false;
    maxFlowRate = 1000;
    settledFlowRate = 0;
    flowRate = 0;
    conversionFactor = 0;
    updateFrequency = 10000000;

}

String Device::getPower(){
    if(digitalRead(POWER)) return "ON";
    else return "OFF";
}

String Device::getLaunch()
{
    if(digitalRead(LAUNCH)) return "ON";
    else return "OFF";
}

String Device::getPurge() {
    if(digitalRead(PURGE)) return "OFF";
    else return "ON";
}

void Device::updateDeviceInfo(){
    if(getPower().equals("ON")) power = true;
    else power = false;
    if(getLaunch().equals("ON")) launch =true;
    else launch = false;
    if(getPurge().equals("ON")) purge = true;
    else purge = false;
    flowRate = getFlowRate();
}

int Device::getFlowRate() {
    return 0;
}

//set类函数的返回值：
//0表示设置失败，1代表设置成功
int Device::setPower(int val) {
    if(val==1){
        digitalWrite(POWER,HIGH);
        return 1;
    }
    else if(val==0){
        digitalWrite(POWER,LOW);
        return 1;
    }
    else return 0;

}

int Device::setLaunch(int val) {
    if(val==1){
        digitalWrite(LAUNCH,HIGH);
        updateFrequency = 1000000;
        return 1;
    }
    else if(val==0){
        digitalWrite(LAUNCH,LOW);
        updateFrequency = 10000000;
        return 1;
    }
    else return 0;
}

void Device::setPurge(int val) {

}

void Device::SetFactor(int val) {

}

void Device::setFlowRate(int val) {

}

int Device::getUpdateFrequency() {
    if(digitalRead(LAUNCH)) return 1000000;
    else return 100000;
}

String Device::getDeviceInfo() {
    info["power"] = getPower();
    info["launch"] = getLaunch();
    info["purge"] = getPurge();
    info["maxFlowRate"] = maxFlowRate;
    info["settledFlowRate"] = settledFlowRate;
    info["flowRate"] = flowRate;
    info["conversionFactor"] = conversionFactor;

    String jsonBuffer;
    serializeJson(info,jsonBuffer);
    return jsonBuffer;
}
