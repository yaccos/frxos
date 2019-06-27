#include <stddef.h>
#include <stdint.h>

#include "attr.h"
#include "debug.h"

#include "display.h"
#include "timer.h"
#include "keyboard.h"

#define SHELL_BUFFER_LENGTH 256
#define ENTER_KEY 0x1C

extern uint8_t reading_key;
static const char *readline(char *buffer, size_t length);
void shell() {
  reading_key = 1;
  uint16_t color = 0x1F00;
  vga_fill(color);
  vga_printf(0,0,color,"This is frxos 0.2\n");
  vga_printf(2,0,color,"Created by Fredrik Ostrem and Jakob Peder Pettersen 2017-2019\n");
  vga_printf(4,0,color,"Press PAUSE or SPACE to enter debug mode, press ENTER to quit the OS\n");
  vga_printf(6,0,color,"For the moment, the OS cannot do much more than this :-)\n");
  while(1){
  	uint8_t key = keystroke_pop();
	dprintf("Key: %2X \n",key);
	// Wait until we obtain a valid keystroke
  	do{
  		key = keystroke_pop();
 	} while(!key);
	dprintf("Key: 0x%2X \n",key);
 	if(key == ENTER_KEY){
		break;
	}
  }
  reading_key = 0;
  vga_printf(8,0,color,"Exiting frxos ..."); 
  // char buffer[SHELL_BUFFER_LENGTH];
  // const char *line = readline(buffer, SHELL_BUFFER_LENGTH);

  // dprintf("line: %s\n", line);
}

static const char *readline(char *buffer, size_t length) {
  buffer[0] = 0;

  return buffer;
}
