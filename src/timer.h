#ifndef TIME_H_
#define TIME_H_

#include <types.h>

#ifndef __cplusplus
#error Trying to include C++ header in non-C++ code
#endif

namespace frxos {
  namespace timer {
    void install();

    namespace impl {
      static inline void wait() {
        asm volatile("hlt");
      }

      static inline void wait_forever() {
        asm volatile("hlt");
      }

      template <typename Fn>
      static inline auto wait_for(Fn &&func) -> decltype(func()) {
        auto __expr = func();
        while(!__expr) {
          asm volatile("hlt");
          __expr = func();
        }
        return __expr;
      }
    }
  }
}

#define WAIT() ::frxos::timer::impl::wait()
#define WAIT_FOREVER() ::frxos::timer::impl::wait_forever()
#define WAIT_FOR(expr) ::frxos::timer::impl::wait_for([&] () { return (expr); })

#endif // TIME_H_
