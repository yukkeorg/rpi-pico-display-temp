#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "so1602a.h"


void so1602a_set_command(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t command)
{
    uint8_t buf[2] = {0x00};
    buf[0] = 0x00;
    buf[1] = command;
    i2c_write_blocking(i2c, i2c_addr, buf, 2, false);
}

void so1602a_send_data(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t *data, size_t len)
{
    uint8_t buf[2] = {0x00};
    for(size_t i = 0; i < len; i++) {
        buf[0] = 0x40;
        buf[1] = data[i];
        i2c_write_blocking(i2c, i2c_addr, buf, 2, false);
    }
}

void so1602a_set_position(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t addr) {
    so1602a_set_command(i2c, i2c_addr, 0x80|addr);
}

void so1602a_setup(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t config)
{
    sleep_ms(100);
    so1602a_set_command(i2c, i2c_addr, 0x01);
    sleep_ms(20);
    so1602a_set_command(i2c, i2c_addr, 0x02);
    sleep_ms(2);
    so1602a_set_command(i2c, i2c_addr, config);
    sleep_ms(2);
    so1602a_set_command(i2c, i2c_addr, 0x01);
    sleep_ms(20);
}
