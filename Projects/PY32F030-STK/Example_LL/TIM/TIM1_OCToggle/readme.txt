================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了TIM1的输出比较模式。将捕获/比较通道1（CH1）的输出映射到PA8，开启捕获
/比较通道1（CH1）并设置为比较输出翻转模式，同时开启捕获/比较中断，每次计数值与比
较值匹配时翻转输出电平，在捕获/比较中断处理中翻转LED灯。

Function descriptions:
This sample demonstrates the output compare mode of TIM1. The output of 
capture/compare channel 1 (CH1) is mapped to pin PA8. Capture/compare 
channel 1 (CH1) is enabled and set to compare output toggle mode. 
Capture/compare interrupt is also enabled. Whenever the counter value 
matches the compare value, the output level will toggle. In the interrupt 
handler of capture/compare, the LED will also toggle.
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
2. LED灯每0.1s翻转一次；
3. 使用示波器观察PA8，频率为5Hz。

Example execution steps:
1.Compile and download the program to the MCU, and then run it.
2.The LED will toggle every 0.1 seconds.
3.Use an oscilloscope to observe pin PA8. The frequency should be 5Hz.
================================================================================
注意事项：

Notes:
================================================================================