#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include <stdlib.h>

volatile uint8_t uartTxBuffer[UART_TX_BUFFER_SIZE];
volatile uint8_t uartTxBufferWritePos = 0;
volatile uint8_t uartTxBufferReadPos = 0;
void (*UART_RX_HANDLER)(uint8_t) = 0;

void uart_init(void)
{	
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
	#if USE_2X
		/* U2X-Modus erforderlich */		
		UCSR0A |= (1 << U2X0);
	#endif
	 
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);	
 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);  // UART RX, TX und RX Interrupt einschalten
	 #ifdef UART_INTERRUPT
		UCSR0B |= (1<<RXCIE0);
	 #endif
}

/*
 * Send byte (waiting for buffer ready)
 */
void uart_sendByte( unsigned char c )
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = c;
    return;

#ifdef UART_INTERRUPT
    // Wait for buffer pos free
    while ((uartTxBufferWritePos + 1) % UART_TX_BUFFER_SIZE == uartTxBufferReadPos)
        ;

    // Write to output buffer
    uartTxBuffer[uartTxBufferWritePos] = c;
    uartTxBufferWritePos++;
    uartTxBufferWritePos %= UART_TX_BUFFER_SIZE;

    // Activate interrupt
    UCSR0B |= (1 << UDRIE0);
#else
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = c;
#endif			
}

void uart_sendHEXUInt8( uint8_t d )
{
	char c[3];
	if( d >= 16 )
	{
		itoa(d, c, 16);
	}
	else
	{
		c[0] = '0';
		itoa(d, c+1, 16);
	}
	uart_sendString( c );
}

void uart_sendUInt8( uint8_t d )
{
	char c[10];
	itoa(d, c, 10);
	uart_sendString( c );
}

void uart_sendUInt32( uint32_t d )
{
	char c[10];
	ltoa(d, c, 10);
	uart_sendString( c );
}

void uart_sendStringArray( char * c, uint8_t d )
{
	while( *c )
	{
		uart_sendByte((uint8_t)*c);
		c++;
		d--;
		if( !d ) break;
	}
}

uint8_t uart_getByte()
{
	while (!(UCSR0A & (1<<RXC0)))   // warten bis Zeichen verfuegbar
	;
	return UDR0;                   // Zeichen aus UDR an Aufrufer zurueckgeben
}

uint8_t uart_canReadByte()
{
	return (UCSR0A & (1<<RXC0));
}

#include <avr/pgmspace.h>
void uart_sendPString(const char *str){
	while(pgm_read_byte(str) != '\0'){
		uart_sendByte(pgm_read_byte(str++));
	}
}

void uart_sendString( char * c )
{
	while(*c)
	{
		uart_sendByte((uint8_t)*c);
		c++;
	}
}

#ifdef UART_INTERRUPT

// receive a byte
ISR(USART_RX_vect)
{
    if( UART_RX_HANDLER != 0 )
        UART_RX_HANDLER(UDR0);
}

// Send next byte
ISR(USART_UDRE_vect)
{
	UDR0 = uartTxBuffer[uartTxBufferReadPos++];
    uartTxBufferReadPos %= UART_TX_BUFFER_SIZE;

    if( uartTxBufferWritePos == uartTxBufferReadPos )
	{
		UCSR0B &= ~(1<<UDRIE0);
	}
}

// Send finished
ISR(USART_TX_vect)
{
}

#endif