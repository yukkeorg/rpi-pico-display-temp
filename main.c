#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
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

    i2c_setup(i2c0, I2C_SDA_PIN, I2C_SCL_PIN, 400000);
    adt7410_set_config(i2c0, ADT7410_I2C_ADDR, ADT7410_CONFIG);
    so1602a_setup(i2c0, SO1602A_I2C_ADDR, SO1602A_DEFAULT);
}

int main(void)
{
    system_init();

    char buf[32] = {0x00};
    double temp = 0.0;
    while(true) {
        temp = adt7410_get_temprature(i2c0, ADT7410_I2C_ADDR);
        sprintf(buf, "%+3.2f\xF2\x43", temp); // +NN.NN℃
        puts(buf);
        so1602a_set_position(i2c0, SO1602A_I2C_ADDR, 0x20);
        so1602a_send_data(i2c0, SO1602A_I2C_ADDR, buf, (size_t)strlen(buf));
        sleep_ms(1000);
    }

    return 0;
}
