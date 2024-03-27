================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了TIM1中的编码器计数功能，TI1(PA8)和TI2(PA9)作为编码器输入引脚，通过
CNT寄存器可观察到计数器变化，通过uwDirection变量可观察到计数器的计数方向，通过
打印数据也可观察计数方向和CNT寄存器计数值，打印数据Direction = 0为向上计数，
Direction = 1为向下计数。

Function descriptions:
This sample demonstrates the encoder counting function in TIM1. TI1 (PA8) 
and TI2 (PA9) serve as encoder input pins. The counter changes can be 
observed through the CNT register, and the counting direction of the counter 
can be observed through the uwDirection variable. The direction and CNT 
register value can also be printed. The printed data shows Direction = 0 for 
counting up and Direction = 1 for counting down.
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
1. 编译下载程序到MCU，并通过debug模式运行；
2. 在PA08和PA09上输入交替脉冲（PA08上升沿在前，PA09上升沿在后，具体请参考用户手册）；
3. 可观察到CNT寄存器的值不断累加；
4. 在PA08和PA09上输入交替脉冲（PA09上升沿在前，PA08上升沿在后，具体请参考用户手册）；
5. 可观察到CNT寄存器的值不断减小；

Example execution steps:
1.Compile and download the program to the MCU and run it in debug mode.
2.Provide alternate pulses on PA08 and PA09 (PA08 rising edge first, PA09 
rising edge second, please refer to the user manual for details).
3.The CNT register value will continuously increase.
4.Provide alternate pulses on PA08 and PA09 (PA09 rising edge first, PA08 
rising edge second, please refer to the user manual for details).
5.The CNT register value will continuously decrease.
================================================================================
注意事项：

Notes:
================================================================================