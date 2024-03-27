================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1和TIM3同步触发（门控触发模式）功能，TIM1作为主机，配置为比较输出
功能，OC1输出频率1kHz，占空比50%（即1ms高电平1ms低电平循环），TIM3作为从机，配置
为外部门控触发模式，TIM1的OC1信号连接到TIM3作为TIM3的门控触发输入，配置TIM3的计
数溢出周期为125us，并允许溢出中断，且在溢出中断中对LED灯翻转。通过运行程序，通过
逻辑分析仪可以看到，当TIM1_CH1(PA8)输出高电平时，LED(PA11)电平翻转；当TIM1_CH1
(PA8)输出低电平时，LED(PA11)电平不翻转。

Function descriptions:
This sample demonstrates the synchronous trigger feature (gate trigger mode) 
of TIM1 and TIM3. TIM1 is configured as the master and set as a compare output 
with a frequency of 1kHz and a duty cycle of 50% (1ms high level, 1ms low 
level cycle). TIM3 is configured as the slave and set as an external gate 
trigger mode with TIM1's OC1 signal connected as TIM3's gate trigger input. 
TIM3's counter overflow period is set to 125us, and overflow interrupt is 
enabled. In the overflow interrupt, the LED toggles.By running the program 
and using a logic analyzer, it can be observed that when TIM1_CH1 (PA8) 
outputs a high level, the LED (PA11) toggles; when TIM1_CH1 (PA8) outputs 
a low level, the LED (PA11) remains unchanged.
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
2. 通过逻分查看，当TIM1_CH1(PA8)输出高电平时，LED(PA11)电平翻转；当TIM1_CH1
(PA8)输出低电平时，LED(PA11)电平不翻转。

Example execution steps:
1.Download and run the program.
2.Use a logic analyzer to observe that when TIM1_CH1 (PA8) outputs a high 
level, the LED (PA11) toggles; when TIM1_CH1 (PA8) outputs a low level, 
the LED (PA11) remains unchanged.
================================================================================
注意事项：

Notes:
================================================================================