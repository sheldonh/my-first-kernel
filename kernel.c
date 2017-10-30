#include "idt.h"
#include "video.h"

void kernel(void)
{
	idt_init();
	video_init();

	while (1);
}
