#include <cmd.h>

void outputViaBT(String target){
    for(int i = 0;i<target.length();i++){
        Serial.print(target[i]);
        //Serial.println(i);
        SerialBT.write(target[i]);
    }
    return;
}

int setLED(int ledVal){
    outputViaBT("LED is set to ");
        if(ledVal==1){
            digitalWrite(LED_BUILTIN,HIGH);
            Serial.print("HIGH");
            SerialBT.write(char(ledVal+48));
        }
        else if(ledVal==0){
            digitalWrite(LED_BUILTIN,LOW);
            Serial.print("LOW");
            SerialBT.write(char(ledVal+48));
        }
        else{
            outputViaBT("error.");
            return 0;
        };

        return 1;
}

int command(String cmdType,int cmdval){
    if(cmdType.equals("setLED")){
        setLED(cmdval);
    }
    return -1;

}