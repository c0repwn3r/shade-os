global entry_x86
external entry_x64

section .text
bits 32
entry_x86:
    mov esp, stack_top
    
    call check_mb2_boot
    call check_cpuid
    call check_x64_supported
    
    call paging_setup
    call paging_enable
    
    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:entry_x64
    
    hlt

check_mb2_boot:
    cmp eax, 0x36d76289 ; compare eax to mb2 magic number
    jne mb2_not_booted
    ret
.mb2_not_booted:
    mov al, "B" ; err code B - boot error
    jmp error

check_cpuid:
    pushfd ; Put flags on stack so we can mess with them
    pop eax ; then put the stack into EAX so we can easily modify it
    mov ecx, eax ; Make a copy of eax in ecx for comparison
    xor eax, 1 << 21 ; Attempt to flip the CPUID bit which is bit 21
    push eax ; Put eax back onto stack
    popfd ; Write flags back
    pushfd ; Copy flags onto stack so we can check if the bit did flip
    pop eax ; Put stack into EAX for comparison
    push ecx ; Put original flags into stack so we can make sure they remain unchanged
    popfs
    
