================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例是利用DMA对串口外设接口（SPI）与外部设备以全双工串行方式进行通信的演示,此
接口设置为从模式。主机通过MOSI引脚发送数据,从MISO引脚接收从机的数据，数据以主机
提供的SCK沿同步被移位，完成全双工通信。

Function descriptions:
This sample demonstrates the communication between the serial peripheral 
interface (SPI) and an external device in full-duplex mode using DMA. The 
SPI interface is configured as the slave. The host sends data through the 
MOSI pin, and receives data from the slave through the MISO pin. The data 
is shifted synchronously with the SCK provided by the host, achieving 
full-duplex communication.
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
使用步骤:
1.选择两块PY32F030_STK板，一块作为主机，一块作为从机；
2.编译下载从机程序（本样例程序）；
3.编译下载主机程序SPI_TwoBoards_FullDuplexMaster_DMA_Init；
4.主机与从机引脚连接(箭头指向为信号传输方向) 
主机MASTER：         从机SLAVE：
SCK(PB3)   ----->    SCK(PB3)
MISO(PB4)  <-----    MISO(PB4)
MOSI(PB5)  ----->    MOSI(PB5)
GND       <----->    GND
5.主从机上电；
6.按下从机复位按键先运行从机程序，再按下主机用户按键运行主机程序；
7.观察到主从机绿灯都保持“常亮”则通信成功，否则“闪烁”通信失败。

Example execution steps:
1.Prepare two PY32F030_STK development boards, one as the host and the 
other as the slave.
2.Compile and download the slave program (this sample program) to the 
slave development board.
3.Compile and download the host program 
"SPI_TwoBoards_FullDuplexMaster_DMA_Init".
4.onnect the pins between the host and the slave (direction indicated 
by the arrow):
Host (MASTER): Slave (SLAVE):
SCK (PB3) -----> SCK (PB3)
MISO (PB4) <----- MISO (PB4)
MOSI (PB5) -----> MOSI (PB5)
GND <-----> GND
5.Power on the host and the slave.
6.Press the reset button on the slave to run the slave program first, 
then press the user button on the host to run the host program.
7.Observe that the green LED indicators on both the host and the slave 
remain lit, indicating successful communication. If the LED indicators 
blink, it means communication has failed.
================================================================================
注意事项:
1.必须先按从机复位按键使从机程序先运行，再按主机用户按键开始运行主机程序，否则会
导致主从机通信失败。
2.主机模式可通过程序设置IO控制方式为DMA方式、中断方式和查询方式
3.NSS引脚只需要在使用NSS硬件方式时连接（本样例使用的是NSS软件方式，无需连接NSS引
脚）

Notes:
1.It is necessary to press the reset button on the slave to run the slave program 
first, and then press the user button on the host to start running the host 
program, otherwise communication between the host and slave will fail.
2.The host mode can be configured to use DMA, interrupt, or polling for IO control 
in the program.
3.The NSS pin only needs to be connected when using the NSS hardware mode (this 
sample uses NSS software mode, so there is no need to connect the NSS pin).
================================================================================