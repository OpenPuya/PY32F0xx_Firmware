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
2. 通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA2(TX) --> RX
PA3(RX) --> TX
GND     --> GND
3. PC端打开串口调试助手，正确连接上通讯COM口；
4. 按下STK复位按键，调试助手每秒钟都能收到字符串：RTC_IT_SEC和当前RTC计数时间;
   当到达闹钟时间时，打印“RTC_IT_ALARM”。

Example execution steps:
1.Compile and download the program to the MCU.
2.Connect the PC and STK board using a USB to TTL module. The connection 
between the STK board and the USB to TTL module is as follows:
STK board USB to TTL module
PA2(TX) --> RX
PA3(RX) --> TX
GND     --> GND
3.Open a serial terminal on the PC and correctly connect to the corresponding 
COM port.
4.Press the reset button on the STK board. The serial terminal should receive 
the string "RTC_IT_SEC" and the current RTC count time every second;When the
alarm time is reached, print "RTC-IT-ALARM".
================================================================================
注意事项：
打印字符需要通过串口调试助手在上位机上显示。

Notes:
The printed characters need to be displayed on the PC using a serial terminal.
================================================================================