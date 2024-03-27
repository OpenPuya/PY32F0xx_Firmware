================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
定时器1的使能由定时器3控制，当定时器3计数时，LED会常亮，当定时器3发生更新事件时，
更新事件会触发定时器1，定时器1开始计数后，LED会以5Hz的频率进行翻转。

Function descriptions:
This sample demonstrates the functionality where Timer 1 is enabled by Timer 3. 
When Timer 3 starts counting, the LED remains constantly on. When Timer 3 
triggers an update event, it enables Timer 1 to start counting. Once Timer 1 
starts counting, the LED toggles at a frequency of 5Hz.
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
1. 下载程序并运行；
2. 运行程序，并在仿真模式下查看。初始状态下，Timer 1不会计数。当Timer 3开始计数后，
LED保持常亮。
3. 当Timer 3发生更新事件时，触发Timer 1开始计数。Timer 1开始计数后，LED以5Hz的频率
进行翻转。

Example execution steps:
1.Compile and download the program.
2.Run the program and observe in simulation mode. Initially, Timer 1 does not 
count. When Timer 3 starts counting, the LED remains constantly on.
3.When Timer 3 triggers an update event, it enables Timer 1 to start counting. 
Once Timer 1 starts counting, the LED toggles at a frequency of 5Hz.
================================================================================
注意事项：
主频为8M

Notes:
The system frequency is 8MHz.
================================================================================