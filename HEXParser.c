#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include "RS232.h"

struct HEXRecord
{
	uint8_t length;
	uint16_t offset;
	uint8_t type;
	uint8_t * data;
	size_t maxlen;
};

void initHEXRecord(struct HEXRecord * record, uint8_t * data, size_t data_size)
{
	record->data = data;
	record->maxlen = data_size;
}

uint8_t convertHex4(char hex)
{
	if (hex >= '0' && hex <= '9')
		return hex - '0';
	else if (hex >= 'A' && hex <= 'F')
		return hex - 'A' + 10;
	else
		return 0;
}

uint8_t convertHex8(const char * hexLine)
{
	return (convertHex4(hexLine[0]) << 4) |
			convertHex4(hexLine[1]);
}

uint16_t convertHex16(const char * hexLine)
{
	return (convertHex4(hexLine[0]) << 12) |
		   (convertHex4(hexLine[1]) << 8) |
		   (convertHex4(hexLine[2]) << 4) |
		    convertHex4(hexLine[3]);
}

int parseRecord(const char * hexLine, size_t size, struct HEXRecord * recp)
{
	uint8_t checksum;
	size_t recordPos; // Position inside record data fields.

	if(size < 11)
		return 1;

	/* Check format for line */
	if(hexLine[0] != ':') // Always start with colon.
		return 1;

	/* Parse length, offset and type */
	recp->length = convertHex8(hexLine + 1);
	recp->offset = convertHex16(hexLine + 3);
	recp->type = convertHex8(hexLine + 7);

	/* We now know how long the record should be */
	if(size < (11+recp->length*2))
		return 1;

	/* Process checksum */
	checksum = recp->length;
	checksum += (uint8_t) ((recp->offset >> 8) & 0xff);
	checksum += (uint8_t) (recp->offset & 0xff);
	checksum += recp->type;

	/* Parse data fields */
	if(recp->length)
	{
		if (recp->length > recp->maxlen)
			return 1;

		/* Read data from record */
		for( recordPos = 0; recordPos < recp->length; recordPos++)
		{
			recp->data[recordPos] = convertHex8(hexLine + 9 + recordPos*2);
			checksum += recp->data[recordPos];
		}
	}

	/* Correct checksum? */
	checksum += convertHex8(hexLine + 9 + recp->length*2);
	if( checksum != 0 )
	{
		return 1;
	}
	return 0;
}

char hexLine[100];
uint8_t hexData[sizeof(hexLine)/2];
//uint8_t databuff[2*SPM_PAGESIZE];
struct HEXRecord rec;

void readFile(void)
{
	initHEXRecord(&rec, hexData, sizeof(hexData));
	int error = 0;
	size_t baseAddress = 0;
	size_t dataPos;
	uint16_t word;
	size_t size = 1024*16;
	size_t Page_Address = 0;
	int hex_size;

//	usart_putc(XON);
	hex_size = usart_gets(hexLine, sizeof(hexLine));
//	usart_putc(XOFF);

	while( 1 )
	{
		/* Process record according to type */
		error |= parseRecord(hexLine, hex_size, &rec);

		switch( rec.type )
		{
			case 0x00 : // Data record
				if(baseAddress + rec.offset + rec.length > size)
					error = 1;

				for(dataPos = 0; dataPos < rec.length; dataPos+=2) {
					size_t Byte_Address = (baseAddress + rec.offset + dataPos) & (SPM_PAGESIZE-1);
					word = rec.data[dataPos] | (rec.data[dataPos+1] << 8);
					boot_page_fill(Byte_Address, word);
					if (Byte_Address == SPM_PAGESIZE-2) {
						usart_putc('*');
						Page_Address = (baseAddress + rec.offset + dataPos) & 0xFFFFFF80;
	                    boot_page_write(Page_Address);
	                    boot_spm_busy_wait();
					}
				}

				break;

			case 0x02 : // Extended segment address record ?
				baseAddress = (rec.data[0] << 8) | rec.data[1];
				baseAddress <<= 4;
				break;

			case 0x03 : // Start segment address record ?
				break; // Ignore it, since we have no influence on execution start address.

			case 0x04 : // Extendenot a word address.d linear address record ?
				baseAddress = (rec.data[0] << 8) | rec.data[1];
				baseAddress <<= 16;
				break;

			case 0x05 : // Start linear address record ?
				break; // Ignore it, since we have no influence on exectuion start address.

			case 0x01 : // End of file record ?
                boot_page_write(Page_Address + SPM_PAGESIZE);
                boot_spm_busy_wait();
                boot_rww_enable();
				if (error)
					usart_puts("KO");
				else
					usart_puts("OK");
				return;

			default:
				error = 1;
		}

		if (error)
			usart_putc('-');
		else
			usart_putc('+');
//		usart_putc(XON);
		usart_gets(hexLine, sizeof(hexLine));
//		usart_putc(XOFF);
	}
}
