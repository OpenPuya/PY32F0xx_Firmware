================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了在TIM1中使用DMA连续两次burst传输数据的功能，burst每传输一次更新三
个寄存器，PSC,ARR,RCR，在更新事件中断中，PA0会进行翻转，通过逻辑分析仪监测，
可看到PA0的翻转间隔会从第一次的400ms，第二次400ms，第三次20ms,第四次及后续变为
200us，此时两次burst传输完成，并且PCS,ARR,RCR均更新完毕。

Function descriptions:
This sample demonstrates the functionality of using DMA to perform consecutive 
burst data transfers in TIM1. Each burst transfer updates three registers: PSC, 
ARR, and RCR. In the update event interrupt, PA0 will toggle. By using a logic 
analyzer, you can observe that the interval between PA0 toggles will be 400ms 
for the first and second time, 20ms for the third time, and 200us for the 
fourth time onwards. This indicates that the two burst transfers are completed, 
and PSC, ARR, RCR are all updated.
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
2. 通过逻辑分析仪示波器捕捉PA0上翻转间隔；
3. 翻转间隔从400ms,接着变为20ms,最后变为200us；
4. 变为200us后，翻转间隔均为200us。

Example execution steps:
1.Download and run the program.
2.Capture the interval of PA0 toggles using a logic analyzer.
3.The toggle interval starts at 400ms, then changes to 20ms, and finally 
becomes 200us.
4.Once it becomes 200us, the toggle interval remains at 200us.
================================================================================
注意事项：

Notes:
================================================================================