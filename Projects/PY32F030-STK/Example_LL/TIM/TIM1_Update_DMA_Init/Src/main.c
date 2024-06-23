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
uint32_t TIM1ReloadCounter[9] = {900-1,800-1,700-1,600-1,500-1,400-1,300-1,200-1,100-1};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Count(void);
static void APP_ConfigDMATIM1Reload(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Enable TIM1, DMA, SYSCFG clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  
  /* Configure system clock */
  APP_SystemClockConfig();
  
  /* Initialize LED */
  BSP_LED_Init(LED3);
  
  /* Configure and enable DMA */
  APP_ConfigDMATIM1Reload();
  
  /* Configure and enable TIM1 counter mode */
  APP_ConfigTIM1Count();
  
  while (1)
  {
  }
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
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1; /* No clock division */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;     /* Up counting mode */
  TIM1CountInit.Prescaler           = 8000-1;                    /* Prescaler value: 8000 */
  TIM1CountInit.Autoreload          = 1000-1;                    /* Autoreload value: 1000 */
  TIM1CountInit.RepetitionCounter   = 0;                         /* Repetition counter value: 0 */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Enable UPDATE interrupt */
  LL_TIM_EnableIT_UPDATE(TIM1);
  
  /* Enable UPDATE DMA request */
  LL_TIM_EnableDMAReq_UPDATE(TIM1);
  
  /* Enable TIM1 counter */
  LL_TIM_EnableCounter(TIM1);
  
  /* Enable UPDATE interrupt request */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0);
}

/**
  * @brief  Configure DMA transfer
  * @param  None
  * @retval None
  */
static void APP_ConfigDMATIM1Reload(void)
{
  
  LL_DMA_InitTypeDef DMA_TIM1Reload = {0};
  
  /* Configure DMA channel 1 */
  DMA_TIM1Reload.PeriphOrM2MSrcAddress  = (uint32_t)&(TIM1->ARR);
  DMA_TIM1Reload.MemoryOrM2MDstAddress  = (uint32_t)TIM1ReloadCounter;
  DMA_TIM1Reload.Direction              = LL_DMA_DIRECTION_MEMORY_TO_PERIPH;
  DMA_TIM1Reload.Mode                   = LL_DMA_MODE_NORMAL;
  DMA_TIM1Reload.PeriphOrM2MSrcIncMode  = LL_DMA_PERIPH_NOINCREMENT;
  DMA_TIM1Reload.MemoryOrM2MDstIncMode  = LL_DMA_MEMORY_INCREMENT;
  DMA_TIM1Reload.PeriphOrM2MSrcDataSize = LL_DMA_PDATAALIGN_WORD;
  DMA_TIM1Reload.MemoryOrM2MDstDataSize = LL_DMA_MDATAALIGN_WORD;
  DMA_TIM1Reload.NbData                 = 9;
  DMA_TIM1Reload.Priority               = LL_DMA_PRIORITY_MEDIUM;
  
  /* Initialize DMA channel 1 */
  LL_DMA_Init(DMA1,LL_DMA_CHANNEL_1,&DMA_TIM1Reload);
  
  /* Map TIM1 update interrupt to channel 1 */
  LL_SYSCFG_SetDMARemap_CH1(LL_SYSCFG_DMA_MAP_TIM1_UP);
  
  /* Enable DMA transfer complete interrupt */
  LL_DMA_EnableIT_TC(DMA1,LL_DMA_CHANNEL_1);
  
  /* Enable DMA channel 1 */
  LL_DMA_EnableChannel(DMA1,LL_DMA_CHANNEL_1);
  
  /* Enable DMA channel 1 interrupt request */
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  NVIC_SetPriority(DMA1_Channel1_IRQn,0);
}

/**
  * @brief  TIM update interrupt callback function
  * @param  None
  * @retval None
  */
void APP_UpdateCallback(void)
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
