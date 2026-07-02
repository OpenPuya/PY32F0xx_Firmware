================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的基本计数功能，以及演示了ARR自动重载功能，样例在定时器重载中断
中翻转LED灯修改main.c中的配置
TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;使能自动重载
功能，新的ARR值在第四次进中断时生效，配置TimHandle.Init.AutoReloadPreload = 
TIM_AUTORELOAD_PRELOAD_DISABLE;禁止自动重载功能，新的ARR值在第三次进中断时生效,
生效后，LED灯以1.875HZ的频率翻转

Function descriptions:
This sample implements the basic counting function of the timer, as well as 
demonstrates the ARR AutoReload function, the sample toggles the LED in the 
timer reload interrupt. Enable the auto-reload function by configuring 
TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE in main.c. 
The new ARR value takes effect the fourth time the interrupt is entered; 
configure TimHandle.Init. AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_DISABLE 
to disable the AutoReload function, the new ARR value will take effect in 
the third time into the interrupt, and after that, the LED will toggle at a 
frequency of 1.875HZ.
================================================================================
测试环境：
测试用板：PY32F002A_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F002A_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序并运行；
2. LED灯闪烁，用示波器观测LED引脚。
3. LED引脚在第三次翻转时，频率变为1.875Hz。

Example execution steps:
1.Compile and download the program.
2.The LED will toggle. Use an oscilloscope to observe the LED pin.
3.When the third toggle occurs, the period of the LED pin will change to 1.875Hz.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required

================================================================================