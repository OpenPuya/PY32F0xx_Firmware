================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1 PWM2模式输出三路频率为10Hz占空比分别为25%、50%、75%的PWM波形。

Function descriptions:
This sample demonstrates the use of TIM1 PWM2 mode to output three PWM 
waveforms with frequencies of 10Hz and duty cycles of 25%, 50%, and 75% 
respectively.
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
2. 使用逻辑分析仪观察引脚PA8/PA9/PA10的波形。

Example execution steps:
1. Compile and download the program to the MCU.
2. Use a logic analyzer to observe the waveforms on pins PA8/PA9/PA10.
================================================================================
注意事项：
PA8  -> CH1  占空比：75%
PA9  -> CH2  占空比：50%
PA10 -> CH3  占空比：25%

Notes:
PA8  -> CH1  Duty cycle: 75%
PA9  -> CH2  Duty cycle: 50%
PA10 -> CH3  Duty cycle: 25%
================================================================================
