/* kernel will execute this function */
ENTRY(module_init)

OUTPUT_ARCH(i386)

SECTIONS{

    .text :
    {
        *(.text)
    }

    /* module info section */

    .modinfo :
    {
        *(.modinfo)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
    }
}