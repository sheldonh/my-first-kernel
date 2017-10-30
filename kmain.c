#include "idt.h"
#include "kb_init.h"
#include "video.h"

void kmain(void)
{
	idt_init();
	kb_init();
	video_init();

	while (1);
}
