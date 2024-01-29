/**
  ******************************************************************************
  * @file    py32f0xx_hal_opt.c
  * @author  MCU Application Team
  * @Version V1.0.0
  * @Date    2020-10-19
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal_opt.h"


#ifdef FLASH_OPT_PROGRAM_ENABLED

#if defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  const uint32_t u32ICG[] __attribute__((section(".opt_sec"))) =
#elif defined (__CC_ARM)
  const uint32_t u32ICG[] __attribute__((at(0x1FFF0E80))) =
#elif defined (__ICCARM__)
  __root const uint32_t u32ICG[] @ 0x1FFF0E80 =
#else
  #error "unsupported compiler!!"
#endif
{
  0x4F55B0AA,
  0xE0EF1F10,
  0xFFFFFFFF,
  0x0000FFFF,
};

#endif /* FLASH_OPT_PROGRAM_ENABLED */



