================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了通过PA6引脚唤醒MCU的功能。下载程序并运行后，LED灯处于常亮状态；按下
用户按键后，LED灯处于常暗状态，且MCU进入STOP模式；拉低PA6引脚后，MCU唤醒，LED灯
处于闪烁状态。

Function descriptions:
This sample demonstrates the functionality of waking up the MCU using 
the PA6 pin. Once the program is downloaded and running, the LED will 
remain lit. Pressing the user button will turn off the LED and put the 
MCU into STOP mode. Pulling the PA6 pin low will wake up the MCU, and 
the LED will start blinking.
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
3. 小灯处于常亮状态，按下用户按键，LED灯处于常暗状态，且MCU进入STOP模式；
4. 拉低PA6引脚后，MCU唤醒，LED灯处于闪烁状态。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.The LED is constantly on. Press the user button, and the LED turns 
off, and the MCU enters STOP mode.
4.Pull the PA6 pin low to wake up the MCU, and the LED will start blinking.
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