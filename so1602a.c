#include <stdlib.h>
#include <stdint.h>

#include "hardware/i2c.h"
#include "so1602a.h"


struct so1602a_t *so1602a_open(i2c_inst_t *i2c, uint8_t i2c_addr) {
    struct so1602a_t *dev = NULL;

    dev = (struct so1602a_t *)malloc(sizeof(struct so1602a_t));

    dev->i2c = i2c;
    dev->addr = i2c_addr;

    return dev;
}

void so1602a_close(struct so1602a_t *dev) {
    if(dev != NULL) {
        free(dev);
        dev = NULL;
    }
}

void so1602a_set_command(struct so1602a_t *dev, uint8_t command) {
    uint8_t buf[2] = {0x00};
    buf[0] = 0x00;
    buf[1] = command;
    i2c_write_blocking(dev->i2c, dev->addr, buf, 2, false);
}

void so1602a_send_data(struct so1602a_t *dev, uint8_t *data, size_t len) {
    uint8_t buf[2] = {0x00};
    for(size_t i = 0; i < len; i++) {
        buf[0] = 0x40;
        buf[1] = data[i];
        i2c_write_blocking(dev->i2c, dev->addr, buf, 2, false);
    }
}

void so1602a_set_position(struct so1602a_t *dev, uint8_t addr) {
    so1602a_set_command(dev, 0x80 | addr);
}

void so1602a_setup(struct so1602a_t *dev, uint8_t config) {
    sleep_ms(100);
    so1602a_set_command(dev, 0x01);
    sleep_ms(20);
    so1602a_set_command(dev, 0x02);
    sleep_ms(2);
    so1602a_set_command(dev, config);
    sleep_ms(2);
    so1602a_set_command(dev, 0x01);
    sleep_ms(20);
}
