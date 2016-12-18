//
// Created by sajad on 12/18/16.
//

#include "gdt.h"

extern void set_gdtr();

extern void gdt_flush();

void init_gdt() {
    // setting base and limit of gdtr
    gdt_r.base = (uint32_t) &gdt;
    gdt_r.limit = sizeof(gdt_r) * sizeof(struct gdt_entry) - 1;

    // null
    set_gdt_entry(0, 0, 0, 0, 0);

    // kernel code segment
    set_gdt_entry(1, 0, 0xffffffff, 0xCF, 0x9A);
    // kernel data segment
    set_gdt_entry(2, 0, 0xffffffff, 0xCF, 0x92);

    set_gdtr();
    gdt_flush();
}

void set_gdt_entry(size_t index, uint32_t base, uint32_t limit, uint8_t flags, uint8_t access) {
    // base
    gdt[index].base_low = (uint16_t) (base & 0xFFFF);
    gdt[index].base_mid = (uint8_t) ((base & 0x00FF0000) >> 16);
    gdt[index].base_hi = (uint8_t) ((base & 0xFF000000) >> 24);

    // limit
    gdt[index].limit_low = (uint16_t) (limit & 0xFFFF);
    gdt[index].limit_hi_flags = (uint8_t) (limit & 0xF0000) >> 16;

    // flags
    gdt[index].limit_hi_flags |= flags & 0xF0;

    // access
    gdt[index].access = access;
}
