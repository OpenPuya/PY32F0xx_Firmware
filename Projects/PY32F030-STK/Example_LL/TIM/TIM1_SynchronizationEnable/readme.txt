================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM的同步触发模式。TIM3设置为主模式触发，TIM1设置从模式触发。程序复位
后TIM3开始计数，触发更新事件后向TIM1发送同步信号，TIM1开始计数，并在更新中断中翻转
LED。

Function descriptions:
This sample demonstrates the synchronous trigger mode of TIM. TIM3 is set as 
the master trigger mode, and TIM1 is set as the slave trigger mode. After the 
program is reset, TIM3 starts counting. After the update event is triggered, 
it sends a synchronization signal to TIM1. TIM1 starts counting and toggles 
the LED in the update interrupt.
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
2. 复位MCU后LED亮起，2s后LED开始翻转，翻转间隔为1s。

Example execution steps:
1.Compile and download the program to the MCU and run it.
After resetting the MCU, the LED will light up. After 2 seconds, the LED will 
start toggling with an interval of 1 second.
================================================================================
注意事项：

Notes:
================================================================================