================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器唤醒功能，PA01作为比较器正端输入，VREFINT作为比较器负端输
入，PA06作为比较器的输出端口，进入stop模式后，通过调整PA01上的输入电压，产生中断
唤醒stop模式。

Function descriptions:
This sample demonstrates the wake-up function of the COMP comparator. PA01 
serves as the positive input of the comparator, VREFINT serves as the negative 
input, and PA06 is the output port of the comparator. After entering the stop 
mode, by adjusting the input voltage on PA01, an interrupt is generated to wake 
up the stop mode.
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
3. LED亮起后按下按键，进入stop模式，LED熄灭；
4. 在PA01上输入从大于1.3V到小于1.1V的电压时，产生中断，LED点亮1s；
5. 接下来LED每隔200ms进行翻转，程序正常运行。

Example execution steps:
1.Compile and download the program to the MCU.
2.Disconnect the SWD connection wire and power on again.
23.Press the button after the LED lights up to enter stop mode, and the LED 
turns off.
4.When the voltage on PA01 is adjusted from greater than 1.3V to less than 1.1V, 
an interrupt is generated, and the LED lights up for 1 second.
5.Then, the LED toggles every 200ms, indicating normal program execution.
================================================================================
注意事项：
1，演示此样例功能时需要断开swd连接线并重新上电，因为默认情况下，仿真器会把
DBGMCU_CR.DBG_STOP置位。

Notes:
1.When demonstrating this sample, disconnect the SWD connection and 
power cycle the board, as the debugger will set DBGMCU_CR.DBG_STOP by default.
================================================================================