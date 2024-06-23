================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了LPTIM中断唤醒stop模式，每次唤醒后再次进入stop模式，每200ms唤醒一次。

Function descriptions:
This sample demonstrates the LPTIM interrupt wake-up in stop mode. After each 
wake-up, it re-enters stop mode and wakes up again every 200ms.
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
3. 按下按键进入stop模式；
4. 200ms后唤醒stop模式并循环进入stop模式再唤醒；
5. LED保持2.5Hz频率闪烁；

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.Press the button to enter stop mode.
4.Wake up from stop mode after 200ms and re-enter stop mode in a loop.
5.The LED will blink at a frequency of 2.5Hz.
================================================================================
注意事项：
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2,每次唤醒后再次进入Stop模式前,必须增加延时120us(至少3个LSI时钟),用于LSI和APB时钟同步。

Notes:
1.When demonstrating this sample, disconnect the SWD connection and 
power cycle the board, as the debugger will set DBGMCU_CR.DBG_STOP by default.
2,Before re-entering stop mode after each wake-up, a delayof 75us (at least 2 LSI 
clocks) must be added to synchronize the LSI and APB clocks.
================================================================================