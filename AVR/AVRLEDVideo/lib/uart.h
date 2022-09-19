#ifndef UART_H_
#define UART_H_

#include "cpu.h"

#include <util/setbaud.h>

#ifndef UART_TX_BUFFER_SIZE
	#define UART_TX_BUFFER_SIZE 64
	//#pragma message "Using default UART TX Buffer size of " XSTR(WS2812_T0H_DELAY) " Byte."
#endif

extern void uart_init(void);
extern void uart_sendByte( unsigned char c );
extern void uart_sendStringArray( char * c, uint8_t d );
extern void uart_sendString( char * c );
extern void uart_sendPString(const char *str);
extern void uart_sendUInt8( uint8_t d );
extern void uart_sendUInt32( uint32_t d );
extern void uart_sendHEXUInt8( uint8_t d );
extern uint8_t uart_canReadByte();
extern uint8_t uart_getByte();

extern void (*UART_RX_HANDLER)(uint8_t);

#endif /* UART_H_ */