//
// Created by sajad on 12/15/16.
//

#include "modules.h"
#include "tty.h"
#include "version.h"
#include <ioports.h>

void init_modules(multiboot_info_t *multibootInfo) {
    klog("modules", LOG_INFO, "loading %d modules...", multibootInfo->mods_count);
    multiboot_module_t *module = (multiboot_module_t *) multibootInfo->mods_addr;
    for (int i = 0; i < multibootInfo->mods_count; i++) {
//        int (*entry)() = (int (*)()) *((int *) module->mod_start + 24);
        int (*entry)() = (int (*)()) 0x10A000;
        printk("0x%x\n", entry);
        BochsBreak()
        __asm__("pause");
        entry();
        module++;
    }
}
