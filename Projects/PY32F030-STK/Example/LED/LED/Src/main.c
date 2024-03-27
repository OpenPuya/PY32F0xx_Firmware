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
  hled.Init.ComNum = 4 - 1;                                 /* Enable 4 COM ports */
  hled.Init.ComDrive  = LED_COMDRIVE_HIGH;                  /* LED COM output */
  hled.Init.Prescaler = 10 - 1;                             /* Fpclk/(PR+1) */
  hled.Init.LightTime = 240;                                /* Time each LED is illuminated (240*fLED, where fLED is the LED module counting clock frequency)  */
  hled.Init.DeadTime = 10;                                  /* Interval time between two LED switches, must not be zero */
  HAL_LED_Init(&hled);

  while (1)
  {
    HAL_LED_SetComDisplay(&hled, LED_COM0, LED_DISP_8);       /* Display number 8 */
    HAL_Delay(200);

    HAL_LED_SetComDisplay(&hled, LED_COM1, LED_DISP_8);       /* Display number 8 */
    HAL_Delay(200);

    HAL_LED_SetComDisplay(&hled, LED_COM2, LED_DISP_8);       /* Display number 8 */
    HAL_Delay(200);

    HAL_LED_SetComDisplay(&hled, LED_COM3, LED_DISP_8);       /* Display number 8 */
    HAL_Delay(200);

    HAL_LED_SetComDisplay(&hled, LED_COM_ALL, LED_DISP_NONE); /* Turn off display */
    HAL_Delay(200);
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
