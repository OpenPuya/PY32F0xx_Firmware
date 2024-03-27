================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了PVD电压检测功能，样例中配置PB07引脚的电压与VREF(1.2v)进行比较，当PB07
引脚的电压高于VREF时,LED灯灭，当低于VREF时，LED灯亮。

Function descriptions:
This sample demonstrates the PVD voltage detection feature. In the sample, the 
voltage on pin PB07 is compared with VREF (1.2V). When the voltage on PB07 is 
higher than VREF, the LED will be turned off. When the voltage is lower than 
VREF, the LED will be turned on.
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
2. PB07输入0V时，进入PVD中断，LED灯亮，PB07悬空时（内部Pull-up相当于接入3.3V）LED灯
灭；
3. 再次输入0V，LED灯亮。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.When the voltage on PB07 is 0V, it will trigger the PVD interrupt and the 
LED will be turned on. When PB07 is left floating (internally pulled up 
to 3.3V), the LED will be turned off.
3.Input 0V again, and the LED will be turned on.
================================================================================
注意事项：
本例程中PA11引脚默认Pull-up，因此默认PVDO状态为0

Notes:
In this example, pin PA11 is pulled up by default, so the default PVDO state is 0.
================================================================================