================================================================================
                                样例使用说明
================================================================================
功能描述：
此样例演示了LED的控制数码管显示的功能，样例中同时控制4个数码管，4个数码管的显示
内容可以在中断中实时修改。

================================================================================
测试环境：
测试用板：PY32F030_STK
MDK版本： 5.28
IAR版本： 9.20
================================================================================
使用步骤：
1. 编译下载程序到MCU，并运行；
2. 可观察到数码管的显示一直在循环更新；


================================================================================
注意事项：
1. 此样例需要STK板外接数码管
2. 数码管的COM0/COM1/COM2/COM3分别接STK板的PA15/PB3/PB4/PB5
3. 数码管的SEG A B C D E F G DP 分别接STK板的PB8/PA00/PA01/PA02/PA03/PA04/PA05/PA06
4. 使用中请确认所选的芯片型号，上述IO口是否都有引出


================================================================================