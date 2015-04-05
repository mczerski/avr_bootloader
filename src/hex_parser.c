#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>
#include "USART.h"

struct hex_record
{
    uint8_t length;
    uint16_t offset;
    uint8_t type;
    uint8_t * data;
    size_t maxlen;
};

static void hex_record_init(struct hex_record * record, uint8_t * data, size_t data_size)
{
    record->data = data;
    record->maxlen = data_size;
}

static uint8_t convert_hex_4(char hex)
{
    if (hex >= '0' && hex <= '9')
        return hex - '0';
    else if (hex >= 'A' && hex <= 'F')
        return hex - 'A' + 10;
    else
        return 0;
}

static uint8_t convert_hex_8(const char * hex_line)
{
    return (convert_hex_4(hex_line[0]) << 4) |
            convert_hex_4(hex_line[1]);
}

static uint16_t convert_hex_16(const char * hex_line)
{
    return (convert_hex_4(hex_line[0]) << 12) |
           (convert_hex_4(hex_line[1]) << 8) |
           (convert_hex_4(hex_line[2]) << 4) |
            convert_hex_4(hex_line[3]);
}

static int parse_record(const char * hex_line, size_t size, struct hex_record * record)
{
    uint8_t checksum;
    size_t record_pos; // Position inside record data fields.

    if(size < 11)
        return 1;

    /* Check format for line */
    if(hex_line[0] != ':') // Always start with colon.
        return 1;

    /* Parse length, offset and type */
    record->length = convert_hex_8(hex_line + 1);
    record->offset = convert_hex_16(hex_line + 3);
    record->type = convert_hex_8(hex_line + 7);

    /* We now know how long the record should be */
    if(size < (11+record->length*2))
        return 1;

    /* Process checksum */
    checksum = record->length;
    checksum += (uint8_t)((record->offset >> 8) & 0xff);
    checksum += (uint8_t)(record->offset & 0xff);
    checksum += record->type;

    /* Parse data fields */
    if(record->length)
    {
        if (record->length > record->maxlen)
            return 1;

        /* Read data from record */
        for(record_pos = 0; record_pos < record->length; record_pos++)
        {
            record->data[record_pos] = convert_hex_8(hex_line + 9 + record_pos*2);
            checksum += record->data[record_pos];
        }
    }

    /* Correct checksum? */
    checksum += convert_hex_8(hex_line + 9 + record->length*2);
    if(checksum != 0)
    {
        return 1;
    }
    return 0;
}

static char hex_line[100];
static uint8_t hex_data[sizeof(hex_line)/2];
static struct hex_record record;

void hex_parser_write_file(void)
{
    hex_record_init(&record, hex_data, sizeof(hex_data));
    int error = 0;
    size_t base_addr = 0;
    size_t data_pos;
    uint16_t word;
    size_t size = 1024*16;
    size_t page_addr = 0;
    int hex_size;

//    USART_putc(XON);
    hex_size = USART_gets(hex_line, sizeof(hex_line));
//    USART_putc(XOFF);

    while( 1 )
    {
        /* Process record according to type */
        error |= parse_record(hex_line, hex_size, &record);

        switch( record.type )
        {
            case 0x00 : // Data record
                if(base_addr + record.offset + record.length > size)
                    error = 1;

                for(data_pos = 0; data_pos < record.length; data_pos+=2) {
                    size_t byte_addr = (base_addr + record.offset + data_pos) & (SPM_PAGESIZE-1);
                    word = record.data[data_pos] | (record.data[data_pos+1] << 8);
                    boot_page_fill(byte_addr, word);
                    if (byte_addr == SPM_PAGESIZE-2) {
                        USART_putc('*');
                        page_addr = (base_addr + record.offset + data_pos) & 0xFFFFFF80;
                        boot_page_write(page_addr);
                        boot_spm_busy_wait();
                    }
                }

                break;

            case 0x02 : // Extended segment address record ?
                base_addr = (record.data[0] << 8) | record.data[1];
                base_addr <<= 4;
                break;

            case 0x03 : // Start segment address record ?
                break; // Ignore it, since we have no influence on execution start address.

            case 0x04 : // Extendenot a word address.d linear address record ?
                break; // Ignore it, since we don't support such large memory

            case 0x05 : // Start linear address record ?
                break; // Ignore it, since we have no influence on exectuion start address.

            case 0x01 : // End of file record ?
                boot_page_write(page_addr + SPM_PAGESIZE);
                boot_spm_busy_wait();
                boot_rww_enable();
                if (error)
                    USART_puts("KO");
                else
                    USART_puts("OK");
                return;

            default:
                error = 1;
        }

        if (error)
            USART_putc('-');
        else
            USART_putc('+');
//        USART_putc(XON);
        USART_gets(hex_line, sizeof(hex_line));
//        USART_putc(XOFF);
    }
}
