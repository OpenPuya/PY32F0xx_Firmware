================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM1中基本计数功能，并使能了更新中断，每次重装ARR值时会产生一次
更新中断，并在中断中翻转LED灯，LED灯会以5Hz的频率进行翻转。

Function descriptions:
This sample demonstrates the basic counting functionality in Timer 1 (TIM1) 
and enables the update interrupt. Every time the ARR value is reloaded, an 
update interrupt is triggered, and the LED light will toggle in the 
interrupt. The LED light will toggle at a frequency of 5Hz.
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
2. LED灯闪烁。

Example execution steps:
1.Compile and download the program.
2.The LED light will blink.
================================================================================
注意事项：
主频时钟为32M

Notes:
The main frequency clock is set to 32MHz.
================================================================================