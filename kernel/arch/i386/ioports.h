//
// Created by simulation on 12/12/16.
//

#include <stdint.h>

#ifndef SJOS_IOPORTS_H
#define SJOS_IOPORTS_H

// ioports write functions
void outportb(uint32_t,uint8_t);
void outportw(uint32_t,uint16_t);
void outportl(uint32_t,uint32_t);

// ioports read functions
uint8_t inportb(uint32_t);
uint16_t inportw(uint32_t);
uint32_t inportl(uint32_t);

#endif //SJOS_IOPORTS_H
