#include <avr/io.h>
#include <avr/interrupt.h>
#include "spi.h"
#include "cpu.h"

void spi_init(SPI_MODE spimode, SPI_DATA_ORDER dataOrder, SPI_FREQUENCY frequency)
{
	// Set MOSI and SCK to output
	SBI(DDRB, 3);
	SBI(DDRB, 5);
	
	// Activate pull up for MISO
	SBI(PORTB, 4);
	
	// Set SPI mode to Master
	SPCR = ( 1 << SPE ) | ( 1 << MSTR ) | ( spimode << 2 ) | ( (dataOrder&0x01) << 5) | (frequency&0x03);
	SPSR = (frequency&0x04) >> 2;	
}

void spi_disable()
{
	CBI(SPCR, SPE);
}

uint8_t spi_transmit(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void spi_write(uint8_t data)
{
	spi_transmit(data);
}

uint8_t spi_read(void)
{
	uint8_t d = spi_transmit(0xFF);
	return d;
}
