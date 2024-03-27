================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例配置系统时钟为LSI，并通过MCO（PA08）引脚输出，注意系统时钟切换为LSI之前，要
求把systick中断关闭掉，因为systick中断默认是1ms一次中断，由于LSI时钟频率过低，
systick中断会导致程序无法正常运行。

Function descriptions:
This sample configures the system clock as LSI and outputs it through the 
MCO (PA08) pin. Note that before switching the system clock to LSI, it is 
required to disable the systick interrupt because the systick interrupt is 
set to trigger every 1ms by default. Due to the low frequency of LSI clock, 
the systick interrupt can cause the program to malfunction.
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
2. 按下用户按键；
3. 用示波器监测PA08引脚上的频率，观察是否和配置的LSI频率一致。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Press the user button.
3.Use an oscilloscope to monitor the frequency on the PA08 pin and observe if 
it matches the configured LSI frequency.
================================================================================
注意事项：
1. 样例中默认启动的系统时钟是HSI，只有按下按键后，系统时钟才会切换到LSI。

Notes:
1.By default, the sample starts with the system clock as HSI. Only after 
pressing the user button, the system clock will switch to LSI.
================================================================================