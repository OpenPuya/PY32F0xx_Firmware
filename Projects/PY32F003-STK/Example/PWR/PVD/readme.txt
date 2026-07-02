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
2. PB07输入0V时，进入PVD中断，LED灯亮，PB07悬空时（内部上拉相当于接入3.3V）LED灯
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
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
1. 本样例中PB07引脚被配置为上拉，因此PB07悬空时PVDO的状态为0。
2. 低功耗应用中，PVD时钟源应该选择LSC，否则无法正常工作。

Notes:
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
1. The PB07 pin is configured as pull-up in this sample, so the state of PVDO 
is 0 when PB07 is suspended.
2. In low-power applications, the PVD clock source should be selected as LSC, 
otherwise it will not work properly.
================================================================================