================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了时钟输出功能，可输出以HSI为源的PLL波形。

Function descriptions:
This sample demonstrates the clock output function, which can output PLL 
waveform with HSI as the source.
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
2. 用示波器监测PA08引脚上的频率，观察到输出的频率为24MHz。

Example execution steps:
1.Compile and download the program to the MCU and run it;
2. Use an oscilloscope to monitor the frequency on the PA08 pin and 
observe that the output frequency is 24MHz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1. PLL的输入时钟源频率只能为24MHz。

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1. The input clock source frequency of the PLL can only be 24 MHz.
================================================================================