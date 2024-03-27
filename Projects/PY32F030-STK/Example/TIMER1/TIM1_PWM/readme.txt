================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本例程输出4路PWM，通道1的占空比为20%，通道2为40%，通道3为60%，通道4为80%
本例程周期为8000000/(50+1)/800=196Hz。

Function descriptions:
This sample demonstrates the generation of 4 PWM signals. Channel 1 has a duty 
cycle of 20%, channel 2 has a duty cycle of 40%, channel 3 has a duty cycle 
of 60%, and channel 4 has a duty cycle of 80%. The period of this example is 
calculated as 8000000/(50+1)/800=196Hz.
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
1. 编译并下载程序；
2. 用逻分或者示波器连接四个通道PA8(TIM1_CH1),PA9(TIM1_CH2),PA10(TIM1_CH3)和
PA11(TIM1_CH4)；
3. 查看发现周期为196Hz，占空比分别为20%，40%，60%，80%。

Example execution steps:
1.Compile and download the program.
2.Connect the logic analyzer or oscilloscope to the four channels: PA8 
(TIM1_CH1), PA9 (TIM1_CH2), PA10 (TIM1_CH3), and PA11 (TIM1_CH4).
3.Check the waveforms and you will observe PWM signals with a period of 196Hz 
and duty cycles of 20%, 40%, 60%, and 80%.
================================================================================
注意事项：
主频为8M

Notes:
The system frequency is 8MHz.
================================================================================