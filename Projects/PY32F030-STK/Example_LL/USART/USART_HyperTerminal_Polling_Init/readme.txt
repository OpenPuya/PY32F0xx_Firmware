================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的轮询方式发送和接收数据，USART配置为9600，数据位8，停止位1，
校验位None,下载并运行程序后，打印提示信息，然后通过上位机下发12个数据，例如
0x1~0xC,则MCU会把接收到的数据再次发送到上位机，然后打印结束信息。

Function descriptions:
This example demonstrates how to use USART to send an amount of data in polling 
mode. USART configuration is 9600 baud rate, data bit 8, stop bit 1, check bit 
None. After download and run the program,Print the prompt message, and then send
12 data through the upper computer, such as 0x1~0xC, the MCU will send the 
received data to the upper computer again, Then print the end message.
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
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为9600，1位
   停止位，8位数据位，无奇偶校验。
4. 按下复位按键，MCU会发送aTxStartMessage数组内的数据到上位机，提示输入12个数据。
5. 上位机发送12个数据到MCU，MCU会反馈同样的12个数据给上位机。同时发送aTxEndMessage
   数组内数据到上位机，提示样例执行结束。
6. 观察开发板上的指示灯，长亮表示通信正常，反之通信异常。

Example execution steps:
1. Compile and download the program to the MCU.
2. Connect the PC and the STK board using a USB to TTL module. The connection 
   is as follows:
STK board USB to TTL module
PA02(TX) --> RX
PA03(RX) --> TX
GND --> GND
3. Open a serial terminal on the PC and correctly connect to the designated 
   COM port. Set the baud rate to 9600, stop bits to 1, data bits to 8, and 
   parity to none.
4. When the reset button is pressed, the MCU sends the data in the aTxStartMessage
   array to the host computer, prompting for 12 data inputs.
5. The host computer sends 12 data to the MCU and the MCU feeds back the same 12
   data to the host computer. Also send the data in the aTxEndMessage array to the
   host computer to signal the end of the sample execution.
6. Observe the indicator light on the development board, a long light means that
   the communication is normal, and vice versa, the communication is abnormal.
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