#ifndef PORTS_H
#define PORTS_H
extern void write_port(unsigned short port, unsigned char data);
extern unsigned char read_port(unsigned short port);
#endif
