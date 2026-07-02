================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的单脉冲模式。配置TIM1为从模式触发模式，触发源为TI2FP2，通道1为
PWM2模式，映射到PA3，通道2为输入模式，映射到PA13。当PA13上检测到一个上升沿时，PA3
延迟20ms后产生一个宽度为80ms的脉冲。

Function descriptions:
This sample demonstrates the single pulse mode of TIM1. TIM1 is configured in 
slave mode trigger mode with TI2FP2 as the trigger source. Channel 1 is 
configured as PWM mode 2 and mapped to pin PA3, while channel 2 is configured 
as input mode and mapped to pin PA13. When an rising edge is detected on PA13, 
a 20ms delay is applied, and then PA3 will output a pulse with a width of 80ms.
================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F003_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行
2. 按下按键
2. 使用示波器的捕获模式观察PA3，PA13
3. 当PA13上产生一个上升沿时，延迟20ms后PA3输出一个宽度为80ms的脉冲

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Use an oscilloscope in capture mode to observe pins PA3 and PA13.
3.When a rising edge is detected on PA13, after a delay of 20ms, PA3 will 
output a pulse with a width of 80ms.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required

================================================================================