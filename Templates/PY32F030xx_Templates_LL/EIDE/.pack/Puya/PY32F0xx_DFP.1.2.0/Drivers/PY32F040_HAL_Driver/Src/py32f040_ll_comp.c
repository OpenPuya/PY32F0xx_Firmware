/**
  ******************************************************************************
  * @file    py32f040_ll_comp.c
  * @author  MCU Application Team
  * @brief   COMP LL module driver.
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
#include "py32f040_ll_comp.h"
#include "py32f040_ll_bus.h"



#ifdef  USE_FULL_ASSERT
#include "py32_assert.h"
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/** @addtogroup PY32F040_LL_Driver
  * @{
  */

#if defined(COMP1) || defined(COMP2) || defined(COMP3)

/** @addtogroup COMP_LL COMP
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/** @addtogroup COMP_LL_Private_Macros
  * @{
  */

/* Check of parameters for configuration of COMP hierarchical scope:          */
/* COMP instance.                                                             */

#define IS_LL_COMP_POWER_MODE(__POWER_MODE__)                                  \
  (   ((__POWER_MODE__) == LL_COMP_POWERMODE_HIGHSPEED)                        \
   || ((__POWER_MODE__) == LL_COMP_POWERMODE_MEDIUMSPEED)                      \
  )

#define IS_LL_COMP_INPUT_PLUS(__COMP_INSTANCE__, __INPUT_PLUS__)               \
  (   ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO0)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO1)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO2)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO3)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO4)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO5)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO6)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO7)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO8)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO9)                             \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO10)                            \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO11)                            \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO12)                            \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO13)                            \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO14)                            \
   || ((__INPUT_PLUS__) == LL_COMP_INPUT_PLUS_IO15)                            \
  )


#define IS_LL_COMP_INPUT_MINUS(__COMP_INSTANCE__, __INPUT_MINUS__)             \
  (   ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO0)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO1)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO2)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO3)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO4)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO5)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO6)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO7)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO8)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO9)                           \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO10)                          \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO11)                          \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO12)                          \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO13)                          \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO14)                          \
   || ((__INPUT_MINUS__) == LL_COMP_INPUT_MINUS_IO15)                          \
  )

#define IS_LL_COMP_INPUT_HYSTERESIS(__INPUT_HYSTERESIS__)                      \
  (   ((__INPUT_HYSTERESIS__) == LL_COMP_HYSTERESIS_DISABLE)                   \
   || ((__INPUT_HYSTERESIS__) == LL_COMP_HYSTERESIS_ENABLE)                    \
  )

#define IS_LL_COMP_OUTPUT_POLARITY(__POLARITY__)                               \
  (   ((__POLARITY__) == LL_COMP_OUTPUTPOL_NONINVERTED)                        \
   || ((__POLARITY__) == LL_COMP_OUTPUTPOL_INVERTED)                           \
  )

/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_LL_Exported_Functions
  * @{
  */

/** @addtogroup COMP_LL_EF_Init
  * @{
  */

/**
  * @brief  De-initialize registers of the selected COMP instance
  *         to their default reset values.
  * @param  COMPx COMP instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: COMP registers are de-initialized
  *          - ERROR: COMP registers are not de-initialized
  */
ErrorStatus LL_COMP_DeInit(COMP_TypeDef *COMPx)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_INSTANCE(COMPx));
  
  LL_COMP_WriteReg(COMPx, CSR, 0x00000000U);
  LL_COMP_WriteReg(COMPx, FR, 0x00000000U);
  
  return status;
}

/**
  * @brief  Initialize some features of COMP instance.
  * @note   This function configures features of the selected COMP instance.
  *         Some features are also available at scope COMP common instance
  *         (common to several COMP instances).
  *         Refer to functions having argument "COMPxy_COMMON" as parameter.
  * @param  COMPx COMP instance
  * @param  COMP_InitStruct Pointer to a @ref LL_COMP_InitTypeDef structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: COMP registers are initialized
  *          - ERROR: COMP registers are not initialized
  */
ErrorStatus LL_COMP_Init(COMP_TypeDef *COMPx, LL_COMP_InitTypeDef *COMP_InitStruct)
{
  ErrorStatus status = SUCCESS;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_INSTANCE(COMPx));
  assert_param(IS_LL_COMP_POWER_MODE(COMP_InitStruct->PowerMode));
  assert_param(IS_LL_COMP_INPUT_PLUS(COMPx, COMP_InitStruct->InputPlus));
  assert_param(IS_LL_COMP_INPUT_MINUS(COMPx, COMP_InitStruct->InputMinus));
  assert_param(IS_LL_COMP_INPUT_HYSTERESIS(COMP_InitStruct->InputHysteresis));
  assert_param(IS_LL_COMP_OUTPUT_POLARITY(COMP_InitStruct->OutputPolarity));

  MODIFY_REG(COMPx->CSR,
             COMP_CSR_PWRMODE
             | COMP_CSR_INPSEL
             | COMP_CSR_INNSEL
             | COMP_CSR_POLARITY
             ,
             COMP_InitStruct->PowerMode
             | COMP_InitStruct->InputPlus
             | COMP_InitStruct->InputMinus
             | COMP_InitStruct->OutputPolarity
             );
    /* Set comparator hysteresis mode */
    if(COMP_InitStruct->InputHysteresis==LL_COMP_HYSTERESIS_ENABLE)
    {
      if(COMPx==COMP1)
      {
         SET_BIT(COMPx->CSR, COMP1_CSR_HYST);
      }
      else
      {
         SET_BIT(COMPx->CSR, COMP2_CSR_HYST);
      }    
    }
    else
    {
      if(COMPx==COMP1)
      {
         CLEAR_BIT(COMPx->CSR, COMP1_CSR_HYST);
      }
      else
      {
         CLEAR_BIT(COMPx->CSR, COMP2_CSR_HYST);
      }     
    }
    
    if (COMP_InitStruct->DigitalFilter == 0)
    {
      /* Disable digital filter */
      CLEAR_BIT(COMPx->FR, COMP_FR_FLTEN);
    }
    else
    {
      WRITE_REG(COMPx->FR, (COMP_FR_FLTEN | (COMP_InitStruct->DigitalFilter << COMP_FR_FLTCNT_Pos)));
    }

  return status;
}

/**
  * @brief Set each @ref LL_COMP_InitTypeDef field to default value.
  * @param COMP_InitStruct Pointer to a @ref LL_COMP_InitTypeDef structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void LL_COMP_StructInit(LL_COMP_InitTypeDef *COMP_InitStruct)
{
  /* Set COMP_InitStruct fields to default values  */
  COMP_InitStruct->PowerMode            = LL_COMP_POWERMODE_MEDIUMSPEED;
  COMP_InitStruct->InputPlus            = LL_COMP_INPUT_PLUS_IO0;
  COMP_InitStruct->InputMinus           = LL_COMP_INPUT_MINUS_IO0;
  COMP_InitStruct->InputHysteresis      = LL_COMP_HYSTERESIS_DISABLE;
  COMP_InitStruct->OutputPolarity       = LL_COMP_OUTPUTPOL_NONINVERTED;
  COMP_InitStruct->DigitalFilter        = 0;
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

#endif /* COMP1 || COMP2 || COMP3*/

/**
  * @}
  */

#endif /* USE_FULL_LL_DRIVER */


/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
