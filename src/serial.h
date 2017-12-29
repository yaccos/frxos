#ifndef SERIAL_H_
#define SERIAL_H_

#include <types.h>

#include "port_io.h"

#ifndef __cplusplus
#error Trying to include C++ header in non-C++ code
#endif

namespace frxos {
  namespace serial {
    static constexpr port_t COM1 = 0x03F8;
    static constexpr port_t COM2 = 0x02F8;
    static constexpr port_t COM3 = 0x02E8;
    static constexpr port_t COM4 = 0x02E8;

    void install(port_t port);
    
    static void install_all() {
      install(COM1);
      install(COM2);
      install(COM3);
      install(COM4);
    }

    void putch(port_t port, uint8_t ch);
    uint8_t getch(port_t port);

    ssize_t write(port_t port, const void *buf, size_t size);
    ssize_t read(port_t port, void *buf, size_t size);
    ssize_t print(port_t port, const char *str);
  }
}

#endif // SERIAL_H_
