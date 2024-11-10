#ifndef HAL_H
#define HAL_H
/* Include static library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* End of Include static library */

/* Include my library */
#include "FATformat.h"
/* End of Include my library */

/* Read a sector */
/* @para: fd: pointer to file
/*        sectorNum: sector number
/*        buffer: buffer which is used to store data
/* @return: length of data which is read (bytes) */
int readSector(FILE* fd, int sectorNum, unsigned char* buffer);

/* Read a sector */
/* @para: fd: pointer to file
/*        sectorNum: sector number as base sector
/*        buffer: buffer which is used to store data
/*        numSector: number
/* @return: length of data which is read (bytes) */
int readMultiSector(FILE* fd, int sectorNum, unsigned char* buffer, int numSectors);

#endif /* HAL_H */