================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了TIM1和TIM3级联成32位计数器，TIM3做主机，TIM3的计数溢出信号作为TIM1的
输入时钟，通过配置TIM1和TIM3的重载寄存器值，（在TIM1中断回调函数中）实现LED灯以
0.5Hz频率闪烁
此例程计算方式为TIM3_ARR*TIM3_PSC*TIM1_ARR*TIM1_PSC/时钟
=800*100*100*1/8000000=1Hz

Function descriptions:
This sample demonstrates the functionality of cascading Timer 1 (TIM1) and 
Timer 3 (TIM3) to form a 32-bit counter. Timer 3 acts as the master counter, 
and its overflow signal serves as the input clock for Timer 1. By configuring 
the reload register values of Timer 1 and Timer 3, the LED blinks at a 
frequency of 0.5Hz in the Timer 1 interrupt callback function.
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
1. 编译下载程序并运行；
2. LED灯以0.5Hz频率闪烁

Example execution steps:
1.Compile and download the program.
2.Run the program, and observe the LED blinking at a frequency of 0.5Hz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
默认主频为8M

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
The system frequency is 8MHz.
================================================================================