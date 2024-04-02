#include <cmd.h>

//转换std::string数据到String
String toString(std::string str){
    String buffer;
    for(auto it=str.begin();it!=str.end();it++){
        buffer+=*it;
    }
    return buffer;
}





//处理命令
//返回值：1表示存在指令并开始执行；
//      0表示指令不存在
int executeCommand(const String& commandBuffer){
    String commandType; //命令类型
    int commandValue = 0;   //命令中的整数部分

    //分离命令中的类型和整数部分
    for (int i = 0; i < commandBuffer.length(); i++)
    {
        if (isalpha(commandBuffer[i]))
        {
            commandType += commandBuffer[i];
        }
        if (isdigit(commandBuffer[i]))
        {
            commandValue = commandValue * 10 + commandBuffer[i] - '0';
        }
    }

    //处理命令
    if (commandType.equals("pow")){
        if(defaultDevice->setPow(commandValue)){
            // outputViaBT("Power is set to ");
            // outputViaBT(defaultDevice.getPow()?"ON":"OFF");
            // outputViaBT("\n");
            return 1;
        }
        // outputViaBT("Can not set power\n");
        return 0;
    }
    else if (commandType.equals("lch")){
        if(defaultDevice->setLch(commandValue)){
            // outputViaBT("Launch is set to ");
            // outputViaBT(defaultDevice.getLch()?"ON":"OFF");
            // outputViaBT("\n");
            return 1;
        }
        // outputViaBT("Can not set launch\n");;
        return 0;
    }
    else if (commandType.equals("pur")){
        if(defaultDevice->setPur(commandValue)){
            // outputViaBT("Purge is set to ");
            // outputViaBT(defaultDevice.getPur()?"ON":"OFF");
            // outputViaBT("\n");
            return 1;
        }
        // outputViaBT("Can not set purge\n");
        return 0;
    }
    else if (commandType.equals("fct")){
        if(defaultDevice->setFct(commandValue)){
            // outputViaBT("Factor is settled\n");
            return 1;
        }
        // outputViaBT("Can not set Factor\n");
        return 0;
    }
    else if (commandType.equals("mrt")){
        if(defaultDevice->setMRt(commandValue)){
            // outputViaBT("maxFlowRate is settled\n");
            return 1;
        }
        // outputViaBT("Can not set maxFlowRate\n");
        return 0;
    }
    else if (commandType.equals("rat")){
        if(defaultDevice->setRat(commandValue)){
            // outputViaBT("setFlowRate is settled\n");
            return 1;
        }
        // outputViaBT("Can not set setFlowRate\n");
        return 0;
    }
    else if (commandType.equals("vol")){

        if(defaultDevice->setVol(double(commandValue))){
            // outputViaBT("Volume is settled\n");
            return 1;
        }
        // outputViaBT("Can not set Volume\n");
        return 0;
    }
    else if (commandType.equals("sec")){

        if(defaultDevice->setSec(commandValue)){
            // outputViaBT("setSecond is settled\n");
            return 1;
        }
        // outputViaBT("Can not set setSecond\n");
        return 0;
    }
    else return 0;
}

