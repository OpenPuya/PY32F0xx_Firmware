================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在stop模式下，使用GPIO事件唤醒。

Function descriptions:
This sample demonstrates using GPIO event to wake up the MCU from stop mode.
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
3. LED灯亮，按下按键，LED灯灭，进入stop模式；
4. 在PA06上产生一个下降沿，程序退出stop模式；
5. LED以200ms的间隔进行翻转。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.The LED lights up. Press the button, and the LED turns off, entering stop mode.
4.Generate a falling edge on PA06 to wake up the MCU from stop mode.
5.The LED toggles at an interval of 200ms.
================================================================================
注意事项：
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。
2，注意关闭systick中断，防止该中断唤醒MCU。

Notes:
1.To demonstrate this sample functionality, disconnect the SWD connection and 
power cycle the board, as the debugger sets the DBGMCU_CR.DBG_STOP bit by default.
2.Make sure to disable the SysTick interrupt to prevent it from waking up the MCU.
================================================================================