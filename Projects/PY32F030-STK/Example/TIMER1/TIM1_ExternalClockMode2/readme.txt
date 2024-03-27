================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的外部时钟模式2功能，选择ETR(PA12)引脚作为外部时钟输入源，并使能
更新中断，在中断中翻转LED灯。

Function descriptions:
This sample demonstrates the External Clock Mode 2 functionality of TIM1. It 
selects the ETR (PA12) pin as the external clock input source and enables the 
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
2. PA12引脚，输入外部时钟；
3. 可观察到MCU从PA12引脚上每检测到800个脉冲，会让LED灯翻转一次。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Input the external clock to the PA12 pin.
3.Whenever the MCU detects 800 pulses, the LED light will toggle.
================================================================================
注意事项：

Notes:
================================================================================