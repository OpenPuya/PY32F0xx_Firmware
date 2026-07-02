================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的重装载功能和自动重载预装载功能，在初始化阶段配置重载值为1000，
在ARR中断回调函数中重新设置重载值为500。每次进入中断时翻转LED。
可以通过注释main.c中LL_TIM_EnableARRPreload(TIM1); 代码关闭自动重载预装载
功能。
若关闭自动重载预装载功能，新的重载值将在第一次进入中断后立即生效，则LED引脚前1次翻转
为1000ms后续保持500ms。
若开启自动重载预装载功能，新的重载值将在下一次进入中断后生效，则LED引脚前2次翻转为
1000ms后续保持500ms。

Function descriptions:
This sample demonstrates the reload function and the auto-reload preload function 
of TIM1. configure the reload value to 1000 during the initialisation phase.
The reload value is reset to 500 in the ARR interrupt callback function. flipping 
the LED each time an interrupt is entered.
You can turn off the automatic reload preload by commenting the 
LL_TIM_EnableARRPreload(TIM1); code in main.c.
function in main.c.
If you disable the automatic reload preload function, the new reload value will 
take effect immediately after the first interrupt entry, then the first flip-flop 
of the LED pin will be 1000ms and the subsequent flip-flops will be 500ms.
The first flip of the LED pin will be 1000ms and the subsequent hold will be 500ms.
If the auto reload preload function is enabled, the new reload value will take
 effect after the next interrupt entry, then the first 2 times of LED pin flip-flop 
 will be 1000ms and then hold for 500ms. 1000ms and then hold for 500ms.
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
1. 编译下载程序到MCU，并运行
2. 使用示波器观察LED引脚，前2（或1）次翻转间隔为1000ms，后续为500ms
3. LED保持1Hz的频率闪烁

Example execution steps:
1. Compile and download the programme to the MCU and run it.
2. Use an oscilloscope to observe the LED pins, the first 2 (or 1) flip-flops 
are at 1000ms intervals, and the subsequent ones are at 500ms.
3. Keep the LED blinking at 1Hz
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