================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了时钟输出功能，可输出HSI波形。

Function descriptions:
This sample demonstrates the clock output function, which can output 
the HSI waveform.
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
1. 编译下载程序到MCU，并运行；
2. 可由示波器观察到PA01输出HSI波形（24MHz）。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The HSI waveform (24M) output from PA01 can be observed by the oscilloscope.
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