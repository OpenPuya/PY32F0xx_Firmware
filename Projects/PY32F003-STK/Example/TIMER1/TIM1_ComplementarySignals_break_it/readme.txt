================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例实现了定时器的刹车功能，CH1和CH1N互补pwm输出，接收到外部IO口的刹车信号（低
电平）后，PWM信号关闭，由于BDTR.AOE置位，所以刹车信号取消（高电平）后，继续pwm输
出，此样例实现了死区功能。本样例开启了刹车中断，并在刹车中断里翻转LED灯。

通过调整OCxE,CCxP,OISx,CCxNE,CCxNP,OISxN的配置，可实现刹车功能的各种应用

Function descriptions:
This sample demonstrates the brake function of the timer. It generates 
complementary PWM outputs using CH1 and CH1N. When receiving the 
brake signal (low level) from the external IO port, the PWM signal is 
turned off. Due to BDTR.AOE being set, when the brake signal is canceled 
(high level), PWM output resumes. This sample implements the dead time feature.
The sample also enables the brake interrupt and toggles an LED in the brake 
interrupt handler.
By adjusting the configuration of OCxE, CCxP, OISx, CCxNE, CCxNP, OISxN, 
various brake function applications can be achieved.
================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
GCC版本： GNU Arm Embedded Toolchain 10.3-2021.10

Test environment:
Test board: PY32F003_STK
MDK Version: 5.28
IAR Version: 9.20
GCC Version: GNU Arm Embedded Toolchain 10.3-2021.10
================================================================================
使用步骤：
1. 下载并运行程序
2. 通过逻辑分析仪捕捉CH1(PA3)、CH1N(PA0)这两个通道的电平，可以看到互补的PWM输出；
3. 当PA6输入低电平时，CH1和CH1N无互补的PWM输出，即刹车信号生效。
4. 每产生一次刹车信号，LED灯就翻转一次。

Example execution steps:
1.Download and run the program.
2.Capture the levels of the two channels CH1 (PA3) and CH1N (PA0) through a 
logic analyzer to see the complementary PWM outputs.
3.when PA6 input is low, there is no complementary PWM output from CH1 and CH1N, 
i.e. brake signal is in effect.
4.The LED toggles over every time a brake signal is generated.
================================================================================
注意事项：
如果需要使用按键:
StartKit版本为V2.0以下,需将StartKit.h中的StartKitVersion 2 注释掉，并打开
StartKitVersion 1
StartKit版本为V2.0及以上版本,则无需操作
CH1   ->  PA3
CH1N  ->  PA0
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
If you need to use buttons:
StartKit version is below V2.0, you need to comment StartKitVersion 2 in
StartKit.h, and open StartKitVersion 1 
StartKit version is V2.0 and above, no operation is required
CH1 -> PA3
CH1N -> PA0
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