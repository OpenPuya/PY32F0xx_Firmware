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
COMP_HandleTypeDef  hcomp;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();                                                         

  hcomp.Instance = COMP2;                                              /* Select COMP2 */
  hcomp.Init.InputMinus      = COMP_INPUT_MINUS_VREFINT;               /* Negative input is VREF (1.2V) */
  hcomp.Init.InputPlus       = COMP_INPUT_PLUS_IO3;                    /* Positive input is PA3 */
  hcomp.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;             /* COMP2 polarity is non-inverted */
  hcomp.Init.Mode            = COMP_POWERMODE_HIGHSPEED;               /* COMP2 power mode is set to High speed */
  hcomp.Init.Hysteresis      = COMP_HYSTERESIS_ENABLE;                 /* Hysteresis function is enabled */
  hcomp.Init.WindowMode      = COMP_WINDOWMODE_DISABLE;                /* Window mode is disabled */
  hcomp.Init.TriggerMode     = COMP_TRIGGERMODE_NONE;                  /* External trigger for COMP2 is disabled */
  hcomp.Init.DigitalFilter   = 0;

  /* Initialize COMP2 */
  if (HAL_COMP_Init(&hcomp) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }
  /* Start COMP2 */
  HAL_COMP_Start(&hcomp);                                              

  while (1)
  {
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
