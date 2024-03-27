================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器中断功能，PA01作为比较器正端输入，VREFINT作为比较器负端输
入，运行程序，PA01输入1.3V电压，LED灯亮。

Function descriptions:
This sample demonstrates the interrupt function of the COMP comparator. 
PA01 is used as the positive input of the comparator, VREFINT is used as 
the negative input. When the program is running, if a voltage of 1.3V is 
applied to PA01, the LED will turn on.
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
2. PA01输入小于1.1V电压，LED灯不亮；
3. PA01输入大于1.3V电压，LED灯亮。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.When the input voltage on PA01 is less than 1.1V, the LED will not light up.
3.When the input voltage on PA01 is greater than 1.3V, the LED will light up.
================================================================================
注意事项：

Notes:
================================================================================