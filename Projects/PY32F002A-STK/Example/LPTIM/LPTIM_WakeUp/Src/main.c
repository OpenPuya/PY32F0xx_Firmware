/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
LPTIM_HandleTypeDef       LPTIMCONF = {0};
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Error_Handler(void);
static void APP_LPTIMConfig(void);
void delay_us(uint32_t nus,uint32_t fac_us);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  RCC_OscInitTypeDef OSCINIT;
  RCC_PeriphCLKInitTypeDef LPTIM_RCC;

  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();
  
  __HAL_RCC_LPTIM_CLK_ENABLE();                                      /* 使能LPTIM时钟 */
                                                                     /* 使能PWR时钟 */
  __HAL_RCC_PWR_CLK_ENABLE();

  OSCINIT.OscillatorType = RCC_OSCILLATORTYPE_LSI;
  OSCINIT.LSIState = RCC_LSI_ON;                                      /* 设置LSI */
  if(HAL_RCC_OscConfig(&OSCINIT) != HAL_OK)
  {
    Error_Handler();
  }

  LPTIM_RCC.PeriphClockSelection = RCC_PERIPHCLK_LPTIM;
  LPTIM_RCC.LptimClockSelection = RCC_LPTIMCLKSOURCE_LSI;            /* 选用LSI作为LPTIM的时钟源 */
  if(HAL_RCCEx_PeriphCLKConfig(&LPTIM_RCC) != HAL_OK)
  {
    Error_Handler();
  }

  APP_LPTIMConfig();

  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }

  /* 无限循环 */
  while (1)
  {
    LPTIM->CR &= ~LPTIM_CR_ENABLE;
    LPTIM->CR |= LPTIM_CR_ENABLE;
    
    delay_us(75,8);                                                       /* delay 2*LSI时钟 */      
    LPTIM->CR |= LPTIM_CR_SNGSTRT;
    LPTIM->IER |=LPTIM_IER_ARRMIE;
    LPTIM->ARR=51;

    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);   /* 进入低功耗,PWR_STOPENTRY_WFI=中断唤醒,PWR_STOPENTRY_WFE=事件唤醒 */
  }
}

/**
  * @brief  LPTIM初始化函数
  * @param  无
  * @retval 无
  */
static void APP_LPTIMConfig(void)
{
  LPTIMCONF.Instance = LPTIM;
  LPTIMCONF.Init.Prescaler = LPTIM_PRESCALER_DIV128;                      /* LSI 128分频 */
  LPTIMCONF.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;                     /* 立刻更新 */

  if (HAL_LPTIM_Init(&LPTIMCONF) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief  LPTIM中断执行函数
  * @param  无
  * @retval 无
  */
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  BSP_LED_Toggle(LED_GREEN);
}

 /**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void delay_us(uint32_t nus,uint32_t fac_us)
 {
  HAL_SuspendTick();
  uint32_t temp;
  SysTick->LOAD=nus*fac_us;
  SysTick->VAL=0x00;
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
  do
  {
    temp=SysTick->CTRL;
  }
  while((temp&0x01)&&!(temp&(1<<16)));
  SysTick->CTRL=0x00;
  SysTick->VAL =0x00;
 }

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
