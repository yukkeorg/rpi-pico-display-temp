#include <string.h>

#include "hardware/gpio.h"
#include "hardware/i2c.h"

#include "i2c_util.h"


#define MAX_LEN (64 + 1)


void i2c_setup(i2c_inst_t *i2c, uint sda, uint scl, uint freq)
{
    i2c_init(i2c, freq);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);
}

void i2c_writeto_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, const uint8_t *buf, size_t len)
{
    uint8_t tmp[MAX_LEN] = {0};

    if(len > (MAX_LEN - 1)) return;

    tmp[0] = regaddr;
    memcpy(&tmp[1], buf, len);
    i2c_write_blocking(i2c, i2c_addr, tmp, len+1, false);
}

void i2c_readfrom_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, uint8_t *buf, size_t len)
{
    i2c_write_blocking(i2c, i2c_addr, &regaddr, 1, true);
    i2c_read_blocking(i2c, i2c_addr, buf, len, false);
}
