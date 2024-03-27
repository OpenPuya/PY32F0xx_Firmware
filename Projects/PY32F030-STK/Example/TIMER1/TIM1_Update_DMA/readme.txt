================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM1中使用DMA传输数据的功能，通过DMA从SRAM中搬运数据到ARR寄存器，
实现TIM1周期变化，在TIM1第一次溢出后，PA0会翻转，此时翻转间隔为400ms，DMA开始
搬运数据到TIM1_ARR，第二次PA0翻转间隔为400ms，第三次翻转间隔为100ms，第四次翻
转间隔为200ms，第五次翻转间隔为300ms，此时DMA搬运结束，后续翻转间隔均为300ms。

Function descriptions:
This sample demonstrates the functionality of using DMA to transfer data in 
Timer 1 (TIM1). DMA is used to move data from SRAM to the ARR register of TIM1, 
resulting in a changing period of TIM1. After the first overflow of TIM1, 
pin PA0 will toggle with an interval of 400ms. Once the DMA starts 
transferring data to TIM1_ARR, the second toggle interval of PA0 will 
be 400ms, the third will be 100ms, the fourth will be 200ms, and the fifth 
will be 300ms. After the DMA transfer is completed, the subsequent toggle 
intervals will remain at 300ms.
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
1. 下载并运行程序；
2. 通过逻辑分析仪或示波器捕捉PA0上翻转间隔；
3. 翻转间隔从400ms，变为100ms，200ms，300ms；
4. 变为300ms后，翻转间隔均为300ms。

Example execution steps:
1.Download and run the program.
2.Use a logic analyzer or an oscilloscope to capture the toggle interval 
on pin PA0.
3.Observe the toggle intervals changing from 400ms to 100ms, 200ms, and 300ms.
4.After the toggle interval becomes 300ms, the subsequent toggle intervals 
will remain at 300ms.
================================================================================
注意事项：

Notes:
================================================================================