================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了CRC校验功能，通过对一个数组里的数据进行校验，得到的校验值与理论校验
值进行比较，相等则LED灯亮，否则LED灯熄灭。

Function descriptions:
This sample demonstrates the CRC checksum function. It performs a checksum on 
the data in an array and compares the calculated checksum with the expected 
checksum. If they are equal, the LED turns on; otherwise, the LED turns off.
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
2. 观察LED灯是否亮起，如果灯亮表示运行成功，否则运行失败。

Example execution steps:
1.Compile and download the program to the MCU, and run it.
2.Observe if the LED turns on. If the LED is on, it indicates 
successful execution;
3.otherwise, it indicates a failure.
================================================================================
注意事项：

Notes:
================================================================================