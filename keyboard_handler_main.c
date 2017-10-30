#include "keyboard_handler.h"
#include "ports.h"
#include "video.h"

// From http://www.osdever.net/bkerndev/Docs/keyboard.htm
unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned short keyboard_shift;

void keyboard_handler_main(void) {

	if (read_port(KEYBOARD_STATUS_PORT) & 0x01) {
		unsigned char keycode = read_port(KEYBOARD_DATA_PORT);
		write_port(0x20, 0x20); // End Of Interrupt
		if (keycode == 0x2A)
			keyboard_shift = 1;
		else if (keycode == 0xAA)
			keyboard_shift = 0;
		else if (keycode == 0x0E) {
			putc('\b');
			putc(' ');
			putc('\b');
		} else if (keycode == 0x1C)
			putc('\n');
		else if (keycode > 127)
			return;
		else
			putc(keyboard_map[keycode] - (32 * keyboard_shift));
	}
}
