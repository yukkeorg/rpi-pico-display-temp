#ifndef __SO1602A_H__
#define __SO1602A_H__

#include "hardware/i2c.h"

#define SO1602A_DISPLAY          (0x04)
#define SO1602A_CURSOR           (0x02)
#define SO1602A_BLINK            (0x02)
#define SO1602A_DEFAULT          (SO1602A_DISPLAY|SO1602A_CURSOR|SO1602A_BLINK)


void so1602a_set_command(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t command);

void so1602a_send_data(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t *buf, size_t len);

void so1602a_set_position(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t addr);

void so1602a_setup(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t config);

#endif
