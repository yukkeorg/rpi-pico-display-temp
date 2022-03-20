#include <string.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "config.h"
#include "i2c_util.h"
#include "adt7410.h"
#include "so1602a.h"

enum status {
    INIT,
    RUNNING
};


int main(void)
{
    stdio_init_all();

    i2c_setup(i2c0, I2C_SDA_PIN, I2C_SCL_PIN, 400000);

    struct adt7410_t *sensor = NULL;
    sensor = adt7410_open(i2c0, ADT7410_I2C_ADDR);
    adt7410_set_config(sensor, ADT7410_CONFIG);

    struct so1602a_t *display = NULL;
    display = so1602a_open(i2c0, SO1602A_I2C_ADDR);
    so1602a_setup(display, SO1602A_CONFIG);

    char indicator[16 + 1] = {0x00};
    char buf[32] = {0x00};
    double temp = 0.0;

    enum status s = INIT;
    uint32_t c = 0;
    int l = 0;
    int i = 1;

    while(true) {
        if((c & 0x03) == 0) {
            temp = adt7410_get_temprature(sensor);
            snprintf(buf, 17, "Temp.%9.2f\xF2\x43", temp); // +NN.NN℃
        }

        if(s == INIT) {
            so1602a_set_position(display, 0x00);
            so1602a_send_data(display, (uint8_t *)"Initializing...", 15);
            if(c > 2) {
                s = RUNNING;
            }
        } else if (s == RUNNING) {
            // so1602a_set_position(display, 0x00);
            // so1602a_send_data(display, (uint8_t *)"Temp.", 5);

            so1602a_set_position(display, 0x00);
            so1602a_send_data(display, (uint8_t *)buf, (size_t)strlen((const char *)buf));
        }

        //
        memset(indicator, '-', 16);
        indicator[l] = 'o';
        so1602a_set_position(display, 0x20);
        so1602a_send_data(display, (uint8_t *)indicator, 16);

        //
        l += i;
        c++;
        if(c%15==0) i *= -1;

        //
        sleep_ms(1000);
    }

    adt7410_close(sensor);
    so1602a_close(display);

    return 0;
}
