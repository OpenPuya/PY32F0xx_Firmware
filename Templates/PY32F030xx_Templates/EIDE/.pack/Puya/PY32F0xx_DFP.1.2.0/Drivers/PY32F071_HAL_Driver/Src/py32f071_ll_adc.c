/**
  ******************************************************************************
  * @file    py32f071_ll_adc.c
  * @author  MCU Application Team
  * @brief   ADC LL module driver
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

#if defined(USE_FULL_LL_DRIVER)

/* Includes ------------------------------------------------------------------*/
#include "py32f071_ll_adc.h"
#include "py32f071_ll_bus.h"

#ifdef  USE_FULL_ASSERT
  #include "py32_assert.h"
#else
  #define assert_param(expr) ((void)0U)
#endif

/** @addtogroup PY32F071_LL_Driver
  * @{
  */

#if defined (ADC1)

/** @addtogroup ADC_LL ADC
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup ADC_LL_Private_Macros
  * @{
  */

/* Check of parameters for configuration of ADC hierarchical scope:           */
/* common to several ADC instances.                                           */
/* Check of parameters for configuration of ADC hierarchical scope:           */
/* ADC instance.                                                              */
#define IS_LL_ADC_DATA_ALIGN(__DATA_ALIGN__)                                   \
  (   ((__DATA_ALIGN__) == LL_ADC_DATA_ALIGN_RIGHT)                            \
   || ((__DATA_ALIGN__) == LL_ADC_DATA_ALIGN_LEFT)                             \
  )

#define IS_LL_ADC_SCAN_SELECTION(__SCAN_SELECTION__)                           \
  (   ((__SCAN_SELECTION__) == LL_ADC_SEQ_SCAN_DISABLE)                        \
   || ((__SCAN_SELECTION__) == LL_ADC_SEQ_SCAN_ENABLE)                         \
  )

#define IS_LL_ADC_SEQ_SCAN_MODE(__SEQ_SCAN_MODE__)                             \
  (   ((__SCAN_MODE__) == LL_ADC_SEQ_SCAN_DISABLE)                             \
   || ((__SCAN_MODE__) == LL_ADC_SEQ_SCAN_ENABLE)                              \
  )

/* Check of parameters for configuration of ADC hierarchical scope:           */
/* ADC group regular                                                          */
#define IS_LL_ADC_REG_TRIG_SOURCE(__REG_TRIG_SOURCE__)                         \
  (   ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_SOFTWARE)                      \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM1_CH1)                  \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM1_CH2)                  \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM1_CH3)                  \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM2_CH2)                  \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM3_TRGO)                 \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_TIM15_TRGO)                \
   || ((__REG_TRIG_SOURCE__) == LL_ADC_REG_TRIG_EXT_EXTI_LINE11)               \
  )

#define IS_LL_ADC_REG_CONTINUOUS_MODE(__REG_CONTINUOUS_MODE__)                 \
  (   ((__REG_CONTINUOUS_MODE__) == LL_ADC_REG_CONV_SINGLE)                    \
   || ((__REG_CONTINUOUS_MODE__) == LL_ADC_REG_CONV_CONTINUOUS)                \
  )

#define IS_LL_ADC_REG_DMA_TRANSFER(__REG_DMA_TRANSFER__)                       \
  (   ((__REG_DMA_TRANSFER__) == LL_ADC_REG_DMA_TRANSFER_NONE)                 \
   || ((__REG_DMA_TRANSFER__) == LL_ADC_REG_DMA_TRANSFER_UNLIMITED)            \
  )

#define IS_LL_ADC_REG_SEQ_SCAN_LENGTH(__REG_SEQ_SCAN_LENGTH__)                 \
  (   ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_DISABLE)               \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_2RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_3RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_4RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_5RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_7RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_8RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_9RANKS)         \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_10RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_11RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_12RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_13RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_14RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_15RANKS)        \
   || ((__REG_SEQ_SCAN_LENGTH__) == LL_ADC_REG_SEQ_SCAN_ENABLE_16RANKS)        \
  )

#define IS_LL_ADC_REG_SEQ_SCAN_DISCONT_MODE(__REG_SEQ_DISCONT_MODE__)          \
  (   ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_DISABLE)           \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_1RANK)             \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_2RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_3RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_4RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_5RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_6RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_7RANKS)            \
   || ((__REG_SEQ_DISCONT_MODE__) == LL_ADC_REG_SEQ_DISCONT_8RANKS)            \
  )

/* Check of parameters for configuration of ADC hierarchical scope:           */
/* ADC group injected                                                         */
#define IS_LL_ADC_INJ_TRIG_SOURCE(__INJ_TRIG_SOURCE__)                         \
  (   ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_SOFTWARE)                      \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM1_TRGO)                 \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM1_CH4)                  \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM2_TRGO)                 \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM2_CH1)                  \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM3_TRGO)                 \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_TIM15_TRGO)                \
   || ((__INJ_TRIG_SOURCE__) == LL_ADC_INJ_TRIG_EXT_EXTI_LINE15)               \
  )


#define IS_LL_ADC_INJ_TRIG_AUTO(__INJ_TRIG_AUTO__)                             \
  (   ((__INJ_TRIG_AUTO__) == LL_ADC_INJ_TRIG_INDEPENDENT)                     \
   || ((__INJ_TRIG_AUTO__) == LL_ADC_INJ_TRIG_FROM_GRP_REGULAR)                \
  )

#define IS_LL_ADC_INJ_SEQ_SCAN_LENGTH(__INJ_SEQ_SCAN_LENGTH__)                 \
  (   ((__INJ_SEQ_SCAN_LENGTH__) == LL_ADC_INJ_SEQ_SCAN_DISABLE)               \
   || ((__INJ_SEQ_SCAN_LENGTH__) == LL_ADC_INJ_SEQ_SCAN_ENABLE_2RANKS)         \
   || ((__INJ_SEQ_SCAN_LENGTH__) == LL_ADC_INJ_SEQ_SCAN_ENABLE_3RANKS)         \
   || ((__INJ_SEQ_SCAN_LENGTH__) == LL_ADC_INJ_SEQ_SCAN_ENABLE_4RANKS)         \
  )

#define IS_LL_ADC_INJ_SEQ_SCAN_DISCONT_MODE(__INJ_SEQ_DISCONT_MODE__)          \
  (   ((__INJ_SEQ_DISCONT_MODE__) == LL_ADC_INJ_SEQ_DISCONT_DISABLE)           \
   || ((__INJ_SEQ_DISCONT_MODE__) == LL_ADC_INJ_SEQ_DISCONT_1RANK)             \
  )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_LL_Exported_Functions
  * @{
  */

/** @addtogroup ADC_LL_EF_Init
  * @{
  */

#if defined(ADC_MULTIMODE_SUPPORT)
/**
  * @brief  De-initialize registers of all ADC instances belonging to
  *         the same ADC common instance to their default reset values.
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC common registers are de-initialized
  *          - ERROR: not applicable
  */
ErrorStatus LL_ADC_CommonDeInit(ADC_Common_TypeDef *ADCxy_COMMON)
{
  /* Check the parameters */
  assert_param(IS_ADC_COMMON_INSTANCE(ADCxy_COMMON));
  
  /* Force reset of ADC clock (core clock) */
  LL_APB1_GRP2_ForceReset(LL_APB1_GRP2_PERIPH_ADC1);
  
  /* Release reset of ADC clock (core clock) */
  LL_APB1_GRP2_ReleaseReset(LL_APB1_GRP2_PERIPH_ADC1);
  
  return SUCCESS;
}

/**
  * @brief  Initialize some features of ADC common parameters
  *         (all ADC instances belonging to the same ADC common instance)
  *         and multimode (for devices with several ADC instances available).
  * @note   The setting of ADC common parameters is conditioned to
  *         ADC instances state:
  *         All ADC instances belonging to the same ADC common instance
  *         must be disabled.
  * @param  ADCxy_COMMON ADC common instance
  *         (can be set directly from CMSIS definition or by using helper macro @ref __LL_ADC_COMMON_INSTANCE() )
  * @param  ADC_CommonInitStruct Pointer to a @ref LL_ADC_CommonInitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC common registers are initialized
  *          - ERROR: ADC common registers are not initialized
  */
ErrorStatus LL_ADC_CommonInit(ADC_Common_TypeDef *ADCxy_COMMON, LL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_ADC_COMMON_INSTANCE(ADCxy_COMMON));
#if defined(ADC_MULTIMODE_SUPPORT)
  assert_param(IS_LL_ADC_MULTI_MODE(ADC_CommonInitStruct->Multimode));
#endif /* ADC_MULTIMODE_SUPPORT */

  /* Note: Hardware constraint (refer to description of functions             */
  /*       "LL_ADC_SetCommonXXX()" and "LL_ADC_SetMultiXXX()"):               */
  /*       All ADC instances of the ADC common group must be disabled.        */
  if(__LL_ADC_IS_ENABLED_ALL_COMMON_INSTANCE(ADCxy_COMMON) == 0U)
  {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - common to several ADC                                               */
    /*    (all ADC instances belonging to the same ADC common instance)       */
    /*  - multimode (if several ADC instances available on the                */
    /*    selected device)                                                    */
    /*    - Set ADC multimode configuration                                   */
    /*    - Set ADC multimode DMA transfer                                    */
    /*    - Set ADC multimode: delay between 2 sampling phases                */

  }
  else
  {
    /* Initialization error: One or several ADC instances belonging to        */
    /* the same ADC common instance are not disabled.                         */
    status = ERROR;
  }
  
  return status;
}

/**
  * @brief  Set each @ref LL_ADC_CommonInitTypeDef field to default value.
  * @param  ADC_CommonInitStruct Pointer to a @ref LL_ADC_CommonInitTypeDef structure
  *                              whose fields will be set to default values.
  * @retval None
  */
void LL_ADC_CommonStructInit(LL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
  /* Set ADC_CommonInitStruct fields to default values */
  /* Set fields of ADC common */
  /* (all ADC instances belonging to the same ADC common instance) */
  
}

#endif

/**
  * @brief  De-initialize registers of the selected ADC instance
  *         to their default reset values.
  * @note   To reset all ADC instances quickly (perform a hard reset),
  *         use function @ref LL_ADC_CommonDeInit().
  * @param  ADCx ADC instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are de-initialized
  *          - ERROR: ADC registers are not de-initialized
  */
ErrorStatus LL_ADC_DeInit(ADC_TypeDef *ADCx)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  
  /* Disable ADC instance if not already disabled.                            */
  if(LL_ADC_IsEnabled(ADCx) == 1U)
  {
    /* Set ADC group regular trigger source to SW start to ensure to not      */
    /* have an external trigger event occurring during the conversion stop    */
    /* ADC disable process.                                                   */
    LL_ADC_REG_SetTriggerSource(ADCx, LL_ADC_REG_TRIG_SOFTWARE);
    
    /* Set ADC group injected trigger source to SW start to ensure to not     */
    /* have an external trigger event occurring during the conversion stop    */
    /* ADC disable process.                                                   */
    LL_ADC_INJ_SetTriggerSource(ADCx, LL_ADC_INJ_TRIG_SOFTWARE);
    
    /* Disable the ADC instance */
    LL_ADC_Disable(ADCx);
  }
  
  /* Check whether ADC state is compliant with expected state */
  /* (hardware requirements of bits state to reset registers below) */
  if(READ_BIT(ADCx->CR2, ADC_CR2_ADON) == 0U)
  {
    /* Read DR to clear the Over flag */
    (void)ADCx->DR;
    
    /* ========== Reset ADC registers ========== */
    /* Reset register SR */
    CLEAR_BIT(ADCx->SR,
              (  LL_ADC_FLAG_STRT
               | LL_ADC_FLAG_JSTRT
               | LL_ADC_FLAG_EOS
               | LL_ADC_FLAG_JEOS
               | LL_ADC_FLAG_AWD1 )
             );

    CLEAR_BIT(ADCx->CR1,
              (  ADC_CR1_AWDEN   | ADC_CR1_JAWDEN  | ADC_CR1_DISCNUM 
               | ADC_CR1_JDISCEN | ADC_CR1_DISCEN  | ADC_CR1_JAUTO
               | ADC_CR1_AWDSGL  | ADC_CR1_SCAN    | ADC_CR1_JEOCIE  
               | ADC_CR1_AWDIE   | ADC_CR1_EOCIE   | ADC_CR1_AWDCH | ADC_CR1_RESSEL | ADC_CR1_OVRIE)
             );
#if defined(ADC_CR2_VREFBUFFERE)
    /* Reset register CR2 */
    CLEAR_BIT(ADCx->CR2,
              (  ADC_CR2_TSVREFE  | ADC_CR2_VREFBUFFERE | ADC_CR2_VREFBUFFERSEL
               | ADC_CR2_SWSTART  | ADC_CR2_EXTTRIG  | ADC_CR2_EXTSEL
               | ADC_CR2_JSWSTART | ADC_CR2_JEXTTRIG | ADC_CR2_JEXTSEL
               | ADC_CR2_ALIGN    | ADC_CR2_DMA
               | ADC_CR2_RSTCAL   | ADC_CR2_CAL
               | ADC_CR2_CONT     | ADC_CR2_ADON                      )
             );
#else
    /* Reset register CR2 */
    CLEAR_BIT(ADCx->CR2,
              (  ADC_CR2_TSVREFE
               | ADC_CR2_SWSTART  | ADC_CR2_EXTTRIG  | ADC_CR2_EXTSEL
               | ADC_CR2_JSWSTART | ADC_CR2_JEXTTRIG | ADC_CR2_JEXTSEL
               | ADC_CR2_ALIGN    | ADC_CR2_DMA
               | ADC_CR2_RSTCAL   | ADC_CR2_CAL
               | ADC_CR2_CONT     | ADC_CR2_ADON                      )
             );
#endif
             
    /* Reset register SMPR1 */
    CLEAR_BIT(ADCx->SMPR1,
              (  ADC_SMPR1_SMP23
               | ADC_SMPR1_SMP22 | ADC_SMPR1_SMP21 | ADC_SMPR1_SMP20)
             );        
    
    /* Reset register SMPR2 */
    CLEAR_BIT(ADCx->SMPR2,
              (  ADC_SMPR2_SMP19
               | ADC_SMPR2_SMP18 | ADC_SMPR2_SMP17 | ADC_SMPR2_SMP16
               | ADC_SMPR2_SMP15 | ADC_SMPR2_SMP14 | ADC_SMPR2_SMP13
               | ADC_SMPR2_SMP12 | ADC_SMPR2_SMP11 | ADC_SMPR2_SMP10)
             );
    
    /* Reset register SMPR3 */
    CLEAR_BIT(ADCx->SMPR3,
              (  ADC_SMPR3_SMP9
               | ADC_SMPR3_SMP8 | ADC_SMPR3_SMP7 | ADC_SMPR3_SMP6
               | ADC_SMPR3_SMP5 | ADC_SMPR3_SMP4 | ADC_SMPR3_SMP3
               | ADC_SMPR3_SMP2 | ADC_SMPR3_SMP1 | ADC_SMPR3_SMP0)
             );
    
    /* Reset register JOFR1 */
    CLEAR_BIT(ADCx->JOFR1, ADC_JOFR1_JOFFSET1);
    /* Reset register JOFR2 */
    CLEAR_BIT(ADCx->JOFR2, ADC_JOFR2_JOFFSET2);
    /* Reset register JOFR3 */
    CLEAR_BIT(ADCx->JOFR3, ADC_JOFR3_JOFFSET3);
    /* Reset register JOFR4 */
    CLEAR_BIT(ADCx->JOFR4, ADC_JOFR4_JOFFSET4);
    
    /* Reset register HTR */
    SET_BIT(ADCx->HTR, ADC_HTR_HT);
    /* Reset register LTR */
    CLEAR_BIT(ADCx->LTR, ADC_LTR_LT);
    
    /* Reset register SQR1 */
    CLEAR_BIT(ADCx->SQR1,
              (  ADC_SQR1_L
               | ADC_SQR1_SQ16
               | ADC_SQR1_SQ15 | ADC_SQR1_SQ14 | ADC_SQR1_SQ13)
             );
             
    /* Reset register SQR2 */
    CLEAR_BIT(ADCx->SQR2,
              (  ADC_SQR2_SQ12 | ADC_SQR2_SQ11 | ADC_SQR2_SQ10
               | ADC_SQR2_SQ9 | ADC_SQR2_SQ8 | ADC_SQR2_SQ7)
             );
             
    /* Reset register SQR3 */
    CLEAR_BIT(ADCx->SQR3,
              (  ADC_SQR3_SQ6 | ADC_SQR3_SQ5 | ADC_SQR3_SQ4
               | ADC_SQR3_SQ3 | ADC_SQR3_SQ2 | ADC_SQR3_SQ1)
             );
      
    /* Reset register JSQR */
    CLEAR_BIT(ADCx->JSQR,
              (  ADC_JSQR_JL
               | ADC_JSQR_JSQ4 | ADC_JSQR_JSQ3
               | ADC_JSQR_JSQ2 | ADC_JSQR_JSQ1  )
             );
             
    /* Reset register CCSR */
    CLEAR_BIT(ADCx->CCSR,
              ( ADC_CCSR_CALSMP | ADC_CCSR_CALSEL  )
             );
    /* Reset register CCSR */
    SET_BIT(ADCx->CCSR,
              ( ADC_CCSR_CAPSUC | ADC_CCSR_OFFSUC )
             );        
    
    /* Reset register DR */
    /* bits in access mode read only, no direct reset applicable */
    
    /* Reset registers JDR1, JDR2, JDR3, JDR4 */
    /* bits in access mode read only, no direct reset applicable */
    
  }
  
  return status;
}

/**
  * @brief  Initialize some features of ADC instance.
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  * @note   After using this function, some other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group regular or group injected sequencer:
  *            map channel on the selected sequencer rank.
  *            Refer to function @ref LL_ADC_REG_SetSequencerRanks().
  *          - Set ADC channel sampling time
  *            Refer to function LL_ADC_SetChannelSamplingTime();
  * @param  ADCx ADC instance
  * @param  ADC_InitStruct Pointer to a @ref LL_ADC_REG_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus LL_ADC_Init(ADC_TypeDef *ADCx, LL_ADC_InitTypeDef *ADC_InitStruct)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  
  assert_param(IS_LL_ADC_DATA_ALIGN(ADC_InitStruct->DataAlignment));
  assert_param(IS_LL_ADC_SCAN_SELECTION(ADC_InitStruct->SequencersScanMode));
  
  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if(LL_ADC_IsEnabled(ADCx) == 0U)
  {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC instance                                                        */
    /*    - Set ADC conversion data alignment                                 */
    MODIFY_REG(ADCx->CR1,
                 ADC_CR1_SCAN
              ,
                 ADC_InitStruct->SequencersScanMode
              );
    
    MODIFY_REG(ADCx->CR2,
                 ADC_CR2_ALIGN
              ,
                 ADC_InitStruct->DataAlignment
              );

  }
  else
  {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }
  return status;
}

/**
  * @brief  Set each @ref LL_ADC_InitTypeDef field to default value.
  * @param  ADC_InitStruct Pointer to a @ref LL_ADC_InitTypeDef structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void LL_ADC_StructInit(LL_ADC_InitTypeDef *ADC_InitStruct)
{
  /* Set ADC_InitStruct fields to default values */
  /* Set fields of ADC instance */
  ADC_InitStruct->DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
  
  /* Enable scan mode to have a generic behavior with ADC of other            */
  /* ADC group regular sequencer and ADC group injected sequencer depend      */
  /* only of their own configuration.                                         */
  ADC_InitStruct->SequencersScanMode      = LL_ADC_SEQ_SCAN_ENABLE;
  
}

/**
  * @brief  Initialize some features of ADC group regular.
  * @note   These parameters have an impact on ADC scope: ADC group regular.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "REG").
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @note   After using this function, other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group regular or group injected sequencer:
  *            map channel on the selected sequencer rank.
  *            Refer to function @ref LL_ADC_REG_SetSequencerRanks().
  *          - Set ADC channel sampling time
  *            Refer to function LL_ADC_SetChannelSamplingTime();
  * @param  ADCx ADC instance
  * @param  ADC_REG_InitStruct Pointer to a @ref LL_ADC_REG_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus LL_ADC_REG_Init(ADC_TypeDef *ADCx, LL_ADC_REG_InitTypeDef *ADC_REG_InitStruct)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_REG_TRIG_SOURCE(ADC_REG_InitStruct->TriggerSource));
  assert_param(IS_LL_ADC_REG_SEQ_SCAN_LENGTH(ADC_REG_InitStruct->SequencerLength));
  if(ADC_REG_InitStruct->SequencerLength != LL_ADC_REG_SEQ_SCAN_DISABLE)
  {
    assert_param(IS_LL_ADC_REG_SEQ_SCAN_DISCONT_MODE(ADC_REG_InitStruct->SequencerDiscont));
  }
  assert_param(IS_LL_ADC_REG_CONTINUOUS_MODE(ADC_REG_InitStruct->ContinuousMode));
  assert_param(IS_LL_ADC_REG_DMA_TRANSFER(ADC_REG_InitStruct->DMATransfer));
  
  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if(LL_ADC_IsEnabled(ADCx) == 0U)
  {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC group regular                                                   */
    /*    - Set ADC group regular trigger source                              */
    /*    - Set ADC group regular sequencer length                            */
    /*    - Set ADC group regular sequencer discontinuous mode                */
    /*    - Set ADC group regular continuous mode                             */
    /*    - Set ADC group regular conversion data transfer: no transfer or    */
    /*      transfer by DMA, and DMA requests mode                            */
    if(ADC_REG_InitStruct->SequencerLength != LL_ADC_REG_SEQ_SCAN_DISABLE)
    {
      MODIFY_REG(ADCx->CR1,
                   ADC_CR1_DISCEN
                 | ADC_CR1_DISCNUM
                ,
                   ADC_REG_InitStruct->SequencerLength
                 | ADC_REG_InitStruct->SequencerDiscont
                );
    }
    else
    {
      MODIFY_REG(ADCx->CR1,
                   ADC_CR1_DISCEN
                 | ADC_CR1_DISCNUM
                ,
                   ADC_REG_InitStruct->SequencerLength
                 | LL_ADC_REG_SEQ_DISCONT_DISABLE
                );
    }
    
    MODIFY_REG(ADCx->CR2,
                 ADC_CR2_EXTSEL
               | ADC_CR2_CONT
               | ADC_CR2_DMA
              ,
                 ADC_REG_InitStruct->TriggerSource
               | ADC_REG_InitStruct->ContinuousMode
               | ADC_REG_InitStruct->DMATransfer
              );

    /* Set ADC group regular sequencer length and scan direction */
    /* Note: Hardware constraint (refer to description of this function):     */
    /* Note: If ADC instance feature scan mode is disabled                    */
    /*       (refer to  ADC instance initialization structure                 */
    /*       parameter @ref SequencersScanMode                                */
    /*       or function @ref LL_ADC_SetSequencersScanMode() ),               */
    /*       this parameter is discarded.                                     */
    LL_ADC_REG_SetSequencerLength(ADCx, ADC_REG_InitStruct->SequencerLength);
  }
  else
  {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }
  return status;
}

/**
  * @brief  Set each @ref LL_ADC_REG_InitTypeDef field to default value.
  * @param  ADC_REG_InitStruct Pointer to a @ref LL_ADC_REG_InitTypeDef structure
  *                            whose fields will be set to default values.
  * @retval None
  */
void LL_ADC_REG_StructInit(LL_ADC_REG_InitTypeDef *ADC_REG_InitStruct)
{
  /* Set ADC_REG_InitStruct fields to default values */
  /* Set fields of ADC group regular */
  ADC_REG_InitStruct->TriggerSource    = LL_ADC_REG_TRIG_SOFTWARE;
  ADC_REG_InitStruct->SequencerLength  = LL_ADC_REG_SEQ_SCAN_DISABLE;
  ADC_REG_InitStruct->SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
  ADC_REG_InitStruct->ContinuousMode   = LL_ADC_REG_CONV_SINGLE;
  ADC_REG_InitStruct->DMATransfer      = LL_ADC_REG_DMA_TRANSFER_NONE;
}

/**
  * @brief  Initialize some features of ADC group injected.
  * @note   These parameters have an impact on ADC scope: ADC group injected.
  *         Refer to corresponding unitary functions into
  *         @ref ADC_LL_EF_Configuration_ADC_Group_Regular
  *         (functions with prefix "INJ").
  * @note   The setting of these parameters by function @ref LL_ADC_Init()
  *         is conditioned to ADC state:
  *         ADC instance must be disabled.
  *         Each feature can be updated afterwards with a unitary function
  *         and potentially with ADC in a different state than disabled,
  *         refer to description of each function for setting
  *         conditioned to ADC state.
  * @note   After using this function, other features must be configured
  *         using LL unitary functions.
  *         The minimum configuration remaining to be done is:
  *          - Set ADC group injected sequencer:
  *            map channel on the selected sequencer rank.
  *            Refer to function @ref LL_ADC_INJ_SetSequencerRanks().
  *          - Set ADC channel sampling time
  *            Refer to function LL_ADC_SetChannelSamplingTime();
  * @param  ADCx ADC instance
  * @param  ADC_INJ_InitStruct Pointer to a @ref LL_ADC_INJ_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: ADC registers are initialized
  *          - ERROR: ADC registers are not initialized
  */
ErrorStatus LL_ADC_INJ_Init(ADC_TypeDef *ADCx, LL_ADC_INJ_InitTypeDef *ADC_INJ_InitStruct)
{
  ErrorStatus status = SUCCESS;
  
  /* Check the parameters */
  assert_param(IS_ADC_ALL_INSTANCE(ADCx));
  assert_param(IS_LL_ADC_INJ_TRIG_SOURCE(ADC_INJ_InitStruct->TriggerSource));
  assert_param(IS_LL_ADC_INJ_SEQ_SCAN_LENGTH(ADC_INJ_InitStruct->SequencerLength));
  if(ADC_INJ_InitStruct->SequencerLength != LL_ADC_INJ_SEQ_SCAN_DISABLE)
  {
    assert_param(IS_LL_ADC_INJ_SEQ_SCAN_DISCONT_MODE(ADC_INJ_InitStruct->SequencerDiscont));
  }
  assert_param(IS_LL_ADC_INJ_TRIG_AUTO(ADC_INJ_InitStruct->TrigAuto));
  
  /* Note: Hardware constraint (refer to description of this function):       */
  /*       ADC instance must be disabled.                                     */
  if(LL_ADC_IsEnabled(ADCx) == 0U)
  {
    /* Configuration of ADC hierarchical scope:                               */
    /*  - ADC group injected                                                  */
    /*    - Set ADC group injected trigger source                             */
    /*    - Set ADC group injected sequencer length                           */
    /*    - Set ADC group injected sequencer discontinuous mode               */
    /*    - Set ADC group injected conversion trigger: independent or         */
    /*      from ADC group regular                                            */
    if(ADC_INJ_InitStruct->SequencerLength != LL_ADC_REG_SEQ_SCAN_DISABLE)
    {
      MODIFY_REG(ADCx->CR1,
                   ADC_CR1_JDISCEN
                 | ADC_CR1_JAUTO
                ,
                   ADC_INJ_InitStruct->SequencerDiscont
                 | ADC_INJ_InitStruct->TrigAuto
                );
    }
    else
    {
      MODIFY_REG(ADCx->CR1,
                   ADC_CR1_JDISCEN
                 | ADC_CR1_JAUTO
                ,
                   LL_ADC_REG_SEQ_DISCONT_DISABLE
                 | ADC_INJ_InitStruct->TrigAuto
                );
    }
    
    MODIFY_REG(ADCx->CR2,
               ADC_CR2_JEXTSEL
              ,
               ADC_INJ_InitStruct->TriggerSource
              );
    
    /* Note: Hardware constraint (refer to description of this function):     */
    /* Note: If ADC instance feature scan mode is disabled                    */
    /*       (refer to  ADC instance initialization structure                 */
    /*       parameter @ref SequencersScanMode                                */
    /*       or function @ref LL_ADC_SetSequencersScanMode() ),               */
    /*       this parameter is discarded.                                     */
    LL_ADC_INJ_SetSequencerLength(ADCx, ADC_INJ_InitStruct->SequencerLength);
  }
  else
  {
    /* Initialization error: ADC instance is not disabled. */
    status = ERROR;
  }
  return status;
}

/**
  * @brief  Set each @ref LL_ADC_INJ_InitTypeDef field to default value.
  * @param  ADC_INJ_InitStruct Pointer to a @ref LL_ADC_INJ_InitTypeDef structure
  *                            whose fields will be set to default values.
  * @retval None
  */
void LL_ADC_INJ_StructInit(LL_ADC_INJ_InitTypeDef *ADC_INJ_InitStruct)
{
  /* Set ADC_INJ_InitStruct fields to default values */
  /* Set fields of ADC group injected */
  ADC_INJ_InitStruct->TriggerSource    = LL_ADC_INJ_TRIG_SOFTWARE;
  ADC_INJ_InitStruct->SequencerLength  = LL_ADC_INJ_SEQ_SCAN_DISABLE;
  ADC_INJ_InitStruct->SequencerDiscont = LL_ADC_INJ_SEQ_DISCONT_DISABLE;
  ADC_INJ_InitStruct->TrigAuto         = LL_ADC_INJ_TRIG_INDEPENDENT;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* ADC1 */

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/