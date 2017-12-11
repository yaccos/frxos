#ifndef TIMER_H_
#define TIMER_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TICKS_PER_SEC 1193182      // base frequency, in Hz

void install_timer();
void set_timer_divider(uint16_t divider);
uint64_t clock();

// sleep CPU for a while
void sleep(uint64_t sec);   // sleep for a whole number of seconds
void usleep(uint64_t usec); // sleep for a whole number of microseconds

// short CPU sleep
#define wait() ({ asm volatile("hlt"); 0; })

// CPU sleep forever
#define wait_forever() ({ for(;;) { asm volatile("hlt")); }; 1; })

// CPU sleep until condition is true
#define wait_for(expr) ({ typeof(expr) __expr; while(!(__expr = expr)) { asm volatile("hlt"); }; __expr; })

#ifdef __cplusplus
}
#endif

#endif // TIMER_H_
