================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了IWDG看门狗功能，配置看门狗重载计数值，计数1s后复位，然后通过调整每次
喂狗的时间（main函数while循环中代码），可以观察到，如果每次喂狗时间小于1s，程序
能一直正常运行（LED灯闪烁），如果喂狗时间超过1s，程序会一直复位（LED灯熄灭）。

Function descriptions:
This sample demonstrates the use of the IWDG (Independent Watchdog) 
functionality. The watchdog is configured with a reload value, and the system 
will be reset when the watchdog counter reaches 1 second. By adjusting the time 
interval between each watchdog feed (located in the main function's while loop), 
the following observations can be made: if the watchdog is fed within an 
interval shorter than 1 second, the program will continue running normally 
(LED blinking); if the feeding interval exceeds 1 second, the program will be 
reset by the watchdog timer (LED turned off).
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
2. 可观察到LED能正常亮起；
3. 修改程序（main函数while循环中注释代码），配置喂狗时间为1.1s；
4. 重新编译下载程序到MCU，并运行；
5. 可观察到LED不能正常亮起。

Example execution steps:
1.Compile and download the program to the target MCU and run it.
2.Observe if the LED lights up normally.
3.Modify the program (commented code in the main function's while loop) to set 
the watchdog feeding interval to 1.1 seconds.
4.Recompile and download the program to the target MCU, and run it.
5.Observe if the LED fails to light up normally.
================================================================================
注意事项：

Notes:
================================================================================