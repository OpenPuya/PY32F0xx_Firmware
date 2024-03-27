================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了GPIO外部中断功能，PA12引脚上的每一个下降沿都会产生中断，中断函数中
LED灯会翻转一次。

Function descriptions:
This sample demonstrates the functionality of GPIO external interrupts. 
Whenever a falling edge is detected on pin PA12, an interrupt is triggered, 
and the interrupt handler toggles the state of the LED.
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
2. 每按一次用户按键，观察到LED翻转一次。

Example execution steps:
1.Compile and download the program to the MCU, and run it.
2.Each time the user button is pressed, observe the LED toggling its state.
================================================================================
注意事项：
用户按键所对应的引脚为PA12

Notes:
The user button is connected to pin PA12.
================================================================================