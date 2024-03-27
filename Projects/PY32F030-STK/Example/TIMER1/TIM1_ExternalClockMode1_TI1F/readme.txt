================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的外部时钟模式1功能，选择TI1FD(PA8)引脚作为外部时钟输入源，并使能
更新中断，在中断中翻转LED灯。

Function descriptions:
This sample demonstrates the External Clock Mode 1 functionality of TIM1. It 
selects the TI1FD (PA8) pin as the external clock input source and enables the 
update interrupt. In the interrupt, the LED light will toggle.
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
2. PA8引脚，输入外部时钟；
3. 可观察到MCU从PA8引脚上输入时钟信号，CNT计数器计到800时，产生更新事件，LED翻转一次。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Input the external clock to the PA8 pin.
3.You can observe that when the MCU receives the clock signal from the PA8 pin 
and the CNT counter reaches 800, an update event will occur, causing the LED 
to toggle.
================================================================================
注意事项：

Notes:
================================================================================