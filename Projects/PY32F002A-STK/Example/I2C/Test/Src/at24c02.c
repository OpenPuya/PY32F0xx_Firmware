#include "at24c02.h"


#define AT24C02_ADDR    (0xA0)


uint8_t at24c02_write_buf[AT24C02_MAX_BYTE_NUM] = {0};
uint8_t at24c02_read_buf[AT24C02_MAX_BYTE_NUM]  = {0};


/**
  * @brief  AT24C02 write data.
  * @param  page, AT24C02 write page.
            data, Write data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WriteByte(uint8_t addr, uint8_t data)
{
    uint8_t write_byte[1] = {data};
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Write(&I2cHandle, AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, write_byte, 1, 0xFF);

    if(status != HAL_OK)
    {
        return H_ERROR;
    }

    return H_SUCCESS;
}


/**
  * @brief  AT24C02 write page data.
  * @param  page, AT24C02 write page.
            pData, Write data buffer.
            len, Write data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WritePage(H_AT24C02_PAGE_T page, uint8_t* pData, uint8_t len)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint8_t page_addr = (uint8_t)page;

    //H_PARA_ASSERT((pData == NULL) || (len > AT24C02_PAGE_SIZE));

    status = HAL_I2C_Mem_Write(&I2cHandle, AT24C02_ADDR, page_addr, I2C_MEMADD_SIZE_8BIT, pData, len, 0xFFFF);

    if(status != HAL_OK)
    {
        return H_ERROR;
    }

    return H_SUCCESS;
}


/**
  * @brief  AT24C02 write serial data.
  * @param  addr, AT24C02 write data memory.
            pData, Write data buffer.
            len, Write data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_WriteData(uint8_t addr, uint8_t* pData, uint16_t len)
{
    uint8_t start_page_remain = 0;
    uint8_t remain_page_num = 0;
    uint8_t write_num = 0;
    uint32_t i = 0;

    //H_PARA_ASSERT(((AT24C02_MAX_BYTE_NUM - (addr + 1)) < len) || (pData == NULL));

    /* How many memory remain for start page */
    start_page_remain = AT24C02_PAGE_SIZE - addr % AT24C02_PAGE_SIZE;

    /* Write first page */
    write_num = len > start_page_remain ? start_page_remain : len;
    for(i = 0; i < write_num; i++)
    {
        if(H_SUCCESS != Fn_AT24C02_WriteByte(addr++, *pData++))
        {
            return H_ERROR;
        }
        len--;

        /* For auto sync write */
        HAL_Delay(5);
    }

    /* Write completely */
    if(len == 0)
    {
        return H_SUCCESS;
    }

    /* How many completely page to write */
    remain_page_num = len / AT24C02_PAGE_SIZE;

    for(i = 0; i < remain_page_num; i++)
    {
        if(H_SUCCESS != Fn_AT24C02_WritePage((H_AT24C02_PAGE_T)addr, pData, AT24C02_PAGE_SIZE))
        {
            return H_ERROR;
        }

        addr += AT24C02_PAGE_SIZE;
        pData += AT24C02_PAGE_SIZE;
        len -= AT24C02_PAGE_SIZE;

        /* For auto sync write */
        HAL_Delay(5);
    }

    /* Write cpm */
    if(len == 0)
    {
        return H_SUCCESS;
    }

    /* Last page remain number */
    if(H_SUCCESS != Fn_AT24C02_WritePage((H_AT24C02_PAGE_T)addr, pData, len))
    {
        return H_ERROR;
    }

    /* Note: if called Read function after this function, Please insert a delay time between write / read */
    return H_SUCCESS;
}


/**
  * @brief  AT24C02 read current address data.
  * @param  pData, Read data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadCurrentByte(uint8_t *pData)
{
    //H_PARA_ASSERT(pData == NULL);

    if(HAL_OK != HAL_I2C_Master_Receive(&I2cHandle, AT24C02_ADDR, pData, 1, 0xFF))
    {
        return H_ERROR;
    }

    return H_SUCCESS;
}


/**
  * @brief  AT24C02 read a byte.
  * @param  addr, AT24C02 read data memory.
            pData, Read data buffer.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadByte(uint8_t addr, uint8_t *pData)
{
    //H_PARA_ASSERT(pData == NULL);

    if(HAL_OK != HAL_I2C_Mem_Read(&I2cHandle, AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, pData, 1, 0xFF))
    {
        return H_ERROR;
    }

    return H_SUCCESS;
}


/**
  * @brief  AT24C02 read serial data.
  * @param  addr, AT24C02 read data memory.
            pData, Read data buffer.
            len, Read data length.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ReadData(uint8_t addr, uint8_t *pData, uint16_t len)
{
    //H_PARA_ASSERT((pData == NULL) || (len > AT24C02_MAX_BYTE_NUM));

    if(HAL_OK != HAL_I2C_Mem_Read(&I2cHandle, AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, pData, len, 0xFFFF))
    {
        return H_ERROR;
    }

    return H_SUCCESS;
}


/**
  * @brief  AT24C02 clear memory data.
  * @param  None.
  * @retval H_SUCCESS or H_ERROR.
  */
H_STATUS_T Fn_AT24C02_ClearMemData(void)
{
    uint32_t i = 0;
    uint8_t  page_addr = 0x00;
    uint8_t  data[AT24C02_PAGE_SIZE] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    for(i = 0; i < AT24C02_PAGE_NUM; i++)
    {
        if(H_SUCCESS != Fn_AT24C02_WritePage((H_AT24C02_PAGE_T)page_addr, data, AT24C02_PAGE_SIZE))
        {
             return H_ERROR;
        }

        page_addr += AT24C02_PAGE_SIZE;

        /* For auto sync write */
        HAL_Delay(5);
    }

    return H_SUCCESS;
}