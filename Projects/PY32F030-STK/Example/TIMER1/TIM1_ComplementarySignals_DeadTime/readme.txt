================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的刹车功能，通过CH1(PA8)和CH1N(PA7)产生互补的PWM输出。当接收到
外部IO口(PA6)的刹车信号（低电平）时，PWM信号关闭。由于BDTR.AOE被置位，当刹车信号
被取消（高电平）时，PWM输出恢复。此样例实现了死区功能。

通过调整OCxE、CCxP、OISx、CCxNE、CCxNP、OISxN等配置，可以实现不同的刹车功能应用。

Function descriptions:
This sample demonstrates the brake function of the timer. It generates 
complementary PWM outputs using CH1 (PA8) and CH1N (PA7). When receiving the 
brake signal (low level) from the external IO port (PA6), the PWM signal is 
turned off. Due to BDTR.AOE being set, when the brake signal is canceled 
(high level), PWM output resumes. This sample implements the dead time feature.

By adjusting the configuration of OCxE, CCxP, OISx, CCxNE, CCxNP, OISxN, 
various brake function applications can be achieved.
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
2. 通过逻辑分析仪捕捉CH1(PA8)、CH1N(PA7)这两个通道的电平，可以看到互补的PWM输出；
3. 当PA6输入低电平时，CH1和CH1N无互补的PWM输出，即刹车信号生效。

Example execution steps:
1.Download and run the program.
2.Capture the levels of the two channels CH1 (PA8) and CH1N (PA7) through a 
logic analyzer to see the complementary PWM outputs.
3.when PA6 input is low, there is no complementary PWM output from CH1 and CH1N, 
i.e. brake signal is in effect.
================================================================================
注意事项：
CH1   ->  PA8
CH1N  ->  PA7
刹车输入 -> PA6
死区时间计算:
DTG[7:5]=0xx => DT=DTG[7:0] × Tdtg， Tdtg = TDTS；
DTG[7:5]=10x => DT=(64+DTG[5:0]) × Tdtg， Tdtg = 2
× TDTS；
DTG[7:5]=110 => DT=(32+DTG[4:0]) × Tdtg， Tdtg = 8
× TDTS；
DTG[7:5]=111 => DT=(32+DTG[4:0]) × Tdtg， Tdtg = 16
× TDTS；
例：若 TDTS = 125ns(8MHZ)，可能的死区时间为：
0 到 15875ns，若步长时间为 125ns；
16us 到 31750ns，若步长时间为 250ns；
32us 到 63us，若步长时间为 1us；
64us 到 126us，若步长时间为 2us；

Notes:
CH1  -> PA8
CH1N -> PA7
Brake input -> PA6

Dead time calculation:
DTG[7:5]=0xx => DT=DTG[7:0] × Tdtg, Tdtg = TDTS;
DTG[7:5]=10x => DT=(64+DTG[5:0]) × Tdtg, Tdtg = 2 × TDTS;
DTG[7:5]=110 => DT=(32+DTG[4:0]) × Tdtg, Tdtg = 8 × TDTS;
DTG[7:5]=111 => DT=(32+DTG[4:0]) × Tdtg, Tdtg = 16 × TDTS;

Example: If TDTS = 125ns (8MHz), the possible dead time ranges are:
0 to 15875ns, with a step time of 125ns;
16us to 31750ns, with a step time of 250ns;
32us to 63us, with a step time of 1us;
64us to 126us, with a step time of 2us.
================================================================================