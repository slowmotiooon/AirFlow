#include <Bluetooth.h>

uint8_t txValue = 0;




void BLEOutput(String s){
    for(int i = 0;i<s.length();i++){
        uint8_t buffer = s[i];
        pTxCharacteristic->setValue(&buffer,1);
        pTxCharacteristic->notify();
    }
}

void MyCallbacks::onWrite(BLECharacteristic* pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    if(rxValue.length())
    {
        if (!executeCommand(toString(rxValue))) {
            BLEOutput("Command error: "+ toString(rxValue));
        }
    }
}

void BLEInit(){
    //创建蓝牙设备
    BLEDevice::init("Wangziyi's grandpa");

    //创建蓝牙服务
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallback());
    BLEService* pService = pServer->createService(SERVICE_UUID);

    //创建蓝牙特征
    pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX,BLECharacteristic::PROPERTY_NOTIFY);
    pTxCharacteristic->addDescriptor(new BLE2902());
    BLECharacteristic* pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX,BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyCallbacks());

    pService->start();
    pServer->getAdvertising()->start();

}
