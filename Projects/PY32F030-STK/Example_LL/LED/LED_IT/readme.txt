================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了LED的控制数码管显示的功能，样例中同时控制4个数码管，4个数码管的显示
内容可以在中断中实时修改。

Function descriptions:
This sample demonstrates the control of LEDs to display on a 4-digit display. 
The example simultaneously controls 4 digits, and the display content of the 
4-digit display can be modified in real-time in an interrupt.
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
2. 可观察到数码管的显示一直在循环更新。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Observe that the display on the 4-digit display is continuously 
updated in a loop.
================================================================================
注意事项：
1. 此样例需要STK板外接数码管
2. 数码管的COM0/COM1/COM2/COM3分别接STK板的PA15/PB3/PB4/PB5
3. 数码管的SEG A B C D E F G DP 分别接STK板的PB8/PA00/PA01/PA02/PA03/PA04/PA05/PA06
4. 使用中请确认所选的芯片型号，上述IO口是否都有引出

Notes:
1.This example requires an external 4-digit display connected to the STK board.
2.The COM0/COM1/COM2/COM3 pins of the 4-digit display are respectively connected to
PA15/PB3/PB4/PB5 of the STK board.
3.The SEG A B C D E F G DP pins of the 4-digit display are respectively connected to
PB8/PA00/PA01/PA02/PA03/PA04/PA05/PA06 of the STK board.
4.Please confirm the selected chip model and whether the above IO ports are all available
for use.
================================================================================