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
#include "py32f003xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
/* 定义与时钟配置相关的 */
#define RTC_ASYNCH_PREDIV          ((uint32_t)0x7FFF)

/* Private variables ---------------------------------------------------------*/
/* 时间结构体及其变量 */
struct time_t
{
  uint8_t sec;
  uint8_t min;
  uint8_t hour;
};
struct time_t RTC_TimeStruct;
struct time_t RTC_AlarmStruct;
/* 日期结构体及其变量 */
struct date_t
{
  uint8_t month;
  uint8_t day;
  uint8_t year;
};
struct date_t RTC_DateStruct;
uint8_t EndOfMonth[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/* 用于显示时间和日期的缓冲区 */
uint32_t TimeCounter = 0;
uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigRtc(void);
static void APP_ConfigRtcDate(uint8_t ,uint8_t , uint8_t);
static void APP_EnterStop(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);
  
  /* 初始化按键BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* 配置RTC外设 */
  APP_ConfigRtc();
  
  /* 打开LED */
  BSP_LED_On(LED_GREEN);
  
  /* 等待按键按下 */
  while(BSP_PB_GetState(BUTTON_KEY) == 1);
  
  /* 关闭LED */
  BSP_LED_Off(LED_GREEN);
  
  /* 进入STOP模式 */
  APP_EnterStop();

  while (1)
  {
    /* 翻转LED灯 */
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(500);
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
static void APP_SystemClockConfig(void)
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
  * @brief  配置RTC时钟
  * @param  无
  * @retval 无
  */
static void APP_ConfigRtc(void)
{
  LL_RTC_InitTypeDef rtc_initstruct = {0};
  
  /*##-1- 启用 PWR 时钟并启用对备份域的访问 #######*/
  /* 要更改 RTC 功能（LSE、LSI）的源时钟，必须：
      - 启用PWR时钟
      - 启用写访问以配置 RTC 时钟源（在复位后完成一次）。
      - 复位备份域
      - 配置需要的RTC时钟源 */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  LL_PWR_EnableBkUpAccess();

  /*##-2- 将LSI配置为RTC时钟源##############################*/
  /* 使能 LSI */
  LL_RCC_LSI_Enable();
  while (LL_RCC_LSI_IsReady() != 1)
  {
  }
  /* 仅当 LSI 尚未被选为 RTC 时钟源时才复位备份域 */
  if (LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSI)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSI);
  }
  
  /* 使能 RTC 时钟和 RTC APB 时钟*/
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_RTC);
  LL_RCC_EnableRTC();
  
  /*##-4 配置RTC ######################################### ############*/
  /* 配置 RTC 预分频器和 RTC 数据寄存器 */
  if (LL_RTC_DeInit(RTC) != SUCCESS) 
  {
    /* 错误提示 */
    
  }
  
  /* 配置分频因子和输出源 */
  rtc_initstruct.AsynchPrescaler = RTC_ASYNCH_PREDIV;
  rtc_initstruct.OutPutSource    = LL_RTC_CALIB_OUTPUT_NONE;
  if (LL_RTC_Init(RTC, &rtc_initstruct) != SUCCESS)
  {
    /* 错误提示 */
    
  }
  
  
  LL_RTC_TimeTypeDef  rtc_time_initstruct = {0};
  /*## 配置日期 ##################################################*/
  /* 设定日期: 2022.08.16 */
  APP_ConfigRtcDate(16, 8, 22);
  
  /*##配置时间 ################################################*/
  /* Set Time: 00:00:00 */
  rtc_time_initstruct.Hours      =0;
  rtc_time_initstruct.Minutes    =0 ;
  rtc_time_initstruct.Seconds    =0;
  /* 根据初始化结构中定义的参数初始化 RTC 时间 */  
  if (LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &rtc_time_initstruct) != SUCCESS)   
  {
    /* 错误提示 */
    
  }
  
  /*##- 配置RTC的NVIC */
  NVIC_SetPriority(RTC_IRQn, 0x00);
  NVIC_EnableIRQ(RTC_IRQn);
  
  /* 使能秒中断 */
  LL_RTC_EnableIT_SEC(RTC);
  
  /* 使能RTC对应的EXTI中断 */
  LL_EXTI_EnableIT(LL_EXTI_LINE_19);
}

/**
  * @brief  配置日期
  * @param  fYear：年份
  * @param  fMonth：月份
  * @param  fDate：天
  * @retval 无
  */
static void APP_ConfigRtcDate(uint8_t fDate , uint8_t fMonth , uint8_t fYear)
{
  RTC_DateStruct.day   = fDate;
  RTC_DateStruct.month = fMonth;
  RTC_DateStruct.year  = fYear;
}

/**
  * @brief  进入stop模式
  * @param  无
  * @retval 无
  */
static void APP_EnterStop(void)
{
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* Low power STOP voltage 1.0V */
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE2);

  /* Enter low power mode */
  LL_PWR_EnableLowPowerRunMode();
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
  
  LL_LPM_EnableSleep();
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
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
