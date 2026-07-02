================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例配置系统时钟为PLL，并通过MCO（PA08）引脚输出，PLL的输入时钟源选择HSI。

Function descriptions:
This sample configures the system clock as PLL and outputs it through the 
MCO (PA08) pin. The input clock source for the PLL is set to HSI.
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
2. 按下用户按键；
3. 用示波器监测PA08引脚上的频率，观察到输出的频率为24MHz。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Press the user button.
3. Use an oscilloscope to monitor the frequency on the PA08 pin and observe 
that the output frequency is 24MHz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1. PLL的输入时钟源频率请参考数据手册

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1. Please refer to the data manual for the PLL input clock source frequency.
================================================================================