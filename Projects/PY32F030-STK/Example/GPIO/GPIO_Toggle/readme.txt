================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了GPIO输出模式，配置LED引脚(PA11)为数字输出模式，并且每隔250ms翻转一次
LED引脚电平，运行程序，可以看到LED灯以2Hz的频率闪烁。

Function descriptions:
This sample demonstrates GPIO output mode. It configures the LED pin (PA11) as 
a digital output and toggles the LED pin level every 250ms. When the program 
runs, you can observe the LED blinking at a frequency of 2Hz.
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
2. 可观察到STK板上的LED以2Hz的频率闪烁。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.You can observe the LED on the STK board blinking at a frequency of 2Hz.
================================================================================
注意事项：

Notes:
================================================================================