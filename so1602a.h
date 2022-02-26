#ifndef __SO1602A_H__
#define __SO1602A_H__

#include "hardware/i2c.h"

void so1602a_set_command(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t command);
void so1602a_send_data(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t *buf, size_t len);
void so1602a_setup(i2c_inst_t *i2c, uint8_t i2c_addr);

#endif
