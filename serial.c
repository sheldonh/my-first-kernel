#include "ports.h"
#include "video.h"

#define PORT_COM1 0x3F8

/*
 * https://www.lammertbies.nl/comm/info/serial-uart.html
 */
void serial_init() {
	wport(PORT_COM1 + 1, 0x01);    // Enable data available interrupt
	wport(PORT_COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	wport(PORT_COM1 + 0, 0x01);    // Set divisor to 3 (lo byte) 115200 baud
	wport(PORT_COM1 + 1, 0x00);    //                  (hi byte)
	wport(PORT_COM1 + 3, 0x03);    // Disable DLAB, 8 bits, no parity, one stop bit
	wport(PORT_COM1 + 2, 0x07);    // Enable FIFO, clear them, with 1-byte threshold
	wport(PORT_COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set
	puts("COM1 initialized.\n");
}

int serial_received() {
	return rport(PORT_COM1 + 5) & 1;
}

char read_serial() {
	while (serial_received() == 0);

	return rport(PORT_COM1);
}

void serial_input(void) {
	puts("COM1 interrupt: ");
	putc(rport(PORT_COM1));
	putc('\n');
	wport(0x20, 0x20); // End Of Interrupt
}

