================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的重装载功能，配置计数周期为1s，在ARR中断回调函数中翻转LED。

Function descriptions:
This sample demonstrates the reload function of TIM1. It configures the 
counting period as 1 second and toggles the LED in the ARR interrupt callback 
function.
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
2. LED每过1s翻转一次。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The LED will toggle every 1 second.
================================================================================
注意事项：

Notes:
================================================================================