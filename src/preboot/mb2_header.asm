section .mb2_header
header_start:
    ; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html for more information, section 3.1.1
    dd 0xe85250d6 ; multiboot2 magic number
    
    dd 0 ; i386 protected 32 bit mode
    
    dd header_end - header_start ; Header length
    
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum, total is 0
    
    ; Ending tag
	  dw 0
	  dw 0
	  dd 8
header_end:
