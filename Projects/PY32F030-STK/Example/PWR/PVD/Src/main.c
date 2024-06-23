/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
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
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();   

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Configure PVD */
  APP_PvdConfig();    
 
  /* Enable PVD */
  HAL_PWR_EnablePVD();       
  while (1)
  {
  }
}

/**
  * @brief  Configure PVD
  * @param  None
  * @retval None
  */
static void APP_PvdConfig(void)
{
  /* Enable PWR clock and GPIOB clock */
  GPIO_InitTypeDef  GPIO_InitStruct = {0};
  PWR_PVDTypeDef    sConfigPVD      = {0};
  
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Initialize PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  sConfigPVD.Mode = PWR_PVD_MODE_IT_RISING_FALLING;     /* PVD configured as interrupt on rising/falling edge */
  sConfigPVD.PVDFilter = PWR_PVD_FILTER_NONE;           /* Filter functionality disabled */
  sConfigPVD.PVDLevel = PWR_PVDLEVEL_0;                 /* This parameter is not applicable when using PB07 as the detection source */
  sConfigPVD.PVDSource = PWR_PVD_SOURCE_PB07;           /* PVD detection source is PB07 */
  HAL_PWR_ConfigPVD(&sConfigPVD);  
  /* Enable PVD interrupt */
  HAL_NVIC_EnableIRQ(PVD_IRQn);
  HAL_NVIC_SetPriority(PVD_IRQn, 0, 0);                 /* Set interrupt priority */
}

/**
  * @brief  PVD callback function
  * @param  None
  * @retval None
  */
void HAL_PWR_PVD_Callback(void)
{
  if(__HAL_PWR_GET_FLAG(PWR_SR_PVDO)==1)
  {
    BSP_LED_On(LED_GREEN);
  }
  else
  {
    BSP_LED_Off(LED_GREEN);
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
