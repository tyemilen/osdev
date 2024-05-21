#ifndef HAL_H_
#define HAL_H_

#include "types.h"

void io_write8(unsigned short port, unsigned char val);
unsigned char io_read8(unsigned short port);

void io_write16(unsigned short port, unsigned char val);
unsigned char io_read16(unsigned short port);

void io_write32(unsigned short port, u32 val);

#endif /* HAL_H_ */