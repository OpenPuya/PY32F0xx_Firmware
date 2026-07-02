================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了使用TIM1输出频率为10Hz占空比为50%的PWM波形及其互补信号，并实现了250ns
的死区和刹车功能。

Function descriptions:
This sample demonstrates the generation of three PWM waveforms with frequencies 
of 10Hz and duty cycles of 25%, 50%, and 75% using TIM1. It also generates their 
complementary signals and implements a 250ns dead-time and brake function.
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
1. 编译下载程序到MCU，并运行
2. 将PA6引脚接低电平
3. 使用逻辑分析仪观察引脚PA3，PA7的波形
4. 将PA6引脚接高电平，PWM停止输出

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Set pin PA6 to the low logic level.
3.Use a logic analyzer to observe the waveforms on pins PA3/PA7.
4.Set pin PA6 to a high logic level to stop PWM output.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
CH1  -> PA3 占空比：50%
CH1N -> PA7 占空比：50%

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
CH1  -> PA3 Duty cycle：50%
CH1N -> PA7 Duty cycle：50%
================================================================================