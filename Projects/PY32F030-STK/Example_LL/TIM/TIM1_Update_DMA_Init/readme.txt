================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM1中使用DMA传输数据的功能,通过DMA从SRAM中搬运数据到ARR寄存器实现
TIM1更新周期变化,TIM1第一次溢出后LED会翻转,此次翻转时间间隔为1000ms,DMA将数据搬
运到TIM1_ARR,第二次LED翻转间隔为900ms,以此类推,最后LED翻转间隔为100msDMA搬运结束,
LED保持100ms的翻转间隔闪烁。

Function descriptions:
This sample demonstrates the use of DMA to transfer data in TIM1, copying data 
from SRAM to the ARR register to achieve varying update periods for TIM1. After 
the first overflow of TIM1, the LED will toggle, with a time interval of 1000ms. 
After the data is transferred to TIM1_ARR using DMA, the LED toggling interval 
gradually decreases: 900ms, 800ms, 700ms, 600ms, 500ms, 400ms, 300ms, 200ms, 
100ms. Finally, the LED will blink with a constant toggling interval of 100ms.
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
2. 使用示波器捕捉PA11波形；
3. 电平保持时间为：1000ms,900ms,800ms,700ms,600ms,500ms,400ms,300ms,200ms,100ms,
100ms...；
4. LED闪烁逐渐加快，最后保持5Hz频率闪烁。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.Use an oscilloscope to capture the waveform of PA11.
3.The duration of each level is as follows: 1000ms, 900ms, 800ms, 700ms, 
600ms, 500ms, 400ms, 300ms, 200ms, 100ms, 100ms...
4.The LED blinking will gradually accelerate and finally maintain a frequency 
of 5Hz.
================================================================================
注意事项：

Notes:
================================================================================