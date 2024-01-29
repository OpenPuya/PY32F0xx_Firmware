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
#include "py32f030xx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t) 1)
#define VDDA_APPLI                       ((uint32_t)3300)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private variables ---------------------------------------------------------*/
__IO uint32_t ubUserButtonPressed = 0;
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;

/*DMA传输的目标源*/
static uint32_t ADCxConvertedDatas;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcCalibrate(void);
static void APP_AdcConfig(void);
static void APP_AdcEnable(void);
static void APP_TimerInit(void);
static void APP_DmaConfig(void);

/**
  * @brief  应用程序入口函数.
  * @retval int
  */
int main(void)
{
  /* 配置系统时钟 */
  APP_SystemClockConfig();

  /* 初始化LED */
  BSP_LED_Init(LED_GREEN);

  /* 初始化调试串口(printf使用) */
  BSP_USART_Config();
  printf("ADC Timer Trigger DMA Demo");

  /* 配置DMA */
  APP_DmaConfig();

  /* 使能DMA */
  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

  /* 复位ADC*/
  LL_ADC_Reset(ADC1);

  /* 使能ADC1时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* ADC校准 */
  APP_AdcCalibrate();

  /* 配置ADC参数 */
  APP_AdcConfig();

  /* 使能ADC */
  APP_AdcEnable();

  /* 开始ADC转换(如果是软件触发则直接开始转换) */
  LL_ADC_REG_StartConversion(ADC1);

  /* TIM1初始化*/
  APP_TimerInit();
  while (1)
  {
    /* LED灯闪烁 */
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(1000);
  }
}

/**
  * @brief  ADC配置函数
  * @param  无
  * @retval 无
  */
static void APP_AdcConfig(void)
{
  /* 使能GPIOA时钟 */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* 配置管脚4为模拟输入 */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_ANALOG);

  /* ADC通道和时钟源需在ADEN=0时配置，其余的需在ADSTART=0时配置 */
  /* 配置内部转换通道 */
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

  /* 设置触发源为TIM1 TRGO */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_EXT_TIM1_TRGO);

  /* 设置上升沿触发转换 */
  LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);

  /* 设置转换模式为单次转换 */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  /* 设置DMA模式为循环模式，并开启 */
  LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_UNLIMITED);

  /* 设置过载管理模式为覆盖上一个值 */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* 设置非连续模式为不使能 */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* 设置通道4为转换通道      */
  LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);

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
  * @brief  ADC校准函数
  * @param  无
  * @retval 无
  */
static void APP_AdcCalibrate(void)
{
  __IO uint32_t wait_loop_index = 0;
  __IO uint32_t backup_setting_adc_dma_transfer = 0;
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0;
#endif

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {
    /* 校准时关闭ADC的DMA配置 */
    backup_setting_adc_dma_transfer = LL_ADC_REG_GetDMATransfer(ADC1);
    LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
    /* 使能校准 */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif

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
#endif
    }

    /* ADC校准结束和使能ADC之间的延时最低4个ADC Clock */
    LL_mDelay(1);

    /* 还原ADC的DMA配置 */
    LL_ADC_REG_SetDMATransfer(ADC1, backup_setting_adc_dma_transfer);
  }
}

/**
  * @brief  TIM配置函数
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
  * @brief  DMA配置函数
  * @param  无
  * @retval 无
  */
static void APP_DmaConfig(void)
{
  /* 使能DMA1 时钟 */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* 使能syscfg 时钟 */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);

  /* ADC对应通道LL_DMA_CHANNEL_1 */
  SET_BIT(SYSCFG->CFGR3, 0x0);

  /* 配置DMA传输方向为外设到存储器 */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  /* 配置DMA优先级为高 */
  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);

  /* 配置DMA循环模式 */
  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

  /* 配置DMA外设地址不变模式 */
  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

  /* 配置DMA存储地址不变模式 */
  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_NOINCREMENT);

  /* 配置DMA外设传输方式为字 */
  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);

  /* 配置DMA存储器传输方式为字 */
  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_WORD);

  /* 配置DMA传输长度为1 */
  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 1);

  /* 配置DMA外设和存储器的地址 */
  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&ADC1->DR, (uint32_t)&ADCxConvertedDatas, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1));

  /* 使能DMA传输完成中断 */
  LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_1);

  NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
  NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}

/**
  * @brief  DMA传输完成回调函数
  * @param  无
  * @retval 无
  */
void APP_TransferCompleteCallback(void)
{
  /*将ADC的采样值转换为电压值*/
  uhADCxConvertedData_Voltage_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI, ADCxConvertedDatas, LL_ADC_RESOLUTION_12B);
  printf("%s%s%d mV\r\n","Channel4","Voltage:",uhADCxConvertedData_Voltage_mVolt);
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
