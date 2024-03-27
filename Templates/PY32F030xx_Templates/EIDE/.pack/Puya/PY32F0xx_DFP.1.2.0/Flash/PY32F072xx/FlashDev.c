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
 * Project:      Flash Device Description for Puya PY32F030xx Flash
 * --------------------------------------------------------------------------- */

/* History:
 *  Version 1.0.0
 *    Initial release
 */
#include "FlashOS.h"        // FlashOS Structures

#ifdef FLASH_MEM

#ifdef PY32F072x6
struct FlashDevice const FlashDevice  =
{
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "Cortex-M0+ 32kB Flash",    // Device Name (32kB)
    ONCHIP,                     // Device Type
    0x08000000,                 // Device Start Address
    0x00008000,                 // Device Size in Bytes (128kB)
    0x100,                      // Programming Page Size
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    600,                        // Program Page Timeout 600 mSec
    6000,                       // Erase Sector Timeout 6000 mSec

//Specify Size and Address of Sectors
    0x2000, 0x000000,           // Sector Size  4kB (2 sectors)
    SECTOR_END
};
#endif // PY32F072x6

#ifdef PY32F072x8
struct FlashDevice const FlashDevice  =
{
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "Cortex-M0+ 64kB Flash",    // Device Name (64kB)
    ONCHIP,                     // Device Type
    0x08000000,                 // Device Start Address
    0x00010000,                 // Device Size in Bytes (128kB)
    0x100,                      // Programming Page Size
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    600,                        // Program Page Timeout 600 mSec
    6000,                       // Erase Sector Timeout 6000 mSec

//Specify Size and Address of Sectors
    0x2000, 0x000000,           // Sector Size  4kB (2 sectors)
    SECTOR_END
};
#endif // PY32F072x8

#ifdef PY32F072x9
struct FlashDevice const FlashDevice  =
{
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "Cortex-M0+ 96kB Flash",    // Device Name (96kB)
    ONCHIP,                     // Device Type
    0x08000000,                 // Device Start Address
    0x00018000,                 // Device Size in Bytes (128kB)
    0x100,                      // Programming Page Size
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    600,                        // Program Page Timeout 600 mSec
    6000,                       // Erase Sector Timeout 6000 mSec

//Specify Size and Address of Sectors
    0x2000, 0x000000,           // Sector Size  4kB (2 sectors)
    SECTOR_END
};
#endif // PY32F072x9

#ifdef PY32F072xB
struct FlashDevice const FlashDevice  =
{
    FLASH_DRV_VERS,             // Driver Version, do not modify!
    "Cortex-M0+ 128kB Flash",   // Device Name (128kB)
    ONCHIP,                     // Device Type
    0x08000000,                 // Device Start Address
    0x00020000,                 // Device Size in Bytes (128kB)
    0x100,                      // Programming Page Size
    0,                          // Reserved, must be 0
    0xFF,                       // Initial Content of Erased Memory
    600,                        // Program Page Timeout 600 mSec
    6000,                       // Erase Sector Timeout 6000 mSec

//Specify Size and Address of Sectors
    0x2000, 0x000000,           // Sector Size  4kB (2 sectors)
    SECTOR_END
};
#endif // PY32F072xB

#endif // FLASH_MEM

#ifdef PY32F072xx_OPT
struct FlashDevice const FlashDevice  =  
{
  FLASH_DRV_VERS,                     // Driver Version, do not modify!
  "Cortex-M0+ Flash Options",         // Device Name
  ONCHIP,                             // Device Type
  0x1FFF3100,                         // Device Start Address
  0x00000020,                         // Device Size in Bytes (32)
  0x20,                               // Programming Page Size
  0,                                  // Reserved, must be 0
  0xFF,                               // Initial Content of Erased Memory
  3000,                               // Program Page Timeout 3 Sec
  3000,                               // Erase Sector Timeout 3 Sec

//Specify Size and Address of Sectors
  0x00020, 0x000000,                  // Sector Size  32B (1 sectors)
  SECTOR_END
};
#endif // PY32F072xx_OPT
