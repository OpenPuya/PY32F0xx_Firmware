================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的互补输出功能，共有三组互补输出，即六路PWM输出。样例中并未实现死区
功能。

Function descriptions:
This sample demonstrates the complementary output feature of the timer, 
providing a total of three complementary output pairs, resulting in six PWM 
outputs. The sample does not implement the dead time feature. 
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
2. 通过逻辑分析仪捕捉上述六通道的电平，判断pwm输出信号是否正确。

Example execution steps:
1.Download and run the program.
2.Use a logic analyzer to capture the voltage levels of the six channels 
mentioned above to verify the correctness of the PWM outputs.
================================================================================
注意事项：
具体的通道和引脚对应关系如下：
CH1   ->  PA8
CH1N  ->  PA7
CH2   ->  PA9
CH2N  ->  PB0
CH3   ->  PA10
CH3N  ->  PB1

Notes:
The specific 
channel-to-pin mappings are as follows:
CH1   ->  PA8
CH1N  ->  PA7
CH2   ->  PA9
CH2N  ->  PB0
CH3   ->  PA10
CH3N  ->  PB1
================================================================================