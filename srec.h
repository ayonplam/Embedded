#ifndef SREC_H
#define SREC_H

/* Include static library */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* End of include static library*/

/* Include my library */
/* End of include my library */

/* Macro for return */
#define NOT_SREC -1    /* Not SREC file, wrong format */
#define EXIT_FAILURE 1 /* SREC file have failure */
#define SREC_FORMAT 0  /* SREC file no failure, read success */
/* End of macro for return */

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
} Result;

/* Structure for a record */
typedef struct record {
    uint32_t address;  /* Address */
    uint8_t count;     /* Count */
    Rectype type;      /* Record type */
    Result result;     /* Result */
    uint8_t data[255]; /* Data */
} record_t;

/* Read and parse records */
/* @para: buffer */
int read_srec_file(uint8_t* buffer, FILE* fp);

#endif /* SREC_H */
