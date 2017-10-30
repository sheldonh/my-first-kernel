#include "keyboard_handler.h"
#include "ports.h"

void kb_init(void) {
	/* 0xFD is 11111101 - enables only IRQ1 (keyboard) */
	keyboard_shift = 0;
	wport(0x21, 0xFD);
}
