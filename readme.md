# Soft I2C

原作者：https://schkorea.tistory.com/437

精简了部分代码，并将STM32版示例代码移植到了AT32F415

## 示例

**usage:**

define GPIO in `i2c_sw.h`:

```c
#define   GPIO_SW_I2C1_SCL        GPIOB
#define   GPIO_SW_I2C1_SDA        GPIOB
#define   GPIO_SW_I2C1_SCL_PIN    GPIO_PIN_13
#define   GPIO_SW_I2C1_SDA_PIN    GPIO_PIN_14
```

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



