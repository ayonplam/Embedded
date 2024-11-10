#include "srec.h"

/* Convert an ascii hex character */
static uint8_t
hex(const char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else {
        return 0xff;
    }
}

/* Parse a record */
static record_t
parse_record(uint8_t* record) {
    record_t rec;       /* Create new record to save data into after parse a record */
    size_t i;           /* the number of byte in a record  use for loop and check byte count */
    uint8_t byte_count; /* variable to save count field*/

    /* Check for start code */
    if (record[0] != 'S') {
        rec.result = BAD_FORMAT;
        return rec;
    }
    /* Check for valid characters */
    for (i = 1; record[i] != '\r' && record[i] != '\n'; i++) {
        if (hex(record[i]) > 0x0F) {
            rec.result = BAD_FORMAT;
            return rec;
        }
    }
    /* Get the record type */
    rec.type = (hex(record[1]));
    if (rec.type > S9) {
        rec.result = BAD_RECORD;
        return rec;
    }
    /* Get the count field */
    byte_count = (hex(record[2]) << 4) | hex(record[3]);
    if (i < byte_count * 2 + 4) {
        rec.result = BAD_COUNT;
        return rec;
    }
    /* Get the record address */
    switch (rec.type) {
        case S0:
            rec.address = 0;
            rec.count = byte_count - 3;
            break;
        case S1:
        case S5:
        case S9:
            /* Four hex digits address */
            rec.address = (hex(record[4]) << 12) | (hex(record[5]) << 8) |
                          (hex(record[6]) << 4) | hex(record[7]);
            rec.count = byte_count - 3;
            break;
        case S2:
        case S6:
        case S8:
            /* Six hex digits address */
            rec.address = (hex(record[4]) << 20) | (hex(record[5]) << 16) |
                          (hex(record[6]) << 12) | (hex(record[7]) << 8) |
                          (hex(record[8]) << 4) | hex(record[9]);
            rec.count = byte_count - 4;
            break;
        case S3:
        case S7:
            /* Eight hex digits address */
            rec.address = (hex(record[4]) << 28) | (hex(record[5]) << 24) |
                          (hex(record[6]) << 20) | (hex(record[7]) << 16) |
                          (hex(record[8]) << 12) | (hex(record[9]) << 8) |
                          (hex(record[10]) << 4) | hex(record[11]);
            rec.count = byte_count - 5;
            break;
        /* S4 record ignored */
        default:
            rec.result = NO_ERROR;
            return rec;
    }

    /* Calculate checksum and copy data bytes */
    uint8_t checksum_c = byte_count + (rec.address >> 24) +
                         (rec.address >> 16) + (rec.address >> 8) +
                         (rec.address & 0xff);

    if (rec.type < S4) {
        memset(rec.data, 0x00, sizeof(rec.data));
        size_t data_offset = (byte_count - rec.count) * 2 + 2;
        for (i = 0; i < rec.count; i++) {
            rec.data[i] = (hex(record[data_offset + i * 2]) << 4) |
                          hex(record[data_offset + i * 2 + 1]);
            checksum_c += rec.data[i];
        }
    }

    checksum_c = ~checksum_c;
    uint8_t checksum_f = (hex(record[byte_count * 2 + 2]) << 4) |
                         hex(record[byte_count * 2 + 3]);
    if (checksum_c != checksum_f) {
        rec.result = BAD_CKECKSUM;
        return rec;
    }
    rec.result = NO_ERROR;
    return rec;
}

/* Read a S-Record file */
int
read_srec_file(uint8_t* buffer, FILE* fp) {
    uint32_t line = 0;
    record_t rec;
    size_t s0 = 0;
    size_t data_offset;
    /* read buffer */
    while (buffer) {
        /* Skip empty lines */
        line++;
        if (*buffer == '\r' || *buffer == '\n') {
            buffer++;
            continue;
        }
        /* Parse a record */
        rec = parse_record(buffer);
        /* Return result */
        switch (rec.result) {
            case BAD_FORMAT:
                return NOT_SREC;
            case BAD_RECORD:
                fprintf(stderr, "Error on line %u: bad record type.\n",
                        line);
                return EXIT_FAILURE;
            case BAD_COUNT:
                fprintf(stderr, "Error on line %u: bad count.\n", line);
                return EXIT_FAILURE;
            case BAD_CKECKSUM:
                fprintf(stderr, "Error on line %u: bad checksum.\n",
                        line);
                return EXIT_FAILURE;
            default:
                /* Excute data field */
                switch (rec.type) {
                    case S0:
                        s0++;
                        fprintf(fp, "%s\n", rec.data);
                        break;
                    case S1:
                        data_offset = 8;
                        for (int i = 0; i < (rec.count * 2); i++) {
                            fprintf(fp, "%c", buffer[data_offset]);
                            ++data_offset;
                        }
                        fprintf(fp, "\n");
                        break;
                    case S2:
                        data_offset = 10;
                        for (int i = 0; i < (rec.count * 2); i++) {
                            fprintf(fp, "%c", buffer[data_offset]);
                            ++data_offset;
                        }
                        fprintf(fp, "\n");
                        break;
                    case S3:
                        data_offset = 12;
                        for (int i = 0; i < (rec.count * 2); i++) {
                            fprintf(fp, "%c", buffer[data_offset]);
                            ++data_offset;
                        }
                        fprintf(fp, "\n");
                        break;
                    case S5:
                    case S6:
                        if (rec.address != line - 1 - s0) {
                            fprintf(stderr,
                                    "Error: wrong record count.\n");
                            fclose(fp);
                            return EXIT_FAILURE;
                        }
                        break;
                    case S7:
                    case S8:
                    case S9:
                        break;
                    default:
                        fprintf(stderr,
                                "Error on line %u: unknown record type.\n",
                                line);
                        fclose(fp);
                        return EXIT_FAILURE;
                }
        }
        /* End of return result*/
        buffer = (uint8_t*)strchr((char*)++buffer, 'S');
    }
    /* End of read buffer */
    return SREC_FORMAT;
}
