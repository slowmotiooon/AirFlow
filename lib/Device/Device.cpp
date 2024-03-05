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

void Device::setPower(int val) {

}

void Device::setLaunch(int val) {

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

void Device::uploadDeviceInfo() {
    info["power"] = getPower();
}
