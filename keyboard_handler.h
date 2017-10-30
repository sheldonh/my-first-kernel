#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H 1

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern unsigned short keyboard_shift;
extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);

#endif
