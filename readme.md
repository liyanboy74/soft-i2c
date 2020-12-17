# Soft I2C For STM32 using HAL

That is Edited version of  [Original version](https://schkorea.tistory.com/437) for stm32

**usage:**

define GPIO in `i2c_sw.h`:

```c
#define   GPIO_SW_I2C1_SCL			GPIOB
#define   GPIO_SW_I2C1_SDA			GPIOB
#define   GPIO_SW_I2C1_SCL_PIN		GPIO_PIN_13
#define   GPIO_SW_I2C1_SDA_PIN		GPIO_PIN_14
```

That example is for `stm32f103` , for use other micro replace `#include "stm32f1xx_hal_gpio.h"` in `i2c_sw.h`.

This library has the ability to activate more than 10 software I2C , which have been commented in this library, but by default only one of them has been activated.

**Example:**

```c
#include "i2c_sw.h"

int main()
{
    SW_I2C_initial();
    i2c_port_initial(SW_I2C1);
    
    while(1)
    {
        //Write DATA to Reg at Reg_Addr from I2C_Add Device connected to SW_I2C1
        SW_I2C_WriteControl_8Bit(SW_I2C1,I2C_Add,Reg_Addr,DATA);
        //Read DATA at Reg_Add from I2C_Add Device connected to SW_I2C1
        DATA=SW_I2C_ReadControl_8Bit(SW_I2C1,I2C_Add,Reg_Add);
    }
    
}

```



