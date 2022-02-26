#ifndef __ADT7410_H__
#define __ADT7410_H__

#include "hardware/i2c.h"

double adt7410_get_temprature(i2c_inst_t *i2c, uint8_t i2c_addr);
uint8_t adt7410_get_config(i2c_inst_t *i2c, uint8_t i2c_addr);
void adt7410_set_config(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t value);

#endif
