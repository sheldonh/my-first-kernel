#include "idt.h"
#include "video.h"

void kmain(void)
{
	idt_init();
	video_init();

	while (1);
}
