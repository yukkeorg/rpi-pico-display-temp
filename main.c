#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "config.h"
#include "i2c_util.h"
#include "adt7410.h"
#include "so1602a.h"


static void system_init()
{
    stdio_init_all();

    i2c_setup(i2c0, I2C_SDA_PIN, I2C_SCL_PIN, 400000);
    adt7410_set_config(i2c0, ADT7410_I2C_ADDR, ADT7410_CONFIG);
    so1602a_setup(i2c0, SO1602A_I2C_ADDR, SO1602A_CONFIG);
}

int main(void)
{
    system_init();

    char indicator[] = {'O', 'o'};
    char buf[32] = {0x00};
    double temp = 0.0;
    uint32_t c = 0;

    while(true) {
        if((c & 0x03) == 0) {
            temp = adt7410_get_temprature(i2c0, ADT7410_I2C_ADDR);
            sprintf(buf, "%+3.2f\xF2\x43", temp); // +NN.NN℃
            puts(buf);
        }

        //
        so1602a_set_position(i2c0, SO1602A_I2C_ADDR, 0x00);
        so1602a_send_data(i2c0, SO1602A_I2C_ADDR, (uint8_t *)"Temperature:", 12);

        so1602a_set_position(i2c0, SO1602A_I2C_ADDR, 0x0F);
        so1602a_send_data(i2c0, SO1602A_I2C_ADDR, (uint8_t *)&indicator[(c & 1)], 1);

        so1602a_set_position(i2c0, SO1602A_I2C_ADDR, 0x28);
        so1602a_send_data(i2c0, SO1602A_I2C_ADDR, buf, (size_t)strlen(buf));

        //
        sleep_ms(1000);
        c++;
    }

    return 0;
}
