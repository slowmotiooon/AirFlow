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
    Device();
    static String getPower();
    static String getLaunch();
    static String getPurge();
    static int getFlowRate();
    static int getUpdateFrequency();
    void setPower(int val);
    void setLaunch(int val);
    void setPurge(int val);
    void SetFactor(int val);
    void setFlowRate(int val);

    void updateDeviceInfo();
    void uploadDeviceInfo();

};
