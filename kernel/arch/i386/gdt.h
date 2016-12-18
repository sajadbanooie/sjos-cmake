//
// Created by sajad on 12/18/16.
//

#ifndef SJOS_GDT_H
#define SJOS_GDT_H


#include <stdint.h>
#include <stddef.h>

struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_r;

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t limit_hi_flags;
    uint8_t base_hi;
} __attribute__((packed)) gdt[6];


void init_gdt();

void set_gdt_entry(size_t index, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access);

#endif //SJOS_GDT_H
