================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了TIM1和TIM3级联成32位计数器，TIM3做主机，TIM3的溢出信号作为TIM1的输入
时钟。TIM3每1ms计数一次，计数1000次后产生溢出，TIM1计数一次。

================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行
2. 串口每秒打印一次TIM1计数值，从0~10依次递增

================================================================================
注意事项：
STK板        USB转TTL模块
PA02(TX) --> RX
PA03(RX) --> TX
GND      --> GND

波特率:115200

================================================================================