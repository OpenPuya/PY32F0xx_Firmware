================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的单脉冲模式，CH2(PA13)引脚上的上升沿，触发计数器开始计数，当计数
值与CCR1匹配时，CH1(PA3)输出高电平，直到计数器溢出，CH1再次输出低电平，计数器溢
出后，定时器停止工作。

本例程脉冲宽度计算 (TIM1_ARR-TI1_CCR1)/CLK=（65535-16383）/16000000=3.072ms

Function descriptions:
This sample demonstrates the single pulse mode of TIM1. When the rising edge is 
detected on CH2 (PA13) pin, the counter starts counting. When the counter value 
matches CCR1, CH1 (PA03) outputs a high level until the counter overflows. After 
the counter overflows, CH1 outputs a low level and the timer stops working. The 
pulse width in this example is calculated using the formula 
(TIM1_ARR-TIM1_CCR1)/CLK = (65535-16383)/16000000 = 3.072ms
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
1. 编译下载程序到MCU，并运行；
2. 按下按键后，在PA13上产生一个上升沿；
3. 通过示波器监测PA13和PA3引脚，可监测到上述波形；

Example execution steps:
1.Compile, download, and run the program.
2.Generate a rising edge on the PA13 pin.
3.Use an oscilloscope to monitor the PA13 and PA03 pins. You will observe 
the waveforms.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
时钟主频为16M
因为PA13（默认为SWD_DIO）引脚复用为CH2，如果要重新烧录程序需要复位后再下载
输出效果见下图：
                                ____
                                |   |
   CH2 _________________________|   |_________________________________________
   
                                              ___________________________
                                             |                           |
   CH1 ______________________________________|                           |____
                                <---Delay----><------Pulse--------------->

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
The system frequency is 16MHz.
Because PA13 (default SWD_DIO) pin is multiplexed to CH2, if you want to 
re-burn the programme you need to reset it before downloading.
The output effect is shown in the figure below:
                                ____
                                |   |
   CH2 _________________________|   |_________________________________________
   
                                              ___________________________
                                             |                           |
   CH1 ______________________________________|                           |____
                                <---Delay----><------Pulse--------------->
================================================================================