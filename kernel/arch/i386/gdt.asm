global set_gdtr
global gdt_flush

extern gdt_r

set_gdtr:
    lgdt [gdt_r]
    ret

gdt_flush:
    jmp 0x08:.reload
.reload:
    mov ax,0x10
    mov ds,ax
    mov ss,ax
    mov gs,ax
    mov es,ax
    mov fs,ax