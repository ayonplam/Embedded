#ifndef FAT_FORMAT_H
#define FAT_FORMAT_H

/* Include static library */
#include <stdint.h>
#include <stdlib.h>
/* End of Include static library */

/* Include my library */
/* End of Include my library */

/* Macro */
#define SUBDIRECTORY 0x10 /* attribute is subdirectory */
#define BPE 32 /* Bytes per entry */
#define EPS 16 /* Entry per sector */
#define BPS 512 /* bytes per sector */
/* End of Macro */

/* Struct for BIOS parameter boot sector FAT12
/* @size: 512 bytes */
#pragma pack(push)
#pragma pack(1)
struct BPB_FAT12 {
    char BS_jmpBoot[3];
    char BS_OEMName[8];
    uint16_t BPB_BytesPerSec;
    uint8_t BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t BPB_NumFATs;
    uint16_t BPB_RootEntCnt;
    uint16_t BPB_TotSec16;
    uint8_t BPB_Media;
    uint16_t BPB_FATSz16;
    uint16_t BPB_SecPerTrk;
    uint16_t BPB_NumHeads;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;

    uint8_t BS_DrvNum;
    uint8_t BS_Reserved1;
    uint8_t BS_BootSig;
    uint32_t BS_VolID;
    char BS_VolLab[11];
    char BS_FilSysType[8];
    char boot_code[448];
    uint16_t signature;
};
#pragma pack(pop)
typedef struct BPB_FAT12 BPB_FAT12;

/* Struct for a Directory Entry
/* @size: 32 bytes */
#pragma pack(push)
#pragma pack(1)
struct dir_struct {
    unsigned char DIR_Name[8];
    unsigned char DIR_Extension[3];
    uint8_t DIR_Attr;
    uint16_t DIR_Reserved;
    uint16_t DIR_CrtTime;
    uint16_t DIR_CrtDate;
    uint16_t DIR_LstAccDate;
    uint16_t DIR_Ignore;
    uint16_t DIR_WrtTime;
    uint16_t DIR_WrtDate;
    uint16_t DIR_FstClusLO;
    uint32_t DIR_FileSize;
};
#pragma pack(pop)
typedef struct dir_struct DIR;

#endif /* FAT_FORMAT_H */
