#include "i2c_sw.h"


#define  SW_I2C_WAIT_TIME  22	


#define  I2C_READ       0x01
#define  READ_CMD       1
#define  WRITE_CMD      0

#define SW_I2C1_SCL_GPIO  GPIO_SW_I2C1_SCL
#define SW_I2C1_SDA_GPIO  GPIO_SW_I2C1_SDA
#define SW_I2C1_SCL_PIN   GPIO_SW_I2C1_SCL_PIN
#define SW_I2C1_SDA_PIN   GPIO_SW_I2C1_SDA_PIN
/*
#define SW_I2Cx_SCL_GPIO  GPIO_SW_I2Cx_SCL
#define SW_I2Cx_SDA_GPIO  GPIO_SW_I2Cx_SDA
#define SW_I2Cx_SCL_PIN   GPIO_SW_I2Cx_SCL_PIN
#define SW_I2Cx_SDA_PIN   GPIO_SW_I2Cx_SDA_PIN
*/

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif


void TIMER__Wait_us(__IO uint32_t nCount)
{
    for (; nCount != 0;nCount--);
}


void SW_I2C_initial(void)
{
	GPIO_InitTypeDef			GPIO_InitStructure;

	GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;
	
	GPIO_InitStructure.Pin   = GPIO_SW_I2C1_SCL_PIN;
	HAL_GPIO_Init(GPIO_SW_I2C1_SCL, &GPIO_InitStructure);
	GPIO_InitStructure.Pin   = GPIO_SW_I2C1_SDA_PIN;
	HAL_GPIO_Init(GPIO_SW_I2C1_SDA, &GPIO_InitStructure);

	/*
	GPIO_InitStructure.Pin   = GPIO_SW_I2Cx_SCL_PIN;
	HAL_GPIO_Init(GPIO_SW_I2Cx_SCL, &GPIO_InitStructure);
	GPIO_InitStructure.Pin   = GPIO_SW_I2Cx_SDA_PIN;
	HAL_GPIO_Init(GPIO_SW_I2Cx_SDA, &GPIO_InitStructure);
	*/


}

void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_SET);
}

void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_RESET);
}

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	uint8_t Ret;
	Ret=(uint16_t)HAL_GPIO_ReadPin(GPIOx,GPIO_Pin);
	return Ret;
}
	
void sda_high(uint8_t sel)
{
    if(sel == 1)
        GPIO_SetBits(SW_I2C1_SDA_GPIO, SW_I2C1_SDA_PIN);
    //else if(sel==x) ...
}


void sda_low(uint8_t sel)
{
    if(sel == 1)
        GPIO_ResetBits(SW_I2C1_SDA_GPIO, SW_I2C1_SDA_PIN);
    //else if(sel==x) ...
}


void scl_high(uint8_t sel)
{
    if(sel == 1)
        GPIO_SetBits(SW_I2C1_SCL_GPIO, SW_I2C1_SCL_PIN);
    //else if(sel==x) ...
}


void scl_low(uint8_t sel)
{
    if(sel == 1)
        GPIO_ResetBits(SW_I2C1_SCL_GPIO, SW_I2C1_SCL_PIN);
    //else if(sel==x) ...
}

void sda_out(uint8_t sel, uint8_t out)
{
    if (out)
    {
        sda_high(sel);
    }
    else
    {
        sda_low(sel);
    }
}

void sda_in_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStructure.Mode=GPIO_MODE_INPUT;
		
    if(sel == 1)
    {
        GPIO_InitStructure.Pin   = SW_I2C1_SDA_PIN;
        HAL_GPIO_Init(SW_I2C1_SDA_GPIO, &GPIO_InitStructure);
    }
    //else if(sel==x) ...

}

void sda_out_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_OD;
		
    if(sel == 1)
    {
        GPIO_InitStructure.Pin   = SW_I2C1_SDA_PIN;
        HAL_GPIO_Init(SW_I2C1_SDA_GPIO, &GPIO_InitStructure);
    }
    //else if(sel==x) ...
}

void scl_in_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_OD;
		
    if(sel == 1)
    {
        GPIO_InitStructure.Pin   = SW_I2C1_SCL_PIN;
        HAL_GPIO_Init(SW_I2C1_SCL_GPIO, &GPIO_InitStructure);
    }
    //else if(sel==x) ...
}

void scl_out_mode(uint8_t sel)
{
		GPIO_InitTypeDef GPIO_InitStructure;

		GPIO_InitStructure.Speed=GPIO_SPEED_FREQ_HIGH;
		GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_OD;
		
    if(sel == 1)
    {
        GPIO_InitStructure.Pin   = SW_I2C1_SCL_PIN;
        HAL_GPIO_Init(SW_I2C1_SCL_GPIO, &GPIO_InitStructure);
    }
    //else if(sel==x) ...
}

void i2c_clk_data_out(uint8_t sel)
{
    scl_high(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    scl_low(sel);

}

void i2c_port_initial(uint8_t sel)
{
    sda_high(sel);
    scl_high(sel);
}

void i2c_start_condition(uint8_t sel)
{
    sda_high(sel);
    scl_high(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    sda_low(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    scl_low(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME << 1);
}

void i2c_stop_condition(uint8_t sel)
{
    sda_low(sel);
    scl_high(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    sda_high(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
}

uint8_t i2c_check_ack(uint8_t sel)
{
    uint8_t         ack;
    int             i;
    unsigned int    temp;

    sda_in_mode(sel);

    scl_high(sel);

    ack = 0;
    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    for (i = 10; i > 0; i--)
    {
        temp = !(SW_I2C_ReadVal_SDA(sel));	
        if (temp)	
        {
            ack = 1;
            break;
        }
    }
    scl_low(sel);
    sda_out_mode(sel);	

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    return ack;
}

void i2c_check_not_ack(uint8_t sel)
{
    sda_in_mode(sel);
    i2c_clk_data_out(sel);
    sda_out_mode(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
}

void i2c_check_not_ack_continue(uint8_t sel)
{

    i2c_clk_data_out(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
}

void i2c_slave_address(uint8_t sel, uint8_t IICID, uint8_t readwrite)
{
    int x;

    if (readwrite)
    {
        IICID |= I2C_READ;
    }
    else
    {
        IICID &= ~I2C_READ;
    }

    scl_low(sel);

    for (x = 7; x >= 0; x--)
    {
        sda_out(sel, IICID & (1 << x));
        TIMER__Wait_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(sel);

    }
}

void i2c_register_address(uint8_t sel, uint8_t addr)
{
    int  x;

    scl_low(sel);

    for (x = 7; x >= 0; x--)
    {
        sda_out(sel, addr & (1 << x));
        TIMER__Wait_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(sel);

    }
}

void i2c_send_ack(uint8_t sel)
{
    sda_out_mode(sel);
    sda_low(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    scl_high(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME << 1);

    sda_low(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME << 1);

    scl_low(sel);

    sda_out_mode(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
}


uint8_t SW_I2C_ReadVal_SDA(uint8_t sel)
{
    if(sel == 1)
        return GPIO_ReadInputDataBit(SW_I2C1_SDA_GPIO, SW_I2C1_SDA_PIN);
		return 0;
}

uint8_t SW_I2C_ReadVal_SCL(uint8_t sel)
{
    if(sel == 1)
        return GPIO_ReadInputDataBit(SW_I2C1_SCL_GPIO, SW_I2C1_SCL_PIN);

    return 0;
}

void SW_I2C_Write_Data(uint8_t sel, uint8_t data)
{
    int  x;

    scl_low(sel);

    for (x = 7; x >= 0; x--)
    {
        sda_out(sel, data & (1 << x));
        TIMER__Wait_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(sel);

    }
}

uint8_t SW_I2C_Read_Data(uint8_t sel)
{
    int      x;
    uint8_t  readdata = 0;

    sda_in_mode(sel);

    for (x = 8; x--;)
    {
        scl_high(sel);

        readdata <<= 1;
        if (SW_I2C_ReadVal_SDA(sel))
            readdata |= 0x01;

        TIMER__Wait_us(SW_I2C_WAIT_TIME);
        scl_low(sel);

        TIMER__Wait_us(SW_I2C_WAIT_TIME);
    }

    sda_out_mode(sel);
    return readdata;
}

uint8_t SW_I2C_WriteControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data)
{
    uint8_t   returnack = TRUE;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data(sel, data);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_WriteControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr)
{
    uint8_t   returnack = TRUE;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }



    return returnack;
}

uint8_t SW_I2C_WriteControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint16_t data)
{
    uint8_t   returnack = TRUE;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data(sel, (data >> 8) & 0xFF);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    SW_I2C_Write_Data(sel, data & 0xFF);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_ReadControl_8Bit_OnlyRegAddr(uint8_t sel, uint8_t IICID, uint8_t regaddr)
{
    uint8_t   returnack = TRUE;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_ReadControl_8Bit_OnlyData(uint8_t sel, uint8_t IICID)
{
    uint8_t  readdata = 0;

    i2c_port_initial(sel);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    i2c_check_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    readdata = SW_I2C_Read_Data(sel);

    i2c_check_not_ack(sel);

    i2c_stop_condition(sel);

    return readdata;
}

uint16_t SW_I2C_ReadControl_16Bit_OnlyData(uint8_t sel, uint8_t IICID)
{
    uint8_t  readimsi = 0;
    uint16_t  readdata = 0;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    i2c_check_not_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    readimsi = SW_I2C_Read_Data(sel);
    i2c_check_not_ack_continue(sel);

    readdata = readimsi<<8;

    readimsi = SW_I2C_Read_Data(sel);
    i2c_check_not_ack(sel);


    readdata |= readimsi;

    i2c_stop_condition(sel);

    return readdata;
}

uint8_t SW_I2C_ReadControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr)
{
    uint8_t  readdata = 0;

    i2c_port_initial(sel);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    i2c_check_ack(sel);

    i2c_register_address(sel, regaddr);
    i2c_check_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    i2c_check_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    readdata = SW_I2C_Read_Data(sel);

    i2c_check_not_ack(sel);

    i2c_stop_condition(sel);

    return readdata;
}

uint16_t SW_I2C_ReadControl_16Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr)
{
    uint16_t  readdata = 0;

    i2c_port_initial(sel);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    i2c_check_ack(sel);

    i2c_register_address(sel, regaddr);
    i2c_check_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    i2c_check_ack(sel);

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    readdata = SW_I2C_Read_Data(sel);
    i2c_send_ack(sel);
    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    readdata = ((readdata << 8) | SW_I2C_Read_Data(sel));

    i2c_check_not_ack(sel);

    i2c_stop_condition(sel);

    return readdata;
}

uint8_t SW_I2C_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata))
{
    uint8_t   returnack = TRUE;
    uint8_t  index;

    i2c_port_initial(sel);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
	
    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    for ( index = 0 ; index < rcnt ; index++){
    	TIMER__Wait_us(SW_I2C_WAIT_TIME);
    	pdata[index] = SW_I2C_Read_Data(sel);
    }

    pdata[rcnt-1] = SW_I2C_Read_Data(sel);
	
    i2c_check_not_ack(sel);

    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_Multi_ReadnControl_8Bit(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata))
{
    uint8_t   returnack = TRUE;
    uint8_t  index;

    i2c_port_initial(sel);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);
	
    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    TIMER__Wait_us(SW_I2C_WAIT_TIME);

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, READ_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }

    for ( index = 0 ; index < (rcnt-1) ; index++){
    	TIMER__Wait_us(SW_I2C_WAIT_TIME);
    	pdata[index] = SW_I2C_Read_Data(sel);
	i2c_send_ack(sel);
	
    }

    pdata[rcnt-1] = SW_I2C_Read_Data(sel);
	
    i2c_check_not_ack(sel);

    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID)
{
    uint8_t   returnack = TRUE;

    i2c_start_condition(sel);

    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        returnack = FALSE;
    }
	
    return returnack;
}

uint8_t SW_I2C_UTIL_WRITE(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t data)
{
	return SW_I2C_WriteControl_8Bit(sel, IICID<<1, regaddr, data);
}

uint8_t SW_I2C_UTIL_Read(uint8_t sel, uint8_t IICID, uint8_t regaddr)
{
	return SW_I2C_ReadControl_8Bit(sel, IICID<<1, regaddr);
}

uint8_t SW_I2C_UTIL_Read_Multi(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t rcnt, uint8_t (*pdata))
{
	return SW_I2C_Multi_ReadnControl_8Bit(sel, IICID<<1, regaddr, rcnt, pdata);
}
