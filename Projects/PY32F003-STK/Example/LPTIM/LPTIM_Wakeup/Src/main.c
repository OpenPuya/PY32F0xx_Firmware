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
LPTIM_HandleTypeDef       LPTIMConf = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_RCCOscConfig(void);
static void APP_LPTIMInit(void);
static void APP_LPTIMStart(void);
static void APP_delay_us(uint32_t nus);

/**
  * @brief   应用程序入口函数
  * @retval  int
  */
int main(void)
{
  /*外设、systick初始化*/
  HAL_Init();
  
  /* 初始化LED */
  BSP_LED_Init(LED3);
  
  /* 初始化按键 */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /*时钟设置*/
  APP_RCCOscConfig();
  
  /*LPTIM初始化*/
  APP_LPTIMInit();

  /* 使能PWR */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* 关闭Systick中断 */
  HAL_SuspendTick();

  /*点亮LED*/
  BSP_LED_On(LED_GREEN);
  
  /*等待按键按下*/
  while (BSP_PB_GetState(BUTTON_USER) != 0)
  {
  }

  /*关闭LED*/
  BSP_LED_Off(LED_GREEN);

  while (1)
  {
    /*Disable LPTIM*/
    __HAL_LPTIM_DISABLE(&LPTIMConf);
   
    /*使能LPTIM并开启中断*/
    APP_LPTIMStart();
    
    /*进入STOP模式，使用中断唤醒*/
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  }
}

/**
  * @brief   时钟配置函数
  * @param   无
  * @retval  无
  */
static void APP_RCCOscConfig(void)
{
  RCC_OscInitTypeDef OSCINIT;
  RCC_PeriphCLKInitTypeDef LPTIM_RCC;

  /*LSI时钟配置*/
  OSCINIT.OscillatorType = RCC_OSCILLATORTYPE_LSI;  /* 选择配置LSI */
  OSCINIT.LSIState = RCC_LSI_ON;                    /* LSI开启 */
  /*时钟初始化*/
  if (HAL_RCC_OscConfig(&OSCINIT) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*LPTIM时钟配置*/
  LPTIM_RCC.PeriphClockSelection = RCC_PERIPHCLK_LPTIM;     /* 选择配置外设时钟：LPTIM */
  LPTIM_RCC.LptimClockSelection = RCC_LPTIMCLKSOURCE_LSI;   /* 选择LPTIM时钟源：LSI */
  /*外设时钟初始化*/
  if (HAL_RCCEx_PeriphCLKConfig(&LPTIM_RCC) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*使能LPTIM时钟*/
  __HAL_RCC_LPTIM_CLK_ENABLE();
}

/**
  * @brief   初始化LPTIM
  * @param   无
  * @retval  无
  */
static void APP_LPTIMInit(void)
{
  /*LPTIM配置*/
  LPTIMConf.Instance = LPTIM;                         /* LPTIM */
  LPTIMConf.Init.Prescaler = LPTIM_PRESCALER_DIV128;  /* 128分频 */
  LPTIMConf.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE; /* 立即更新模式 */
  /*初始化LPTIM*/
  if (HAL_LPTIM_Init(&LPTIMConf) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   使能LPTIM和中断
  * @param   无
  * @retval  无
  */
static void APP_LPTIMStart(void)
{
  /* 使能重载中断 */
  __HAL_LPTIM_ENABLE_IT(&LPTIMConf, LPTIM_IT_ARRM);

  /* 使能LPTIM */
  __HAL_LPTIM_ENABLE(&LPTIMConf);

  /* 加载重载值 */
  __HAL_LPTIM_AUTORELOAD_SET(&LPTIMConf, 51);

  /* 延时65us */
  APP_delay_us(65);
  
  /* 开启单次计数模式 */
  __HAL_LPTIM_START_SINGLE(&LPTIMConf);
}

/**
  * @brief   LPTIM重装载中断回调函数
  * @param   无
  * @retval  无
  */
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
{
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief   微秒延时函数
  * @param   nus：延时时间
  * @retval  无
  * @note    此函数会关闭SysTick中断，如需要使用请重新初始化SysTick
  */
static void APP_delay_us(uint32_t nus)
 {
  HAL_SuspendTick();
  uint32_t temp;
  SysTick->LOAD=nus*(SystemCoreClock/1000000);
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
  * @brief   错误执行函数
  * @param   无
  * @retval  无
  */
void APP_ErrorHandler(void)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
