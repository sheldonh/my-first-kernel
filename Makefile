CFLAGS=-m32 -g -fno-stack-protector -fno-builtin -Wall -Werror

kernel: kernel.ld kernel.o kmain.o ports.o video.o keyboard_handler.o keyboard_handler_main.o load_idt.o idt_init.o kb_init.o
	ld -m elf_i386 -o $@ -T $^
kernel.sym: kernel
	objcopy --only-keep-debug kernel kernel.sym
%.o: %.asm
	nasm -f elf32 -o $@ $<
%.o: %.c *.h
	gcc $(CFLAGS) -o $@ -c $<
run: kernel
	qemu-system-i386 -kernel $<
debug: kernel kernel.sym
	qemu-system-i386 -kernel $< -s -S
clean:
	rm -f kernel kernel.sym *.o

.PHONY: clean run debug