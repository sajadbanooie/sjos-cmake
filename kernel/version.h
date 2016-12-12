//
// Created by sajad on 12/12/16.
// version major minor and revision
// major.minor[.build[.revision]]
// and debugging settings
//

#ifndef SJOS_VERSION_H
#define SJOS_VERSION_H

#define V_MAJOR 0
#define V_MINOR 0
#define V_REVISION 0

// version build:
// 0 for alpha
// 1 for beta 2 for
// release candidate and
// 3 for finial release
#define V_BUILD 0

// 1 when debugging is enabled comment this line to disable
#define DEBUG 1

// bochs debugging macros
// outputs a character to the debug console
#define BochsConsolePrintChar(c) outportb(0xe9, c)
// stops simulation and breaks into the debug console
#define BochsBreak() outportw(0x8A00,0x8A00); outportw(0x8A00,0x08AE0);

#endif //SJOS_VERSION_H
