================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的模拟看门狗功能，当开启看门狗的通道的电压值不在设定的上下限中，会
进入看门狗中断。

Function descriptions:
This sample demonstrates the analog watchdog function of the ADC. When the 
voltage value of the channel with the watchdog on is not in the set upper and 
lower limits, the will enter the watchdog interrupt.
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
2. PA0和PA1的电压值都小于0.4125V(供电电压为3.3V),不会进入看门狗中断，LED灯不亮；
3. PA0或PA1的电压值大于0.4125V(供电电压为3.3V)，进入看门狗中断，LED亮。

Example execution steps:
1.compile and download the program to the MCU and run it;
2.If the voltage values of both PA0 and PA1 are less than 0.4125V (with a supply 
voltage of 3.3V), the watchdog interrupt will not be triggered, and the LED will 
not light up.
3.If the voltage value of either PA0 or PA1 is greater than 0.4125V (with a 
supply voltage of 3.3V), the watchdog interrupt will be triggered, and the LED 
will turn on.
================================================================================
注意事项：

Notes:

================================================================================