#include "sw_i2c.h"

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

//sw_i2c 初始化
void SW_I2C_initial(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    //i2c_sw SCL
    GPIO_InitStruct.Pin = SW_I2C1_SCL_PIN;
    HAL_GPIO_Init(SW_I2C1_SCL_PORT, &GPIO_InitStruct);
    //i2c_sw SDA
    GPIO_InitStruct.Pin = SW_I2C1_SDA_PIN;
    HAL_GPIO_Init(SW_I2C1_SDA_PORT, &GPIO_InitStruct);
}

//引脚置位
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

//引脚复位
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

//读引脚状态
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	return (uint8_t)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

//SDA引脚切换输入模式
void sda_in_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if(sel == 1)
    {
        GPIO_InitStruct.Pin = SW_I2C1_SDA_PIN;
        HAL_GPIO_Init(SW_I2C1_SDA_PORT, &GPIO_InitStruct);
    }
    // if(sel == 2)
}

//SDA引脚切换输出模式
void sda_out_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if(sel == 1)
    {
        GPIO_InitStruct.Pin = SW_I2C1_SDA_PIN;
        HAL_GPIO_Init(SW_I2C1_SDA_PORT, &GPIO_InitStruct);
    }
    // if(sel == 2)
}

//SCL引脚切换输入模式
void scl_in_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if(sel == 1)
    {
        GPIO_InitStruct.Pin = SW_I2C1_SCL_PIN;
        HAL_GPIO_Init(SW_I2C1_SCL_PORT, &GPIO_InitStruct);
    }
    // if(sel == 2)
}

//SCL引脚切换输出模式
void scl_out_mode(uint8_t sel)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    if(sel == 1)
    {
        GPIO_InitStruct.Pin = SW_I2C1_SCL_PIN;
        HAL_GPIO_Init(SW_I2C1_SCL_PORT, &GPIO_InitStruct);
    }
    // if(sel == 2)
}

void TIMER__Wait_us(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

void sda_high(uint8_t sel)
{
    if(sel == 1)
        GPIO_SetBits(SW_I2C1_SDA_PORT, SW_I2C1_SDA_PIN);
}


void sda_low(uint8_t sel)
{
    if(sel == 1)
        GPIO_ResetBits(SW_I2C1_SDA_PORT, SW_I2C1_SDA_PIN);
}


void scl_high(uint8_t sel)
{
    if(sel == 1)
        GPIO_SetBits(SW_I2C1_SCL_PORT, SW_I2C1_SCL_PIN);
}


void scl_low(uint8_t sel)
{
    if(sel == 1)
        GPIO_ResetBits(SW_I2C1_SCL_PORT, SW_I2C1_SCL_PIN);
}

void sda_out(uint8_t sel, uint8_t out)
{
    if(out)
        sda_high(sel);
    else
        sda_low(sel);
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

uint8_t SW_I2C_ReadVal_SDA(uint8_t sel)
{
    if(sel == 1)
        return GPIO_ReadInputDataBit(SW_I2C1_SDA_PORT, SW_I2C1_SDA_PIN);
	return 0;
}

uint8_t SW_I2C_ReadVal_SCL(uint8_t sel)
{
    if(sel == 1)
        return GPIO_ReadInputDataBit(SW_I2C1_SCL_PORT, SW_I2C1_SCL_PIN);
    return 0;
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
    uint8_t ack;
    int i;
    unsigned int temp;
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
    int x;

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

void SW_I2C_Write_Data(uint8_t sel, uint8_t data)
{
    int x;
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
    int x;
    uint8_t readdata = 0;
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

uint8_t SW_I2C_Read_8addr(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(!rcnt) return FALSE;

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
    if(rcnt > 1)
    {
        for ( index = 0 ; index < (rcnt - 1) ; index++)
        {
            TIMER__Wait_us(SW_I2C_WAIT_TIME);
            pdata[index] = SW_I2C_Read_Data(sel);
            i2c_send_ack(sel);
        }
    }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    pdata[rcnt-1] = SW_I2C_Read_Data(sel);
    i2c_check_not_ack(sel);
    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_Read_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(!rcnt) return FALSE;

    i2c_port_initial(sel);
    i2c_start_condition(sel);
    //写ID
    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //写高八位地址
    i2c_register_address(sel, (uint8_t)(regaddr>>8));
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //写低八位地址
    i2c_register_address(sel, (uint8_t)regaddr);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //重启I2C总线
    i2c_start_condition(sel);
    //读ID
    i2c_slave_address(sel, IICID, READ_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    //循环读数据
    if(rcnt > 1)
    {
        for ( index = 0 ; index < (rcnt - 1) ; index++)
        {
            TIMER__Wait_us(SW_I2C_WAIT_TIME);
            pdata[index] = SW_I2C_Read_Data(sel);
            i2c_send_ack(sel);
        }
    }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    pdata[rcnt-1] = SW_I2C_Read_Data(sel);
    i2c_check_not_ack(sel);
    i2c_stop_condition(sel);

    return returnack;
}

uint8_t SW_I2C_Write_8addr(uint8_t sel, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(!rcnt) return FALSE;

    i2c_port_initial(sel);
    i2c_start_condition(sel);
    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    i2c_register_address(sel, regaddr);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    for ( index = 0 ; index < rcnt ; index++)
    {
        SW_I2C_Write_Data(sel, pdata[index]);
        if (!i2c_check_ack(sel)) { returnack = FALSE; }
        TIMER__Wait_us(SW_I2C_WAIT_TIME);
    }
    i2c_stop_condition(sel);
    return returnack;
}

uint8_t SW_I2C_Write_16addr(uint8_t sel, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(!rcnt) return FALSE;

    i2c_port_initial(sel);
    i2c_start_condition(sel);
    //写ID
    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //写高八位地址
    i2c_register_address(sel, (uint8_t)(regaddr>>8));
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //写低八位地址
    i2c_register_address(sel, (uint8_t)regaddr);
    if (!i2c_check_ack(sel)) { returnack = FALSE; }
    TIMER__Wait_us(SW_I2C_WAIT_TIME);
    //写数据
    for ( index = 0 ; index < rcnt ; index++)
    {
        SW_I2C_Write_Data(sel, pdata[index]);
        if (!i2c_check_ack(sel)) { returnack = FALSE; }
        TIMER__Wait_us(SW_I2C_WAIT_TIME);
    }
    i2c_stop_condition(sel);
    return returnack;
}

uint8_t SW_I2C_Check_SlaveAddr(uint8_t sel, uint8_t IICID)
{
    uint8_t returnack = TRUE;
    i2c_start_condition(sel);
    i2c_slave_address(sel, IICID, WRITE_CMD);
    if (!i2c_check_ack(sel))
    {
        i2c_stop_condition(sel);
        returnack = FALSE;
    }
    i2c_stop_condition(sel);
    return returnack;
}
