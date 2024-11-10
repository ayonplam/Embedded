#include "FATformat.h"
#include "FATprototype.h"

/* Get BIOS parameter boot sector */
BPB_FAT12
showBPB(FILE* fd) {
    BPB_FAT12 myBPB;
    uint8_t bootSector[BPS] = {'\0'}; /* buffer 512 bytes is used to store BPB */
    /* Read BIOS parameter boot sector */
    fseek(fd, 0, SEEK_SET);
    fread(bootSector, 1, BPS, fd);
    memcpy(&myBPB, bootSector, BPS);
    /* Print some information */
    printf("Name: %s\n", myBPB.BS_OEMName);
    printf("The number of bytes per sector: %ld\n", myBPB.BPB_BytesPerSec);
    printf("The number of sectors per cluster: %ld\n", myBPB.BPB_SecPerClus);
    printf("The number of File Allocation Tables: %d\n", myBPB.BPB_NumFATs);
    printf("The number of sectors per FAT: %ld\n", myBPB.BPB_FATSz16);
    printf("The number of Entry in RDET: %ld\n", myBPB.BPB_RootEntCnt);
    printf("The size of the partition, in sectors: %d\n", myBPB.BPB_TotSec16);
    /* return BPB_FAT12 myBPB */
    return myBPB;
}

/* Show Root directory */
void
showRoot(FILE* fd, BPB_FAT12* myBPB) {
    DIR myRoot;
    uint8_t root[BPE] = {'\0'}; /* buffer 32 bytes is used to store a entry */
    int i; /* is used for loop */
    int j; /* is used for loop */
    int file; /* is used for loop */
    uint32_t rootStartSector = myBPB->BPB_RsvdSecCnt + myBPB->BPB_FATSz16 * myBPB->BPB_NumFATs; /* base sector BPB region */
    uint32_t rootSector = (BPE * myBPB->BPB_RootEntCnt + BPS - 1) / BPS; /* length of BPB region (in sector) */

    /* traverse each entry in BPB region */
    for (i = rootStartSector; i < (rootStartSector + rootSector); i++) {
        for (file = 0; file < EPS; file++) {
            /* Read entry */
            fseek(fd, (BPS * i + file * BPE), SEEK_SET);
            fread(root, 1, BPE, fd);
            memcpy(&myRoot, root, BPE);
            if (root[0] == '\0') { /* Name NULL */
                continue;
            }
            if (myRoot.DIR_Attr == 0x0F) { /* Long file name, ignore */
                continue;
            }
            printf("\n/");
            /* Print DIRECTORY */
            if (myRoot.DIR_Attr == SUBDIRECTORY) { /* Entry's attribute is subdirectory */
                printf("%s", myRoot.DIR_Name);
                printf("\t<DIR>");
            } else { /* Entry's attribute is regular file */
                for (j = 0; j < 8; j++) {
                    printf("%c", myRoot.DIR_Name[j]);
                }
                printf(".%s", myRoot.DIR_Extension);
            }
        }
    }
    printf("\n");
}

/* Read entry */
static int
readEntry(uint64_t sectorNum, uint8_t* buffer, uint64_t entryNum, FILE* fd) {
    int dest;
    int len;
    /* Position entry */
    dest = fseek(fd, sectorNum * BPS + (entryNum * BPE), SEEK_SET);
    fseek(fd, sectorNum * BPS + (entryNum * BPE), SEEK_SET);
    /* Read entry */
    len = fread(buffer, 1, BPE, fd);
    /* return int len */
    return len;
}

/* Get first sector (cluster) in Data region */
static uint64_t
getFirstSector(uint64_t cluster, BPB_FAT12* myBPB) {
    uint64_t rootStartSector = myBPB->BPB_RsvdSecCnt + myBPB->BPB_FATSz16 * myBPB->BPB_NumFATs; /* Base sector BPB region */
    uint64_t rootSector = (BPE * myBPB->BPB_RootEntCnt + BPS - 1) / BPS; /* length of BPB region (in sector) */
    uint64_t dataSecStart = rootStartSector + rootSector; /* Base sector Data region */
    return dataSecStart + (cluster - 2) * 1;
}

/* Read FAT */
static uint16_t
readFAT(uint64_t reservedSec, uint64_t clusterNum, FILE* fd) {
    uint16_t cluster_value = 0xFFFF;
    uint8_t buffer[2]; /* buffer is used to store a byte in FAT region */
    uint64_t offset = clusterNum * 1.5;
    int current; /* used for check value */
    int len;     /* used for check value */
    /* Position byte offset */
    current = fseek(fd, reservedSec * BPS + offset, SEEK_SET);
    /* Read a byte to buffer */
    fread(buffer, 1, 2, fd);
    /* Caculate cluster_value */
    if (clusterNum % 2) {
        cluster_value = (((uint16_t)buffer[0] >> 4) | ((uint16_t)buffer[1] << 4)) & 0xFFF;
    } else {
        cluster_value = (((uint16_t)buffer[0]) | ((uint16_t)buffer[1] << 8)) & 0xFFF;
    }
    /* return uint16_t cluster_value */
    return cluster_value;
}

/* Read a file */
void
readFile(uint64_t clusterNum, FILE* fd, BPB_FAT12* myBPB) {
    DIR myEntry;
    char name[12]; /* buffer */
    char nameNoSpace[12]; /* buffer */
    uint8_t buffer[BPE] = {'\0'}; /* buffer */
    uint16_t nextCluster; /* is used store next cluster's value */
    int j; /* used for loop */
    int k; /* used for loop*/
    uint64_t baseSector = getFirstSector(clusterNum, myBPB); /* Get base sector */

    /* Traverse each entry in cluster */
    for (j = 0; j < EPS; j++) {
        /* Position entry */
        fseek(fd, (BPS * baseSector + j * BPE), SEEK_SET);
        /* Read entry to buffer */
        fread(buffer, 1, BPE, fd);
        memcpy(&myEntry, buffer, 32);

        if (buffer[0] == '\0') { /* Name NULL */
            continue;
        }
        if (myEntry.DIR_Attr == 0x0F) { /* Long file name, ignore */
            continue;
        }
        printf("\n/");
        /* Print DIRECTORY */
        if (myEntry.DIR_Attr == 0x10) { /* Entry's attribute is subdirectory */
            printf("%s", myEntry.DIR_Name);
            printf("\t<DIR>");
        }
        /* Entry's attribute is regular file */
        else {
            for (k = 0; k < 8; k++) {
                printf("%c", myEntry.DIR_Name[k]);
            }
            printf(".%s", myEntry.DIR_Extension);
        }
    }

    /* Check in FAT region  */
    nextCluster = readFAT(1, clusterNum, fd);
    if (nextCluster < 0xff7) { /* value in FAT not End's value */
        readFile(nextCluster, fd, myBPB);
    }
}

/* Read Data */
void
readData(uint64_t clusterNum, FILE* fd, BPB_FAT12* myBPB) {
    uint8_t buffer[BPS] = {'\0'}; /* buffer */
    int j; /* used for loop */
    uint16_t nextCluster; /* is used store next cluster's value */
    /* Get base sector */
    uint64_t baseSector = getFirstSector(clusterNum, myBPB);
    /* Read cluster to buffer and print */
    readSector(fd, baseSector, buffer);
    printf("%s", buffer);
    /* Check FAT */
    nextCluster = readFAT(1, clusterNum, fd);
    if (nextCluster < 0xff7) {
        readData(nextCluster, fd, myBPB);
    }
}

uint64_t
findFile(uint64_t clusterNum, char* fileName, FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr) {
    uint64_t clusterFilepoint; /* local variable is used to store base address cluster in Data region */
    uint8_t buffer[BPE] = {'\0'}; /* buffer */
    char name[9]; /* buffer */
    char nameNoSpace[9]; /* buffer */
    DIR* currEntry; /* buffer */
    uint16_t nextCluster; /* is used store next cluster's value */
    int i; /* used for loop */
    int j; /* used for loop */
    int k; /* used for loop */
    uint64_t baseSector = getFirstSector(clusterNum, myBPB); /* Get base sector */

    /* Traverse each entry in cluster */
    for (j = 0; j < 16; j++) {
        /* Read entry */
        readEntry(baseSector, buffer, j, fd);
        /* Read current dirEntry in sector, null terminate the name */
        currEntry = (DIR*)buffer;
        memcpy(name, currEntry->DIR_Name, 8);
        /* Convert file's name to lower */
        for (k = 0; name[k] != '\0' && (k < 8); k++) {
            name[k] = tolower(name[k]);
        }
        /* Remove space in file's name*/
        removeSpaces(name, nameNoSpace);
        name[8] = '\0';
        /* Compare name */
        if (strcmp(nameNoSpace, fileName) == 0) { /* If match */
            clusterFilepoint = currEntry->DIR_FstClusLO; /* Get base cluster which that entry point */
            *myAttr = currEntry->DIR_Attr; /* Get entry attribute */
            return clusterFilepoint; /* return uint16_t clusterFilePoint */
        }
    }

    /* Check FAT */
    nextCluster = readFAT(1, clusterNum, fd);
    if (nextCluster < 0xff7) {
        findFile(nextCluster, fileName, fd, myBPB, myAttr);
    }
    /* return if not found file name */
    return 1;
}

uint64_t
findFileInRoot(char* fileName, FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr) {
    uint64_t clusterFilepoint; /* local variable is used to store base address cluster in Data region */
    uint8_t buffer[BPE] = {'\0'}; /* buffer */
    char name[9]; /* buffer */
    char nameNoSpace[9]; /* buffer */
    DIR* currEntry; /* buffer */
    uint16_t nextCluster; /* is used store next cluster's value */
    int i; /* used for loop */
    int j; /* used for loop */
    int k; /* used for loop */
    /* Get base sector */
    uint32_t rootStartSector = myBPB->BPB_RsvdSecCnt + myBPB->BPB_FATSz16 * myBPB->BPB_NumFATs;
    uint32_t rootSector = (BPE * myBPB->BPB_RootEntCnt + BPS - 1) / BPS;

    /* Traverse each entry in BPB region */
    for (i = rootStartSector; i < (rootStartSector + rootSector); i++) {
        for (j = 0; j < EPS; j++) { /* 16 file entries per sector */
            /* Read entry */
            readEntry(rootStartSector, buffer, j, fd);
            /* Read current dirEntry in sector, null terminate the name */
            currEntry = (DIR*)buffer;
            memcpy(name, currEntry->DIR_Name, 8);
            /* Convert file's name to lower */
            for (k = 0; name[k] != '\0' && (k < 8); k++) {
                name[k] = tolower(name[k]);
            }
            /* Remove space in file's name*/
            removeSpaces(name, nameNoSpace);
            name[8] = '\0';
            /* Compare name */
            if (strcmp(nameNoSpace, fileName) == 0) { /* If match */
                clusterFilepoint = currEntry->DIR_FstClusLO; /* Get base cluster which that entry point */
                *myAttr = currEntry->DIR_Attr; /* Get entry attribute */
                return clusterFilepoint; /* return uint16_t clusterFilePoint */
            }
        }
    }
    /* Return if not found */
    return 1;
}

/* Remove space in file name*/
static void
removeSpaces(char* source, char* dest) {
    int i;
    int j = 0;

    for (i = 0; i < strlen(source); i++) {
        if (source[i] != ' ') {
            dest[j] = source[i];
            j++;
        }
    }
    dest[j] = '\0';
}