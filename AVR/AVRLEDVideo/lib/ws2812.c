
#include "ws2812.h"

void ws2812_sendarray_16Mhz(uint8_t *data,uint16_t n)
{
	uint8_t curbyte,ctr;
	
	while (n--) 
	{
		curbyte=*data++;

        asm volatile(
            "    ldi  %0,8       \n\t" // 0
            "    nop\n\t"
            "loop%=:lsl  %1      \n\t" //  1     Datenbit ins Carry
            "    dec  %0         \n\t" //  2     Schleifenzähler in Z-Flag
            "    sbi  %2,  %3    \n\t" //  4
            "    nop\n\t"              //  5
            "    nop\n\t"              //  6
            "    brcs .+2        \n\t" //  7l / 8h
            "    cbi  %2,  %3    \n\t" //  9l / -    überspringen bei C=1
            "    nop\n\t"              // 10l /  9h
            "    nop\n\t"              // 11l / 10h
            "    nop\n\t"              // 12l / 11h
            "    nop\n\t"              // 13l / 12h

            "    brcc .+3        \n\t" // 15l / 13h
            "    cbi  %2,  %3    \n\t" // -  / 15h   überspringen bei C=0
            "    nop\n\t"              // 16
            "    nop\n\t"              // 17
            "    nop\n\t"              // 18
            "    nop\n\t"              // 19
            "    brne loop%=     \n\t" // 11 loop /10nt  Weiter, wenn Z=1
            : "=&d"(ctr)
            : "r"(curbyte), "I"(ws2812_port), "I"(ws2812_pin));

        // loop overhead including byte load is 6+1 cycles
	}
}