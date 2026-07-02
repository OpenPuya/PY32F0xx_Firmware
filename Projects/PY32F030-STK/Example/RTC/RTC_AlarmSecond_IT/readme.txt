================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示RTC的秒中断和闹钟中断功能，每次秒中断，在中断函数中会打印字符
“RTC_IT_SEC”，并且输出实时时间;当到达闹钟时间时，打印“RTC_IT_ALARM”。

Function descriptions:
This sample demonstrates the second interrupt and alarm interrupt functionality 
of the RTC. Each time the second interrupt occurs, the interrupt function will 
print the string "RTC_IT_SEC" and output the current RTC count time;When the
alarm time is reached, print "RTC-IT-ALARM".
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
2. PC端打开串口调试助手，正确连接上通讯COM口；
3. 按下STK复位按键，调试助手每秒钟都能收到字符串：RTC_IT_SEC和当前RTC计数时间;
   当到达闹钟时间时，打印“RTC_IT_ALARM”。

Example execution steps:
1.Compile and download the program to the MCU.
2.Open a serial terminal on the PC and correctly connect to the corresponding 
COM port.
3.Press the reset button on the STK board. The serial terminal should receive 
the string "RTC_IT_SEC" and the current RTC count time every second;When the
alarm time is reached, print "RTC-IT-ALARM".
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