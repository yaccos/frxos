#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void install_keyboard();
uint8_t keystroke_pop();
#ifdef __cplusplus
}
#endif

#endif // KEYBOARD_H_
