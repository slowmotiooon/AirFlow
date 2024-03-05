#pragma once

#include <Arduino.h>
#include <IO.h>
#include "../ArduinoJson/ArduinoJson.h"

class Device {
    bool power; //设备的电源状态，false代表电源关闭，true代表电源开启
    bool launch;    //设备的运行状态，false代表设备待机，true代表设备运行
    bool purge; //设备的清洗状态，在launch == true时，false代表未清洗，true代表处于清洗状态

    int maxFlowRate;    //设备运行时的最大流速，由设备型号决定
    int settledFlowRate;    //设备设定的理论流速
    int flowRate;    //设备的实际流速

    int conversionFactor;   //测量的数据与实际数据之间的比例系数，与通过的气体种类有关，储存的值是因子的1000倍
    JsonDocument info;
public:
    Device();   //构造函数，初始化所有变量
    String getPower();   //获得设备电源信息
    String getLaunch();  //获得设备运行状态信息
    String getPurge();   //获得设备清洗状态信息
    int getFlowRate();   //获得设备流速
    int getUpdateFrequency();    //从运行状态获得设备的信息更新频率，运行：1秒1次，非运行：10秒1次
    int setPower(int val); //设定设备的电源信息
    void setLaunch(int val);    //设定设备的运行状态
    void setPurge(int val); //设定设备的清洗状态
    void SetFactor(int val);    //设定气体转换系数
    void setFlowRate(int val);  //设置流速

    void updateDeviceInfo();    //更新设备信息（内部）
    String getDeviceInfo(); //获取设备信息（外部）

};
