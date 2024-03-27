================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器轮询功能，PA01作为比较器正端输入，VREFINT作为比较器负端输
入，PA06作为比较器的输出端口，通过调整PA01上的输入电压，观测PA06引脚上的电平变化。

Function descriptions:
This sample demonstrates the polling function of the COMP comparator. PA01 
serves as the positive input of the comparator, VREFINT serves as the negative 
input, and PA06 is the output port of the comparator. By adjusting the input 
voltage on PA01, the level change on pin PA06 can be observed.
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
2. 配置PA01输入1.1V电压，检测PA06应该输出低电平；
3. 配置PA01输入1.3V电压，检测PA06应该输出高电平。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Configure PA01 to input a voltage of 1.1V and check that PA06 should output 
a low level.
3.Configure PA01 to input a voltage of 1.3V and check that PA06 should output 
a high level.
================================================================================
注意事项：

Notes:

================================================================================