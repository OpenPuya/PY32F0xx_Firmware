================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示系统时钟切换功能，样例中配置系统时钟从HSI切换到HSE，并通过MCO（PA08）引
脚输出系统时钟。

Function descriptions:
This sample demonstrates the system clock switching functionality. The sample 
configures the system clock to switch from HSI to HSE and outputs the system 
clock through the MCO (PA08) pin.
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
2. 用示波器监测PA08引脚上的频率，MCU启动后一开始输出HSI时钟，频率是16MHz，按
下用户键后，输出HSE时钟。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Use an oscilloscope to monitor the frequency on the PA08 pin. After MCU 
starts, it initially outputs the HSI clock with a frequency of 16MHz. 
Press the user button to switch to the HSE clock.
================================================================================
注意事项：

Notes:

================================================================================