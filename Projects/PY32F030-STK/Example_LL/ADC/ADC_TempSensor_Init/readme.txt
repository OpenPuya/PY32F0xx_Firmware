================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC模块的温度传感器功能，程序下载后，串口每隔200ms打印一次当前检测的
温度值和对应的采样值。

Function descriptions:
This sample demonstrates the temperature sensor function of the ADC module. 
After downloading the program, the current temperature value and corresponding 
sampled value will be printed via the serial port every 200ms.
================================================================================
测试环境：
测试用板：PY32F030_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F030_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 串口每隔200ms打印当前的温度和对应的采样值。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The serial port will print the current temperature and the corresponding 
sampled value every 200ms.
================================================================================
注意事项：
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

波特率:115200

Notes:
STK Board USB to TTL Module
PA02(TX) --> RX
PA03(RX) --> TX
GND --> GND

Baud rate: 115200
================================================================================