#ifndef SREC_H
#define SREC_H

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stdlib.h>

/*******************************************************************************
 * Define a new struct or data type
 ******************************************************************************/
/* Record type S0 - S9 */
typedef enum recordType {
    S0 = 0, /* Header */
    S1,     /* Data */
    S2,     /* Data */
    S3,     /* Data */
    S4,     /* Reserved*/
    S5,     /* Count */
    S6,     /* Count */
    S7,     /* Start Address */
    S8,     /* Start Address */
    S9      /* Start Address */
} Rectype;

/* Result after parse a record */
typedef enum returnResult {
    NO_ERROR = 0, /* No ERROR */
    BAD_FORMAT,   /* Bad format: invalid character */
    BAD_RECORD,   /* Bad record: record type failure*/
    BAD_CKECKSUM, /* Bad check sum: check sum field failure */
    BAD_COUNT,    /* Bad count: count field failure */
    COMPLETE,     /* Complete: parse done */
} Result;

/* Structure for a record */
typedef struct record {
    uint32_t address;  /* Address */
    uint8_t count;     /* Count */
    Rectype type;      /* Record type */
    Result result;     /* Result */
    uint8_t data[125]; /* Data */
} record_t;

/* Read and parse records */
/* @para: buffer */
record_t
parse_record(uint8_t* record);

#endif /* SREC_H */
