kernel_source_files := $(shell find src/kernel -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/preboot -name *.asm)
x86_64_asm_object_files := $(patsubst src/preboot/%.asm, build/preboot/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	./gcc/bin/x86_64-elf-gcc -c -I src/interface -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_64_c_object_files): build/x86_64/%.o : src/x86_64/%.c
	mkdir -p $(dir $@) && \
	./gcc/bin/x86_64-elf-gcc -c -I src/interface -ffreestanding $(patsubst build/x86_64/%.o, src/x86_64/%.c, $@) -o $@

$(x86_64_asm_object_files): build/preboot/%.o : src/preboot/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/preboot/%.o, src/preboot/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	./gcc/bin/x86_64-elf-ld -n -o dist/x86_64/shadeos.bin -T targets/x86_64-i386/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/shadeos.bin targets/x86_64-i386/iso/boot/shadeos.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/shadeos.iso targets/x86_64-i386/iso

.PHONY: test
test: $(build-x86-64)
	qemu-system-x86_64 -drive file=dist/x86_64/shadeos.iso,index=0,media=disk,format=raw
