#include "kbd.h"
#include "ports.h"
#include "serial.h"

#define IDT_SIZE 256

extern void idt_load(unsigned long *idt_ptr);

struct IDT_entry{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void)
{
	unsigned long irq_handler_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	/* populate IDT entry of keyboard's interrupt */
	irq_handler_address = (unsigned long)kbd_irq;
	IDT[0x21].offset_lowerbits = irq_handler_address & 0xffff;
	IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[0x21].offset_higherbits = (irq_handler_address & 0xffff0000) >> 16;

	irq_handler_address = (unsigned long)serial_irq;
	IDT[0x24].offset_lowerbits = irq_handler_address & 0xffff;
	IDT[0x24].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x24].zero = 0;
	IDT[0x24].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[0x24].offset_higherbits = (irq_handler_address & 0xffff0000) >> 16;

	/*     Ports
	*	 PIC1	PIC2
	*Command 0x20	0xA0
	*Data	 0x21	0xA1
	*/

	/* ICW1 - begin initialization */
	wport(0x20 , 0x11);
	wport(0xA0 , 0x11);

	/* ICW2 - remap offset address of IDT */
	/*
	* In x86 protected mode, we have to remap the PICs beyond 0x20 because
	* Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
	*/
	wport(0x21 , 0x20);
	wport(0xA1 , 0x28);

	/* ICW3 - setup cascading */
	wport(0x21 , 0x00);
	wport(0xA1 , 0x00);

	/* ICW4 - environment info */
	wport(0x21 , 0x01);
	wport(0xA1 , 0x01);
	/* Initialization finished */

	/* mask interrupts */
	wport(0x21 , 0xED); // Unmask IRQ1 and IRQ4
	wport(0xA1 , 0xFF);

	/* fill the IDT descriptor */
	idt_address = (unsigned long)IDT ;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xFFFF) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	idt_load(idt_ptr);
}
