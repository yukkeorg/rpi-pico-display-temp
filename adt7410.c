#include "adt7410.h"
#include "i2c_util.h"


double adt7410_get_temprature(i2c_inst_t *i2c, uint8_t i2c_addr)
{
    uint8_t buf[2] = {0};
    int32_t data = 0;
    double temp = 0.0;

    i2c_readfrom_mem(i2c, i2c_addr, 0x00, buf, 2);
    data = (int32_t)(buf[0] << 8 | buf[1]);
    if (data > 0x8000) {
        data = data - 65536;
    }

    return (double)data / 128.0;
}

uint8_t adt7410_get_config(i2c_inst_t *i2c, uint8_t i2c_addr)
{
    uint8_t buf = 0;

    i2c_readfrom_mem(i2c, i2c_addr, 0x03, &buf, 1);
    return buf;
}

void adt7410_set_config(i2c_inst_t *i2c, uint8_t i2c_addr, uint8_t value)
{
    i2c_writeto_mem(i2c, i2c_addr, 0x03, &value, 1);
}
