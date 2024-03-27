================================================================================
                                样例使用说明
                             Sample Description
================================================================================
功能描述：
此样例是对串口外设接口（SPI）与外部设备以全双工串行方式进行通信 的演示,此接口设
置为从模式，通信时钟SCK由外部主设备提供。从机通过MOSI引脚接收主机数据,从MISO引脚
发送数据，数据以主机提供的SCK沿同步被移位，完成全双工通信。

Function descriptions:
This sample demonstrates communication with an external device using the Serial 
Peripheral Interface (SPI) in full-duplex serial mode. The SPI interface is 
configured as the slave, receiving the communication clock signal (SCK) from the 
external master device. The slave receives data from the master via the MOSI pin 
and sends data to the master via the MISO pin. The data is shifted synchronously 
with the clock signal provided by the master, enabling full-duplex communication.
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
3.编译下载主机程序SPI_TwoBoards_FullDuplexMaster_DMA；
4.主机与从机引脚连接(箭头指向为信号传输方向) 
主机MASTER：         从机SLAVE：
SCK(PB3)   ----->    sck(PB3)
MISO(PB4)  <-----    MISO(PB4)
MOSI(PB5)  ----->    MOSI(PB5)
NSS(PA15)  ----->    NSS(PA15)
5.主从机上电；
6.按下从机复位按键先运行从机程序，再按下主机用户按键运行主机程序 ；
7.观察主从机的LED灯，当主机和从机LED灯由常暗转为常亮状态，则表明主机、从机收发数
据成功；当主机或从机LED灯处于闪烁状态，则表明主机、从机收发数据失败。

Example execution steps:
1.Prepare two PY32F030_STK boards, one as the master and the other as the slave.
2.Compile and download the slave program (this sample program).
3.Compile and download the master program "SPI_TwoBoards_FullDuplexMaster_DMA".
4.Connect the pins between the master and slave (the arrow indicates the direction 
of signal transmission):
Master (MASTER): Slave (SLAVE):
SCK(PB3) -----> sck(PB3)
MISO(PB4) <----- MISO(PB4)
MOSI(PB5) -----> MOSI(PB5)
NSS(PA15) -----> NSS(PA15)
5.Power on the master and slave boards.
6.Press the reset button on the slave board to run the slave program first, and 
then press the user button on the master board to run the master program.
7.Observe the LED status on the master and slave boards. If the LED lights on 
both the master and slave boards transition from off to on continuously, it 
indicates successful data communication between the master and slave. If the LED 
on either the master or slave board blinks, it indicates a failure in data 
communication.
================================================================================
注意事项:
1.必须先按从机复位按键使从机程序先运行，再按主机用户按键开始运行主机程序，否则会
导致主从机通信失败。
2.从机模式可通过程序设置IO控制方式为DMA方式、中断方式和查询方式
3.NSS引脚只需要在使用NSS硬件方式时连接（本样例使用的是NSS硬件方式）

Notes:
1.It is necessary to press the reset button on the slave board first to run the 
slave program, and then press the user button on the master board to start the 
master program. Failure to do so may result in communication failure between the 
master and slave.
2.The slave mode can be configured to use different IO control methods, such as 
DMA, interrupt, or polling, through program settings.
3.The NSS pin only needs to be connected when using the NSS hardware mode (this 
sample uses the NSS hardware mode).
================================================================================
 