================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了DMA从SRAM到SRAM传输数据的功能（SRAM和外设之间传输的样例请参考相关外设
样例工程）。

Function descriptions:
This sample demonstrates the functionality of transferring data from SRAM to 
SRAM using DMA (for examples of data transfer between SRAM and peripherals, 
please refer to the relevant peripheral sample projects).
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
2. LED灯常亮，表明DMA传输完成并且数据正确；
3. LED灯闪烁，表明DMA传输出错或者DMA的数据传输的不正确。

Example execution steps:
1.Compile and download the program to the MCU and run it.
2.The LED remains on, indicating that the DMA transfer is complete and the 
data is correct.
3.The LED blinks, indicating an error in DMA transfer or incorrect data 
transfer.
================================================================================
注意事项：

Notes:

================================================================================