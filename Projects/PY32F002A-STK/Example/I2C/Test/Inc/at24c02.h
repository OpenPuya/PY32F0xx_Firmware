#ifndef __AT24C02_H__
#define __AT24C02_H__


#include "main.h"

#define AT24C02_BASE_ADDR           (0x00)

#define AT24C02_PAGE_SIZE           (0x08)

#define AT24C02_PAGE_NUM            (32)

#define AT24C02_MAX_BYTE_NUM        (256)

#define AT24C02_MAX_MEM_ADDR        (0xFF)

typedef enum
{
    AT24C02_PAGE0  = AT24C02_BASE_ADDR +  0 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE1  = AT24C02_BASE_ADDR +  1 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE2  = AT24C02_BASE_ADDR +  2 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE3  = AT24C02_BASE_ADDR +  3 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE4  = AT24C02_BASE_ADDR +  4 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE5  = AT24C02_BASE_ADDR +  5 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE6  = AT24C02_BASE_ADDR +  6 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE7  = AT24C02_BASE_ADDR +  7 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE8  = AT24C02_BASE_ADDR +  8 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE9  = AT24C02_BASE_ADDR +  9 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE10 = AT24C02_BASE_ADDR + 10 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE11 = AT24C02_BASE_ADDR + 11 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE12 = AT24C02_BASE_ADDR + 12 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE13 = AT24C02_BASE_ADDR + 13 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE14 = AT24C02_BASE_ADDR + 14 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE15 = AT24C02_BASE_ADDR + 15 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE16 = AT24C02_BASE_ADDR + 16 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE17 = AT24C02_BASE_ADDR + 17 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE18 = AT24C02_BASE_ADDR + 18 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE19 = AT24C02_BASE_ADDR + 19 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE20 = AT24C02_BASE_ADDR + 20 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE21 = AT24C02_BASE_ADDR + 21 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE22 = AT24C02_BASE_ADDR + 22 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE23 = AT24C02_BASE_ADDR + 23 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE24 = AT24C02_BASE_ADDR + 24 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE25 = AT24C02_BASE_ADDR + 25 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE26 = AT24C02_BASE_ADDR + 26 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE27 = AT24C02_BASE_ADDR + 27 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE28 = AT24C02_BASE_ADDR + 28 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE29 = AT24C02_BASE_ADDR + 29 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE30 = AT24C02_BASE_ADDR + 30 * AT24C02_PAGE_SIZE,
    AT24C02_PAGE31 = AT24C02_BASE_ADDR + 31 * AT24C02_PAGE_SIZE,
}H_AT24C02_PAGE_T;

typedef enum
{
    H_SUCCESS = 0,
    H_ERROR = 1,
}H_STATUS_T;



/**
  * @brief  AT24C02 write data.
  * @param  page, AT24C02 write page.
            data, Write data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WriteByte(uint8_t addr, uint8_t data);


/**
  * @brief  AT24C02 write page data.
  * @param  page, AT24C02 write page.
            pData, Write data buffer.
            len, Write data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WritePage(H_AT24C02_PAGE_T page, uint8_t* pData, uint8_t len);


/**
  * @brief  AT24C02 write serial data.
  * @param  addr, AT24C02 write data memory.
            pData, Write data buffer.
            len, Write data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WriteData(uint8_t addr, uint8_t* pData, uint16_t len);


/**
  * @brief  AT24C02 read current address data.
  * @param  pData, Read data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadCurrentByte(uint8_t *pData);


/**
  * @brief  AT24C02 read a byte.
  * @param  addr, AT24C02 read data memory.
            pData, Read data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadByte(uint8_t addr, uint8_t *pData);


/**
  * @brief  AT24C02 read serial data.
  * @param  addr, AT24C02 read data memory.
            pData, Read data buffer.
            len, Read data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadData(uint8_t addr, uint8_t *pData, uint16_t len);


/**
  * @brief  AT24C02 clear memory data.
  * @param  None.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ClearMemData(void);


extern uint8_t at24c02_write_buf[AT24C02_MAX_BYTE_NUM];
extern uint8_t at24c02_read_buf[AT24C02_MAX_BYTE_NUM];


#endif