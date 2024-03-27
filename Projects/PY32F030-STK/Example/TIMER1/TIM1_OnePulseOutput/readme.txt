================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的单脉冲模式。当CH2 (PA09)引脚上的上升沿触发计数器开始计数时，当计数值
与CCR1匹配时，CH1 (PA08)输出高电平，直到计数器溢出，CH1再次输出低电平。计数器溢出后，
定时器停止工作。本例程中脉冲宽度的计算公式为 
(TIM1_ARR-TIM1_CCR1)/CLK = (65535-16383)/32000000 = 1.536ms。

Function descriptions:
This sample demonstrates the single pulse mode of TIM1. When the rising edge is 
detected on CH2 (PA09) pin, the counter starts counting. When the counter value 
matches CCR1, CH1 (PA08) outputs a high level until the counter overflows. After 
the counter overflows, CH1 outputs a low level and the timer stops working. The 
pulse width in this example is calculated using the formula 
(TIM1_ARR-TIM1_CCR1)/CLK = (65535-16383)/32000000 = 1.536ms.
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
2. 在PA09上产生一个上升沿；
3. 通过示波器监测PA09和PA08引脚，可监测到波形。

Example execution steps:
1.Compile, download, and run the program.
2.Generate a rising edge on the PA09 pin.
3.Use an oscilloscope to monitor the PA09 and PA08 pins. You will observe 
the waveforms.
================================================================================
注意事项：
时钟主频为32M
输出效果见下图：
                                ____
                                |   |
   CH2 _________________________|   |_________________________________________
   
                                              ___________________________
                                             |                           |
   CH1 ______________________________________|                           |____
                                <---Delay----><------Pulse--------------->

Notes:
The system frequency is 32MHz.
Please refer to the diagram below for the output effect:
                                ____
                                |   |
   CH2 _________________________|   |_________________________________________
   
                                              ___________________________
                                             |                           |
   CH1 ______________________________________|                           |____
                                <---Delay----><------Pulse--------------->

================================================================================