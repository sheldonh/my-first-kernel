bits 32

section .text

global kbd_irq
extern kbd_input

kbd_irq:
	call kbd_input
	iretd
