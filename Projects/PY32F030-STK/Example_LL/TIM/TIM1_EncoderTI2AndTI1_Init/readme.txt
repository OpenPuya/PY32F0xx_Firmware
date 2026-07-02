================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的编码器接口模式。TIM1配置为编码器接口模式3，PA8和PA9配置为通道1
和通道2当PA8输入信号的上升沿在前，PA9输入信号上升沿在后时TIM1向上计数，反之向下
计数。开启通道1和通道2的捕获中断，在中断中打印当前CNT值。

Function descriptions:
This sample demonstrates the encoder interface mode of TIM1. TIM1 is configured 
in encoder interface mode 3, with PA8 and PA9 configured as channel 1 and 
channel 2, respectively. When the rising edge of the input signal on PA8 occurs 
before the rising edge of the input signal on PA9, TIM1 counts up; otherwise, 
it counts down. The capture interrupts for channel 1 and channel 2 are enabled, 
and the current CNT value is printed in the interrupt.
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
2. 在PA8和PA9输入相位不同的脉冲；
3. 连接串口打印当前计数值（不断累加或递减，由输入脉冲时序决定）。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Input pulse signals with different phases on PA8 and PA9.
3.Connect a serial port to print the current count value (it will increment 
or decrement based on the timing of the input pulses).
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
@PrintfConfigStart
STK板        USB转TTL模块
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART配置为波特率115200，数据位8，停止位1，校验位None
@PrintfConfigEnd

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
================================================================================