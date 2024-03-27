================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的自动波特率检测功能,上位机发送1字节的波特率检测字符0x55，如果
MCU检测成功，则返回字符：Auto BaudRate Test。

Function descriptions:
This sample demonstrates the automatic baud rate detection feature of USART. 
The PC sends a 1-byte baud rate detection character 0x55, and if the MCU 
detects it successfully, it returns the string "Auto BaudRate Test".
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
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口，波特率设置为9600，1位
停止位，8位数据位，无奇偶校验；
4. 调试助手发送一个字符0x55，MCU反馈字符串：Auto BaudRate Test。

Example execution steps:
1.Compile and download the program to the MCU.
2.Connect the PC and the STK board using a USB to TTL module. The 
connection is as follows:
STK board USB to TTL module
PA02(TX) --> RX
PA03(RX) --> TX
GND --> GND
3.Open a serial terminal on the PC and correctly connect to the designated 
COM port. Set the baud rate to 9600, stop bits to 1, data bits to 8, and 
parity to none.
4.Send the character 0x55 in the serial terminal. The MCU will respond with 
the string "Auto BaudRate Test".
================================================================================
注意事项：

Notes:
================================================================================