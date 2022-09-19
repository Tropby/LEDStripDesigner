
#include "cpu.h"
#include "fat16.h"
#include "sd.h"
#include "uart.h"
#include <avr/pgmspace.h>

#define FAT16_BYTES_PER_SECTOR			512UL

#define FAT16_BootSectorSize			FAT16_BYTES_PER_SECTOR

#define FAT16_FATRegionStart			(FAT16_ReservedRegionSize + (fat16_reservedSectors*FAT16_BYTES_PER_SECTOR))
#define FAT16_FATRegionSize				(fat16_numbersOfFATs * fat16_sectorsPerFAT * (uint32_t)FAT16_BYTES_PER_SECTOR)
#define FAT16_RootDirectoryRegionStart	(FAT16_FATRegionStart + FAT16_FATRegionSize)
#define FAT16_RootDirectoryRegionSize	(fat16_RootEntriesCount * 32)
#define FAT16_DataRegionStart			(FAT16_RootDirectoryRegionStart + FAT16_RootDirectoryRegionSize)
#define FAT16_CLUSTER_ADDRESS(cluster)	((uint32_t)FAT16_DataRegionStart + ((uint32_t)(cluster-2) * fat16_sectorsPerCluster * FAT16_BYTES_PER_SECTOR))
#define FAT16_CurrentFileReadPosition	(FAT16_CLUSTER_ADDRESS(fat16_currentFileCluster) + fat16_currentFileSectorInCluster * FAT16_BYTES_PER_SECTOR)

// current buffer for SD buffer
uint32_t FAT16_ReservedRegionSize;

uint8_t fat16_sectorsPerCluster; // normally 8 (we can read that many blocks in a row)
uint32_t fat16_startAddress;
uint8_t fat16_numbersOfFATs;
uint16_t fat16_sectorsPerFAT;
uint16_t fat16_reservedSectors;
uint8_t fat16_buffer[FAT16_BYTES_PER_SECTOR];
uint16_t fat16_RootEntriesCount;

uint32_t fat16_currentFileStartCluster;
uint32_t fat16_currentFileCluster;
uint8_t  fat16_currentFileSectorInCluster;
uint32_t fat16_currentFileSize;
uint32_t fat16_currentFilePosition;

bool fat16_init(void)
{
	if( sd_init() != SD_SUCCESSFULL )
	{
		return false;
	}
		
	if( !fat16_readFatInfo() )
		return false;
	
	return true;
}

void fat16_printBuffer()
{
	for( uint16_t i = 0; i < FAT16_BYTES_PER_SECTOR; i++ )
	{
		if( i % 8 == 0)
		uart_sendString(" ");
		if( i % 16 == 0)
		uart_sendString("\r\n");
		uart_sendHEXUInt8(*(fat16_buffer+i));
	}
	uart_sendString("\r\n");	
}

bool fat16_readRootDirectory()
{
	if( sd_read(FAT16_RootDirectoryRegionStart / FAT16_BYTES_PER_SECTOR, fat16_buffer, FAT16_BYTES_PER_SECTOR) != SD_SUCCESSFULL )
		return false;
	
	typedef struct {
		char filename[8];
		uint8_t ext[3];
		uint8_t attributes;
		uint8_t reserved;
		uint8_t creationMs;
		uint16_t creationTime;
		uint16_t creationDate;
		uint16_t lastAccessDate;
		uint16_t reservedForFat32;
		uint16_t lastWriteTime;
		uint16_t lastWriteDate;
		uint16_t startingCluster;
		uint32_t filesize;		
	} FAT16_DIRECTORY_ENTRY;
	
	FAT16_DIRECTORY_ENTRY * file;
	file = (FAT16_DIRECTORY_ENTRY *)fat16_buffer;
	fat16_currentFileStartCluster = 0;
	
	while( file->filename[0] != 0x00 )
	{	
		if( !(file->attributes & (1<<3)) )
		{		
			if( file->filename[0] != 0xE5 )
			{
				if( file->ext[0] == 'A' && file->ext[1] == 'L' && file->ext[2] == 'C' )
				{
					fat16_currentFileStartCluster = file->startingCluster;
					fat16_currentFileSectorInCluster = 0;
					fat16_currentFilePosition = 0;
					fat16_currentFileCluster = fat16_currentFileStartCluster;
					fat16_currentFileSize = file->filesize;
				
					uart_sendPString(PSTR("Selected file: "));
					uart_sendStringArray((char*)file->filename, 8);
					uart_sendStringArray((char*)file->ext, 3);
					uart_sendPString(PSTR("\r\n"));
				
					uart_sendPString(PSTR("Start cluster of file: "));
					uart_sendUInt32(fat16_currentFileStartCluster);
					uart_sendPString(PSTR("\r\n"));
				
					break;
				}	
				else
				{
					uart_sendPString(PSTR("Ignoring file: "));
					uart_sendStringArray((char*)file->filename, 8);
					uart_sendStringArray((char*)file->ext, 3);
					uart_sendPString(PSTR("\r\n"));
				}			
			}			
		}
		file ++;		
	}
	
	if( file->filename[0] == 0x00 )
	{
		uart_sendPString(PSTR("No ALC file found!\r\n"));
		while(1);
	}
	
	uart_sendPString(PSTR("Start of file: "));
	uart_sendUInt32(FAT16_CurrentFileReadPosition);
	uart_sendPString(PSTR("\r\n"));

	return true;
}

bool fat16_readFatInfo()
{	
	// Read Boot region
	if( sd_read(0, fat16_buffer, FAT16_BYTES_PER_SECTOR) != SD_SUCCESSFULL )
	{
		uart_sendPString(PSTR("ERROR: Boot region!\r\n"));
		return false;
	}
	
	uart_sendPString(PSTR("FAT Type: "));
	uart_sendUInt32(fat16_buffer[0x1C2]);
	uart_sendPString(PSTR("\r\n"));	
	
	if( fat16_buffer[0x1C2] != 0x0E )
	{
		uart_sendString("NOT FAT16!\r\n");		
		return false;		
	}
	
	FAT16_ReservedRegionSize = fat16_buffer[0x1C9];
	FAT16_ReservedRegionSize <<= 8;
	FAT16_ReservedRegionSize |= fat16_buffer[0x1C8];
	FAT16_ReservedRegionSize <<= 8;
	FAT16_ReservedRegionSize |= fat16_buffer[0x1C7];
	FAT16_ReservedRegionSize <<= 8;
	FAT16_ReservedRegionSize |= fat16_buffer[0x1C6];
	FAT16_ReservedRegionSize *= FAT16_BYTES_PER_SECTOR;
	
	uart_sendString("FAT Start sector: ");
	uart_sendUInt32(FAT16_ReservedRegionSize);
	uart_sendString("\r\n");

	if( sd_read(FAT16_ReservedRegionSize / FAT16_BYTES_PER_SECTOR, fat16_buffer, FAT16_BYTES_PER_SECTOR) != SD_SUCCESSFULL )
	{
		uart_sendString("Can not read FAT!\r\n");
		return false;
	}
	
	fat16_sectorsPerCluster = fat16_buffer[0x000D];
	
	fat16_numbersOfFATs = fat16_buffer[0x0010];
	
	fat16_sectorsPerFAT = fat16_buffer[0x0017];
	fat16_sectorsPerFAT <<= 8;
	fat16_sectorsPerFAT |= fat16_buffer[0x0016];
	
	fat16_reservedSectors = fat16_buffer[0x000F];
	fat16_reservedSectors <<= 8;
	fat16_reservedSectors |= fat16_buffer[0x000E];
	
	fat16_RootEntriesCount = fat16_buffer[0x0012];
	fat16_RootEntriesCount <<= 8;
	fat16_RootEntriesCount |= fat16_buffer[0x0011];
	
	
	uart_sendString("\r\n");

	uart_sendString("rootEntriesCount: ");
	uart_sendUInt8(fat16_RootEntriesCount);
	uart_sendString("\r\n");

	uart_sendString("SectorsPerCluster: ");
	uart_sendUInt8(fat16_sectorsPerCluster);
	uart_sendString("\r\n");
	
	uart_sendString("NumbersOfFATs: ");
	uart_sendUInt8(fat16_numbersOfFATs);
	uart_sendString("\r\n");

	uart_sendString("ResevedSectors: ");
	uart_sendUInt32(fat16_reservedSectors);
	uart_sendString("\r\n");
	
	uart_sendString("SectorsPerFAT: ");
	uart_sendUInt32(fat16_sectorsPerFAT);
	uart_sendString("\r\n");
	
	uart_sendString("RootDirectoryRegionStart: ");
	uart_sendUInt32(FAT16_RootDirectoryRegionStart);
	uart_sendString("\r\n");	
	
	fat16_readRootDirectory();
	
	return true;
}

uint16_t fat16_readFile( uint8_t * buffer, uint16_t size )
{
	sd_read(FAT16_CurrentFileReadPosition / FAT16_BYTES_PER_SECTOR, buffer, FAT16_BYTES_PER_SECTOR);
	
	// Calculate next Sector address		
	fat16_currentFileSectorInCluster++;
	if(fat16_currentFileSectorInCluster>=fat16_sectorsPerCluster)
	{
		fat16_currentFileSectorInCluster=0;		
		
		// Get the next cluster address
		uint32_t address = (FAT16_FATRegionStart + (( fat16_currentFileCluster * 2 )));
		uint32_t sector = address / FAT16_BYTES_PER_SECTOR;
		sd_read(sector, fat16_buffer, FAT16_BYTES_PER_SECTOR);

		// Get address in sector			
		address -= sector * FAT16_BYTES_PER_SECTOR;
		
		fat16_currentFileCluster = fat16_buffer[address+1];
		fat16_currentFileCluster <<= 8;
		fat16_currentFileCluster |= fat16_buffer[address];
		
		// Check for file end and other errors		
		if( fat16_currentFileCluster >= 0xFFF8 )
		{			
			fat16_currentFileCluster = fat16_currentFileStartCluster;
		}
		else if( fat16_currentFileCluster >= 0xFFF7 )
		{
			uart_sendString("BAD SECTORS!\r\n");
		}
		else if( fat16_currentFileCluster <= 0x0002 )
		{
			uart_sendString("unallocated cluster?\r\n");			
		}		
	}

	// Reset cluster pointer if end is reached!
	fat16_currentFilePosition += size;
	if( fat16_currentFilePosition >= fat16_currentFileSize )
	{	
		fat16_currentFileCluster = fat16_currentFileStartCluster;
		fat16_currentFilePosition = 0;
		fat16_currentFileSectorInCluster=0;		
	}
	
	return size;
}