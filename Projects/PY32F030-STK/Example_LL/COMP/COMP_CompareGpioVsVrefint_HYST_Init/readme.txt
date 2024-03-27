================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器迟滞功能，PA01作为比较器正端输入，VREFINT作为比较器负端输
入，PA00作为比较器的输出端口，通过调整PA01上的输入电压，观测PA00引脚上的电平变化。

Function descriptions:
This sample demonstrates the hysteresis function of the COMP comparator. 
PA01 is used as the positive input of the comparator, VREFINT is used as 
the negative input, and PA00 is the output port of the comparator. By 
adjusting the input voltage on PA01, the level change on the PA00 pin 
can be observed.
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
2. PA01输入小于1.1V电压，检测PA00输出低电平；
3. PA01输入大于1.3V电压，检测PA00输出高电平。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.When the input voltage on PA01 is less than 1.1V, check that the output 
on PA00 is low.
3.When the input voltage on PA01 is greater than 1.3V, check that the output 
on PA00 is high.
================================================================================
注意事项：

Notes:
================================================================================