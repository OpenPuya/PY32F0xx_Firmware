================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了WWDG的 窗口看门狗功能，配置WWDG的窗口上限（下限固定是0x3F），程序中
通过delay延时函数，确保程序是在WWDG计数窗口内进行喂狗动作，通过LED灯闪烁，可以判
断窗口内喂狗并未产生复位。

Function descriptions:
This sample demonstrates the window watchdog (WWDG) function. The upper limit 
of the WWDG window is configured (the lower limit is fixed at 0x3F). In the 
program, a delay function is used to ensure that the watchdog feeding action 
occurs within the WWDG counting window. The LED blinking indicates whether 
the watchdog is fed within the window, thereby verifying that no reset occurs.
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
1. 编译下载程序并运行；
2. 程序默认会在窗口时间内喂狗，程序不会复位，LED灯一致闪烁；
3. 注释掉宏定义”#WINDOW_IN",打开宏定义“WINDOW_UPPER”，重新编译下载并运行；
4. 程序会一直复位,LED灯循环点亮4s，熄灭500ms；
5. 注释掉宏定义”#WINDOW_UPPER",打开宏定义“WINDOW_LOWER”,重新编译下载并运行；
6. 程序会一直复位,LED灯循环点亮4s，熄灭500ms。

Example execution steps:
1.Compile and download the program and run it.
2.By default, the program will feed the watchdog within the window time, and 
the program will not reset. The LED will continue to blink.
3.Comment out the macro definition "//WINDOW_IN" and uncomment the macro 
definition "WINDOW_UPPER", then recompile, download, and run the program.
4.The program will continuously reset, and the LED will cycle on for 4 seconds 
and off for 500 milliseconds.
5.Comment out the macro definition "//WINDOW_UPPER" and uncomment the macro 
definition "WINDOW_LOWER", then recompile, download, and run the program.
6.The program will continuously reset, and the LED will cycle on for 4 seconds 
and off for 500 milliseconds.
================================================================================
注意事项：

Notes:
================================================================================