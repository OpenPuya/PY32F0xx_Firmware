================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示通过RTC闹钟中断每隔1s将MCU从STOP模式下唤醒，每次唤醒会翻转LED，LED翻转
间隔为1s。

Function descriptions:
This sample demonstrates waking up the MCU from the STOP mode every 1 second 
using the RTC alarm interrupt. Each time the MCU wakes up, the LED will toggle, 
with a toggle interval of 1 second.
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
2. 断开swd连接线并重新上电;
3. 等待LED灯亮后，按下用户按键，LED灯关闭，进入STOP模式；
4. RTC开始计时，每隔1s就会通过闹钟中断唤醒MCU，并且翻转LED和串口打印本次闹钟的
时间。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.Wait for the LED to turn on, then press the user button to turn off the 
LED and enter the STOP mode.
4.The RTC starts counting, wakes up the MCU every 1s with an alarm interrupt, 
and toggles the LED and prints the time of this alarm through the serial port.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2，通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
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
1.When demonstrating this sample, disconnect the SWD connection and 
power cycle the board, as the debugger will set DBGMCU_CR.DBG_STOP by default.
2.Connect the PC to the STK board through the USB to TTL module, and the connection
method between the STK board and the USB to TTL module is as follows:
@PrintfConfigStart
STK board USB to TTL module
PA02(TX)  -->  RX
PA03(RX)  -->  TX
GND       -->  GND
UART is configured as BaudRate 115200, data bit 8, stop bit 1, and parity None.
@PrintfConfigEnd
================================================================================