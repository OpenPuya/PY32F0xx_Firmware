================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器的window功能，比较器2的Plus端用比较器1的IO3(PA1)作为输入，
VREFINT作为比较器负端输入，当PA1的电压值大于1.3V时,LED灯亮，小于1.1V时,LED灯灭。

Function descriptions:
This sample demonstrates the window function of the COMP comparator. The 
positive input of comparator 2 is connected to the IO3 (PA1) of comparator 1, 
and VREFINT is used as the negative input of the comparator. When the voltage 
on PA1 is greater than 1.3V, the LED turns on. When the voltage is less 
than 1.1V, the LED turns off.
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
1. 编译下载程序到MCU，并运行；
2. 在PA01上输入大于1.3V的电压，LED灯亮；
3. 在PA01上输入小于1.1V的电压，LED灯灭。

Example execution steps:
1.Compile and download the program to the MCU, and run it.
2.Input a voltage greater than 1.3V on PA01, the LED turns on.
3.Input a voltage less than 1.1V on PA01, the LED turns off.
================================================================================
注意事项：

Notes:
================================================================================