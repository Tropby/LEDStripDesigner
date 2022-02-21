#pragma once

typedef enum {
	SPI_MODE_0 = 0,	
	SPI_MODE_1 = 1,	
	SPI_MODE_2 = 2,	
	SPI_MODE_3 = 3
}SPI_MODE;

typedef enum {
	SPI_DATA_ORDER_LSB_FIRST = 1,
	SPI_DATA_ORDER_MSB_FIRST = 0
}SPI_DATA_ORDER;

typedef enum {
	SPI_FREQUENCY_1_4 = 0,
	SPI_FREQUENCY_1_16 = 1,
	SPI_FREQUENCY_1_64 = 2,
	SPI_FREQUENCY_1_128 = 3,
	SPI_FREQUENCY_1_2 = 4,
	SPI_FREQUENCY_1_8 = 5,
	SPI_FREQUENCY_1_32 = 6,
	SPI_FREQUENCY_1_64S = 7
}SPI_FREQUENCY;

extern void spi_init(SPI_MODE spimode, SPI_DATA_ORDER dataOrder, SPI_FREQUENCY frequency);
extern void spi_disable();
extern void spi_write(uint8_t data);
extern uint8_t spi_read(void);