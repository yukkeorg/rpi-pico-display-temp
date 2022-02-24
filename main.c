#include <stdio.h>
#include <string.h>

#include "boards/pico.h"
#include "hardware/structs/i2c.h"
#include "pico/stdlib.h"
#include "pico/binary_info.h"

#include "hardware/gpio.h"
#include "hardware/i2c.h"


#define SZ(d) ((size_t)(sizeof(d)/sizeof(d[0])))

const uint8_t ADT7410_CONFIG[1] = {0x80};
const uint8_t ADT7410_I2C_ADDR = 0x48;  // 72

const uint AD7410_I2C_SDA_PIN = 24;
const uint AD7410_I2C_SCL_PIN = 25;


static void system_init()
{
    stdio_init_all();
    setup_default_uart();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    // init i2c
    i2c_init(i2c0, 100000);
    gpio_set_function(AD7410_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(AD7410_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(AD7410_I2C_SDA_PIN);
    gpio_pull_up(AD7410_I2C_SCL_PIN);
}

static void init_adt7410(i2c_inst_t *i2c, uint8_t addr)
{
    uint8_t init_data[] = {0x00};
    i2c_write_blocking(i2c, addr, init_data, SZ(init_data), false);
}

#define MAX_LEN (256 + 1)
static void i2c_writeto_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, const uint8_t *buf, size_t len)
{
    uint8_t tmp[MAX_LEN] = {0};

    if(len > (MAX_LEN - 1)) return;

    tmp[0] = regaddr;
    memcpy(&tmp[1], buf, len);
    i2c_write_blocking(i2c, i2c_addr, tmp, len+1, true);
}

static void i2c_readfrom_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, uint8_t *buf, size_t len)
{
    regaddr |= 0x80;
    i2c_write_blocking(i2c, i2c_addr, &regaddr, 1, true);
    i2c_read_blocking(i2c, i2c_addr, buf, len, false);
}

int main(void)
{
    system_init();
    init_adt7410(i2c0, ADT7410_I2C_ADDR);

    i2c_writeto_mem(i2c0, ADT7410_I2C_ADDR, 0x03, ADT7410_CONFIG, 1);

    uint8_t buf[2] = {0};
    int32_t data = 0;
    double temp = 0.0;

    while(true) {
        i2c_readfrom_mem(i2c0, ADT7410_I2C_ADDR, 0x00, buf, 2);
        data = (int32_t)buf[0] << 8 | buf[1];
        if (data > 0x8000) {
            data = data - 65536;
        }
        temp = (double)data / 128.0;
        printf("%f\n", temp);
        sleep_ms(1000);
    }

    return 0;
}
