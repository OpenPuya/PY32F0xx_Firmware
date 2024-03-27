================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1和TIM3同步触发（复位触发模式）功能，TIM1作为主机，配置复位TRGO
输出(TIM1_CR2.MMS=000)，TIM3作为从机并且使能事件更新中断，配置收到主机的TRGO信
号后复位(TIM3_SMCR.SMS=100)。循环打印TIM3计数值。

Function descriptions:
This sample demonstrates the synchronous trigger feature (reset trigger mode) 
of TIM1 and TIM3. TIM1 is configured as the master and set as a reset trigger 
output (TIM1_CR2.MMS=000). TIM3 is configured as the slave and enables the 
update event interrupt. It is set to reset when receiving the reset trigger 
signal from the master (TIM3_SMCR.SMS=100). The program continuously prints 
the value of TIM3's counter.
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
1. 编译下载程序并运行；
2. 查看串口打印TIM3的计数值，TIM3计数值永远小于3999（即TIM1的重装载值）。

Example execution steps:
1.Compile and download the program.
2.Check the serial port to print the TIM3 count value, which is always less 
than 3999 (i.e., the reload value of TIM1).
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
Baud Rate: 115200bps
================================================================================