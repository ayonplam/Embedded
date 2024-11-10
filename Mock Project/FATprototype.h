#ifndef FAT_PROTOTYPE_H
#define FAT_PROTOTYPE_H

/* Include static library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* End of Include static library */

/* Include my library */
#include "HAL.h"
#include "FATformat.h"
/* End of Include my library */

/* Functions for use */
/****************************/
/* Show information in BIOS parameter boot sector */
/* @para: fd: pointer to File floppy
/* @return: BPB_FAT12: BIOS parameter boot sector */
BPB_FAT12 showBPB(FILE* fd);

/* Show information in root directory */
/* @para: fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector */
void showRoot(FILE* fd, BPB_FAT12* myBPB);

/* Read file which is subdirectory */
/* @para: clusterNum: cluster Number which entry point to
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector */
void readFile(uint64_t clusterNum, FILE* fd, BPB_FAT12* myBPB);

/* Read regular file */
/* @para: clusterNum: cluster Number which entry point to
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector */
void readData(uint64_t clusterNum, FILE* fd, BPB_FAT12* myBPB);

/* Find file by Name in Data region */
/* @para: clusterNum: cluster Number which entry point to
/*        fileName: pointer to file's name which want to find
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector
/*        myAttr: pointer to current entry's attribute */
/* @return: 1   : if can't find
/*          else: if find success, return cluster Number which entry point to*/
uint64_t findFile(uint64_t clusterNum, char* fileName, FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr);

/* Find file by Name in Data region */
/* @para: fileName: pointer to file's name which want to find
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector
/*        myAttr: pointer to current entry's attribute */
/* @return: 1   : if can't find
/*          else: if find success, return cluster Number which entry point to*/
uint64_t findFileInRoot(char* fileName, FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr);
/****************************/
/* End of Functions for use */

/* Static function */
/****************************/
/* Read value in FAT region (1.5 bytes) */
/* @para: reservedSec: number of sector before FAT region */
/* @return: cluster's value in FAT (1.5 bytes)*/
static uint16_t readFAT(uint64_t reservedSec, uint64_t clusterNum, FILE* fd);

/* Remove space in file name (8 bytes) */
/* @para: source: file name
          dest: buffer to store file name no spcae */
static void removeSpaces(char* source, char* dest);
/****************************/
/* End of static function */

#endif /* FAT_PROTOTYPE_H */