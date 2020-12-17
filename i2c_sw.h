#ifndef __I2C_SW_H
#define __I2C_SW_H

/* includes */
#include "main.h"
#include "stdio.h"
#include "stm32f1xx_hal_gpio.h"

/* defines */
#define   GPIO_SW_I2C1_SCL			GPIOB
#define   GPIO_SW_I2C1_SDA			GPIOB
#define   GPIO_SW_I2C1_SCL_PIN		GPIO_PIN_13
#define   GPIO_SW_I2C1_SDA_PIN		GPIO_PIN_14
/*
#define   GPIO_SW_I2Cx_SCL			GPIOx
#define   GPIO_SW_I2Cx_SDA			GPIOx
#define   GPIO_SW_I2Cx_SCL_PIN		GPIO_PIN_x
#define   GPIO_SW_I2Cx_SDA_PIN		GPIO_PIN_x
*/

#define SW_I2C1		1
//#define SW_I2Cx		x


/* functions */
void SW_I2C_initial(void);

void i2c_port_initial(uint8_t sel);		

uint8_t SW_I2C_ReadVal_SDA(uint8_t sel);

void SW_I2C_Write_Data(uint8_t sel, uint8_t data);
uint8_t SW_I2C_Read_Data(uint8_t sel);

uint8_t SW_I2C_WriteControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_WriteControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_WriteControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint16_t data);

uint8_t SW_I2C_ReadControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_ReadControl_8Bit_OnlyData(uint8_t sel, uint8_t IICID);
uint16_t SW_I2C_ReadControl_16Bit_OnlyData(uint8_t sel, uint8_t IICID);
uint8_t SW_I2C_ReadControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint16_t SW_I2C_ReadControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);

uint8_t SW_I2C_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_Multi_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID);

uint8_t SW_I2C_UTIL_WRITE(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_UTIL_Read(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_UTIL_Read_Multi(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));

#endif  /* __I2C_SW_H */
