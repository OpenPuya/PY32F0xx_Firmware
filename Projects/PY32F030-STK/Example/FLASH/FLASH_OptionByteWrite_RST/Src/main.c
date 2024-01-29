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
#include "py32f030xx_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define RSTPIN_MODE_GPIO
/* #define RSTPIN_MODE_RST */

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_FlashOBProgram(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 初始化所有外设，Flash接口，SysTick */
  HAL_Init();

  /* 初始化LED */  
  BSP_LED_Init(LED_GREEN);

  /* 判断RST管脚 */
#if defined(RSTPIN_MODE_GPIO)
  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == OB_RESET_MODE_RESET)
#else
  if( READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE) == OB_RESET_MODE_GPIO)
#endif
  {
    /* 写OPTION */
    APP_FlashOBProgram();
  }

  while (1)
  {
#if defined(RSTPIN_MODE_GPIO)
    if(READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE)== OB_RESET_MODE_GPIO )
#else
    if(READ_BIT(FLASH->OPTR, FLASH_OPTR_NRST_MODE)== OB_RESET_MODE_RESET )
#endif
    {
      BSP_LED_On(LED_GREEN);
      while(1)
      {
      }
    }
  }
}

/**
  * @brief  写option空间函数
  * @param  无
  * @retval 无
  */
static void APP_FlashOBProgram(void)
{
  FLASH_OBProgramInitTypeDef OBInitCfg;

  HAL_FLASH_Unlock();        /* 解锁FLASH */
  HAL_FLASH_OB_Unlock();     /* 解锁OPTION */

  /* 配置OPTION选项 */
  OBInitCfg.OptionType = OPTIONBYTE_USER;
  OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_WWDG_SW | OB_USER_NRST_MODE | OB_USER_nBOOT1;

#if defined(RSTPIN_MODE_GPIO)
  /* BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/GPIO功能/System memory作为启动区 */
  OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_WWDG_SW | OB_RESET_MODE_GPIO | OB_BOOT1_SYSTEM;
#else
  /* BOR不使能/BOR上升3.2,下降3.1/软件模式看门狗/RST功能/System memory作为启动区 */
  OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_WWDG_SW | OB_RESET_MODE_RESET | OB_BOOT1_SYSTEM;
#endif

  /* 启动option byte编程 */
  HAL_FLASH_OBProgram(&OBInitCfg);

  HAL_FLASH_Lock();      /* 锁定FLASH */
  HAL_FLASH_OB_Lock();   /* 锁定OPTION */

  /* 产生一个复位，option byte装载 */
  HAL_FLASH_OB_Launch();
}

/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void APP_ErrorHandler(void)
{
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
