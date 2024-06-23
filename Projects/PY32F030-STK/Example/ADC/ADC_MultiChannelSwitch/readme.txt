================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了ADC的多通道切换。

Function descriptions:
This sample demonstrates the multichannel switching of ADC.
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
1. 编译并下载程序；
2. 串口先打印一次通道5(PA5)的电压值
3. 之后切换到通道4(PA4)转换并打印其电压值.
4. 1s后又切换回通道5

Example execution steps:
1. Compile and download the program;
2. The serial port prints the voltage value of channel 5(PA5) first.
3. Then switch to channel 4(PA4) to convert and print its voltage value.
4. Switch back to channel 5 after 1 second
================================================================================
注意事项：
通过USB转TTL模块连接PC与STK板,STK板与USB转TTL模块的连线方式如下；
STK板        USB转TTL模块
PA2(TX)  -->  RX
PA3(RX)  -->  TX
GND      -->  GND

Notes:
Connect the PC to the STK board through the USB to TTL module, the connection
between the STK board and the USB to TTL module is as follows:
STK board      USB to TTL module
PA2(TX)  -->  RX
PA3(RX)  -->  TX
GND      -->  GND
================================================================================