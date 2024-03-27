================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1和TIM3级联成32位计数器，TIM3做主机，TIM3的溢出信号作为TIM1的输入
时钟。TIM3每1ms计数一次，计数1000次后产生溢出，TIM1计数一次。

Function descriptions:
This sample demonstrates the cascading of TIM1 and TIM3 as a 32-bit counter, 
with TIM3 as the master and the overflow signal of TIM3 as the input clock of 
TIM1. TIM3 counts every 1ms, and after counting 1000 times, it overflows and 
TIM1 counts once.
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
2. 串口每秒打印一次TIM1计数值，从0~10依次递增。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The TIM1 count value will be printed via UART every second, incrementing 
from 0 to 10.
================================================================================
注意事项：
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

波特率:115200

Notes:
STK board USB to TTL module
PA02(TX) --> RX
PA03(RX) --> TX
GND --> GND

Baud rate: 115200
================================================================================