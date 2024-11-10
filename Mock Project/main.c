/* Include static library */
/* End of Include static library */

/* Include my library */
#include "HAL.h"
#include "FATformat.h"
#include "FATprototype.h"
/* End of Include my library */

/* List of Prototype function */
/****************************/
/* Excute command if current directory is root */
/* @para: input: file's name which want to access
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector
/*        myAttr: pointer to current entry's attribute
/*        clusterFilePoint: cluster Number which entry point to */
/* @return */
int excuteCommandinRoot(char input[], FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr, uint64_t* clusterFilepoint);

/* Excute command if current directory is not root */
/* @para: input: file's name which want to access
/*        fd: pointer to File floppy
/*        myBPB: pointer to BIOS parameter boot sector
/*        myAttr: pointer to current entry's attribute
/*        clusterFilePoint: cluster Number which entry point to */
/* @return: 0: if find file */
int excuteCommand(char input[], FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr, uint64_t* clusterFilepoint);
/****************************/
/* End of List of Prototype function */
int
main() {
    /* Flag for check */
    short isOpen = 0; /* if =1: file is opened; if =0: file is not opened */
    short isQuit = 0; /* if = 1: exit loop and program and return 0 as success */
    short isFound = 1; /* if = 1: is founding, not find success; if =0: is not founding, find success*/
    short isInRoot = 1; /* if =1: now is in root directory; if =0: now not is in root directory */
    short isDataOpened = 0;
    /* End of Flag for check */

    FILE* fd; /*  pointer to File floppy */
    BPB_FAT12 myBPB; /* BIOS parameter boot sector */
    uint8_t myAttr = 0; /* current entry's attribute */
    uint8_t prevmyAttr = 0; /* previous entry's attribute */
    uint64_t clusterFilepoint = 0; /* current entry's cluster number */
    uint64_t prevclusterFilepoint = 0; /* previous entry's cluster number */
    char input[50];          /* used for get iput from user*/
    char* arg1 = malloc(30); /* used for storing arguments that users pass to commands */
    const char headerHello[] = {"\n:excute: "};
    char command[10];        /* used for store main command*/
    char tokenInput[10][20]; /* used for store token from input */
    short i;                 /* index for token */
    char* token;             /* used to get token from input */
    short j;                 /* used for loop */
    char flagcommand[10];

    /* LOOP PROGRAM */
    while (isQuit == 0) {
        memset(input, 0, 50); // used for storing user input commands
        memset(command, 0, 10);
        memset(flagcommand, 0, 10);

        /* Excute COMMAND */
        /****************************/

        /* COMMAND IN ROOT */
        /****************************/
        if (isInRoot == 1) {
            /* Get input from user */
            printf(headerHello);
            fgets(input, 50, stdin);

            /*Cast input to lowercase. Avoids complication with lower-case and upper-case arguments */
            for (j = 0; input[j] != '\0' && (j < 50); j++) {
                input[j] = tolower(input[j]);
            }
            /* Get the first token as main command */
            token = NULL;
            const char s[2] = " \n"; /* used to get token from input */
            token = strtok(input, s);
            strcpy(tokenInput[0], token);
            strcpy(command, token);
            /* Get another token */
            i = 0;
            while (token != NULL) {
                i++;
                token = strtok(NULL, s);
                if (token != NULL) {
                    strcpy(tokenInput[i], token);
                }
            }
            strcpy(tokenInput[i], "");
            /* Copy file name to arg1 */
            i = 1;
            while (strcmp(tokenInput[i], "") != 0) {
                strcpy(arg1, tokenInput[i]);
                i++;
            }

            /* COMPARE COMMAND */
            /****************************/

            /* COMMAND HELP */
            if (strcmp(command, "help") == 0) {
                printf("Please read file README.txt\n");
            }

            /* COMMAND OPEN */
            else if (strcmp(command, "open") == 0) {
                fd = fopen(arg1, "rb");
                if (fd != NULL) {
                    /* file opened*/
                    isOpen = 1;
                    printf("\n%s was opened\n", arg1);
                    myBPB = showBPB(fd);
                } else {
                    /* error, file not opened */
                    printf("\nFile %s could not be found\n", arg1);
                }
            }

            /* COMMAND CLOSE */
            else if (strcmp(command, "close") == 0) {
                if (isOpen == 1) {
                    fclose(fd);
                    printf("File was closed\n");
                    isOpen = 0;
                } else {
                    printf("\nNo floppy file is opened\n");
                }
            }

            /* COMMAND DIR */
            else if (strcmp(command, "dir") == 0) {
                if (isOpen == 0) {
                    printf("\nNo floppy file is opened\n");
                }

                else {
                    /* Loop program in root */
                    while (isInRoot == 1) {
                        /* Show root directory */
                        showRoot(fd, &myBPB);

                        isFound = 1;
                        /* Loop program to find file in root */
                        while (isFound == 1) {
                            /* Get file name from user */
                            printf("\n:root:");
                            fgets(input, 50, stdin);

                            /* Excute command with file name */
                            isFound = excuteCommandinRoot(input, fd, &myBPB, &myAttr, &clusterFilepoint);

                            /* If find success */
                            if (isFound == 0) {
                                if (((myAttr) == 16) || ((myAttr) == 32)) { /* subdirectory or achive */
                                    isInRoot = 0; /* Only way to exit loop program in root */
                                }

                                else { /* regular file */
                                    isDataOpened = 1;
                                    while (isDataOpened == 1) {
                                        printf("\nEnter . to close Data");
                                        fgets(input, 50, stdin);
                                        if (input[0] == '.') {
                                            isDataOpened = 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            /* COMMAND CLOSE */
            else if (strcmp(command, "quit") == 0) {
                if (isOpen == 1) {
                    fclose(fd);
                }
                printf("File was closed\n");
                isQuit = 1;
            }
        }
        /****************************/
        /* End of COMMAND IN ROOT */

        /* COMMAND IN SUBDIRECTORY */
        /****************************/
        else {
            isFound = 1;
            /* Loop program to find file in root */
            while (isFound == 1) {
                /* Get file name from user */
                printf("\n:in folder:");
                fgets(input, 50, stdin);

                prevclusterFilepoint = clusterFilepoint; /* Store current entry's cluster number */
                prevmyAttr = myAttr; /* Store current entry's attribute */
                /* Excute command with file name */
                isFound = excuteCommand(input, fd, &myBPB, &myAttr, &clusterFilepoint);

                /* If find success */
                if (isFound == 0) {
                    if (clusterFilepoint == 0) { /* Root directory */
                        isInRoot = 1;
                        showRoot(fd, &myBPB);
                        printf("\nPlease enter dir to continue.\n");
                    }

                    else {
                        if (((myAttr) == 16) || ((myAttr) == 32)) { /* subdirectory or achive */
                        } else { /* regular file */
                            isDataOpened = 1;
                            while (isDataOpened == 1) {
                                printf("\nEnter . to back folder");
                                fgets(input, 50, stdin);
                                if (input[0] == '.') {
                                    isDataOpened = 0;
                                    clusterFilepoint = prevclusterFilepoint; /* Retore current entry's cluster number */
                                    myAttr = prevmyAttr; /* Retore current entry's attribute */
                                    readFile(clusterFilepoint, fd, &myBPB);
                                }
                            }
                        }
                    }
                }
            }
        }
        /****************************/
        /* End of COMMAND IN SUBDIRECTORY */
    }
    /****************************/
    /* END of LOOP PROGRAM */
    return 0;
}

/* Function for main ()*/
/****************************/
/* Excute command if current directory is root */
int
excuteCommandinRoot(char input[], FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr, uint64_t* clusterFilepoint) {
    char* token; /* buffer */
    uint64_t temp; /* used to store cluster Number which entry point to */
    char fileName[10]; /* used to store file name */
    int j; /* use for loop */
    char s[2] = " \n";

    /* Convert input to lower */
    for (j = 0; input[j] != '\0' && (j < 50); j++) {
        input[j] = tolower(input[j]);
    }
    /* get file's name */
    token = strtok(input, s);
    strcpy(fileName, token);

    /* Get cluster Number which entry point to by file's name */
    temp = findFileInRoot(fileName, fd, myBPB, myAttr);
    /* Read entry if find success */
    if (temp > 1) {
        *clusterFilepoint = temp; /* Asign current entry's cluster if find success*/
        if (((*myAttr) == 16) || ((*myAttr) == 32)) { /* subdirectory or achive */
            readFile(*clusterFilepoint, fd, myBPB);
        } else {
            readData(*clusterFilepoint, fd, myBPB); /* regular file */
        }
        return 0; /* return 0 as find file success */
    } else {
        return 1;    /* return 1 as can't find file */
    }
}

int
excuteCommand(char input[], FILE* fd, BPB_FAT12* myBPB, uint8_t* myAttr, uint64_t* clusterFilepoint) {
    char* token; /* buffer */
    uint64_t temp; /* used to store cluster Number which entry point to */
    char fileName[10]; /* used to store file name */
    int j; /* use for loop */
    char s[2] = " \n";

    /* Convert input to lower */
    for (j = 0; input[j] != '\0' && (j < 50); j++) {
        input[j] = tolower(input[j]);
    }
    /* get file's name */
    token = strtok(input, s);
    strcpy(fileName, token);

    /* Get cluster Number which entry point to by file's name */
    temp = findFile(*clusterFilepoint, input, fd, myBPB, myAttr);

    /* Read entry if find success */
    if (temp == 0) { /* root directory */
        *clusterFilepoint = 0;
        *myAttr = 0;
        return 0; /* return 0 as find file success */
    } else if (temp > 1) {
        *clusterFilepoint = temp; /* Asign current entry's cluster if find success*/
        if (((*myAttr) == 16) || ((*myAttr) == 32)) { /* subdirectory or achive */
            readFile(*clusterFilepoint, fd, myBPB);
        } else {
            readData(*clusterFilepoint, fd, myBPB); /* regular file */
        }
        return 0; /* return 0 as find file success */
    } else {
        return 1;    /* return 0 as can't find file */
    }

}
/****************************/
/* End of Function for main() */

