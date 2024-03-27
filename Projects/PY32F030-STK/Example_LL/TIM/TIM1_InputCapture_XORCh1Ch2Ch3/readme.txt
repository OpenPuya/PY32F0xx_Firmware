================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的三通道异或输入捕获功能。配置PA8、PA9、PA10为通道1、通道2、通道3
的输入引脚。每当有一个引脚电平变化时会触发捕获中断，并在中断处理中翻转LED。

Function descriptions:
This sample demonstrates the XOR input capture functionality of TIM1 using three 
channels: PA8, PA9, and PA10 as the input pins for channel 1, channel 2, and 
channel 3, respectively. Whenever there is a change in the level of any of the 
input pins, it triggers the capture interrupt and toggles the LED in the 
interrupt handler.
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
2. 保持任意两个引脚电平不变，当剩下一引脚电平变化时LED翻转。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Keep the level of any two pins unchanged, and when the level of the 
remaining pin changes, the LED will toggle.
================================================================================
注意事项：

Notes:
================================================================================