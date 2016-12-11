segment .init
global _init
_init:
    push ebp
    mov ebp,esp

segment .fini
global _fini
_fini:
    push ebp
    mov ebp,esp