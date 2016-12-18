//
// Created by sajad on 12/10/16.
// kernel main function
//


#include <ioports.h>
#include <gdt.h>
#include "version.h"
#include "tty.h"
#include "multiboot.h"
#include "modules.h"

// kernel initial function
void kernel_init(multiboot_info_t *multibootInfo);

// kernel main
void kernel_main();

void kernel_init(multiboot_info_t *multibootInfo) {
    init_gdt();
    init_modules(multibootInfo);
    kernel_main();
}

void kernel_main() {
    klog("kernel", LOG_WARN, "salam %d\n ta salam", 10);
}
