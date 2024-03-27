================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示RTC的闹钟中断功能，在数组aShowTime中显示当前时间，在数组aShowDate中
显示当前日期，当达到闹钟值时，LED灯会亮起。

Function descriptions:
This sample demonstrates the alarm interrupt function of the RTC. It displays 
the current time in the array aShowTime and the current date in the array 
aShowDate. When the alarm value is reached, the LED will light up.
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
1. 编译并下载程序到MCU；
2. 程序运行后，大概30s，LED灯亮起。

Example execution steps:
1.Compile and download the program to the MCU;
2.After the program is running, the LED will light up after approximately 
30 seconds.
================================================================================
注意事项：

Notes:
================================================================================