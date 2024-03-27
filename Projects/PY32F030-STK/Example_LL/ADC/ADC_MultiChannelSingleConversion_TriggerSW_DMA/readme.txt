================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC采集通过DMA传输并从串口打印四个通道的电压值，PA4/PA5/PA6/PA7为模
拟输入，每隔1s会从串口PA2/PA3打印当前的电压值。

Function descriptions:
This sample demonstrates ADC data acquisition using DMA and printing the 
voltage values of four channels via the serial port. PA4/PA5/PA6/PA7 are 
analog inputs, andthe current voltage values will be printed every 1s via 
the serial port PA2/PA3.
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
2. 串口每隔1s会打印一次PA4,PA5,PA6,PA7的电压值。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The serial port will print the voltage values of PA4, PA5, PA6, and PA7 
every 1s.
================================================================================
注意事项：
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

波特率：115200

Notes:
STK Board USB to TTL Module
PA02(TX) --> RX
PA03(RX) --> TX
GND --> GND

Baud rate: 115200
================================================================================