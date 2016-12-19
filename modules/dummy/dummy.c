//
// Created by sajad on 12/15/16.
// dummy module for testing
//

#include <modules.h>

MODULE_NAME("Dummy");

int main() {

}

int module_init() {
    for (;;);
    __asm__("pause");
    return 0;
}
