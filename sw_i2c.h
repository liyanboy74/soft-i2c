#ifndef _SW_I2C_H_
#define _SW_I2C_H_

/* includes */
#include "stm32f1xx_hal.h"

#define SW_I2C1		        1

#define SW_I2C1_SCL_PORT    GPIOB
#define SW_I2C1_SDA_PORT    GPIOB
#define SW_I2C1_SCL_PIN     GPIO_PIN_6
#define SW_I2C1_SDA_PIN     GPIO_PIN_7

#define SW_I2C_WAIT_TIME    25
#define I2C_READ            0x01
#define READ_CMD            1
#define WRITE_CMD           0

/* functions */
void SW_I2C_initial(void);
void i2c_port_initial(uint8_t sel);
uint8_t SW_I2C_ReadVal_SDA(uint8_t sel);
void SW_I2C_Write_Data(uint8_t sel, uint8_t data);
uint8_t SW_I2C_Read_Data(uint8_t sel);
//从指定寄存器写一个字节数据
uint8_t SW_I2C_WriteControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_WriteControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_WriteControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint16_t data);
//从指定寄存器开始突发写多个数据
uint8_t SW_I2C_WritenControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
//从指定寄存器开始突发写多个数据(16位寄存器地址)
uint8_t SW_I2C_WritenControl_8Bit_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_ReadControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_ReadControl_8Bit_OnlyData(uint8_t sel, uint8_t IICID);
uint16_t SW_I2C_ReadControl_16Bit_OnlyData(uint8_t sel, uint8_t IICID);
//从指定寄存器读一个字节数据
uint8_t SW_I2C_ReadControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint16_t SW_I2C_ReadControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr);
//从指定寄存器开始突发读多个数据
uint8_t SW_I2C_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
//从指定寄存器开始突发读多个数据(16位寄存器地址)
uint8_t SW_I2C_ReadnControl_8Bit_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t rcnt, uint8_t (*pdata))
uint8_t SW_I2C_Multi_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));
uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID);
uint8_t SW_I2C_UTIL_WRITE(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data);
uint8_t SW_I2C_UTIL_Read(uint8_t sel, uint8_t IICID, uint8_t regaddr);
uint8_t SW_I2C_UTIL_Read_Multi(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata));

#endif  /* __I2C_SW_H */
