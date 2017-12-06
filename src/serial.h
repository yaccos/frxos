#ifndef SERIAL_H_
#define SERIAL_H_

#include <stddef.h>
#include <stdint.h>

#include "io.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

void install_serial(uint16_t port);

static inline uint8_t serial_received(uint16_t port) {
  return inb(port + 5) & 1;
}

static inline uint8_t serial_getch(uint16_t port) {
  while(serial_received(port) == 0);
  return inb(port);
}

static inline uint8_t serial_is_transmit_empty(uint16_t port) {
  return inb(port + 5) & 0x20;
}

static inline void serial_putch(uint16_t port, uint8_t ch) {
  while(serial_is_transmit_empty(port) == 0);
  outb(port, ch);
}

static inline void serial_write(uint16_t port, void *data, uint32_t size) {
  char *cdata = (char*)data;
  for(uint32_t i = 0; i < size; i++)
    serial_putch(port, (uint8_t)cdata[i]);
}

static inline void serial_print(uint16_t port, const char *str) {
  for(const char *p = str; *p; p++)
    serial_putch(port, (uint8_t)*p);
}

#ifdef __cplusplus
}
#endif

#endif // SERIAL_H_
