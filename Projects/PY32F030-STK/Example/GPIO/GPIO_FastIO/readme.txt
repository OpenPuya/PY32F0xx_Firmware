================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
本样例主要展示GPIO的FAST IO输出功能。FAST IO速度可以达到单周期翻转速度。

Function descriptions:
This sample demonstrates the FAST IO output functionality of GPIO. FAST IO 
speed can achieve single-cycle toggling speed.
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
2. GPIO每个时钟周期输出翻转一次，可观测到端口PA11输出波形输出波形频率为12MHz。


Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The GPIO output toggles once per clock cycle, and you can observe the output 
waveform on pin PA11 with a frequency of 12MHz.
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