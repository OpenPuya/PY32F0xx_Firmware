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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Count(void);
static void APP_ConfigInputCapture(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Enable TIM1 clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize LED */
  BSP_LED_Init(LED3);
  
  /* Configure capture channel TI1 */
  APP_ConfigInputCapture();
  
  /* Configure and enable TIM1 counter mode */
  APP_ConfigTIM1Count();
  
  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure TIM1 input capture channel
  * @param  None
  * @retval None
  */
static void APP_ConfigInputCapture(void)
{
  LL_TIM_IC_InitTypeDef InputCaptureInit = {0};
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  
  /* Configure PA3 as capture input pin */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_3;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_DOWN;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_13;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;  
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  /* Configure capture channel */
  InputCaptureInit.ICActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;
  InputCaptureInit.ICPrescaler    = LL_TIM_ICPSC_DIV1;
  InputCaptureInit.ICPolarity     = LL_TIM_IC_POLARITY_RISING;
  InputCaptureInit.ICFilter       = LL_TIM_IC_FILTER_FDIV1;
  
  LL_TIM_IC_Init(TIM1,LL_TIM_CHANNEL_CH1,&InputCaptureInit);
  
  /* Enable channel 1 capture interrupt */
  LL_TIM_EnableIT_CC1(TIM1);
  
  /* Enable TIM1 capture interrupt request */
  NVIC_EnableIRQ(TIM1_CC_IRQn);
  NVIC_SetPriority(TIM1_CC_IRQn,0);
}

/**
  * @brief  Configure TIM count mode
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Count(void)
{
  /* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* No clock division */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* Up counting mode */
  TIM1CountInit.Prescaler           = 8000-1;                     /* Prescaler value: 8000 */
  TIM1CountInit.Autoreload          = 1000-1;                     /* Autoreload value: 1000 */
  TIM1CountInit.RepetitionCounter   = 0;                          /* Repetition counter value: 0  */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Enable TIM1 counter */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  TIM input capture interrupt callback function
  * @param  None
  * @retval None
  */
void APP_InputcaptureCallback(void)
{
  /* Toggle LED */
  BSP_LED_Toggle(LED3);
}

/**
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Configure HSISYS as system clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 prescaler */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);
  
  /* Update system clock global variable SystemCoreClock (can also be updated by calling SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(8000000);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while(1)
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
