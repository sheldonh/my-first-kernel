#include "ports.h"

/* current cursor location */
unsigned int current_loc = 0;
/* video memory begins at address 0xb8000 */
char *vidptr = (char *)0xb8000;

void update_cursor(unsigned int loc) {
	wport(0x3D4, 0x0F);
	wport(0x3D5, loc & 0xFF);
	wport(0x3D4, 0x0E);
	wport(0x3D5, (loc >> 8) & 0xFF);
}

void clear_screen(void) {
	for (int i = 0; i < 80 * 25 * 2; i += 2) {
		vidptr[i] = ' ';
		vidptr[i + 1] = 0x07;
	}
}

void video_init(void) {
	clear_screen();
	update_cursor(0);
}

void putc(unsigned char c) {
	if (c == '\n')
		while (++current_loc % (80 * 2));
	else if (c == '\b')
		current_loc -= 2;
	else {
		vidptr[current_loc++] = c;
		vidptr[current_loc++] = 0x07;
	}
	update_cursor(current_loc / 2);
}

void puts(char *s) {
	for (int i = 0; s[i] != '\0'; i++)
		putc(s[i]);
}
