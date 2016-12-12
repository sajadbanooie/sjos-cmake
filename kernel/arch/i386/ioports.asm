global outportb
global outportw
global outportl

global inportb
global inportw
global inportl

; io port write functions:

outportb:
    mov edx,[esp + 4]
    mov al,[esp + 8]
    out dx,al
    ret

outportw:
    mov edx,[esp + 4]
    mov ax,[esp + 8]
    out dx,ax
    ret

outportl:
    mov edx,[esp + 4]
    mov eax,[esp + 8]
    out dx,eax
    ret

; io port read functions:

inportb:
    mov edx,[esp + 4]
    in al,dx
    ret

inportw:
    mov edx,[esp + 4]
    in ax,dx
    ret

inportl:
    mov edx,[esp + 4]
    in eax,dx
    ret