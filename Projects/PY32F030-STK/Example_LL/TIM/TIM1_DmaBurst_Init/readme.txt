================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的DMA Burst传输，配置TIM1为PWM模式，更新中断触发DMA传输请求。每次
产生更新中断时将TIM1DataBuff[]中的值按顺序写入RCR和CCR1寄存器，改变PWM脉冲的占空
比和该占空比的脉冲数量。

Function descriptions:
This sample demonstrates the DMA Burst transfer of TIM1. It configures TIM1 
in PWM mode and triggers DMA transfer requests on update interrupt. Each time 
an update interrupt occurs, the values in TIM1DataBuff[] are sequentially 
written to RCR and CCR1 registers, changing the duty cycle and the number 
of pulses for the PWM waveform.
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
2. 使用逻辑分析仪观察引脚PA8的波形；
3. 可以观察到2个10%占空比的脉冲，2个20%，3个30%，4个40%...以此类推直到稳定在90%。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.Use a logic analyzer to observe the waveform on pin PA8.
3.You will observe a sequence of pulses with increasing duty cycle: 2 pulses 
with 10% duty cycle, 2 pulses with 20% duty cycle, 3 pulses with 30% duty 
cycle, 4 pulses with 40% duty cycle, and so on until it stabilizes at 90% 
duty cycle.
================================================================================
注意事项：

Notes:
================================================================================