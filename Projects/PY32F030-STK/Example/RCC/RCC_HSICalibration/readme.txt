================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例使用外接1KHz高精度的时钟来校准内部HSI。

Function descriptions:
This sample uses an external 1KHz high-precision clock to calibrate 
the internal HSI.
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
1. 编译下载程序到MCU，并运行。
2. PA4接1KHz高精度时钟。
3. 按下按键，LED亮，开始校准HSI。
4. LED闪烁表明校准完成，MCO1(PA8)输出3MHz波形。
Example execution steps:
1.Compile and download the program to the MCU and run it.
2.PA4 connected to 1KHz high-precision clock.
3.Press the button and the LED will light up to start calibrating the HSI.
4.LED flashing indicates calibration is complete, and MCO1 (PA8) outputs 
a 3MHz waveform.
================================================================================
注意事项：
PA4输入1Khz高精度时钟。

Notes:
PA4 input 1Khz high precision clock.
================================================================================