================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1输出三路频率为10Hz占空比分别为25%、50%、75%的PWM波形以及他们
的互补信号，并实现了250ns的死区和刹车功能。

Function descriptions:
This sample demonstrates the generation of three PWM waveforms with frequencies 
of 10Hz and duty cycles of 25%, 50%, and 75% using TIM1. It also generates their 
complementary signals and implements a 250ns dead-time and brake function.
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
2. 将PA6引脚接低电平。
3. 使用逻辑分析仪观察引脚PA7/PA8/PA9/PA10/PB0/PB1的波形；
4. 将PA6引脚接高电平，PWM停止输出。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Set pin PA6 to the low logic level.
3.Use a logic analyzer to observe the waveforms on pins PA7/PA8/PA9/PA10/PB0/PB1.
4.Set pin PA6 to a high logic level to stop PWM output.
================================================================================
注意事项：
PA8  -> CH1  占空比：25%
PA9  -> CH2  占空比：50%
PA10 -> CH3  占空比：75%
PA7  -> CH1N
PB0  -> CH2N
PB1  -> CH3N

Notes:
PA8  -> CH1  Duty cycle: 25%
PA9  -> CH2  Duty cycle: 50%
PA10 -> CH3  Duty cycle: 75%
PA7  -> CH1N
PB0  -> CH2N
PB1  -> CH3N
================================================================================