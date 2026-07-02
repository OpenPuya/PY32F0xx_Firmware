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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
void APP_ConfigEXTI(void);
void Enter_Sleep(void);
void GPIO_Config(void);
static void APP_LED_run(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /*Initialize LED*/
  BSP_LED_Init(LED_GREEN);

  /*Initialize button*/  
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);
  
  /* Initialize external interrupt */
  APP_ConfigEXTI();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }
  
  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);;
  
  /* Enter SLEEP mode */
  Enter_Sleep();

  while (1)
  {
    APP_LED_run();
  }
}


/**
  * @brief  System clock configuration
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable and initialize HSI */
  LL_RCC_HSI_Enable();
  LL_RCC_HSI_SetCalibFreq(LL_RCC_HSICALIBRATION_24MHz);
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }
   
  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
   
  /* Configure HSISYS as system clock and initialize it */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }
  
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  
  /* Set APB1 prescaler and initialize it */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ConfigEXTI(void)
{
   LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
   LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
  
   /*Enable GPIOA clock*/
   LL_IOP_GRP1_EnableClock (LL_IOP_GRP1_PERIPH_GPIOA);
  
   /* Select PA06 pin */
   GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
   /* Select input mode */
   GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
   /*Pull-up*/
   GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
   /* Initialize GPIOA */
   LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /* Select EXTI6 as external interrupt input */
   LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA,LL_EXTI_CONFIG_LINE6);

   /* Select EXTI6 */
   EXTI_InitStruct.Line = LL_EXTI_LINE_6;
   /* Enable */
   EXTI_InitStruct.LineCommand = ENABLE;
   /* Select interrupt mode */
   EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
   /* Select rising edge trigger */
   EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
   /* Initialize external interrupt */
   LL_EXTI_Init(&EXTI_InitStruct);
   
   /* Set interrupt priority */
   NVIC_SetPriority(EXTI4_15_IRQn,1);
   /*Enable interrupts*/
   NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/**
  * @brief  Enter SLEEP mode
  * @param  None
  * @retval None
  */
void Enter_Sleep(void)
{
  /*Enable PWR clock*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* Enter SLEEP mode */
  LL_LPM_EnableSleep();
  
  /*Request Wait For Interrupt*/
  __WFI();
}
/**
  * @brief  LED run configuration
  * @param  None
  * @retval None
  */
static void APP_LED_run(void)
{
  /*Toggle LED*/
  BSP_LED_Toggle(LED_GREEN);
  /*Delay 200ms*/
  LL_mDelay(200);
  /*Toggle LED*/
  BSP_LED_Toggle(LED_GREEN);
  /*Delay 200ms*/
  LL_mDelay(200);
}



/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* infinite loop */
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
  /* infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
