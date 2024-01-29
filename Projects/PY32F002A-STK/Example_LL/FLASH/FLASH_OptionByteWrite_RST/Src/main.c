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
static void APP_ProgramFlashOB(void);

/**
  * @brief  应用程序入口函数.
  * @param  无
  * @retval int
  */
int main(void)
{
  /*初始化systick*/
  HAL_Init();

  /*初始化按键PB2*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /*等待按键按下，防止每次上电都擦写OPTION*/
  while (BSP_PB_GetState(BUTTON_USER));

  /*时钟初始化,配置系统时钟为HSI*/
  APP_SystemClockConfig();

  /*写OPTION*/
  APP_ProgramFlashOB();

  while (1)
  {

  }
}
/**
  * @brief  写OPTION
  * @param  无
  * @retval 无
  */
static void APP_ProgramFlashOB(void)
{
  FLASH_OBProgramInitTypeDef OBInitCfg;
  /*获取OPTION值*/
  HAL_FLASH_OBGetConfig(&OBInitCfg);
  /*判断OPTION是否已经配置完成*/
  if((OBInitCfg.USERConfig & OB_RESET_MODE_GPIO) != OB_RESET_MODE_GPIO)
  {
  
    HAL_FLASH_Unlock();/*解锁FLASH*/
    HAL_FLASH_OB_Unlock();/*解锁OPTION*/

    /*配置OPTION选项*/
    OBInitCfg.OptionType = OPTIONBYTE_USER;
    OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_NRST_MODE | OB_USER_nBOOT1;

    /*BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/RST改为GPIO/System memory作为启动区*/
    OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_RESET_MODE_GPIO | OB_BOOT1_SYSTEM;

    /*BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/仅复位输入/System memory作为启动区*/
    /*OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_WWDG_SW | OB_RESET_MODE_RESET | OB_BOOT1_SYSTEM;*/ /*恢复OPTION*/

    /* 启动option byte编程 */
    HAL_FLASH_OBProgram(&OBInitCfg);

    HAL_FLASH_Lock();/*锁定FLASH*/
    HAL_FLASH_OB_Lock();/*锁定OPTION*/

    /*产生一个复位，option byte装载*/
    HAL_FLASH_OB_Launch();
  }
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
