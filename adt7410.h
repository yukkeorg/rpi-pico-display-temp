#ifndef __ADT7410_H__
#define __ADT7410_H__

#include "hardware/i2c.h"

#define ADT7410_REGADDR_DATA_MSB    (0x00)
#define ADT7410_REGADDR_DATA_LSB    (0x01)
#define ADT7410_REGADDR_DATA        (ADT7410_REGADDR_DATA_MSB)
#define ADT7410_REGADDR_CONFIG      (0x03)

struct adt7410_t {
    i2c_inst_t *i2c;
    uint8_t addr;
};

struct adt7410_t *adt7410_open(i2c_inst_t *i2c, uint8_t i2c_addr);
void adt7410_close(struct adt7410_t *dev);

double adt7410_get_temprature(struct adt7410_t *dev);
uint8_t adt7410_get_config(struct adt7410_t *dev);
void adt7410_set_config(struct adt7410_t *dev, uint8_t value);

#endif
