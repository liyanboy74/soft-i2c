#ifndef _SW_I2C_H_
#define _SW_I2C_H_

#define CNIFIC_UNISOC_8850_SUPPORT 1

#if !CNIFIC_UNISOC_8850_SUPPORT
/* includes */
#include "stm32f1xx_hal.h"

#endif

#define SW_I2C1		        1

#if !CNIFIC_UNISOC_8850_SUPPORT

#define SW_I2C1_SCL_PORT    GPIOB
#define SW_I2C1_SDA_PORT    GPIOB
#define SW_I2C1_SCL_PIN     GPIO_PIN_6
#define SW_I2C1_SDA_PIN     GPIO_PIN_7

#else
#include <stdint.h>

#define AIP_SPI_DIO GPIO_35
#define AIP_SPI_CLK GPIO_37

#define SW_I2C1_SCL_PIN     AIP_SPI_CLK
#define SW_I2C1_SDA_PIN     AIP_SPI_DIO
#endif

#if !CNIFIC_UNISOC_8850_SUPPORT

#define SW_I2C_WAIT_TIME    25
#else
#define SW_I2C_WAIT_TIME    10 // 10us 100kHz

#endif

#define I2C_READ            0x01
#define READ_CMD            1
#define WRITE_CMD           0

/* functions */
void SW_I2C_initial(void);
uint8_t SW_I2C_Read_8addr(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt);
uint8_t SW_I2C_Read_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt);
uint8_t SW_I2C_Write_8addr(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt);
uint8_t SW_I2C_Write_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt);
uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID);


#endif  /* __I2C_SW_H */
