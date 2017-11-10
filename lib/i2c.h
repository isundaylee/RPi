#pragma once

#include "lib/common.h"

#define I2C_SUCCESS 0
#define I2C_ERROR   1

void i2c_enable();
void i2c_disable();
int i2c_write(int addr, byte *buf, int len);
int i2c_read(int addr, byte *buf, int len);
