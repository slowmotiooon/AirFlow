#include <Bluetooth.h>


uint8_t txValue = 0;




void BLEOutput(String s){
    for(int i = 0;i<s.length();i++){
        uint8_t buffer = s[i];
        pTxCharacteristic->setValue(&buffer,1);
        pTxCharacteristic->notify();
    }
}

void BLEOutput(uint8_t s[], size_t length){
    pTxCharacteristic->setValue(s, length);
    pTxCharacteristic->notify();
}

void BLEOutput(std::vector<std::string> list) {
    for (auto it = list.begin(); it != list.end(); it++) {


        pTxCharacteristic->setValue(*it);
        pTxCharacteristic->notify();
    }
}

void MyCallbacks::onWrite(BLECharacteristic* pCharacteristic){
    std::string rxValue = pCharacteristic->getValue();
    Serial.println(toString(rxValue));
    if(rxValue.length())
    {
        if (!executeCommand(toString(rxValue))) {
            // BLEOutput("Command error: "+ toString(rxValue));
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
    //esp_ble_gatt_set_local_mtu(40);

    pService->start();
    pServer->getAdvertising()->start();

}
