global entry_x86
external entry_x64

section .text
bits 32
entry_x86:
    mov esp, stack_top
    
    call check_mb2_boot
    call check_cpuid
    call check_x64_supported
    
    call setup_page_tables
    call enable_paging
    
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
    popfd; Push original flags back onto the flags register
    cmp eax, ecx ; Compare the modifided? flags to the original flags
    je .cpuid_unsupported ; Flags were not changed, cpuid not supported
    ret
    
.cpuid_unsupported:
    mov al, "C" ; err code C - cpuid unsupported
    jmp error
    
check_x64_supported:
    mov eax, 0x80000000 ; Magic code that i dont understand
	cpuid ; Magic code that i dont understand
	cmp eax, 0x80000001 ; Magic code that i dont undetstand
	jb .x64_unsupported ; Something went wrong so x64 isnt supported

	mov eax, 0x80000001 ; Set magic value 0x80000001 into EAX for cpuid
	cpuid ; Get "extended features list" from CPU info
	test edx, 1 << 29 ; Check if x64 is supported by checking bit 29
	jz .x64_unsupported ; If zero, x64 unsupported so jump to no x64
    
    ret
.x64_unsupported:
    mov al, "L" ; err code L, long mode/x64 unsupported
    jmp error

; Magic paging code that I don't understand
setup_page_tables:
	mov eax, page_table_l3
	or eax, 0b11 ; present, writable
	mov [page_table_l4], eax
	
	mov eax, page_table_l2
	or eax, 0b11 ; present, writable
	mov [page_table_l3], eax

	mov ecx, 0 ; counter
.loop:

	mov eax, 0x200000 ; 2MiB
	mul ecx
	or eax, 0b10000011 ; present, writable, huge page
	mov [page_table_l2 + ecx * 8], eax

	inc ecx ; increment counter
	cmp ecx, 512 ; checks if the whole table is mapped
	jne .loop ; if not, continue

	ret

enable_paging:
	; pass page table location to cpu
	mov eax, page_table_l4
	mov cr3, eax

	; enable PAE
	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	; enable long mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	; enable paging
	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

error:
	; print "ERR: X" where X is the error code
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt

section .bss
align 4096
page_table_l4:
	resb 4096
page_table_l3:
	resb 4096
page_table_l2:
	resb 4096
stack_bottom:
	resb 4096 * 4
stack_top:

section .rodata
gdt64:
	dq 0 ; zero entry
.code_segment: equ $ - gdt64
	dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) ; code segment
.pointer:
	dw $ - gdt64 - 1 ; length
	dq gdt64 ; address
