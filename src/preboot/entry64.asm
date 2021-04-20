global entry_x64
extern kernel_entry

section .text
bits 64
entry_x64:
    ; Nullify all data registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call kernel_entry ; Jump into C kernel entry
    
    hlt
