================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的外部时钟模式1的功能，选择TI1F_ED(PA8)引脚作为外部时钟输入源，
并使能更新中断，在中断中翻转LED灯。

Function descriptions:
This sample demonstrates the functionality of TIM1 in external clock mode 1. 
It selects TI1F_ED (PA8) pin as the external clock input source and enables 
the update interrupt. In the interrupt, the LED light is toggled.
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
2. 将外部时钟输入到PA8引脚；
3. 当PA8引脚上检测到500000个边沿，LED翻转一次。
   (PA8引脚输入1MHz频率的脉冲LED将以2Hz频率闪烁)
   
Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Connect the external clock input to the PA8 pin.
3.When 500000 edges are detected on the PA8 pin, the LED will toggle.
(If the PA8 pin is receiving pulses with a frequency of 1MHz, the LED 
will blink at a frequency of 2Hz.)
================================================================================
注意事项：

Notes:
================================================================================