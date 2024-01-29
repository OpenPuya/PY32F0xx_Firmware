/**
  ******************************************************************************
  * @file    main.h
  * @author  MCU Application Team
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"
#include "py32f030xx_Start_Kit.h"

/* Private includes ----------------------------------------------------------*/
#include <stdbool.h>

/* Private defines -----------------------------------------------------------*/
#define __TIMx_CLK_ENABLE()              __HAL_RCC_TIM14_CLK_ENABLE()
#define	TIMx                      TIM14
#define	TIM_CHANNEL_y             TIM_CHANNEL_1
#define	HAL_TIM_ACTIVE_CHANNEL_y  HAL_TIM_ACTIVE_CHANNEL_1
#define	TIM_TIMx_RTC              TIM_TIM14_RTC
#define	TIM_TIMx_GPIO             TIM_TIM14_GPIO
#define	TIM_TIMx_HSE              TIM_TIM14_HSE
#define	TIM_TIMx_MCO              TIM_TIM14_MCO
#define	TIMx_COUNTER_PRESCALER    TIM14_COUNTER_PRESCALER
#define	TIMx_IC_DIVIDER           TIM14_IC_DIVIDER
#define	TIMx_IRQn                 TIM14_IRQn
#define	GPIO_AF4_TIMx             GPIO_AF4_TIM14
#define	TIM_TIMx_MCO              TIM_TIM14_MCO

#define INITIAL_ERROR             ((uint32_t)99999000)
#define CAPTURE_START             ((uint32_t)0x00000001)
#define CAPTURE_ONGOING           ((uint32_t)0x00000002)
#define CAPTURE_COMPLETED         ((uint32_t)0x00000003)
#define TIMx_CHANNEL_GPIO_PORT()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define TIMx_GPIO_PORT                 GPIOA
#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_4

#define __HAL_GET_TIM_PRESCALER(__HANDLE__)       ((__HANDLE__)->Instance->PSC)
#define ABS_RETURN(x)                             ((x < 0) ? (-x) : (x))
#define GET_HSI_TRIMMINIG_VALUE()                 (( RCC->CR & RCC_ICSCR_HSI_TRIM ) >> 0)

/* Exported variables prototypes ---------------------------------------------*/
extern TIM_HandleTypeDef       TimHandle; /* Timer handler declaration */
extern uint32_t   ICCapture1, ICCapture2, ICCapture3;
extern uint32_t   __IO CaptureState;
extern uint32_t   __IO Capture;
extern uint32_t   StartCalibration;
extern int32_t    aFrequenceChangeTable[64];
extern uint32_t   TrimmingCurveMeasured;

/* Exported functions prototypes ---------------------------------------------*/
void APP_ErrorHandler(void);
void TimingDelay_Decrement(void);
void SystemClock_Config(uint32_t HSICLKSource_selt);
void SetSysClock_HSI_48MHz(void);
void CLK_ConfigForCalibration(void);
void GPIO_ConfigForCalibration(void);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
