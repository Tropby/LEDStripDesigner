#pragma once

#include <stdint.h>

typedef enum {
	SD_IN_IDLE_STATE = 1,
	SD_ERASE_RESET = 2,
	SD_ILLEGAL_COMMAND = 4,
	SD_COM_CRC_ERROR = 8,
	SD_ERASE_SEQENCE_ERROR = 16,
	SD_ADDRESS_ERROR = 32,
	SD_PARAMETER_ERROR = 64
} SD_ERRORCODE;

typedef enum {
	SD_SUCCESSFULL = 0,
	SD_UNKNWON_CARD_TYPE = 1,
	SD_NO_RESPONSE = 254,
	SD_UNKNWON_ERROR = 255
} SD_RESULT;

extern SD_RESULT sd_init(void);
extern SD_RESULT sd_read(uint32_t address, uint8_t* buffer, uint16_t size);
