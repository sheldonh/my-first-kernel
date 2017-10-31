bits 32

section .text

global serial_irq
extern serial_input

serial_irq:
	call serial_input
	iretd
