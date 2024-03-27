================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本样例主要演示如何配置SYSCLK(系统时钟), HCLK(AHB时钟), PCLK(APB时钟)。
通过MCO输出系统时钟48MHz。

Function descriptions:
This sample demonstrates how to configure SYSCLK (system clock), HCLK 
(AHB clock),and PCLK (APB clock), and outputs the system clock of 48MHz 
through MCO.
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
2. 通过逻辑分析仪或示波器可观测到端口PA8输出频率为48MHz的波形；
3. LED灯按照0.5hz的频率闪烁。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Use a logic analyzer or an oscilloscope to observe the waveform of port PA8,
which outputs a frequency of 48MHz.
3.The LED blinks at a frequency of 0.5Hz.
================================================================================
注意事项：

Notes:
================================================================================