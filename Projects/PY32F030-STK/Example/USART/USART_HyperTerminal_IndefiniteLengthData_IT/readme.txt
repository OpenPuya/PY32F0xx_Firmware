================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了USART的中断方式发送和接收不定长数据，USART配置为115200，数据位8，
停止位1，校验位None,下载并运行程序后，然后通过上位机下发任意长度个数据
（不超过128bytes），例如0x1~0xC,则MCU会把接收到的数据再次发送到上位机。

Function descriptions:
This example demonstrates the interrupt method of USART to send and receive
variable length data. USART is configured as 115200, with data bit 8, stop bit
1, and check bit None. After downloading and running the program, the MCU will
send any length of data (not exceeding 128bytes) through the upper computer,
such as 0x1~0xC. The MCU will send the received data to the upper computer again.
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
4. 上位机发送任意长度个数据（不超过128bytes），MCU会将接收到的数据回发给上位机

Example execution steps:
1. Compile and download the program to the MCU.
2. Connect the PC and STK board using a USB-to-TTL module. The connection is 
   as follows:
STK board USB-to-TTL module
PA09(TX) --> RX
PA10(RX) --> TX
GND --> GND
3. Start the serial assistant on the PC, correctly connect the COM port, and set
the baud rate to 115200.
4. The upper computer sends any length of data (not exceeding 128 bytes), and
the MCU will send the received data back to the upper computer
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
用户可根据需要修改main.h中宏RX_MAX_LEN的值，RX_MAX_LEN定义了MCU单次接收数据长度
（当前样例为128bytes）。

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
Users can modify the values of macros RX_MAX_LEN in main.h as needed. RX_MAX_LEN
defines the length of data received by MCU for a single time (currently 128bytes).
================================================================================