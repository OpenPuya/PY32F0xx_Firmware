================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了LPTIM单次计数功能，配置LPTIM计数周期为0.5s，在ARR中断回调函数中翻转LED
灯，并再次启动单次计数模式。

Function descriptions:
This sample demonstrates the single-count function of LPTIM. It configures the 
LPTIM count period as 0.5s. In the ARR interrupt callback function, it toggles 
the LED and restarts the single-count mode.
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
1. 编译下载程序到MCU，并运行
2. LED灯以1Hz的频率闪烁

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The LED will blink at a frequency of 1Hz.
================================================================================
注意事项：

Notes:
================================================================================