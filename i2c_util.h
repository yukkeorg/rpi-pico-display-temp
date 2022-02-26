#ifndef __I2C_UTIL_H__
#define __I2C_UTIL_H__

#include "pico/types.h"
#include "hardware/i2c.h"

void i2c_setup(i2c_inst_t *i2c, uint sda, uint scl, uint freq);
void i2c_writeto_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, const uint8_t *buf, size_t len);
void i2c_readfrom_mem(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t regaddr, uint8_t *buf, size_t len);

#endif
