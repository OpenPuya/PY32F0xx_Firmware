================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了IWDG看门狗功能，配置看门狗重载计数值，计数1s后复位，然后通过调整每次
喂狗的时间（main函数while循环中代码），可以观察到，如果每次喂狗时间小于1s，程序
能一直正常运行（LED灯闪烁），如果喂狗时间超过1s，程序会一直复位（LED灯不亮）。

Function descriptions:
This sample demonstrates the IWDG watchdog function. It configures the watchdog 
reload counter value to reset after counting for 1 second. By adjusting the 
time for feeding the watchdog (code in the main function's while loop), you 
can observe that if the feeding time is less than 1 second, the program will 
continue to run normally (LED blinking), but if the feeding time exceeds 1 
second, the program will keep resetting (LED off).
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
2. 观察到LED灯闪烁；
3. 修改程序（将main函数while循环中LL_mDelay()的参数该为1100，即配置喂狗时间为1.1s）；
4. 重新编译下载程序到MCU，并运行；
5. 观察到LED灯不亮。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Observe the LED blinking.
3.Modify the program toconfigure the feeding time to be 1.1 seconds (Change the 
parameter "900" of LL_mDelay() to parameter "1100" in the while loop of the main 
function.).
4.Recompile and download the program to the MCU and run it.
5.Observe that the LED does not light up.
================================================================================
注意事项：

Notes:
================================================================================