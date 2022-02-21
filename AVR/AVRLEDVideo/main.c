/*
 * AVRLEDVideo.c
 *
 * Created: 24.01.2022 21:32:42
 * Author : Tropby
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "lib/ws2812.h"
#include "lib/spi.h"
#include "lib/sd.h"
#include "lib/fat16.h"
#include "lib/uart.h"


#ifdef DEBUG
uint8_t ledData[10];
#else
uint8_t ledData[1024];
#endif

volatile uint16_t timerValue;

ISR(TIMER0_COMPA_vect)
{
	timerValue++;	
}

void initTimer0()
{
	// Timer 0 konfigurieren
	TCCR0B = (1<<CS01) | (1<<CS00); // Prescaler 64

	OCR0A = 250;

	// Overflow Interrupt erlauben
	TIMSK0 |= (1<<OCIE0A);
}

int main(void)
{
	_delay_ms(500);
	uart_init();
	while( !fat16_init() )
	{
		uart_sendString("Error fat16 init!\n\r");
		_delay_ms(100);
	}

	SBI( DDRD, 2 );
	SBI( DDRD, 6 );
	SBI( PORTD, 6 );
	SBI( DDRD, 5 );
	SBI( PORTD, 5 );

	uint8_t receiveMode = 0;
	
	initTimer0();
	
	uart_sendString("STARTUP!\r\n");
	
    /* Replace with your application code */
	sei();			
    while (1) 
    {	
		if(uart_canReadByte() || receiveMode == 1)
		{
			if( receiveMode == 0 )
			{
				receiveMode = 1;				
				uart_sendString("UART Mode\n\r");				
			}
			while( uart_getByte() != 0x02 );
			
			for( uint16_t i = 0; i < 1024; i++ )
			{
				ledData[i] = uart_getByte();
			}
			uart_sendPString(PSTR("Frame received\n\r"));
			
			SBI( PORTD, 5 );
			ws2812_sendarray_16Mhz(ledData, 300*3);
			CBI( PORTD, 5 );
		}
		else
		{
			SBI( PORTD, 6 );
			fat16_readFile(ledData, 512);
			fat16_readFile(ledData+512, 512);
			CBI( PORTD, 6 );
			
			while(timerValue < 23);
			timerValue = 0;
			
			cli();
			SBI( PORTD, 5 );
			ws2812_sendarray_16Mhz(ledData, 300*3);
			CBI( PORTD, 5 );
			_delay_us(500);
			sei();			
		}	
    }
}
