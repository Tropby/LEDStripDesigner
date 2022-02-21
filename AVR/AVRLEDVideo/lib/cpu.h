#ifndef CPU_H_
#define CPU_H_

/* 

	ATMEGA 8		Arduino		PIN					E2000
	PIN				NANO		Name				Verwendung
	=============================================================================
	2				D0			PD0					RX
	3				D1			PD1					TX
	4				D2			PD2					RX/TX Umschalter
	5				D3			PD3					LED Bus RX
	6				D4			PD4					LED Status
	11				D5			PD5					Hardware Code (2)
	12				D6			PD6					Hardware Code (1)	 
	13				D7			PD7					S3
	14				D8			PB0					S4
	15				D9			PB1					Port 8 (PWM 2)	
	16				D10			PB2					Hardware Code (5)
	17				D11			PB3		MOSI		Port 7 (PWM 1)
	18				D12			PB4		MISO		Hardware Code (4)
	19				D13			PB5		SCK			Hardware Code (3)

	23				A0			PC0					Port 6
	24				A1			PC1					Port 5
	25				A2			PC2					Port 4
	26				A3			PC3					Port 3
	27				A4			PC4					Port 2
	28				A5			PC5					Port 1

*/

#include <avr/io.h>

#define SEI() asm("sei")
#define CLI() asm("cli")

/**********************************************************************************************************************************************/
/* DON'T CHANGE BEYOND THIS POINT																											  */
/**********************************************************************************************************************************************/

#define XSTR(x) STR(x)
#define STR(x) #x

#define SBI(port,bit) 	( port |= (1<<bit) )
#define CBI(port,bit) 	( port &= ~(1<<bit) )
#define TBI(port,bit) 	( port ^= (1<<bit) )
#define PBI(port,bit,val) if(val){SBI(port,bit);}else{CBI(port,bit);}
	
#define false 0
#define true 1
#define bool uint8_t

// Namen der Register ändern für alte ATMEGA8
#ifdef __AVR_ATmega8__
	#define UCSR0B UCSRB
	#define UDRIE0 UDRIE
	#define UDR0 UDR
	#define TCCR0B TCCR0
	#define TIMSK0 TIMSK
	#define UBRR0H UBRRH
	#define UBRR0L UBRRL
	#define UCSR0A UCSRA
	#define UCSR0B UCSRB
	#define UCSR0C UCSRC
	#define UCSZ01 UCSZ1
	#define UCSZ00 UCSZ0
	#define RXC0 RXC
	#define RXEN0 RXEN
	#define TXEN0 TXEN
	#define RXCIE0 RXCIE
	#define TXCIE0 TXCIE
	#define UDRE0 UDRE
	#define USART_TX_vect USART_TXC_vect
	#define USART_RX_vect USART_RXC_vect
#endif

#ifdef __AVR_ATmega644__
	#define USART_RX_vect USART0_RX_vect
	#define USART_TX_vect USART0_TX_vect
	#define USART_UDRE_vect USART0_UDRE_vect
	#define MCUCSR MCUSR
#endif

#endif /* CPU_H_ */
