/**
 * License: MIT License
 */
#include <stdlib.h>

#include "adt7410.h"
#include "i2c_util.h"


struct adt7410_t *adt7410_open(i2c_inst_t *i2c, uint8_t i2c_addr) {
    struct adt7410_t *dev = NULL;

    dev = (struct adt7410_t *)malloc(sizeof(struct adt7410_t));
    dev->i2c = i2c;
    dev->addr = i2c_addr;

    return dev;
}

void adt7410_close(struct adt7410_t *dev) {
    if(dev != NULL) {
        free(dev);
        dev = NULL;
    }
}

double adt7410_get_temprature(struct adt7410_t *dev) {
    uint8_t buf[2] = {0};
    int32_t data = 0;
    double temp = 0.0;

    i2c_readfrom_mem(dev->i2c, dev->addr, ADT7410_REGADDR_DATA, buf, 2);
    data = (int32_t)(buf[0] << 8 | buf[1]);
    if (data > 0x8000) {
        data = data - 65536;
    }

    return (double)data / 128.0;
}

uint8_t adt7410_get_config(struct adt7410_t *dev) {
    uint8_t buf = 0;

    i2c_readfrom_mem(dev->i2c, dev->addr, ADT7410_REGADDR_CONFIG, &buf, 1);

    return buf;
}

void adt7410_set_config(struct adt7410_t *dev, uint8_t value) {
    i2c_writeto_mem(dev->i2c, dev->addr, ADT7410_REGADDR_CONFIG, &value, 1);
}
