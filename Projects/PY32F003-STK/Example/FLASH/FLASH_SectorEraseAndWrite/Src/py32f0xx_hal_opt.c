/**
  ******************************************************************************
  * @file    py32f0xx_hal_opt.c
  * @author  MCU Application Team
  * @brief   HAL configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
