#ifndef _SERIAL_H
#define _SERIAL_H

extern void serial_init();
extern void serial_irq(void);

extern int serial_received();
extern char read_serial();

#endif
