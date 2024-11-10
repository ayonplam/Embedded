#include "HAL.h"

/* Read a sector */
int
readSector(FILE* fd, int sectorNum, unsigned char* buffer) {
    int currentPointer;
    int lengthSector;
    currentPointer = fseek(fd, sectorNum * BPS, SEEK_SET);
    lengthSector = fread(buffer, 1, BPS, fd);
    return lengthSector;
}

/* Read multi sector */
int
readMultiSector(FILE* fd, int sectorNum, unsigned char* buffer, int numSectors) {
    int currentPointer;
    int lengthSector;
    currentPointer = fseek(fd, sectorNum * BPS, SEEK_SET);
    lengthSector = fread(buffer, 1, BPS * numSectors, fd);
    return lengthSector;
}
