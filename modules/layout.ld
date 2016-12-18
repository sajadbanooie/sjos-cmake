/* kernel will execute this function */
ENTRY(module_init)

SECTIONS{
    /* module info section */
    .modinfo :
    {
        *(.modinfo)
    }
    .mod :
    {
        *(.mod)
    }

    .rodata :
    {
        *(.rodata)
    }

    .data :
    {
        *(.data)
    }

    .text :
    {
        *(.text)
    }

    .bss :
    {
        *(COMMON)
        *(.bss)
    }
}