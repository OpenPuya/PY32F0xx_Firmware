================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC模块的VCC采样功能，通过采样VREFINT的值，计算得出VCC的值，并通过串
口打印出来。

Function descriptions:
This sample demonstrates the VCC sampling function of the ADC module. By 
samplingthe value of VREFINT, the value of VCC is calculated and printed via 
the serial port.
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
2. 串口会连续打印VCC的电压值。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The serial port will continuously print the voltage value of VCC.
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
GND      --> GND

Baud rate: 115200
================================================================================