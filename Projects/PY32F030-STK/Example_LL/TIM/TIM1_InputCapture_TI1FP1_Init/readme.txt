================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输入捕获功能，配置PA3作为输入捕获引脚，PA3每检测到一个上升沿触
发捕获中断在捕获中断回调函数中翻转LED灯。

Function descriptions:
This sample demonstrates the input capture functionality of TIM1 by configuring 
PA3 as the input capture pin. Whenever an rising edge is detected on PA3, it 
triggers the capture interrupt and toggles the LED in the interrupt callback 
function.
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
2. 在PA3上产生一个上升沿，LED灯翻转。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Generate a rising edge on the PA3 pin, and the LED will toggle.
================================================================================
注意事项：

Notes:
================================================================================