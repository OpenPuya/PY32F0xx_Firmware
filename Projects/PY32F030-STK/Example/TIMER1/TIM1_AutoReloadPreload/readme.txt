================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的基本计数功能，以及演示了ARR自动重载功能，样例在定时器重载中断
中翻转LED灯。通过在main.c中配置TimHandle.Init.AutoReloadPreload = 
TIM_AUTORELOAD_PRELOAD_ENABLE使能自动重载功能，新的ARR值在第四次进中断时生效；
配置TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE时禁止自
动重载功能，新的ARR值在第三次进中断时生效,生效后，LED灯以2.5HZ的频率翻转。

Function descriptions:
This sample implements the basic counting function of the timer, as well as 
demonstrates the ARR AutoReload function, the sample toggles the LED in the 
timer reload interrupt. Enable the auto-reload function by configuring 
TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE in main.c. 
The new ARR value takes effect the fourth time the interrupt is entered; 
configure TimHandle.Init. AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_DISABLE 
to disable the AutoReload function, the new ARR value will take effect in 
the third time into the interrupt, and after that, the LED will toggle at a 
frequency of 2.5 HZ.
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
2. LED灯闪烁，用示波器观测PA11引脚；
3. PA11在第三次翻转时，周期变为2.5Hz。

Example execution steps:
1.Compile and download the program.
2.The LED will toggle. Use an oscilloscope to observe the PA11 pin.
3.When the third toggle occurs, the period of the PA11 pin will change to 2.5Hz.
================================================================================
注意事项：

Notes:
================================================================================