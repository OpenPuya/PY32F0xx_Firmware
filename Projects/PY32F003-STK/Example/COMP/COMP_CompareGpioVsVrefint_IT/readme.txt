================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了COMP比较器功能，PA01作为比较器正端输入，VREFINT作为比较器负端输入，
PA06作为比较器的输出端口，通过调整PA01上的输入电压，观测PA06引脚上的电平变化
和LED翻转。

================================================================================
测试环境：
测试用板：PY32F003_STK
MDK版本： 5.28
IAR版本： 9.20
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. PA01输入1.1V电压，检测到PA06输出低电平；
3. PA01输入1.3V电压，检测到PA06输出高电平；
4. 每进一次比较器中断，翻转LED。

================================================================================
注意事项：


================================================================================