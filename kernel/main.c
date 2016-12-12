//
// Created by sajad on 12/10/16.
// kernel main function
//


#include <ioports.h>
#include "version.h"

// kernel initial function
void kernel_init();

// kernel main
void kernel_main();

void kernel_init() {
    kernel_main();
}

void kernel_main() {
    if (DEBUG){
        BochsConsolePrintChar('s');
        BochsBreak();
    }
}
