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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_PvdConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();   

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  
  /* 配置PVD */
  APP_PvdConfig();    
 
  /* 使能PVD */
  HAL_PWR_EnablePVD();       
  while (1)
  {
  }
}

/**
  * @brief  配置PVD
  * @param  无
  * @retval 无
  */
static void APP_PvdConfig(void)
{
  /* PWR时钟和GPIOB时钟使能 */
  GPIO_InitTypeDef  GPIO_InitStruct;
  PWR_PVDTypeDef sConfigPVD;
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* PB7初始化 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  sConfigPVD.Mode = PWR_PVD_MODE_IT_RISING_FALLING;     /* PVD配置为上升/下降沿中断方式 */
  sConfigPVD.PVDFilter = PWR_PVD_FILTER_NONE;           /* 滤波功能禁止 */
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;                 /* PB07作为检测源，此参数设置无效 */
  sConfigPVD.PVDSource = PWR_PVD_SOURCE_PB07;           /* PVD检测为PB07 */
  HAL_PWR_ConfigPVD(&sConfigPVD);  
  /* PVD初始化 */
  HAL_NVIC_EnableIRQ(PVD_IRQn);
}

/**
  * @brief  PVD回调函数
  * @param  无
  * @retval 无
  */
void HAL_PWR_PVD_Callback(void)
{
  if (__HAL_PWR_GET_FLAG(PWR_SR_PVDO))
  {
    BSP_LED_On(LED_GREEN);
  }
  else
  {
    BSP_LED_Off(LED_GREEN);
  }
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
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
