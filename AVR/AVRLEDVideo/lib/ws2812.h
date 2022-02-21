#include "cpu.h"

#define ws2812_port 0x0B  // Number of the data port register
#define ws2812_pin 2      // Number of the data out pin

// n = number of bytes 
extern void ws2812_sendarray_16Mhz(uint8_t *data,uint16_t n);