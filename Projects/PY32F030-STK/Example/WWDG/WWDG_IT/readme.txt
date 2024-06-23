================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了WWDG的提前唤醒中断功能，看门狗计数器向下计数到0x40时产生中断，中断中
喂狗，可以确保看门狗不会复位。

Function descriptions:
This sample demonstrates the early wakeup interrupt feature of the 
WWDG (Window Watchdog). When the watchdog counter counts down to 0x40, an 
interrupt is generated. In the interrupt handler, the watchdog is refreshed 
to ensure that the watchdog does not cause a system reset.
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
2. 程序在看门狗提前唤醒中断中喂狗，LED以1hz在闪烁。

Example execution steps:
1.Compile and download the program to the MCU.
2.The program will periodically refresh the watchdog in the watchdog early 
wakeup interrupt, resulting in the LED blinking at a frequency of 1Hz.
================================================================================
注意事项：

Notes:
================================================================================