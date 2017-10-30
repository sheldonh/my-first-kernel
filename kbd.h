#ifndef _KBD_H
#define _KBD_H

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern void kbd_irq(void);

#endif
