/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* I2C SPEEDCLOCK 定义为最大值：快速模式(400kHz) */
#define I2C_SPEEDCLOCK           400000
#define I2C_DUTYCYCLE            LL_I2C_DUTYCYCLE_2
/* Private variables ---------------------------------------------------------*/
const uint8_t aLedOn[]           = "LED ON";
#ifdef SLAVE_BOARD
uint8_t      aReceiveBuffer[0xF] = {0};
uint8_t ubReceiveIndex      = 0;
#else /* MASTER_BOARD */
uint8_t  ubNbDataToTransmit = sizeof(aLedOn);
uint8_t*      pTransmitBuffer    = (uint8_t*)aLedOn;
#endif /* SLAVE_BOARD */
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
#ifdef SLAVE_BOARD
static void     APP_ConfigI2cSlave(void);
static void     APP_ActivateI2cSlave(void);
static void     APP_HandleI2cSlave(void);
static uint8_t  APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
#else /* MASTER_BOARD */
static void     APP_ConfigI2cMaster(void);
static void     APP_ActivateI2cMaster(void);
static void     APP_HandleI2cMaster(void);
#endif /* SLAVE_BOARD */

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();
/* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  #ifdef SLAVE_BOARD
  /* 配置I2C1（Slave模式下的I2C配置及相关GPIO初始化）*/
  APP_ConfigI2cSlave();

  /* 等待用户按下按钮开始传输 */
  while(BSP_PB_GetState(BUTTON_KEY) == 1)
  {}

  /* 使能 I2C1 外设（从机） */
  APP_ActivateI2cSlave();

  /* 处理 I2C1 事件（从机） */
  APP_HandleI2cSlave();
#else /* MASTER_BOARD */
  /*配置I2C1（主模式下I2C配置及相关GPIO初始化）*/
  APP_ConfigI2cMaster();

  /* 等待用户按下按钮开始传输 */
  while(BSP_PB_GetState(BUTTON_KEY) == 1)
  {}

  /* 使能 I2C1 外设（主机） */
  APP_ActivateI2cMaster();

  /* 处理 I2C1 事件（主机） */
  APP_HandleI2cMaster();
#endif /* SLAVE_BOARD */
  while (1)
  {

  }
}


/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
{
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
}
#ifdef SLAVE_BOARD
/**
  * @brief  配置I2C1为从模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigI2cSlave(void)
{
  /* (1) 使能 GPIO 时钟 ************************/

  /* 使能 GPIOA 的外设时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* (2) 使能 I2C1 外设时钟 *************************************/

  /* 启用 I2C1 的外设时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* 将 SCL 引脚配置为：可选功能、高速、开漏、上拉 */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* 将 SDA 引脚配置为：可选功能、高速、开漏、上拉 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* (3) 配置I2C1功能参数***********************/
  
  /* 在修改配置寄存器之前禁用 I2C1 */
  LL_I2C_Disable(I2C1);
  
  /* 配置从机地址：
    * - OwnAddress1 是 SLAVE_OWN_ADDRESS
    */
  LL_I2C_SetOwnAddress1(I2C1, SLAVE_OWN_ADDRESS, 0);

  /* 启用时钟拉伸 */
  /* 复位值是启用时钟延长 */
  /* LL_I2C_EnableClockStretching(I2C1); */
  
  /* 启用广播呼叫 */
  /* 复位值为禁用广播呼叫 */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  使能I2C1(从机)
  * @param  无
  * @retval 无
  */
static void APP_ActivateI2cSlave(void)
{
  /* (1) 使能 I2C1 **********************************************************/
  LL_I2C_Enable(I2C1);
}

#else /* MASTER_BOARD */
/**
  * @brief  配置I2C1为主模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigI2cMaster(void)
{
  LL_RCC_ClocksTypeDef rcc_clocks;

  /* (1) 启用 GPIO 时钟 ************************/

  /* 使能 GPIOA 的外设时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* (2) 使能 I2C1 外设时钟 *************************************/

  /* 启用 I2C1 的外设时钟 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* 将 SCL 引脚配置为：可选功能、高速、开漏、上拉 */
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  
  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* 将 SDA 引脚配置为：可选功能、高速、开漏、上拉 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_12;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* (3) 配置I2C1功能参数********************************/
  
  /* 在修改配置寄存器之前禁用 I2C1 */
  LL_I2C_Disable(I2C1);
  
  /* 获取时钟频率 */
  LL_RCC_GetSystemClocksFreq(&rcc_clocks);

  /* 配置 SCL 时钟速度 */
  LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, I2C_SPEEDCLOCK, I2C_DUTYCYCLE);

  /* 启用时钟拉伸 */
  /* 复位值是启用时钟延长 */
  /* LL_I2C_EnableClockStretching(I2C1);*/

  
  /* 启用广播呼叫 */
  /* 复位值为禁用广播呼叫 */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  使能I2C1(主机)
  * @param  无
  * @retval 无
  */
static void APP_ActivateI2cMaster(void)
{
  /* (1) Enable I2C1 **********************************************************/
  LL_I2C_Enable(I2C1);
}
#endif /* SLAVE_BOARD */
#ifdef SLAVE_BOARD
/**
* @brief  从机处理函数
  * @param  无
  * @retval 无
  */
static void APP_HandleI2cSlave(void)
{
  /* (1) 准备从机地址接收的确认 ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  /* (2) 等待 ADDR 标志并检查地址匹配码和方向 ************/
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* 验证传输方向，Read 时的方向，Slave 进入接收器模式 */
  if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ)
  {
    /* 清除 ISR 寄存器中的 ADDR 标志值 */
    LL_I2C_ClearFlag_ADDR(I2C1);
  }
  else
  {
    /* 清除 ISR 寄存器中的 ADDR 标志值 */
    LL_I2C_ClearFlag_ADDR(I2C1);

    /* 调用错误函数 */
    Error_Handler();
  }

  /* (3) 循环直到接收到传输结束（STOP 标志出现） ***************/

  /* 循环直到 STOP 标志置位 */
  while(!LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* (3.1) 接收数据（RXNE 标志置位） **********************************/

    /* 检查 ISR 寄存器中的 RXNE 标志值 */
    if(LL_I2C_IsActiveFlag_RXNE(I2C1))
    {
      /* 读取接收数据寄存器中的字符。
       通过读取 DR 寄存器中的数据清除 RXNE 标志 */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }

    /* (3.2) 接收数据（BTF 标志置位） ***********************************/
    /* 检查 ISR 寄存器中的 BTF 标志值 */
    if(LL_I2C_IsActiveFlag_BTF(I2C1))
    {
      /* 读取接收数据寄存器中的字符。
       通过读取 DR 寄存器中的数据清除 BTF 标志 */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }
  }

  /* (4) 清除挂起标志，检查数据一致性 **************************/
  LL_I2C_ClearFlag_STOP(I2C1);

  /* 检查数据是否请求打开 LED */
  if(APP_Buffercmp8((uint8_t*)aReceiveBuffer, (uint8_t*)aLedOn, (ubReceiveIndex-1)) == 0)
  {
    /* 打开 LED：
      * - 已收到预期的字节
      * - 从 Rx 序列成功完成
      */
      BSP_LED_On(LED_GREEN);
  }
  else
  {
    /* 调用错误函数 */
    Error_Handler();
  }
}

/**
* @brief  字符比较函数
  * @param  pBuffer1：待比较字符存放的buff1；
**          pBuffer2：待比较字符存放的buff2；
**          BufferLength：待比较字符长度
  * @retval 0：比较的字符完全一致；
**          1：比较的字符不完全一致；
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

#else /* MASTER_BOARD */

/**
* @brief  主机处理函数
  * @param  无
  * @retval 无
  */
static void APP_HandleI2cMaster(void)
{
  /* (1) 使能 Master 数据接收的应答 ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
  
  /* (2) 向从设备发起启动条件 ***********************/
   /* Master 生成开始条件 */
  LL_I2C_GenerateStartCondition(I2C1);

  /* (3) 循环直到发送起始位（SB 标志置位） ********************/
  while(!LL_I2C_IsActiveFlag_SB(I2C1))
  {
  }

  /* (4) 发送带有 7 位 从机地址+方向位 */
    LL_I2C_TransmitData8(I2C1, SLAVE_OWN_ADDRESS | I2C_REQUEST_WRITE);

  /* (5) 循环直到收到地址应答（ADDR 标志置位）*******/
  /* 循环直到 ADDR 标志被置位 */
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* (6) 清除 ADDR 标志并循环直到传输结束 (ubNbDataToTransmit == 0) */
  /* 清除 ISR 寄存器中的 ADDR 标志值 */
  LL_I2C_ClearFlag_ADDR(I2C1);

  /* 循环直到 TXE 标志被置位 */
  while(ubNbDataToTransmit > 0)
  {
    /* (6.1) 发送数据（TXE 标志置位） **********************************/

    /* 检查 ISR 寄存器中的 TXE 标志值 */
    if(LL_I2C_IsActiveFlag_TXE(I2C1))
    {
      /* 将数据写入发送数据寄存器。
       通过向 TXDR 寄存器写入数据清除 TXE 标志 */
      LL_I2C_TransmitData8(I2C1, (*pTransmitBuffer++));

      ubNbDataToTransmit--;
    }
  }

  /* (7) 传输结束，数据一致性正在检查到从进程 *****/ 
  /* 生成停止条件 */
  LL_I2C_GenerateStopCondition(I2C1);

  /* 打开 LED：
    * - 预期的字节已发送
    * - 主 Tx 序列成功完成
    */
  BSP_LED_On(LED_GREEN);
}

#endif /* SLAVE_BOARD */
/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
{
  /* 无限循环 */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  输出产生断言错误的源文件名及行号
  * @param  file：源文件名指针
  * @param  line：发生断言错误的行号
  * @retval 无
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* 用户可以根据需要添加自己的打印信息,
     例如: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* 无限循环 */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
