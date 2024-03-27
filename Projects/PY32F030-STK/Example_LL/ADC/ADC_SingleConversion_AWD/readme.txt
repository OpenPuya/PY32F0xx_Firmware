================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的模拟看门狗功能，PA4为模拟输入，当PA4的电压值不在设定的上下限中，
会进入看门狗中断。

Function descriptions:
This sample demonstrates the analog watchdog function of the ADC. PA4 is 
an analog input,and when the voltage value of PA4 is not within the set 
upper and lower limits, it will enter the watchdog interrupt.
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
2. PA4的电压值小于1.65V(供电电压为3.3V),LED灯熄灭；
3. PA4的电压值大于1.65V(供电电压为3.3V),LED灯会一直闪烁。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.If the voltage value of PA4 is less than 1.65V (the supply voltage 
is 3.3V), the LED will be off.
3.If the voltage value of PA4 is greater than 1.65V (the supply voltage 
is 3.3V), the LED will blink continuously.
================================================================================
注意事项：

Notes:
================================================================================