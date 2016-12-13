//
// Created by sajad on 12/10/16.
// kernel main function
//


#include <ioports.h>
#include "version.h"
#include "tty.h"

// kernel initial function
void kernel_init();

// kernel main
void kernel_main();

void kernel_init() {
    kernel_main();
}

void kernel_main() {
    klog("kernel", LOG_WARN, "salam %d ta salam", 10);
    if (LOG_LEVEL == LOG_DEBUG) {
        BochsConsolePrintChar('s');
//        BochsBreak();
    }
}
