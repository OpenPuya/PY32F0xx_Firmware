================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的基本计数功能，以及演示了ARR自动重载功能，样例在定时器重载中断
中翻转LED灯
修改配置TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;使能自动
重载功能，新的ARR值在第四次进中断时生效，配置TimHandle.Init.AutoReloadPreload = 
TIM_AUTORELOAD_PRELOAD_DISABLE;禁止自动重载功能，新的ARR值在第三次进中断时生效,
生效后，LED灯每隔400ms翻转一次

Function descriptions:
This sample implements the basic counting function of the timer, as well as 
demonstrating the ARR auto-reload function, the sample interrupts the timer 
reload in the
The sample flips the LED in the timer reload interrupt.
Modify the configuration TimHandle.Init.AutoReloadPreload = 
TIM_AUTORELOAD_PRELOAD_ENABLE; to enable the auto reload function, the new 
ARR value will be set on the fourth interrupt entry.
Reload function, the new ARR value takes effect on the fourth incoming 
interrupt, configure TimHandle.Init.AutoReloadPreload = 
TIM_AUTORELOAD_PRELOAD_DISABLE; disable the auto-reeload function, the new 
ARR value will take effect at the third interrupt entry.
After the new ARR value takes effect at the third interrupt entry, the LEDs 
will flip every 400ms.
================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F003_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 编译下载程序并运行；
2. LED灯闪烁，用示波器观测LED引脚。
3. LED引脚在第三次翻转时，翻转间隔变为400ms

Example execution steps:
1. Compile and download the programme and run it;
2. the LED blinks and the LED pin is observed with an oscilloscope.
3. The LED pin flips for the third time and the flipping interval changes to 400ms
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