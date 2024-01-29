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
#define FLASH_USER_START_ADDR     0x08002000
/* Private variables ---------------------------------------------------------*/
typedef struct
{
  uint32_t arrA[64];
} NewDataType;                                                      /* 结构体定义 */
#define VarA (*(volatile NewDataType *)FLASH_USER_START_ADDR)       /* Flash存储地址定义 */
uint32_t dat2[10];

uint32_t DATA[64] = {0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                    };

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_FlashErase(void);
static void APP_FlashProgram(void);
static void APP_FlashBlank(void);
static void APP_FlashVerify(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /*初始化systick*/
  HAL_Init();

  /*初始化按键PB2*/
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /*等待按键按下，防止每次上电都擦写FLASH*/
  while (BSP_PB_GetState(BUTTON_USER));

  /*初始化LED灯PA5*/
  BSP_LED_Init(LED_GREEN);

  /*配置系统时钟*/
  APP_SystemClockConfig();

  /*解锁FLASH*/
  HAL_FLASH_Unlock();

  /*擦除FLASH*/
  APP_FlashErase();

  /*查空FLASH*/
  APP_FlashBlank();

  /*写FLASH*/
  APP_FlashProgram();

  /*锁定FLASH*/
  HAL_FLASH_Lock();

  /*校验FLASH*/
  APP_FlashVerify();

  while (1)
  {
    /*程序执行成功，LED灯翻转*/
    BSP_LED_Toggle(LED_GREEN);

    /*延时500ms*/
    HAL_Delay(500);
  }
}

/**
  * @brief  系统时钟配置函数
  * @param  无
  * @retval 无
  */
void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* 振荡器配置 */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI; /* 选择振荡器HSE,HSI,LSI */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                                                       /* 开启HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                                                       /* HSI 1分频 */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_8MHz;                               /* 配置HSI时钟8MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_OFF;                                                      /* 关闭HSE */
  /*RCC_OscInitStruct.HSEFreq = RCC_HSE_16_32MHz;*/
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                                                      /* 关闭LSI */
                         
  /* 配置振荡器 */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* 时钟源配置 */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* 选择配置时钟 HCLK,SYSCLK,PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;                                         /* 选择HSI作为系统时钟 */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;                                             /* AHB时钟 1分频 */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;                                              /* APB时钟 1分频 */
  /* 配置时钟源 */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  擦除FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashErase(void)
{
  uint32_t PAGEError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct;

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGEERASE;                                     /* 擦写类型FLASH_TYPEERASE_PAGEERASE=Page擦, FLASH_TYPEERASE_SECTORERASE=Sector擦 */
  EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;                                         /* 擦写起始地址 */
  EraseInitStruct.NbPages  = sizeof(DATA) / FLASH_PAGE_SIZE;                                   /* 需要擦写的页数量 */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)                               /* 执行page擦除,PAGEError返回擦写错误的page,返回0xFFFFFFFF,表示擦写成功 */
  {
    Error_Handler();
  }
}
/**
  * @brief  写FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* flash写起始地址 */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* flash写结束地址 */
  uint32_t *src = (uint32_t *)DATA;                                                     /* 数组指针 */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* 执行Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* flash起始指针指向第一个page */
      src += FLASH_PAGE_SIZE / 4;                                                       /* 更新数据指针 */
    }
  }
}
/**
  * @brief  查空FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashBlank(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (0xFFFFFFFF != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      Error_Handler();
    }
    addr += 4;
  }
}
/**
  * @brief  校验FLASH
  * @param  无
  * @retval 无
  */
static void APP_FlashVerify(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (DATA[addr / 4] != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      Error_Handler();
    }
    addr += 4;
  }
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
