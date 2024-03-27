================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了stop模式下，通过GPIO事件唤醒功能。

Function descriptions:
This sample demonstrates the GPIO event wake-up feature in stop mode.
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
1. 编译下载程序到MCU；
2. 断开swd连接线并重新上电;
3. LED灯亮，按下按键，LED灯灭，串口打印"STOP MODE!",进入stop模式；
4. 在PA06上产生一个下降沿，程序退出stop模式，并且串口打印"WAKEUP OK!"；
5. LED以200ms的间隔进行翻转。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.The LED will be turned on. Press the button to turn off the LED and print 
"STOP MODE!" to the serial port, entering stop mode.
4.Generate a falling edge on PA06 to wake up the program from stop mode. The 
serial port will print "WAKEUP OK!".
5.The LED will toggle at an interval of 200ms.
================================================================================
注意事项：
MCU与串口调试助手连线:
RX ---> PA02
TX ---> PA03
波特率：115200bps

1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2，注意关闭systick中断，防止该中断唤醒MCU。

Notes:
Connection between MCU and Serial Debug Assistant:
RX ---> PA02
TX ---> PA03
Baud Rate: 115200bps

1.When demonstrating this sample, disconnect the SWD connection and power 
cycle the board, as the debugger will set DBGMCU_CR.DBG_STOP by default.
2.Make sure to disable the SysTick interrupt to prevent it from waking up the 
MCU.
================================================================================