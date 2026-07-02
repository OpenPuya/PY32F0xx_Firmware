================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了LPTIM中断唤醒stop模式，每次唤醒后再次进入stop模式，每200ms唤醒一次。

Function descriptions:
This sample demonstrates the LPTIM interrupt wake-up from stop mode. It enters stop mode
after each wake-up and wakes up every 200ms.
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
1. 编译下载程序到MCU，并运行；
2. 按下按键进入stop模式；
3. 200ms后唤醒stop模式并循环进入stop模式再唤醒；
4. LED保持2.5Hz频率闪烁；

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.Press the button to enter stop mode.
4.Wake up from stop mode after 200ms and repeatedly enter stop mode 
and wake up.
5.The LED will blink at a frequency of 2.5Hz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2,每次唤醒后再次进入Stop模式前,必须增加延时160us(至少4个LSI时钟),用于LSI和APB时
钟同步。

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1.When demonstrating this sample, disconnect the SWD connection and 
power cycle the board, as the debugger will set DBGMCU_CR.DBG_STOP by default.
2,Before re-entering stop mode after each wake-up, a delay of 160us (at least 4 
LSI clocks) must be added to synchronize the LSI and APB clocks.
================================================================================