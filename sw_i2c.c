#include <stdlib.h>

#include "sw_i2c.h"

#ifndef TRUE
	#define TRUE 1
#endif
#ifndef FALSE
	#define FALSE 0
#endif

// sw_i2c 初始化
void SW_I2C_initial(sw_i2c_t *d)
{
    if (d)
    {
        d->hal_init();
    }
}

static void sda_out(sw_i2c_t *d, uint8_t out)
{
    if(out)
        d->hal_io_ctl(HAL_IO_OPT_SET_SDA_HIGH, NULL);
    else
        d->hal_io_ctl(HAL_IO_OPT_SET_SDA_LOW, NULL);
}

static void i2c_clk_data_out(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
}

static void i2c_port_initial(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_HIGH, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
}


static uint8_t SW_I2C_ReadVal_SDA(sw_i2c_t *d)
{
    
    return d->hal_io_ctl(HAL_IO_OPT_GET_SDA_LEVEL, NULL);
}

#if 0
static uint8_t SW_I2C_ReadVal_SCL(sw_i2c_t *d)
{

    return d->hal_io_ctl(HAL_IO_OPT_GET_SCL_LEVEL, NULL);
}
#endif

static void i2c_start_condition(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_HIGH, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_LOW, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME << 1);
}

static void i2c_stop_condition(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_LOW, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_HIGH, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
}

static uint8_t i2c_check_ack(sw_i2c_t *d)
{
    uint8_t ack;
    int i;
    unsigned int temp;
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_INPUT, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
    ack = 0;
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    for (i = 10; i > 0; i--)
    {
        temp = !(SW_I2C_ReadVal_SDA(d));
        if (temp)
        {
            ack = 1;
            break;
        }
    }
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_OUTPUT, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    return ack;
}

static void i2c_check_not_ack(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_INPUT, NULL);
    i2c_clk_data_out(d);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_OUTPUT, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
}

static void i2c_slave_address(sw_i2c_t *d, uint8_t IICID, uint8_t readwrite)
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

    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);

    for (x = 7; x >= 0; x--)
    {
        sda_out(d, IICID & (1 << x));
        d->hal_delay_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(d);

    }
}

static void i2c_register_address(sw_i2c_t *d, uint8_t addr)
{
    int x;

    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);

    for (x = 7; x >= 0; x--)
    {
        sda_out(d, addr & (1 << x));
        d->hal_delay_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(d);
    }
}

static void i2c_send_ack(sw_i2c_t *d)
{
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_OUTPUT, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_LOW, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME << 1);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_LOW, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME << 1);
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_OUTPUT, NULL);
    d->hal_delay_us(SW_I2C_WAIT_TIME);
}

static void SW_I2C_Write_Data(sw_i2c_t *d, uint8_t data)
{
    int x;
    d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
    for (x = 7; x >= 0; x--)
    {
        sda_out(d, data & (1 << x));
        d->hal_delay_us(SW_I2C_WAIT_TIME);
        i2c_clk_data_out(d);
    }
}

static uint8_t SW_I2C_Read_Data(sw_i2c_t *d)
{
    int x;
    uint8_t readdata = 0;
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_INPUT, NULL);
    for (x = 8; x--;)
    {
        d->hal_io_ctl(HAL_IO_OPT_SET_SCL_HIGH, NULL);
        readdata <<= 1;
        if (SW_I2C_ReadVal_SDA(d))
            readdata |= 0x01;
        d->hal_delay_us(SW_I2C_WAIT_TIME);
        d->hal_io_ctl(HAL_IO_OPT_SET_SCL_LOW, NULL);
        d->hal_delay_us(SW_I2C_WAIT_TIME);
    }
    d->hal_io_ctl(HAL_IO_OPT_SET_SDA_OUTPUT, NULL);
    return readdata;
}

uint8_t SW_I2C_Read_8addr(sw_i2c_t *d, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(d==NULL) return FALSE;

    if(!rcnt) return FALSE;

    i2c_port_initial(d);
    i2c_start_condition(d);
    i2c_slave_address(d, IICID, WRITE_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    i2c_register_address(d, regaddr);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    i2c_start_condition(d);
    i2c_slave_address(d, IICID, READ_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    if(rcnt > 1)
    {
        for ( index = 0 ; index < (rcnt - 1) ; index++)
        {
            d->hal_delay_us(SW_I2C_WAIT_TIME);
            pdata[index] = SW_I2C_Read_Data(d);
            i2c_send_ack(d);
        }
    }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    pdata[rcnt-1] = SW_I2C_Read_Data(d);
    i2c_check_not_ack(d);
    i2c_stop_condition(d);

    return returnack;
}

uint8_t SW_I2C_Read_16addr(sw_i2c_t *d, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(d==NULL) return FALSE;

    if(!rcnt) return FALSE;

    i2c_port_initial(d);
    i2c_start_condition(d);
    //写ID
    i2c_slave_address(d, IICID, WRITE_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //写高八位地址
    i2c_register_address(d, (uint8_t)(regaddr>>8));
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //写低八位地址
    i2c_register_address(d, (uint8_t)regaddr);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //重启I2C总线
    i2c_start_condition(d);
    //读ID
    i2c_slave_address(d, IICID, READ_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    //循环读数据
    if(rcnt > 1)
    {
        for ( index = 0 ; index < (rcnt - 1) ; index++)
        {
            d->hal_delay_us(SW_I2C_WAIT_TIME);
            pdata[index] = SW_I2C_Read_Data(d);
            i2c_send_ack(d);
        }
    }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    pdata[rcnt-1] = SW_I2C_Read_Data(d);
    i2c_check_not_ack(d);
    i2c_stop_condition(d);

    return returnack;
}

uint8_t SW_I2C_Write_8addr(sw_i2c_t *d, uint8_t IICID, uint8_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(d==NULL) return FALSE;

    if(!rcnt) return FALSE;

    i2c_port_initial(d);
    i2c_start_condition(d);
    i2c_slave_address(d, IICID, WRITE_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    i2c_register_address(d, regaddr);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    for ( index = 0 ; index < rcnt ; index++)
    {
        SW_I2C_Write_Data(d, pdata[index]);
        if (!i2c_check_ack(d)) { returnack = FALSE; }
        d->hal_delay_us(SW_I2C_WAIT_TIME);
    }
    i2c_stop_condition(d);
    return returnack;
}

uint8_t SW_I2C_Write_16addr(sw_i2c_t *d, uint8_t IICID, uint16_t regaddr, uint8_t *pdata, uint8_t rcnt)
{
    uint8_t returnack = TRUE;
    uint8_t index;

    if(d==NULL) return FALSE;

    if(!rcnt) return FALSE;

    i2c_port_initial(d);
    i2c_start_condition(d);
    //写ID
    i2c_slave_address(d, IICID, WRITE_CMD);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //写高八位地址
    i2c_register_address(d, (uint8_t)(regaddr>>8));
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //写低八位地址
    i2c_register_address(d, (uint8_t)regaddr);
    if (!i2c_check_ack(d)) { returnack = FALSE; }
    d->hal_delay_us(SW_I2C_WAIT_TIME);
    //写数据
    for ( index = 0 ; index < rcnt ; index++)
    {
        SW_I2C_Write_Data(d, pdata[index]);
        if (!i2c_check_ack(d)) { returnack = FALSE; }
        d->hal_delay_us(SW_I2C_WAIT_TIME);
    }
    i2c_stop_condition(d);
    return returnack;
}

uint8_t SW_I2C_Check_SlaveAddr(sw_i2c_t *d, uint8_t IICID)
{
    uint8_t returnack = TRUE;
    i2c_start_condition(d);
    i2c_slave_address(d, IICID, WRITE_CMD);
    if (!i2c_check_ack(d))
    {
        i2c_stop_condition(d);
        returnack = FALSE;
    }
    i2c_stop_condition(d);
    return returnack;
}
