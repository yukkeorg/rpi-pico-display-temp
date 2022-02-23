#include <stdio.h>

#include "boards/pico.h"
#include "hardware/structs/i2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"


#define SZ(d) ((size_t)(sizeof(d)/sizeof(d[0])))


static void system_init()
{
    stdio_init_all();
    setup_default_uart();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // init i2c
    i2c_init(i2c0, 100000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
}

static void init_adt7410(i2c_inst_t *i2c, uint8_t addr)
{
    uint8_t init_data[] = {0x00};
    i2c_write_blocking(i2c, addr, init_data, SZ(init_data), false);
}

static void i2c_writeto_mem(i2c_inst_t *i2c, uint8_t addr, uint8_t regaddr, uint8_t *buf, size_t len)
{
    i2c_write_blocking(i2c, addr, &regaddr, 1, false);
    i2c_write_blocking(i2c, addr, buf, len, false);
}

static void i2c_readfrom_mem(i2c_inst_t *i2c, uint8_t addr, uint8_t regaddr, uint8_t *buf, size_t len)
{
    i2c_write_blocking(i2c, addr, &regaddr, 1, false);
    i2c_read_blocking(i2c, addr, buf, len, false);
}

int main(void)
{
    system_init();
    init_adt7410(i2c0, 72);

    while(true) {
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(200);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        sleep_ms(300);
    }

    return 0;
}
