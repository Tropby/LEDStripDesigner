/*
 * sd.c
 *
 * Created: 24.01.2022 22:20:03
 *  Author: Tropby
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "spi.h"
#include "cpu.h"
#include "sd.h"

#define SD_CMD_GO_IDLE								0 
#define SD_CMD_SEND_OP_COND							1 
#define SD_CMD_ALL_SEND_CID							2 
#define SD_CMD_SEND_RELATIVE_ADDR					3 
#define SD_CMD_SET_DSR								4 
#define SD_CMD_SWITCH_FUNC							6 
#define SD_CMD_SELECT_DESELECT_CARD					7 
#define SD_CMD_IF_COND								8 
#define SD_CMD_SEND_CSD								9 
#define SD_CMD_SEND_CID								10 
#define SD_CMD_STOP_TRANSMISSION					12 
#define SD_CMD_SEND_STATUS							13 
#define SD_CMD_GO_INACTIVE							15 
#define SD_CMD_SET_BLOCKLEN							16 
#define SD_CMD_READ_SINGLE_BLOCK					17 
#define SD_CMD_READ_MULTIPLE_BLOCK					18 
#define SD_CMD_WRITE_SINGLE_BLOCK					24 
#define SD_CMD_WRITE_MULTIPLE_BLOCK					25 
#define SD_CMD_PROGRAMM_CSD							27 
#define SD_CMD_SET_WRITE_PROT						28 
#define SD_CMD_SET_CLR_PROT							29 
#define SD_CMD_SET_SEND_PROT						30 
#define SD_CMD_ERASE_WR_BLK_START					32 
#define SD_CMD_ERASE_WR_BLK_END						33 
#define SD_CMD_ERASE								38 
#define SD_CMD_APP_SEND_OP_COND						41 
#define SD_CMD_LOCK_UNLOCK							42 
#define SD_CMD_APP_CMD								55 
#define SD_CMD_READ_OCR								58 
		
#define SD_CMD_ACMD13								SD_CMD_SEND_STATUS
#define SD_CMD_ACMD41								SD_CMD_APP_SEND_OP_COND

enum SD_CARD_TYPE{
	SD_CARD_TYPE_V1,
	SD_CARD_TYPE_V2
} sdCardType;

#define SD_CMD_VER(X)          ((X >> 4) & 0xF0)
#define SD_VOL_ACC(X)          (X & 0x1F)

#define SD_VOLTAGE_ACC_27_33   0b00000001
#define SD_VOLTAGE_ACC_LOW     0b00000010
#define SD_VOLTAGE_ACC_RES1    0b00000100
#define SD_VOLTAGE_ACC_RES2    0b00001000

#define SD_POWER_UP_STATUS(X)  X & 0x40
#define SD_CCS_VAL(X)          X & 0x40
#define SD_VDD_2728(X)         X & 0b10000000
#define SD_VDD_2829(X)         X & 0b00000001
#define SD_VDD_2930(X)         X & 0b00000010
#define SD_VDD_3031(X)         X & 0b00000100
#define SD_VDD_3132(X)         X & 0b00001000
#define SD_VDD_3233(X)         X & 0b00010000
#define SD_VDD_3334(X)         X & 0b00100000
#define SD_VDD_3435(X)         X & 0b01000000
#define SD_VDD_3536(X)         X & 0b10000000

#ifdef DEBUG

#include "uart.h"

#define sd_debug(a) uart_sendPString(PSTR(a)

void sd_showOCR( uint8_t * res )
{
	uart_sendPString(PSTR("\tCard Power Up Status: "));
	if(SD_POWER_UP_STATUS(res[0]))
	{
		uart_sendPString(PSTR("READY\r\n"));
		uart_sendPString(PSTR("\tCCS Status: "));
		if(SD_CCS_VAL(res[0])){ uart_sendPString(PSTR("1\r\n")); }
		else uart_sendPString(PSTR("0\r\n"));
	}
	else
	{
		uart_sendPString(PSTR("BUSY\r\n"));
	}

	uart_sendPString(PSTR("\tVDD Window: ");
	if(SD_VDD_2728(res[2])) uart_sendPString(PSTR("2.7-2.8, "));
	if(SD_VDD_2829(res[1])) uart_sendPString(PSTR("2.8-2.9, "));
	if(SD_VDD_2930(res[1])) uart_sendPString(PSTR("2.9-3.0, "));
	if(SD_VDD_3031(res[1])) uart_sendPString(PSTR("3.0-3.1, "));
	if(SD_VDD_3132(res[1])) uart_sendPString(PSTR("3.1-3.2, "));
	if(SD_VDD_3233(res[1])) uart_sendPString(PSTR("3.2-3.3, "));
	if(SD_VDD_3334(res[1])) uart_sendPString(PSTR("3.3-3.4, "));
	if(SD_VDD_3435(res[1])) uart_sendPString(PSTR("3.4-3.5, "));
	if(SD_VDD_3536(res[1])) uart_sendPString(PSTR("3.5-3.6"));
	uart_sendPString(PSTR("\r\n"));
}

void sd_showR1( uint8_t result )
{
	if(result & 0b10000000)
		{ uart_sendPString(PSTR("\tError: MSB = 1\r\n")); return; }
			
	if(result == 0)
		{ uart_sendPString(PSTR("\tCard Ready\r\n")); return; }
			
	if(result & SD_PARAMETER_ERROR)
		uart_sendPString(PSTR("\tParameter Error\r\n"));
		
	if(result & SD_ADDRESS_ERROR)
		uart_sendPString(PSTR("\tAddress Error\r\n"));
		
	if(result & SD_ERASE_SEQENCE_ERROR)
		uart_sendPString(PSTR("\tErase Sequence Error\r\n"));
		
	if(result & SD_COM_CRC_ERROR)
		uart_sendPString(PSTR("\tCRC Error\r\n"));
		
	if(result & SD_ILLEGAL_COMMAND)
		uart_sendPString(PSTR("\tIllegal Command\r\n"));
		
	if(result & SD_ERASE_RESET)
		uart_sendPString(PSTR("\tErase Reset Error\r\n"));
		
	if(result & SD_IN_IDLE_STATE)
		uart_sendPString(PSTR("\tIn Idle State\r\n"));	
}

void sd_showR7(uint8_t *res)
{	
	uart_sendPString(PSTR("\tCommand Version: "));
	uart_sendUInt8(SD_CMD_VER(res[0]));
	uart_sendPString(PSTR("\r\n"));

	uart_sendPString(PSTR("\tVoltage Accepted: "));
	if(SD_VOL_ACC(res[2]) == SD_VOLTAGE_ACC_27_33)
		uart_sendPString(PSTR("2.7-3.6V\r\n"));
	else if(SD_VOL_ACC(res[2]) == SD_VOLTAGE_ACC_LOW)
		uart_sendPString(PSTR("LOW VOLTAGE\r\n"));
	else if(SD_VOL_ACC(res[2]) == SD_VOLTAGE_ACC_RES1)
		uart_sendPString(PSTR("RESERVED 1\r\n"));
	else if(SD_VOL_ACC(res[2]) == SD_VOLTAGE_ACC_RES2)
		uart_sendPString(PSTR("RESERVED 2\r\n"));
	else
		uart_sendPString(PSTR("NOT DEFINED\r\n"));

	uart_sendPString(PSTR("\tEcho: "));
	uart_sendUInt8(res[3]);
	uart_sendPString(PSTR("\r\n"));
}

#else

#define sd_debug(a)
#define sd_showR1(a)
#define sd_showR7(a)
#define sd_showOCR(a)

#endif

void sd_clearBus()
{
	// Clear buffer state
	for(uint8_t i = 0; i < 0x0A; i++)
	{
		spi_write(0xFF);		
	}
}

void sd_select()
{
	// Create BUS
	spi_write(0xFF);
	CBI(PORTB, 2);	
}

void sd_deselect()
{
	SBI(PORTB, 2);
	sd_clearBus();
}

SD_ERRORCODE sd_sendCommand(const uint8_t command, const uint32_t arg, const uint8_t checksum)
{
    SD_ERRORCODE response = 0x00;
    uint8_t commandTemp = command;

    sd_select();	
	spi_write( 0xFF );
	spi_write( 0xFF );
	spi_write( 0xFF );
	spi_write( 0xFF );
	
	spi_write( commandTemp | 0x40 );
    spi_write( (arg >> 0x18) & 0xFF );
    spi_write( (arg >> 0x10) & 0xFF );
    spi_write( (arg >> 0x08) & 0xFF );
    spi_write( arg );
   
    spi_write(checksum | 0x01);
	
    if(commandTemp == SD_CMD_STOP_TRANSMISSION)
    {
	    // Skip stuff byte when transmission stop
	    spi_write(0xFF);
    }
	
    // Wait for the response (0 - 8 bytes for SD cards and 1 - 8 bytes for MMC)
    for(uint8_t i = 0x00; i < 0x30; i++)
    {
	    uint8_t dataIn = spi_read();

	    if(dataIn != 0xFF)
	    {	    
			sd_showR1(dataIn);
		    return dataIn;
	    }
    }
    return SD_NO_RESPONSE;
}

SD_RESULT sd_checkOperatingCondition(uint8_t * r1, uint8_t * result)
{
	*r1 = sd_sendCommand(SD_CMD_READ_OCR, 0x00000000, 0x00);
	result[0] = spi_read();
	result[1] = spi_read();
	result[2] = spi_read();
	result[3] = spi_read();
	return SD_SUCCESSFULL;
}

SD_RESULT sd_softwareRest(uint8_t * r1)
{	
	uint8_t repeat = 0x00;
	
	sd_clearBus();
	
	while( 1 )
	{
		*r1 = sd_sendCommand(SD_CMD_GO_IDLE, 0x00000000, 0x94);
		if( *r1 == SD_IN_IDLE_STATE )
		{
			sd_deselect();
			return SD_SUCCESSFULL;
		}
		
		if(repeat++ == 0x0A)
		{
			sd_deselect();
			return SD_NO_RESPONSE;
		}
	}
}

SD_RESULT sd_checkCapacitySupport(SD_ERRORCODE * r1, uint8_t * result)
{	
	
	*r1 = sd_sendCommand(SD_CMD_APP_CMD, 0x00000000, 0x65);	
	if( *r1 > 0x01 )
	{
		return *r1;
	}
	*r1 = sd_sendCommand(SD_CMD_ACMD41, 0x40000000, 0x00);
	
	sd_deselect();
	return SD_SUCCESSFULL;
}

SD_RESULT sd_checkInterfaceCondition(SD_ERRORCODE * r1, uint8_t * result)
{
	sd_clearBus();
	
	*r1 = sd_sendCommand(SD_CMD_IF_COND, 0x0000001AA, 0x86);
	if( *r1  == SD_IN_IDLE_STATE )
	{
		// SD-Card V2 - Read Argument
		sdCardType = SD_CARD_TYPE_V2;		
		result[0] = spi_read();
		result[1] = spi_read();
		result[2] = spi_read();
		result[3] = spi_read();
	}
	else if( *r1  == SD_ILLEGAL_COMMAND )
	{
		// SD-Card V1
		sdCardType = SD_CARD_TYPE_V1;
	}
	else
	{
		// Undefined error occured return errorCode
		sd_deselect();
		return SD_UNKNWON_CARD_TYPE;		
	}

	sd_deselect();
	return SD_SUCCESSFULL;
}

SD_RESULT sd_setCardReady(SD_ERRORCODE * r1, uint8_t * r7)
{
	uint8_t attempts = 5;
	while(attempts--)
	{
		// Init Card
		sd_debug("sd_checkCapacitySupport\r\n");
		SD_RESULT res = sd_checkCapacitySupport(r1, r7);
		sd_showR1(*r1);
		if( *r1 == 0 )
			return SD_SUCCESSFULL;
			
		if( res != SD_SUCCESSFULL )
			return SD_UNKNWON_ERROR;
	
		_delay_ms(10);
	}	
	
	return SD_UNKNWON_ERROR;
}

SD_RESULT sd_init(void)
{
	// Chip select as output and disable chip
	SBI(DDRB, 2);
	SBI(PORTB, 2);
		
	// Init SPI slow connection
	spi_init(SPI_MODE_0, SPI_DATA_ORDER_MSB_FIRST, SPI_FREQUENCY_1_128);
	
	SD_RESULT res;
	SD_ERRORCODE r1;
	
	// SD-Card Reset
	sd_debug("\r\n\r\nsd_softwareRest\r\n");
	res = sd_softwareRest(&r1);	
	sd_showR1(r1);	
	if( res != SD_SUCCESSFULL )
		return SD_UNKNWON_ERROR;
	
	// Check Interface Condition
	uint8_t r7[4];
	sd_debug("sd_checkInterfaceCondition\r\n");
	res = sd_checkInterfaceCondition(&r1, r7);
	sd_showR1(r1);
	switch(sdCardType)
	{
		case SD_CARD_TYPE_V2:
			uart_sendPString(PSTR("SD_CARD_TYPE_V2\r\n"));
			sd_showR7(r7);
			break;
		default:
			uart_sendPString(PSTR("SD_CARD_TYPE_V1??\r\n"));
			break;
	}
	if( res != SD_SUCCESSFULL )
		return SD_UNKNWON_ERROR;
	
	// Get supported Voltages
	sd_debug("sd_checkOperatingCondition\r\n");
	res = sd_checkOperatingCondition(&r1, r7);
	sd_showR1(r1);
	sd_showOCR(r7);
	if( res != SD_SUCCESSFULL )
		return SD_UNKNWON_ERROR;		
		
	res = sd_setCardReady(&r1, r7);
	if( res != SD_SUCCESSFULL )
		return SD_UNKNWON_ERROR;
		
		
	spi_init(SPI_MODE_0, SPI_DATA_ORDER_MSB_FIRST, SPI_FREQUENCY_1_2);
		
	
	return SD_SUCCESSFULL;
}

SD_RESULT sd_read(uint32_t address, uint8_t* buffer, uint16_t size)
{
	SD_ERRORCODE r1 = sd_sendCommand(SD_CMD_READ_SINGLE_BLOCK, address, 0x00);
	sd_debug("sd_read\n");
	sd_showR1(r1);
	if( r1 != 0xFF )
	{	
		uint16_t readAttempts = 15063;
		uint8_t res = 0xFF;
		while(readAttempts--)
		{
			res = spi_read();
			if( res != 0xFF )
			{
				break;
			}
		}
		// Read Start okay
		if( res == 0xFE )
		{
			for(uint16_t i = 0; i < size; i++) 
				*buffer++ = spi_read();
				
			// read CRC (ignore)
			spi_read();
			spi_read();
			sd_deselect();
			return SD_SUCCESSFULL;
		}
		else
		{
			sd_deselect();
			return SD_NO_RESPONSE;			
		}		
	}
	
	sd_deselect();
	return SD_UNKNWON_ERROR;
}