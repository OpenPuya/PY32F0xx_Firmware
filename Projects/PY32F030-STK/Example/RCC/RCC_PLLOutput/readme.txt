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
3. 用示波器监测PA08引脚上的频率，观察到和配置的PLL频率（32MHz）一致。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Press the user button.
3.Use an oscilloscope to monitor the frequency on the PA08 pin and observes that
it matches the configured PLL frequency (32MHz).
================================================================================
注意事项：
1. 注意PLL的输入时钟源频率必须大于等于16MHz

Notes:
Note that the input clock source for PLL must have a frequency greater than 
or equal to 16MHz.
================================================================================