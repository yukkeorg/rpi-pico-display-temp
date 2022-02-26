#include <string.h>
#include <stdio.h>

#include "boards/pico.h"
#include "pico/stdlib.h"
// #include "pico/binary_info.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "config.h"
#include "i2c_util.h"
#include "adt7410.h"
#include "so1602a.h"


#define SZ(d) ((size_t)(sizeof(d)/sizeof(d[0])))


static void system_init()
{
    stdio_init_all();

    i2c_setup(i2c0, I2C_SDA_PIN, I2C_SCL_PIN, 100000);
    adt7410_set_config(i2c0, ADT7410_I2C_ADDR, ADT7410_CONFIG);
    so1602a_setup(i2c0, SO1602A_I2C_ADDR);
}

int main(void)
{
    char buf[128] = "";

    system_init();

    double temp = 0.0;
    while(true) {
        sprintf(buf, "%f C", adt7410_get_temprature(i2c0, ADT7410_I2C_ADDR));
        puts(buf);
        so1602a_set_command(i2c0, SO1602A_I2C_ADDR, 0x02);
        so1602a_send_data(i2c0, SO1602A_I2C_ADDR, buf, (size_t)strlen(buf));
        sleep_ms(1000);
    }

    return 0;
}
