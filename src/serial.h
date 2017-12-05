#ifndef SERIAL_H_
#define SERIAL_H_

#include <stddef.h>
#include <stdint.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void serial_init(int port);

char serial_getch(int port);

void serial_putch(int port, char ch);
void serial_write(int port, void *data, uint32_t size);
void serial_print(int port, const char *str);

#endif // SERIAL_H_
