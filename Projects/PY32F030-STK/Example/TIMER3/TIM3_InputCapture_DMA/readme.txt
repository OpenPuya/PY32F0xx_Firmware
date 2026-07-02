================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM3输入捕获功能，捕获数据通过DMA传输到变量CC1_Capture中，并通过
串口打印输出。

Function descriptions:
This sample demonstrates the input capture feature in TIM3. The captured data 
is transferred to the variable CC1_Capture using DMA and printed through the UART.

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
1. 下载并运行程序；
2. 开始打印数据，未在PA6输入时钟信号，则打印输出的结果为0；
3. 在PA6输入时钟信号后，打印数据会根据捕获值进行输出。

Example execution steps:
1.Download and run the program.
2.Start printing the data. If there is no clock signal on PA6, the printed 
output will be 0.
3.When a clock signal is input on PA6, the printed data will be output based 
on the captured value.
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