================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的自动波特率检测功能，调试助手发送一个字符0x7F，MCU反馈字符
串：Auto BaudRate Test。

Function descriptions:
This sample demonstrates the automatic baud rate detection feature of the 
USART. When a character 0x7F is sent from the debug assistant, the MCU will 
respond with the string "Auto BaudRate Test".
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
1. 编译并下载程序到MCU；
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA0(TX) --> RX
PA1(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为9600；
4. 调试助手发送一个字符0x7F，MCU反馈字符串：Auto BaudRate Test；

Example execution steps:
1.Compile and download the program to the MCU.
2.Connect the PC and STK board using a USB-to-TTL module. The connection is 
as follows:
STK board USB-to-TTL module
PA0(TX) --> RX
PA1(RX) --> TX
GND      --> GND
3.Open a serial debugging assistant on the PC and connect to the appropriate 
COM port with a baud rate of 9600.
4.Send the character 0x7F from the debugging assistant. The MCU will respond 
with the string "Auto BaudRate Test".
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1. 不注释掉宏AUTO_BAUD_MODE0(main.c中)，上位机发送1字节的波特率检测0x7f，如果
MCU检测成功,返回字符：Auto BaudRate Test
2. 注释掉宏AUTO_BAUD_MODE0(main.c中)，上位机发送1字节的波特率检测0x55，如果MCU
检测成功，返回字符：Auto BaudRate Test

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1.If the macro AUTO_BAUD_MODE0 is not commented out in main.c, when the host 
computer sends a 1-byte baud rate detection signal 0x7F, and the MCU detects 
it successfully, it will return the string "Auto BaudRate Test".
2.If the macro AUTO_BAUD_MODE0 is commented out in main.c, when the host 
computer sends a 1-byte baud rate detection signal 0x55 and the MCU detects 
it successfully, it will return the string "Auto BaudRate Test".
================================================================================