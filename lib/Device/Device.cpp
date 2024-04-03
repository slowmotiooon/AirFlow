#include <Device.h>

//device的默认构造函数，设置所有程序均为关闭状态。
Device::Device():
    power(false),  // 设备的电源状态，false代表电源关闭，true代表电源开启
    launch(false), // 设备的运行状态，false代表设备并非在定量状态，true代表设备在定量状态
    purge(false),  // 设备的清洗状态，false代表设备并非在清洗状态，true代表设备在清洗状态

    Factor(0),      // 测量的数据与实际数据之间的比例系数，与通过的气体种类有关，储存的值是因子的1000倍，值从0-2047
    maxFlowRate(0), // 设备运行时的最大流速，由设备型号决定，最大流速为10 * maxFR SCCM 值从0-1023（允许标定20SCCM至10SLM）
    setFlowRate(0), // 设备设定的理论流速，从0-1023 设定的流速 = 10 * setF * maxF / 1024 (SCCM)
    curFlowRate(0), // 设备的实际流速，从0-1023 真实的流速 = 10 * curF * maxF / 1024 (SCCM)

    setVolume(0),   // 设定的目标体积 单位mm^3
    curVolume(0),   // 从进入定量状态后输入的实际气体体积 单位mm^3
    intVolume(0),   // curVolume的整数部分，保留3位有效数字 0-999
    fltVolume(0),   // curVolume的浮点部分，0-63
    // curV = intV * 10 ^ fltV mm^3
    setSecond(0) // 设定的清洗时长 小于32767
{}

// 获得设备电源信息
bool Device::getPow() {return digitalRead(POWER);}

// 获得设备运行状态信息
bool Device::getLch() {return digitalRead(LAUNCH);}

// 获得设备清洗状态信息
bool Device::getPur() {return digitalRead(PURGE);}

// 更新curFlowRate
int Device::getRat() {
    return 0;
}

// 设定设备的电源信息
bool Device::setPow(bool x) {
    if(x) {
        power = true;
        digitalWrite(POWER, HIGH);
    }
    else {
        if(purge)setPur(false);
        if(launch)setLch(false);
        power = false;
        digitalWrite(POWER, LOW);
    }
    return true;
}

// 设定设备的运行状态
bool Device::setLch(bool x) {
    if(x){
        if(!power || purge || !Factor || !maxFlowRate || !setFlowRate || setVolume < 0.1) {return false;}
        launch = true;
        digitalWrite(LAUNCH, HIGH);
    } else {
        setFlowRate = 0;
        setVolume = 0;
        launch = false;
        digitalWrite(LAUNCH, LOW);
    }
    return true;
}

// 设定设备的清洗状态
bool Device::setPur(bool x) {
    if(x){
        if(!power || launch || !setSecond) {return false;}
        purge = true;
        digitalWrite(PURGE, HIGH);
        ticker.attach(1, tickPurge);
    } else {
        setSecond = 0;
        purge = false;
        digitalWrite(PURGE, LOW);
        ticker.detach();
    }
    return true;
}

// 设定气体转换系数
bool Device::setFct(int x) {
    if(x > 100 && x < 2000) {
        Factor = x;
        return true;
    } else return false;
}

// 设置最大流速
bool Device::setMRt(int r) {
    if(r > 10 && r < 10240) {
        maxFlowRate = r / 10;
        return true;
    } else
        maxFlowRate = 0;
    return false;
}

// 设置目标流速
bool Device::setRat(int r) {
    r = int((r * 1024 / 10) / maxFlowRate);
    if(r > 0 && r < 1024){
        setFlowRate = r;
        return true;
    } else
        setFlowRate = 0;
    return false;
}

// 输入整数部分和浮点部分，设置目标体积
bool Device::setVol(int i, int f){
    if(i > 0 && i < 1000 && f >= 0 && f < 64){
        setVolume = i * pow(10, f);
        return true;
    }
    setVolume = 0;
    return false;
}

bool Device::setVol(double a){
    if(a > 1){
        setVolume = a;
        return true;
    }
    setVolume = 0;
    return false;
}

// 设置清洗时间 /秒
bool Device::setSec(int x) {
    if(x > 0 && x < 32768) {
        setSecond = x;
        return true;
    }
    setSecond = 0;
    return false;
}

String Device::toString() {
    String str = "";
    str.concat(power?"1":"0");
    str.concat(launch?"1":"0");
    str.concat(purge?"1":"0");
    str.concat(" ");
    str.concat(Factor % 2048);
    str.concat(" ");
    str.concat(maxFlowRate % 1024);
    str.concat(" ");
    str.concat(setFlowRate % 1024);
    str.concat(" ");
    str.concat(curFlowRate % 1024);
    str.concat(" ");
    str.concat(setVolume);
    str.concat(" ");
    str.concat(curVolume);
    str.concat(" ");
    str.concat(intVolume % 1000);
    str.concat(" ");
    str.concat(fltVolume % 64);
    str.concat(" ");
    str.concat(setSecond % 32768);
    str.concat("\n");
    return str;
}

std::vector<std::string> Device::toString(const int length){
    String total = this->toString();
    std::vector<std::string> stringList;
    std::string buffer;
    for(int i = 0;i<total.length();i++){
        if(i%length==0){
            stringList.push_back(buffer);
            buffer.clear();
        }
        buffer+=total[i];
    }
    stringList.push_back(buffer);
    return stringList;
}



uint8_t* Device::convert(){
    uint8_t* list = new uint8_t[2];
    list[0] = '\0';
    list[0] = list[0]<<1;
    list[0] = list[0]+(power?1:0);
    list[0] = list[0]<<1;
    list[0] = list[0]+(launch?1:0);
    list[0] = list[0]<<1;
    list[0] = list[0]+(purge?1:0);

    return list;
}

// 回调函数，在计时器的触发时刻执行
// IRAM_ATTR属性表示将此函数存入内存RAM当中而非闪存Flash，使得该函数能被快速调用
void IRAM_ATTR tickPurge() {
    if(defaultDevice->setSecond <= 0){
        defaultDevice->setPur(false);
    }
    else defaultDevice->setSecond -= 1;
}

void IRAM_ATTR tickLaunch() {
}
