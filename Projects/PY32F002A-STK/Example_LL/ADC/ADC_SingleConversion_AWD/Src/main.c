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
#define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t) 1)
#define VDDA_APPLI                       ((uint32_t)3300)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private variables ---------------------------------------------------------*/
__IO uint8_t ubAnalogWatchdog1Status = 0;

/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
static void APP_AdcConfig(void);
static void APP_AdcEnable(void);
static void APP_AdcCalibrate(void);
static void APP_TimerInit(void);
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

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();

  LL_ADC_Reset(ADC1);

  /* 使能ADC1时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* ADC校准 */
  APP_AdcCalibrate();

  /* 配置ADC参数 */
  APP_AdcConfig();

  /* 使能ADC */
  APP_AdcEnable();

  LL_ADC_REG_StartConversion(ADC1);

  /* TIM1初始化 */
  APP_TimerInit();
  while (1)
  {
     if(ubAnalogWatchdog1Status==1)
    {
      /* LED灯闪烁 */
      BSP_LED_Toggle(LED_GREEN);
      LL_mDelay(500);
    }
  }
}

/**
  * @brief  ADC配置函数.
  * @param  无
  * @retval 无
  */
static void APP_AdcConfig(void)
{

  /*## 配置ADC通道和管脚 ############################*/

  /* 注意: 在PY32系列中，ADC 通道4对应 GPIO PA4 */

  /* 使能GPIOA时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 配置管脚4为模拟输入 */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* ADC通道和时钟源需在ADEN=0时配置，其余的需在ADSTART=0时配置 */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE);

  /* 设置ADC时钟 */
  LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV2);

  /* 设置12位分辨率 */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

  /* 设置数据右对齐 */
  LL_ADC_SetResolution(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* 设置低功率模式无 */
  LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

  /* 设置通道转换时间 */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_41CYCLES_5);

  /* 设置触发源为TIM1_TRGO触发 */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_EXT_TIM1_TRGO);

  /* 设置上升沿触发转换 */
  LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);

  /* 设置转换模式为单次转换 */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);


  /* 设置过载管理模式为覆盖上一个值 */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* 设置非连续模式为不使能 */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* 设置通道4为转换通道      */
  LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);

  /*## 配置模拟看门狗 ###############*/

  /* 设置看门狗的通道 */
  LL_ADC_SetAnalogWDMonitChannels(ADC1, LL_ADC_AWD_ALL_CHANNELS_REG);

  /* 设置看门狗的阙值 */
  LL_ADC_ConfigAnalogWDThresholds(ADC1, __LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B)/2, 0x000);

  LL_ADC_EnableIT_AWD(ADC1);
  NVIC_SetPriority(ADC_COMP_IRQn, 0);
  NVIC_EnableIRQ(ADC_COMP_IRQn);
  
}
/**
  * @brief  ADC校准函数.
  * @param  无
  * @retval 无
  */
static void APP_AdcCalibrate(void)
{
  __IO uint32_t wait_loop_index = 0;
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
#endif /* USE_TIMEOUT */

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* 使能校准 */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif /* USE_TIMEOUT */

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
#if (USE_TIMEOUT == 1)
      /* 检测校准是否超时 */
      if (LL_SYSTICK_IsActiveCounterFlag())
      {
        if(Timeout-- == 0)
        {

        }
      }
#endif /* USE_TIMEOUT */
    }

    /* ADC校准结束和使能ADC之间的延时最低4个ADC Clock */
    LL_mDelay(1);
  }
}

/**
  * @brief  ADC使能函数
  * @param  无
  * @retval 无
  */
static void APP_AdcEnable(void)
{
  /* 使能ADC */
  LL_ADC_Enable(ADC1);

  /* 使能ADC 稳定时间，最低8个ADC Clock */
  LL_mDelay(1);
}
/**
  * @brief  模拟看门狗回调函数
  * @param  无
  * @retval 无
  */
void APP_AdcAnalogWatchdogCallback(void)
{
  /* 关闭看门狗中断 */
  LL_ADC_DisableIT_AWD(ADC1);

  /* 设置看门狗状态 */
  ubAnalogWatchdog1Status = 1;
}
/**
  * @brief  TIM1配置函数
  * @param  无
  * @retval 无
  */
static void APP_TimerInit(void)
{
  /* 使能TIM1时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* 设置TIM1预分频器 */
  LL_TIM_SetPrescaler(TIM1,2000);

  /* 设置TIM1自动重装载值 */
  LL_TIM_SetAutoReload(TIM1, 4000);

  /* 设置TIM1更新触发 */
  LL_TIM_SetTriggerOutput(TIM1,LL_TIM_TRGO_UPDATE);

  /* 使能TIM1 */
  LL_TIM_EnableCounter(TIM1);
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
