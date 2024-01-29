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
#include "py32f002xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
static void APP_ConfigLPTIM_OneShot(void);
static void APP_PwrEnterStopMode(void);
void delay_us(uint32_t nus,uint32_t fac_us);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  
  /*使能LPTIM时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
  
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  /* 初始化按键 */
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  /*配置并开启LPTIM*/
  APP_ConfigLPTIM_OneShot();

  /*等待按键按下*/
  while(BSP_PB_GetState(BUTTON_USER) != 0)
  {
    
  }
  while (1)
  {
    /* 关闭LPTIM */
    LL_LPTIM_Disable(LPTIM1);
    /* 使能LPTIM */
    LL_LPTIM_Enable(LPTIM1);
    /* 延时 2*LSI时钟 */
    delay_us(75,8);
    /*使能ARR中断*/
    LL_LPTIM_EnableIT_ARRM(LPTIM1); 
    /*配置重装载值：62500*/
    /*8000000/64/62500 = 2Hz*/
    LL_LPTIM_SetAutoReload(LPTIM1,62500);
  
    /*开启单次模式*/
    LL_LPTIM_StartCounter(LPTIM1,LL_LPTIM_OPERATING_MODE_ONESHOT);
    /* 进入STOP模式 */
    APP_PwrEnterStopMode();
  }
}
/**
  * @brief  配置LPTIM单次模式
  * @param  无
  * @retval 无
  */
static void APP_ConfigLPTIM_OneShot(void)
{
  /*配置LPTIM*/
  /*LPTIM预分频器64分频    */
  LL_LPTIM_SetPrescaler(LPTIM1,LL_LPTIM_PRESCALER_DIV64);
  
  /*LPTIM计数周期结束更新ARR*/
  LL_LPTIM_SetUpdateMode(LPTIM1,LL_LPTIM_UPDATE_MODE_ENDOFPERIOD);
  
  /*使能ARR中断*/
  LL_LPTIM_EnableIT_ARRM(LPTIM1);
  
  /*使能LPTIM*/
  LL_LPTIM_Enable(LPTIM1);
  
  /*配置重装载值：62500*/
  /*8000000/64/62500 = 2Hz*/
  LL_LPTIM_SetAutoReload(LPTIM1,62500);
  
  /*开启单次模式*/
  LL_LPTIM_StartCounter(LPTIM1,LL_LPTIM_OPERATING_MODE_ONESHOT);
  
  /*使能NVIC请求*/
  NVIC_EnableIRQ(LPTIM1_IRQn);
  NVIC_SetPriority(LPTIM1_IRQn,0);
}

/**
  * @brief  LPTIM ARR中断回调函数
  * @param  无
  * @retval 无
  */
void APP_LPTIMCallback(void)
{
  /*翻转LED*/
  BSP_LED_Toggle(LED3);
  
}
/**
  * @brief  进入STOP模式
  * @param  无
  * @retval 无
  */
static void APP_PwrEnterStopMode(void)
{
  /*使能PWR时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  /* 低功耗工作在STOP模式 */
  LL_PWR_EnableLowPowerRunMode();
  /*进入DeepSleep模式*/
  LL_LPM_EnableDeepSleep();

  /*等待中断指令*/
  __WFI();
}
/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
{
  /* 使能HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* 设置 AHB 分频*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* 配置HSISYS作为系统时钟源 */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* 设置 APB1 分频*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(8000000);

  /* 更新系统时钟全局变量SystemCoreClock(也可以通过调用SystemCoreClockUpdate函数更新) */
  LL_SetSystemCoreClock(8000000);
}
/**
  * @brief  us级延时
  * @param  nus = 延时的us量,
  *         fac_us=系统时钟/1000000
  * @retval 无
  */
void delay_us(uint32_t nus,uint32_t fac_us)
 {
  LL_SYSTICK_DisableIT();
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
