find_program(GCC_AR i686-elf-ar REQUIRED PATHS ~/opt/cross/bin)
find_program(GCC_LD i686-elf-ld REQUIRED PATHS ~/opt/cross/bin)
find_program(GCC_NM i686-elf-nm REQUIRED PATHS ~/opt/cross/bin)
find_program(GCC_OBJDUMP i686-elf-objdump REQUIRED PATHS ~/opt/cross/bin)
find_program(GCC_RANLIB i686-elf-ranlib REQUIRED PATHS ~/opt/cross/bin)
find_program(GCC i686-elf-gcc REQUIRED PATHS ~/opt/cross/bin)
find_program(GPP i686-elf-g++ REQUIRED PATHS ~/opt/cross/bin)

set(ARCH_ASM_FLAGS "-f elf32")
