#include "cpu.h"

extern bool fat16_init(void);
extern bool fat16_readFatInfo();
extern uint16_t fat16_readFile( uint8_t * buffer, uint16_t size );
