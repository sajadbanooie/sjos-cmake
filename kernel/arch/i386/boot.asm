MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot


; multiboot section holds multiboot specifications
segment .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

; kernels stack
segment .bss
align 4
kernel_stack_bottom:
resb 16384 ; 16 KiB
kernel_stack_top:

segment .text
global _start
_start:

    ; load esp with kernels stack address
    mov esp,kernel_stack_top

    extern _init
    call _init

    extern kernel_init
    call kernel_init

    cli
.hang:	hlt
    jmp .hang
