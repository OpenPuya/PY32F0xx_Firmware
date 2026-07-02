================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的互补输出功能，一组互补共两路pwm输出，此样例没有实现死区功能。

Function descriptions:
This sample implements the complementary output function of the timer, a set of 
complementary total two pwm outputs, this sample does not implement the deadband 
function.
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
1. 下载并运行程序
2. 通过逻辑分析仪捕捉CH1、CH1N这两通道的电平，判断pwm输出信号是否正确

Example execution steps:
1. Download and run the programme
2. Capture the level of CH1 and CH1N through the logic analyser to determine 
whether the pwm output signal is correct.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
具体的通道和引脚对应关系如下：
CH1   ->  PA3
CH1N  ->  PA0

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
The specific channel and pin correspondences are as follows:
CH1 -> PA3
CH1N -> PA0
================================================================================