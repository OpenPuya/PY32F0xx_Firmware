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
static void APP_ConfigTIM1Encoder(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Enable TIM1 and GPIOA clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize LED and USART */
  BSP_LED_Init(LED3);
  BSP_USART_Config();
  
  /* Configure and enable TIM1 encoder mode */
  APP_ConfigTIM1Encoder();
  
  while (1)
  {
  }
}

/**
  * @brief  Configure TIM encoder mode
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Encoder(void)
{
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  LL_TIM_ENCODER_InitTypeDef TIM1EncoderInit = {0};
  LL_GPIO_InitTypeDef TIM1ChannelInit = {0};

  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1; /* No clock division */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;     /* Up counting mode */
  TIM1CountInit.Prescaler           = 1-1;    /* No prescaler */
  TIM1CountInit.Autoreload          = 1000-1; /* Autoreload value: 1000 */
  TIM1CountInit.RepetitionCounter   = 0;      /* Repetition counter value: 0 */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Enable CH1 and CH2 capture interrupts */
  LL_TIM_EnableIT_CC1(TIM1);
  LL_TIM_EnableIT_CC2(TIM1);
  NVIC_EnableIRQ(TIM1_CC_IRQn);
  
  /* Configure Encoder */
  LL_TIM_SetEncoderMode(TIM1,LL_TIM_ENCODERMODE_X4_TI12);

  TIM1EncoderInit.EncoderMode     = LL_TIM_ENCODERMODE_X4_TI12;   /* Encoder mode: Mode 3  */
  TIM1EncoderInit.IC1Polarity     = LL_TIM_IC_POLARITY_BOTHEDGE;  /* Input capture 1 active edge: Both edges */
  TIM1EncoderInit.IC1ActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;  /* Input capture 1 active input: TI1 */
  TIM1EncoderInit.IC1Filter       = LL_TIM_IC_FILTER_FDIV1;       /* Input capture 1 filter value: No filter */
  TIM1EncoderInit.IC1Prescaler    = LL_TIM_ICPSC_DIV1;            /* Input capture 1 prescaler value: 1 */
  TIM1EncoderInit.IC2Polarity     = LL_TIM_IC_POLARITY_BOTHEDGE;  /* Input capture 2 active edge: Both edges */
  TIM1EncoderInit.IC2ActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;  /* Input capture 2 active input: TI2 */
  TIM1EncoderInit.IC2Filter       = LL_TIM_IC_FILTER_FDIV1;       /* Input capture 2 filter value: No filter */
  TIM1EncoderInit.IC2Prescaler    = LL_TIM_ICPSC_DIV1;            /* Input capture 2 prescaler value: 1 */
  
  /* Initialize Encoder configuration */
  LL_TIM_ENCODER_Init(TIM1,&TIM1EncoderInit);
  
  /* Map TI1 and TI2 to PA8 and PA9 */
  TIM1ChannelInit.Pin       = LL_GPIO_PIN_8 | LL_GPIO_PIN_9;
  TIM1ChannelInit.Mode      = LL_GPIO_MODE_ALTERNATE;
  TIM1ChannelInit.Alternate = LL_GPIO_AF_2;
  TIM1ChannelInit.Speed     = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1ChannelInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1ChannelInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1ChannelInit);
  
  /* Enable TIM1 counter */
  LL_TIM_EnableCounter(TIM1);
  
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
  * @brief  TIM capture/compare interrupt callback function
  * @param  None
  * @retval None
  */
void APP_CCCallback(void)
{
  printf("Count:%u\r\n",(unsigned int)LL_TIM_GetCounter(TIM1));
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
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
