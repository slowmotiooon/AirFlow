#pragma once

#include <Arduino.h>
#include <Ticker.h>
#include "../ESP32/ESP32.h"

class Device {
    bool power;  // 设备的电源状态，false代表电源关闭，true代表电源开启
    bool launch; // 设备的运行状态，false代表设备并非在定量状态，true代表设备在定量状态
    bool purge;  // 设备的清洗状态，false代表设备并非在清洗状态，true代表设备在清洗状态

    int Factor;      // 测量的数据与实际数据之间的比例系数，与通过的气体种类有关，储存的值是因子的1000倍，值从0-2047
    int maxFlowRate; // 设备运行时的最大流速，由设备型号决定，最大流速为10 * maxFR SCCM 值从0-1023（允许标定20SCCM至10SLM）
    int setFlowRate; // 设备设定的理论流速，从0-1023 设定的流速 = 10 * setF * maxF / 1024 (SCCM)
    int curFlowRate; // 设备的实际流速，从0-1023 真实的流速 = 10 * curF * maxF / 1024 (SCCM)

    double setVolume; // 设定的目标体积 单位mm^3
    double curVolume; // 从进入定量状态后输入的实际气体体积 单位mm^3
    int intVolume;    // curVolume的整数部分，保留3位有效数字 0-999
    int fltVolume;    // curVolume的浮点部分，0-50
    // curV = intV * 10 ^ fltV mm^3
    int setSecond; // 设定的清洗时长
    Ticker ticker;

public:
    Device(); // 构造函数，初始化所有变量
    bool getPow(); // 获得设备电源信息
    bool getLch(); // 获得设备运行状态信息
    bool getPur(); // 获得设备清洗状态信息
    int getRat();  // 更新curFlowRate

    bool setPow(bool); // 设定设备的电源信息
    bool setLch(bool); // 设定设备的运行状态
    bool setPur(bool); // 设定设备的清洗状态

    bool setFct(int); // 设定气体转换系数
    bool setMRt(int); // 设置最大流速 输入单位为SCCM
    bool setRat(int); // 设置目标流速 输入单位为SCCM
    bool setVol(int, int); // 输入整数部分和浮点部分，设置目标体积
    bool setVol(double);
    bool setSec(int); // 设置清洗时间 /秒

    String toString(); // 转换为字符串
    //000 Fct 0000 Frt 0000 0000 0000 Vol 0000.000 000 00 Sec 00000
    //pow lch pur三位；最大流速、设定流速、实际流速；真实体积（浮点）、体积整数部分+浮点部分；清洗时长

    friend void IRAM_ATTR tickPurge();
    friend void IRAM_ATTR tickLaunch();
};
extern Device* defaultDevice;   //创建默认设备对象

// 回调函数，在计时器的触发时刻执行
// IRAM_ATTR属性表示将此函数存入内存RAM当中而非闪存Flash，使得该函数能被快速调用
void IRAM_ATTR tickPurge();
void IRAM_ATTR tickLaunch();
