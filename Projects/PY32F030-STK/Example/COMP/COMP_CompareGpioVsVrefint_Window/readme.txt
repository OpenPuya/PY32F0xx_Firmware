================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了比较器窗口功能，PA01作为比较器正端输入，内部通过COMP1和COMP2的正极
相连，PA1输入大于VREF的电压，LED以200ms的间隔进行翻转；PA1输入小于1/4VREF的电压，
LED熄灭；PA1输入的电压小于VREF大于1/4VREF，LED常亮。

Function descriptions:
This sample demonstrates the window function of the comparator. PA01 serves 
as the positive input of the comparator, and it is internally connected to 
the positive terminals of COMP1 and COMP2. When PA1 inputs a voltage greater 
than VREF, the LED toggles every 200ms. When PA1 inputs a voltage less than 
1/4VREF, the LED turns off. When PA1 inputs a voltage less than VREF but 
greater than 1/4VREF, the LED remains on.
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
2. 配置PA01输入3.3V，LED以200ms的间隔进行翻转；
3. 配置PA01输入1.0V，LED常亮；
4. 配置PA01输入0V，LED熄灭。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Configure PA01 to input 3.3V, and the LED toggles every 200ms.
3.Configure PA01 to input 1.0V, and the LED remains on.
4.Configure PA01 to input 0V, and the LED turns off.
================================================================================
注意事项：

Notes:

================================================================================