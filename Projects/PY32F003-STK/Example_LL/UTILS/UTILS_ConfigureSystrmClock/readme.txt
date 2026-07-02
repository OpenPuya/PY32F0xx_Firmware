================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本样例主要演示如何配置SYSCLK(系统时钟), HCLK(AHB时钟), PCLK(APB时钟)。
通过MCO输出系统时钟8MHz。

Function descriptions:
This sample demonstrates how to configure SYSCLK (system clock), HCLK 
(AHB clock),and PCLK (APB clock), and outputs the system clock of 8MHz 
through MCO.
================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F003_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10

================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 通过逻辑分析仪或示波器可观测到端口PA1输出频率为8MHz的波形；
3. LED灯按照1s的频率闪烁。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Use a logic analyzer or an oscilloscope to observe the waveform of port PA1,
which outputs a frequency of 8MHz.
3.The LED flashes at a frequency of 1s.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
================================================================================