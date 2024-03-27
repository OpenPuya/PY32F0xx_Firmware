================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例演示了主机I2C通过DMA方式进行通讯，从机使用EEPROM外设芯片P24C32，按下user按
键，主机先向从机写15bytes数据为0x1~0xf，然后再从EEPROM中将写入的数据读出，读取成
功后，主机板上的小灯处于“常亮”状态。

Function descriptions:
This sample demonstrates I2C communication using DMA on the master. The slave 
device uses the EEPROM peripheral chip P24C32. When the user button is pressed 
on the master, the master writes 15 bytes of data (0x1 to 0xf) to the slave. 
Then, the master reads the written data from the EEPROM. After successful data 
retrieval, the LED on the master board will remain constantly lit.
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
1. 编译下载程序到MCU；
2. 先复位从机，然后再复位主机
3. 复位完成后，按下主机user按键，先写15bytes数据0x1-0xf
4. 延时100ms后，从eeprom读取15bytes数据
5. 观察主机的LED灯，当主机LED灯由常暗转为常亮状态，则表明主机收发数据成功；当
主机机LED灯处于闪烁状态，则表明主机收发数据失败。

Example execution steps:
1.Compile and download the program to the MCU.
2.Reset the slave first, then reset the master.
3.After the reset is complete, press the user button on the master. The master 
will write 15 bytes of data (0x1 to 0xf) to the slave.
4.After a delay of 100ms, the master will read 15 bytes of data from the EEPROM.
5.Observe the LED on the master board. When the LED on the master changes from 
being constantly dim to constantly lit, it indicates successful data 
transmission and reception. If the LED on the master is blinking, it means 
there was a failure in data transmission or reception.
================================================================================
注意事项：
PA9     ------> I2C_SCL
PA10    ------> I2C_SDA

Notes:
PA9     ------> I2C_SCL
PA10    ------> I2C_SDA
================================================================================