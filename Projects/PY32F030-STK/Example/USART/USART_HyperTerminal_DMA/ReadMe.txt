================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的DMA方式发送和接收数据，USART配置为115200，数据位8，停止位1，
校验位None,下载并运行程序后，通过上位机下发12个数据，例如0x1~0xC,则，MCU会把接收
到的数据再次发送。

Function descriptions:
 This sample demonstrates USART DMA mode to send and receive data, USART
 configuration is 115200, data bit 8, stop bit 1, check bit None, download and
 run the program, through the host computer to send 12 data, such as 0x1 ~0xC,
 MCU will send the received data again. 
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
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA09(TX) --> RX
PA10(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为115200；
4. 上位机发送12个数据，MCU会反馈同样的12个数据给上位机。

Example execution steps:
1.Compile and download the program to the MCU.
2.Connect the PC and STK board using a USB-to-TTL module. The connection is 
as follows:
STK board USB-to-TTL module
PA09(TX) --> RX
PA10(RX) --> TX
GND      --> GND
3.Open a serial debugging assistant on the PC and connect to the appropriate 
COM port with a baud rate of 115200.
4.Send 12 data from the host computer. The MCU will send back the received 
data to the host computer.
================================================================================
注意事项：

Notes:
================================================================================