================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了通过软件方式将RESET引脚改为普通GPIO。

Function descriptions:
This sample demonstrates the functionality of changing the RESET pin to a 
general-purpose GPIO pin using software.
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
2. 将MCU断电并重新上电；
3. 按下按键，RST键变为GPIO功能，LED点亮；
4. 注释掉"RSTPIN_MODE_GPIO",打开"RSTPIN_MODE_RST",编译重新下载到MCU;
5. 将MCU断电并重新上电；
6. 按下按键，RST键变为RESET功能，LED点亮；

Example execution steps:
1.Compile and download the program to the MCU, and run it.
2.Power off and then power on the MCU.
3.Press the button,The RST button will function as a GPIO, and the LED will turn
on.
4.Comment out "RSTPIN_MODE_GPIO" and uncomment "RSTPIN_MODE_RST". Recompile 
and download the program to the MCU.
5.Power off and then power on the MCU.
6.Press the button,The RST button will return to its RESET function, and the LED
will turn on.
================================================================================
注意事项：
该样例将RST的按键改成GPIO功能，在使用其他样例前请将RST按键改回RST功能。

Notes:
This sample changes the RST button to function as a GPIO. Before using other 
samples, please restore the RST button to its RESET function.
================================================================================