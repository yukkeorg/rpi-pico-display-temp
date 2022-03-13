#ifndef __SO1602A_H__
#define __SO1602A_H__

#include "hardware/i2c.h"

#define SO1602A_DISPLAY          (0x04)
#define SO1602A_CURSOR           (0x02)
#define SO1602A_BLINK            (0x02)
#define SO1602A_DEFAULT          (SO1602A_DISPLAY|SO1602A_CURSOR|SO1602A_BLINK)

#define SO1602A_1STLINE_BEGIN_POS  (0x00)
#define SO1602A_2NDLINE_BEGIN_POS  (0x20)

struct so1602a_t {
    i2c_inst_t *i2c;
    uint8_t addr;
};

struct so1602a_t *so1602a_open(i2c_inst_t *i2c, uint8_t i2c_addr);
void so1602a_close(struct so1602a_t *dev);
void so1602a_set_command(struct so1602a_t *dev, uint8_t command);
void so1602a_send_data(struct so1602a_t *dev, uint8_t *buf, size_t len);
void so1602a_set_position(struct so1602a_t *dev, uint8_t addr);
void so1602a_setup(struct so1602a_t *dev, uint8_t config);

#endif
