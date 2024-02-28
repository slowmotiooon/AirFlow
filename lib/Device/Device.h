#pragma once

#include <Arduino.h>
#include <IO.h>

class Device {
    bool power; //设备的电源状态，false代表电源关闭，true代表电源开启
    bool launch;    //设备的运行状态，false代表设备待机，true代表设备运行
    bool purge; //设备的清洗状态，在launch == true时，false代表未清洗，true代表处于清洗状态
    double flowRate;    //设备
    int flowRange;
public:
    Device();
};
