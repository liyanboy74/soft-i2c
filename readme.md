# Soft I2C

原作者：https://schkorea.tistory.com/437

精简了部分代码，增加8/16bit寄存器地址的突发（连续）读写函数

## 示例

**usage:**

define GPIO in `sw_i2c.h`:

```c
#define SW_I2C1_SCL_PORT    GPIOB
#define SW_I2C1_SDA_PORT    GPIOB
#define SW_I2C1_SCL_PIN     GPIO_PIN_6
#define SW_I2C1_SDA_PIN     GPIO_PIN_7
```

**Example:**

```c
#include "sw_i2c.h"
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



