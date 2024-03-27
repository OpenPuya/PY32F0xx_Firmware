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
const uint8_t dispArr[] = {LED_DISP_0, LED_DISP_1, LED_DISP_2, LED_DISP_3, LED_DISP_4, \
                           LED_DISP_5, LED_DISP_6, LED_DISP_7, LED_DISP_8, LED_DISP_9};
uint8_t dispNum = 0;
LED_HandleTypeDef hled;
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief   Main program
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* LED initialization */
  hled.Instance = LED;
  hled.Init.ComNum = 4 - 1;               /* Enable 4 COM ports */
  hled.Init.ComDrive = LED_COMDRIVE_LOW;  /* LED non-COM output */
  hled.Init.Prescaler = 10 - 1;           /* Fpclk/(PR+1) */
  hled.Init.LightTime = 0xF0;             /* Time each LED is illuminated */
  hled.Init.DeadTime = 0x10;              /* Interval time between two LED switches, must not be zero */
  HAL_LED_Init(&hled);

  /* Infinite loop */
  while (1)
  {
    dispNum++;
    if (dispNum == 10)
    {
      dispNum = 0;
    }
    HAL_Delay(1000);
  }
}

/**
  * @brief   LED interrupt callback function
  * @param   None
  * @retval  None
  */
void HAL_LED_LightCpltCallback(LED_HandleTypeDef *hled)
{
  static uint32_t oldValue = 0xFF;

  if (oldValue != dispNum)
  {
    oldValue = dispNum;
    HAL_LED_SetComDisplay(hled, LED_COM0, dispArr[(dispNum) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM1, dispArr[(dispNum + 1) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM2, dispArr[(dispNum + 2) % 10]);
    HAL_LED_SetComDisplay(hled, LED_COM3, dispArr[(dispNum + 3) % 10]);
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
