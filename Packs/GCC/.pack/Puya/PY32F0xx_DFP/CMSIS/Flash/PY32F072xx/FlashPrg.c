/* -----------------------------------------------------------------------------
 * Copyright (c) 2014 - 2019 ARM Ltd.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software. Permission is granted to anyone to use this
 * software for any purpose, including commercial applications, and to alter
 * it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 *
 *
 * $Date:        2021-7-1
 * $Revision:    V1.0.0
 *
 * Project:      Flash Programming Functions for Puya PY32F030xx Flash
 * --------------------------------------------------------------------------- */

/* History:
 *  Version 1.0.0
 *    Initial release
 */

#include "FlashOS.h"        // FlashOS Structures
#include "py32f0xx.h"

typedef volatile unsigned char    vu8;
typedef          unsigned char     u8;
typedef volatile unsigned short   vu16;
typedef          unsigned short    u16;
typedef volatile unsigned long    vu32;
typedef          unsigned long     u32;

//#define M8(adr)  (*((vu8  *) (adr)))
//#define M16(adr) (*((vu16 *) (adr)))
//#define M32(adr) (*((vu32 *) (adr)))

uint32_t gdw_HSI_FS;

//uiOffset = 0(4MHz), 1(8MHz), 2(16MHz), 3(22.12MHz), 4(24MHz)
void SetFlashParameter(uint32_t uiOffset)
{
//  WRITE_REG(FLASH->KEYR, FLASH_KEY1);
//  WRITE_REG(FLASH->KEYR, FLASH_KEY2);
  FLASH->TS0 = ((HW32_REG(0x1FFF3238 + uiOffset * 0x28) >> 0) & 0x000000FF);
  FLASH->TS3 = ((HW32_REG(0x1FFF3238 + uiOffset * 0x28) >> 8) & 0x000000FF);
  FLASH->TS1 = ((HW32_REG(0x1FFF3238 + uiOffset * 0x28) >> 16) & 0x000001FF);
  FLASH->TS2P = ((HW32_REG(0x1FFF3240 + uiOffset * 0x28) >> 0) & 0x000000FF);
  FLASH->TPS3 = ((HW32_REG(0x1FFF3240 + uiOffset * 0x28) >> 16) & 0x000007FF);
  FLASH->PERTPE = ((HW32_REG(0x1FFF3248 + uiOffset * 0x28) >> 0) & 0x0001FFFF);
  FLASH->SMERTPE = ((HW32_REG(0x1FFF3250 + uiOffset * 0x28) >> 0) & 0x0001FFFF);
  FLASH->PRGTPE = ((HW32_REG(0x1FFF3258 + uiOffset * 0x28) >> 0) & 0x0000FFFF);
  FLASH->PRETPE = ((HW32_REG(0x1FFF3258 + uiOffset * 0x28) >> 16) & 0x0000FFFF);
//  SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

void InitRccAndFlashParam(void)
{
  gdw_HSI_FS = READ_BIT(RCC->ICSCR, RCC_ICSCR_HSI_FS);
  MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3220)); //HSI_24MHz
  while (RCC_CR_HSIRDY != READ_BIT(RCC->CR, RCC_CR_HSIRDY));
  SetFlashParameter(4);
}

void UnInitRccAndFlashParam(void)
{
  MODIFY_REG(RCC->ICSCR, RCC_ICSCR_HSI_FS, gdw_HSI_FS);
  switch (gdw_HSI_FS)
  {
  case RCC_ICSCR_HSI_FS_2://24MHz
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3220));
    break;
  case (RCC_ICSCR_HSI_FS_1|RCC_ICSCR_HSI_FS_0)://22.12MHz
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3218));
    break;
  case RCC_ICSCR_HSI_FS_1://16MHz
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3210));
    break;
  case RCC_ICSCR_HSI_FS_0://8MHz
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3208));
    break;
  default://4MHz
    MODIFY_REG(RCC->ICSCR, (RCC_ICSCR_HSI_FS | RCC_ICSCR_HSI_TRIM), M32(0x1FFF3200));
    break;
  }
  while (RCC_CR_HSIRDY != READ_BIT(RCC->CR, RCC_CR_HSIRDY));
}

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{

  // Unlock Flash
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;

  InitRccAndFlashParam();

  FLASH->SR  |= FLASH_SR_EOP;                              // Reset FLASH_EOP

  if (FLASH_OPTR_IWDG_SW != READ_BIT(FLASH->OPTR, FLASH_OPTR_IWDG_SW))        // Test if IWDG is running (IWDG in HW mode)
  {
    // Set IWDG time out to maximum
    IWDG->KR  = 0x5555;                                  // Enable write access to IWDG_PR and IWDG_RLR
    IWDG->PR  = 0x06;                                    // Set prescaler to maximum
    IWDG->RLR = 0xFFF;                                   // Set reload value to maximum
  }
  if (FLASH_OPTR_WWDG_SW != READ_BIT(FLASH->OPTR, FLASH_OPTR_WWDG_SW))         // Test if WWDG is running (WWDG in HW mode)
  {
    // Set WWDG time out to maximum
    SET_BIT(WWDG->CFR, WWDG_CFR_WDGTB);                 // Set prescaler to maximum
  }

  return (0);
}
#endif

#ifdef PY32F072xx_OPT
int Init(unsigned long adr, unsigned long clk, unsigned long fnc)
{


  // Unlock Flash
  FLASH->KEYR = FLASH_KEY1;
  FLASH->KEYR = FLASH_KEY2;
  // Unlock Option Bytes
  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;

  InitRccAndFlashParam();

//    FLASH->ACR  = 0x00000000;                             // Zero Wait State, no Prefetch
  FLASH->SR  |= FLASH_SR_EOP;                              // Reset FLASH_EOP


  if (FLASH_OPTR_IWDG_SW != READ_BIT(FLASH->OPTR, FLASH_OPTR_IWDG_SW))        // Test if IWDG is running (IWDG in HW mode)
  {
    // Set IWDG time out to maximum
    IWDG->KR  = 0x5555;                                  // Enable write access to IWDG_PR and IWDG_RLR
    IWDG->PR  = 0x06;                                    // Set prescaler to maximum
    IWDG->RLR = 0xFFF;                                   // Set reload value to maximum
  }
  if (FLASH_OPTR_WWDG_SW != READ_BIT(FLASH->OPTR, FLASH_OPTR_WWDG_SW))         // Test if WWDG is running (WWDG in HW mode)
  {
    // Set WWDG time out to maximum
    SET_BIT(WWDG->CFR, WWDG_CFR_WDGTB);                 // Set prescaler to maximum
  }

  return (0);
}
#endif


/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int UnInit(unsigned long fnc)
{

  UnInitRccAndFlashParam();

  FLASH->CR    |=  FLASH_CR_LOCK;                          // Lock Flash

  return (0);
}
#endif

#ifdef PY32F072xx_OPT
int UnInit(unsigned long fnc)
{

  UnInitRccAndFlashParam();

  FLASH->CR    |=  FLASH_CR_LOCK;                          // Lock Flash
  FLASH->CR    |=  FLASH_CR_OPTLOCK;                       // Lock Option Bytes

  return (0);
}
#endif

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseChip(void)
{
  FLASH->SR  |= FLASH_SR_EOP;                              // Reset FLASH_EOP

  FLASH->CR |=  FLASH_CR_MER;                              // Mass Erase Enabled
  FLASH->CR |=  FLASH_CR_EOPIE;
  M32(0x08000000) = 0xFF;
  __asm("DSB");

  while (FLASH->SR & FLASH_SR_BSY)
  {
    SET_BIT(WWDG->CR, WWDG_CR_T);                      // Reload WWDG
    WRITE_REG(IWDG->KR, 0x0000AAAAU);                  // Reload IWDG
  }

  FLASH->CR &= ~FLASH_CR_MER;                              // Mass Erase Disabled
  FLASH->CR &= ~FLASH_CR_EOPIE;                            // Reset FLASH_EOPIE

  if (FLASH_SR_EOP != (FLASH->SR & FLASH_SR_EOP))             // Check for FLASH_SR_EOP
  {
    FLASH->SR |= FLASH_SR_EOP;
    return (1);                                         // Failed
  }

  return (0);                                           // Done
}
#endif

#ifdef PY32F072xx_OPT
int EraseChip(void)
{

  /* erase chip is not needed for
     - Flash Option bytes
     - Flash One Time Programmable bytes
  */
  return (0);                                           // Done
}
#endif

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int EraseSector(unsigned long adr)
{
  FLASH->SR  |= FLASH_SR_EOP;                              // Reset FLASH_EOP

  FLASH->CR  |=  FLASH_CR_SER;                             // Sector Erase Enabled
  FLASH->CR  |=  FLASH_CR_EOPIE;
  M32(adr) = 0xFF;                                      // Sector Address
  __asm("DSB");

  while (FLASH->SR & FLASH_SR_BSY)
  {
    SET_BIT(WWDG->CR, WWDG_CR_T);                      // Reload WWDG
    WRITE_REG(IWDG->KR, 0x0000AAAAU);                  // Reload IWDG
  }

  FLASH->CR  &= ~FLASH_CR_SER;                             // Sector Erase Disabled
  FLASH->CR  &= ~FLASH_CR_EOPIE;                           // Reset FLASH_EOPIE

//  if (FLASH_EOP != (FLASH->SR & FLASH_EOP)) {           // Check for FLASH_SR_EOP
//    FLASH->SR |= FLASH_EOP;
//    return (1);                                         // Failed
//  }

  return (0);                                           // Done
}
#endif


#ifdef PY32F072xx_OPT
int EraseSector(unsigned long adr)
{
  /* erase sector is not needed for
     - Flash Option bytes
     - Flash One Time Programmable bytes
  */
  return (0);                                           // Done
}
#endif

/*
 *  Blank Check Checks if Memory is Blank
 *    Parameter:      adr:  Block Start Address
 *                    sz:   Block Size (in bytes)
 *                    pat:  Block Pattern
 *    Return Value:   0 - OK,  1 - Failed
 */

int BlankCheck(unsigned long adr, unsigned long sz, unsigned char pat)
{
  return (1);                                            // Always Force Erase
}


/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

#ifdef FLASH_MEM
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
  sz = (sz + (FLASH_PAGE_SIZE - 1)) & ~(FLASH_PAGE_SIZE - 1); // Adjust size for 32 Words

  FLASH->SR  |= FLASH_SR_EOP;                               // Reset FLASH_EOP

  while (sz)
  {
    FLASH->CR  |=  FLASH_CR_PG;                           // Programming Enabled
    FLASH->CR  |=  FLASH_CR_EOPIE;

    for (u8 i = 0; i < FLASH_PAGE_SIZE / 4; i++)
    {

      M32(adr + i * 4) = *((u32 *)(buf + i * 4));       // Program the first word of the Double Word
      if (i == (FLASH_PAGE_SIZE / 4 - 2))
      {
        FLASH->CR  |= FLASH_CR_PGSTRT;
      }
    }
    __asm("DSB");

    while (FLASH->SR & FLASH_SR_BSY)
    {
      SET_BIT(WWDG->CR, WWDG_CR_T);                      // Reload WWDG
      WRITE_REG(IWDG->KR, 0x0000AAAAU);                  // Reload IWDG
    }

    FLASH->CR  &= ~FLASH_CR_PG;                           // Programming Disabled
    FLASH->CR  &= ~FLASH_CR_EOPIE;                        // Reset FLASH_EOPIE

    //为了能够Program SRAM，屏蔽下面的EOP检查
//      if (FLASH_EOP != (FLASH->SR & FLASH_EOP)) {           // Check for FLASH_SR_EOP
//          FLASH->SR |= FLASH_EOP;
//          return (1);                                       // Failed
//      }

    adr += FLASH_PAGE_SIZE;                               // Go to next Page
    buf += FLASH_PAGE_SIZE;
    sz  -= FLASH_PAGE_SIZE;
  }

  return (0);                                              // Done
}
#endif // PY32F030xx_64 || FLASH_OTP

#ifdef PY32F072xx_OPT
int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf)
{
  u32 optr;
  u32 sdkr;
  u32 wrpr;

  optr = *((u32 *)(buf + 0x00));
  sdkr = *((u32 *)(buf + 0x08));
  wrpr = *((u32 *)(buf + 0x18));

  FLASH->SR |= FLASH_SR_EOP;                            // Reset FLASH_EOP

  FLASH->OPTR = (optr & 0x0000FFFF);                 // Write OPTR values
  FLASH->SDKR = (sdkr & 0x00001F1F);                 // Write SDKR values
  FLASH->WRPR = (wrpr & 0x0000FFFF);                 // Write WRPR values

  FLASH->CR |= FLASH_CR_OPTSTRT;
  FLASH->CR |= FLASH_CR_EOPIE;
  M32(0x40022080) = 0xFF;
  __asm("DSB");

  while (FLASH->SR & FLASH_SR_BSY);

  FLASH->CR  &= ~FLASH_CR_OPTSTRT;                      // Programming Disabled
  FLASH->CR  &= ~FLASH_CR_EOPIE;                        // Reset FLASH_EOPIE

  //FLASH->CR |= FLASH_CR_OBL_LAUNCH;//不能添加这句，不然MDK下载报错

  return (0);                                           // Done
}
#endif //  PY32F072xx_OPT


/*
 *  Verify Flash Contents
 *    Parameter:      adr:  Start Address
 *                    sz:   Size (in bytes)
 *                    buf:  Data
 *    Return Value:   (adr+sz) - OK, Failed Address
 */

#ifdef PY32F072xx_OPT
unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf)
{
  u32 optr;
  u32 sdkr;
  u32 wrpr;

  optr = *((u32 *)(buf +  0x00));
  sdkr = *((u32 *)(buf +  0x08));
  wrpr = *((u32 *)(buf +  0x18));

  if (M32(adr + 0x00) != optr)
  {
    return (adr + 0x00);
  }
  if (M32(adr + 0x08) != sdkr)
  {
    return (adr + 0x08);
  }
  if (M32(adr + 0x18) != wrpr)
  {
    return (adr + 0x18);
  }

  return (adr + sz);
}
#endif // PY32F072xx_OPT
