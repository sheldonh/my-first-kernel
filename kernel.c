#include "idt.h"
#include "serial.h"
#include "video.h"

void kernel(void)
{
	idt_init();
	video_init();
	serial_init();

	puts("Entering HLT loop.\n");
	for (;;)
		asm("hlt");
}
