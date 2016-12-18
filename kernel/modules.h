//
// Created by sajad on 12/15/16.
//

#ifndef SJOS_MODULES_H
#define SJOS_MODULES_H

#include "multiboot.h"

#define MODULE_NAME(X) __attribute__ ((section ("modinfo"))) const char *modname = #X
#define MODULE_INIT __attribute__ ((section ("mod")))

void init_modules(multiboot_info_t *multibootInfo);

#endif //SJOS_MODULES_H
