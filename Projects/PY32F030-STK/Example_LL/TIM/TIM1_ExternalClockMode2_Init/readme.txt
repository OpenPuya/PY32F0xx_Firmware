================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的外部时钟模式2的功能，选择ETR(PA12)引脚作为外部时钟输入源，并使
能更新中断，在中断中翻转LED灯。

Function descriptions:
This sample demonstrates the functionality of TIM1 in external clock mode 2. 
It selects the ETR (PA12) pin as the external clock input source and enables 
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
2. 将外部时钟输入到PA12引脚；
3. 当PA12引脚上检测到500000个脉冲，LED翻转一次。
   (PA12引脚输入1MHz频率的脉冲LED将以1Hz频率闪烁)
   
Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Connect the external clock input to the PA12 pin.
3.When 500000 pulses are detected on the PA12 pin, the LED will toggle.
(If the PA12 pin is receiving pulses with a frequency of 1MHz, the LED 
will blink at a frequency of 1Hz.)
================================================================================
注意事项：

Notes:
================================================================================