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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t aShowDeviceID[30]    = {0};
uint8_t aShowRevisionID[30]  = {0};
uint8_t aShowCoordinate[40]  = {0};
uint8_t aShowWaferNumber[30] = {0};
uint8_t aShowLotNumber[30]   = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GetMcuInfo(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();

  /* 获取MCU信息 */
  APP_GetMcuInfo();

  while (1)
  {
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
{
  /* 使能并配置HSI */
  LL_RCC_HSI_Enable();
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
  while (LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  LL_Init1msTick(24000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  获取MCU信息
  * @param  无
  * @retval 无
  */
static void APP_GetMcuInfo(void)
{
  register uint32_t size_string = 0, read_info = 0, read_info2 = 0;

  /* 打印Device ID */
  sprintf((char *)aShowDeviceID, "Device ID = 0x%03X", LL_DBGMCU_GetDeviceID());
  printf("%s\r\n",aShowDeviceID);

  /* 打印Revision ID */
  sprintf((char *)aShowRevisionID, "Revision ID = 0x%04X", LL_DBGMCU_GetRevisionID());
  printf("%s\r\n",aShowRevisionID);

  /* 打印X and Y coordinates */
  sprintf((char *)aShowCoordinate, "X and Y coordinates = 0x%08X", LL_GetUID_Word2());
  printf("%s\r\n",aShowCoordinate);

  /* 打印Wafer NB */
  read_info = LL_GetUID_Word1();
  read_info2 = LL_GetUID_Word0();
  sprintf((char *)aShowWaferNumber, "Wafer NB = 0x%08X", (uint8_t)read_info);
  printf("%s\r\n",aShowWaferNumber);
  
  /* 打印Lot NB */
  size_string = sprintf((char *)aShowLotNumber, "Lot NB = 0x%08X", read_info2);
  sprintf((char *)aShowLotNumber + size_string, "%08X", (read_info >> 8));
  printf("%s\r\n",aShowLotNumber);
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
