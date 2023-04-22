
#include "sw_i2c.h"

#include "ql_api_osi.h"
#include "ql_gpio.h"

#define AIP_SPI_DIO GPIO_35
#define AIP_SPI_CLK GPIO_37

#define SW_I2C1_SCL_PIN     AIP_SPI_CLK
#define SW_I2C1_SDA_PIN     AIP_SPI_DIO


static int sw_i2c_port_initial(void)
{
    ql_gpio_init(AIP_SPI_DIO, GPIO_OUTPUT, PULL_NONE, LVL_HIGH); // DIO
    ql_gpio_init(AIP_SPI_CLK, GPIO_OUTPUT, PULL_NONE, LVL_HIGH); // CLK
    ql_delay_us(SW_I2C_WAIT_TIME);
    return 0;
}

static void sw_i2c_port_delay_us(uint32_t us)
{
    ql_delay_us(us);
}

static int sw_i2c_port_io_ctl(uint8_t opt, void *param)
{
    int ret = -1;
    ql_LvlMode l = 0;
    switch (opt)
    {
    case HAL_IO_OPT_SET_SDA_HIGH:
        ql_gpio_set_level(SW_I2C1_SDA_PIN, LVL_HIGH);
        break;
    case HAL_IO_OPT_SET_SDA_LOW:
        ql_gpio_set_level(SW_I2C1_SDA_PIN, LVL_LOW);
        break;
    case HAL_IO_OPT_GET_SDA_LEVEL:
        ql_gpio_get_level(SW_I2C1_SDA_PIN, &l);
        ret = l;
        break;
    case HAL_IO_OPT_SET_SDA_INPUT:
        ql_gpio_set_direction(SW_I2C1_SDA_PIN, GPIO_INPUT);
        ql_gpio_set_pull(SW_I2C1_SDA_PIN, PULL_NONE);
        break;
    case HAL_IO_OPT_SET_SDA_OUTPUT:
        ql_gpio_set_direction(SW_I2C1_SDA_PIN, GPIO_OUTPUT);
        break;
    case HAL_IO_OPT_SET_SCL_HIGH:
        ql_gpio_set_level(SW_I2C1_SCL_PIN, LVL_HIGH);
        break;
    case HAL_IO_OPT_SET_SCL_LOW:
        ql_gpio_set_level(SW_I2C1_SCL_PIN, LVL_LOW);
        break;
    case HAL_IO_OPT_GET_SCL_LEVEL:
        ql_gpio_get_level(SW_I2C1_SCL_PIN, &l);
        ret = l;
        break;
    case HAL_IO_OPT_SET_SCL_INPUT:
        ql_gpio_set_direction(SW_I2C1_SCL_PIN, GPIO_INPUT);
        ql_gpio_set_pull(SW_I2C1_SCL_PIN, PULL_NONE);
        break;
    case HAL_IO_OPT_SET_SCL_OUTPUT:
        ql_gpio_set_direction(SW_I2C1_SCL_PIN, GPIO_OUTPUT);
        break;
    default:
        break;
    }
    return ret;
}


sw_i2c_t sw_i2c_8850 = {
    .hal_init = sw_i2c_port_initial,
    .hal_io_ctl = sw_i2c_port_io_ctl,
    .hal_delay_us = sw_i2c_port_delay_us,
    };
