#include <Arduino.h>
#include <BluetoothSerial.h>
#include <cmd.h>

BluetoothSerial SerialBT; //创建蓝牙服务器对象
hw_timer_t *timer = NULL; // 设置硬件计时器
int interruptCounter = 0;

void IRAM_ATTR timerEvent()
{
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
}

hw_timer_t *TimerStart(hw_timer_t *timer){
  // 设置计时器属性
  // 第一个参数指定了计时器编号。esp32中共有4个计时器。其中0，1是80MHz的，2，3是1MHz的。
  // 第二个参数设置分频数，每间隔多少次单位记一次时。
  // 第三个参数设定是否是累加模式
  timer = timerBegin(0, 80, true);

  // 绑定回调函数
  // 第一个是计时器
  // 第二个参数是回调函数
  // 第三个是设置是否重复调用
  timerAttachInterrupt(timer, &timerEvent, true);

  // 设置回调函数触发时间
  // 第一个参数是（绑定好回调函数的）计时器
  // 第二个参数是设置触发间隔， 1000000，指一秒钟触发一次
  timerAlarmWrite(timer, 1000000, true);

  // 启动
  timerAlarmEnable(timer);

  return timer;
}

void setup()
{
  Serial.begin(115200); // 设置串口通信，波特率为115200
  pinMode(LED_BUILTIN, OUTPUT);

  SerialBT.begin("esppppppp32"); // 启动蓝牙终端
  SerialBT.setPin("1234");       // 设置配对码
  timer = TimerStart(timer);
}

void loop()
{
  String cmdBuffer; // 来自蓝牙串口的字符串命令
  int cmdval = 0;   // 命令中的整形数据

  // SerialBT的available函数指的是什么：
  // 在其它蓝牙设备向esp32输入蓝牙信息后，esp32会把接收到的信息放入缓冲区，
  // 当缓冲区的字符长度不为0时，avaliable为true，否则为false。
  while (SerialBT.available())
  {
    cmdBuffer += char(SerialBT.read()); // 读取SerialBT中的内容，并且存放到cmdBuffer中，便于后续操作。
  }
  // Serial的available函数也同理。
  while (Serial.available())
  {
    SerialBT.write(Serial.read());
  }

  if (cmdBuffer.length())
  {

    // Serial.println(cmdBuffer); //测试用，查看是否接收到信息。

    String commandType; // 存储的命令类型

    // 遍历cmdBuffer，分割命令类型和命令参数；
    for (int i = 0; i < cmdBuffer.length(); i++)
    {
      if (isalpha(cmdBuffer[i]))
      {
        commandType += cmdBuffer[i];
      }
      if (isdigit(cmdBuffer[i]))
      {
        cmdval = cmdval * 10 + cmdBuffer[i] - '0';
      }
    }

    if (command(commandType, cmdval) == -1)
    {
      Serial.print("UnknownCommand ");
      Serial.print(commandType);
      Serial.print(' ');
      Serial.print(cmdval, DEC);
      Serial.print('\n');
    }

    // LED响应
    // Serial.print(cmdBuffer);
    // digitalWrite(LED_BUILTIN,HIGH);
    // delay(10);
    // digitalWrite(LED_BUILTIN,LOW);
  }
}
