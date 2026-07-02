================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的模拟看门狗功能。

Function description:
This sample demonstrates the analogue watchdog function of the ADC.
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
1. 编译下载程序到MCU，并运行；
2. PA0和PA1的电压值都小于0.4125V(供电电压为3.3V),不会进入看门狗中断，LED灯不亮；
3. PA0或PA1的电压值大于0.4125V(供电电压为3.3V)，进入看门狗中断，LED亮。

Example execution steps:
1. Compile and download the programme to MCU and run it;
2. PA0 and PA1 voltage value is less than 0.4125V (supply voltage is 3.3V), will 
not enter the watchdog interrupt, the LED will not light up;
3. The voltage value of PA0 or PA1 is greater than 0.4125V (supply voltage 
is 3.3V), it will enter the watchdog interrupt and the LED will be on.
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