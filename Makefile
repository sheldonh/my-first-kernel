CFLAGS=-m32 -g -fno-stack-protector -fno-builtin -Wall -Werror
OBJECTS=boot.o idt_load.o idt.o kbd_irq.o kbd.o kernel.o ports.o serial_irq.o serial.o video.o

kernel: kernel.debug
	strip -o $@ $<
kernel.sym: kernel.debug
	objcopy --only-keep-debug $< $@
kernel.debug: kernel.ld $(OBJECTS)
	ld -m elf_i386 -o $@ -T $^
%.o: %.asm
	nasm -f elf32 -o $@ $<
%.o: %.c *.h
	gcc $(CFLAGS) -o $@ -c $<
run: kernel
	qemu-system-i386 -kernel $< -m 1056K -serial pty
debug: kernel kernel.sym
	qemu-system-i386 -kernel $< -s -S -serial pty
clean:
	rm -f kernel kernel.debug kernel.sym *.o

.PHONY: clean run debug
