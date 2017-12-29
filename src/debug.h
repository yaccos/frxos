#ifndef DEBUG_H_
#define DEBUG_H_

#include <types.h>

#include <pp/utility.h>

#include "serial.h"

#ifndef __cplusplus
#error Trying to include C++ header in non-C++ code
#endif

namespace frxos {
  namespace debug {
    static constexpr port_t PORT = serial::COM1;

    static ssize_t print(char ch) {
      serial::putch(PORT, ch);
    }

    static ssize_t print(const char *str) {
      serial::print(PORT, str);
    }

    template <typename T>
    static ssize_t print_all(T &&obj) {
      return print(pp::forward<T>(obj));
    }

    template <typename T, typename... Ts>
    static ssize_t print_all(T &&obj, Ts&&... objs) {
      size_t count = 0;
      count += print(pp::forward<T>(obj));
      count += print_all(pp::forward<Ts>(obj)...);

      return count;
    }
  }
}

#endif // DEBUG_H_
