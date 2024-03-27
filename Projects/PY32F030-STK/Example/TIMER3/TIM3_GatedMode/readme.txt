================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM3从模式下的门控触发功能，配置CH1(PA06)作为门控触发输入信号，并使能
触发中断，每次进触发中断，翻转一次LED灯，在IDE仿真界面里，可以看到，当PA06输入低
电平时，定时器CNT寄存器停止计数，当PA06输入高电平时，定时器CNT寄存器持续在计数。
并且PA06引脚上的每产生一次触发中断，LED都会翻转一次。

Function descriptions:
This sample demonstrates the gated trigger functionality in Timer 3 (TIM3). 
It configures CH1 (PA06) as the gated trigger input signal and enables the 
trigger interrupt. Every time the trigger interrupt is triggered, the LED 
light will toggle. In the IDE simulation interface, you can observe that 
when the input level on PA06 is low, the timer's CNT register stops counting, 
and when the input level on PA06 is high, the timer's CNT register continues 
counting. Every time the trigger interrupt occurs, the LED light will toggle.
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
1. 下载程序并运行;
2. 从PA06引脚输入变化的电平，可以观察到PA06引脚上每产生一次触发中断，LED灯会翻
转一次。

Example execution steps:
1.Download and run the program.
2.Input varying levels on the PA06 pin, and you will observe that the LED 
light toggles every time a trigger interrupt occurs.
================================================================================
注意事项：

Notes:
================================================================================