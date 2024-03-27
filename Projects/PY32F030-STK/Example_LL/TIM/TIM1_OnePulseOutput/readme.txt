================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的单脉冲模式。配置TIM1为从模式触发模式，触发源为TI2FP2，通道1为
PWM2模式，映射到PA8，通道2为输入模式，映射到PA9。当PA9上检测到一个上升沿时，PA8
延迟20ms后产生一个宽度为80ms的脉冲。

Function descriptions:
This sample demonstrates the single pulse mode of TIM1. TIM1 is configured in 
slave mode trigger mode with TI2FP2 as the trigger source. Channel 1 is 
configured as PWM mode 2 and mapped to pin PA8, while channel 2 is configured 
as input mode and mapped to pin PA9. When an rising edge is detected on PA9, 
a 20ms delay is applied, and then PA8 will output a pulse with a width of 80ms.
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
2. 使用示波器的捕获模式观察PA8，PA9；
3. 当PA9上产生一个上升沿时，延迟20ms后PA8输出一个宽度为80ms的脉冲。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Use an oscilloscope in capture mode to observe pins PA8 and PA9.
3.When a rising edge is detected on PA9, after a delay of 20ms, PA8 will 
output a pulse with a width of 80ms.
================================================================================
注意事项：

Notes:
================================================================================