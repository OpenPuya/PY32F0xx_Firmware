================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了COMP比较器迟滞功能，PA03作为比较器正端输入，VREFINT作为比较器负端输入，
PA07作为比较器的输出端口，通过调整PA03上的输入电压，观测PA07引脚上的电平变化。

Function descriptions:
This sample demonstrates the hysteresis function of the COMP comparator. PA03 
serves as the positive input of the comparator, VREFINT serves as the negative 
input, and PA07 is the output port of the comparator. By adjusting the input 
voltage on PA03, the level change on pin PA07 can be observed.
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
2. 配置PA03输入1.1V电压，检测PA07应该输出低电平；
3. 配置PA03输入1.3V电压，检测PA07应该输出高电平。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Configure PA03 to input a voltage of 1.1V and check that PA07 should 
output a low level.
3.Configure PA03 to input a voltage of 1.3V and check that PA07 should 
output a high level.
================================================================================
注意事项：

Notes:

================================================================================