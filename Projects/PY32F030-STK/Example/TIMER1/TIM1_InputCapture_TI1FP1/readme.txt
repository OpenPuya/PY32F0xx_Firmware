================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM1(PA8)输入捕获功能，PA8输入时钟信号，TIM1捕获成功后，会进入
捕获中断，每进一次中断，翻转一次LED。

Function descriptions:
This sample demonstrates the input capture function of TIM1 (PA8). When a clock 
signal is input to PA8, TIM1 captures it successfully and enters the capture 
interrupt. With each interrupt, the LED will toggle.
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
1. 下载并运行程序；
2. PA8引脚不输入时钟信号的情况下，LED不翻转；
3. PA8输入时钟信号，TIM1捕获成功后，LED会翻转。

Example execution steps:
1.Download and run the program.
2.With no clock signal input to PA8 pin, the LED will not toggle.
3.When a clock signal is input to PA8, and TIM1 successfully captures it, 
the LED will toggle.
================================================================================
注意事项：
主频为8M

Notes:
The system frequency is 8MHz.
================================================================================