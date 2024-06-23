================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了通过TIM1触发ADC,再通过ADC触发DMA搬运ADC_DR中的数据，配置CH0(PA00)
为ADC的模拟输入通道，TIM1配置为主模式，TIM1每产生一次更新事件，触发一次ADC采样，
然后ADC触发DMA搬运采样数据，采样数据在中断中打印。

Function descriptions:
This sample demonstrates the use of TIM1 to trigger ADC conversion, followed by 
DMA transfer of data from ADC_DR. CH0(PA00) is configured as the analog input 
channel for ADC. TIM1 is set to the master mode, triggering ADC conversion on 
each update event. The sampled data is then transferred by DMA, and the data is 
printed in an interrupt handler.
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
2. 每经过1s,TIM1触发一次ADC采样，将采到的数据通过uart打印。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Every 1 second, TIM1 triggers ADC conversion, and the sampled data is printed 
via UART.
================================================================================
注意事项：
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

波特率:115200

Notes:
STK board    USB to TTL module
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

Baud rate: 115200
================================================================================