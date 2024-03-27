================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器唤醒功能，PA01作为比较器正端输入，VREFINT作为比较器负端输
入，上完电LED灯会常亮，用户点击按键，LED灯灭，进入stop模式，通过调整PA01上的输入
电压，产生中断唤醒stop模式。

Function descriptions:
This sample demonstrates the wake-up function of the COMP comparator. PA01 
is used as the positive input of the comparator, VREFINT is used as the 
negative input. After power on, the LED will be constantly on. When the user 
clicks the button, the LED will turn off and enter stop mode. By adjusting 
the input voltage on PA01, an interrupt is generated to wake up the stop mode.
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
1. 编译下载程序到MCU;
2. 断开swd连接线并重新上电;
3. PA01上输入小于1.1V的电压，发现LED灯常亮；
4. 按下按键，LED灯熄灭，进入stop模式；
5. 在PA01上输入大于1.3V的电压，产生中断唤醒；
6. 接下来LED每隔200ms进行翻转，程序正常运行。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
3.Input a voltage less than 1.1V on PA01. The LED will 
be constantly on.
4.Press the button, the LED will turn off and enter stop mode.
5.Input a voltage greater than 1.3V on PA01 to generate an interrupt and 
wake up the system.
6.The LED will toggle every 200ms after waking up, and the program will 
run normally.
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