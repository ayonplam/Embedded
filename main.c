/* Include static library */
/* End of include static library */

/* Include my library */
#include "srec.h"
/* End of include my library */

int
main() {
    FILE* fp;       /* file to read */
    FILE* fp1;      /* file to write*/
    long file_size; /* file size of fp*/
    int ret;        /* return */
    size_t br = 0;

    /* open srec file */
    fp = fopen("srecfile\\freg", "rb");
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    /* Allocate memory in heap to save data from sreg file */
    uint8_t* buffer = calloc(1, file_size);
    if (!buffer) {
        fclose(fp);
        fprintf(stderr, "Out of memory!\n");
        return EXIT_FAILURE;
    }
    br = fread(buffer, 1, file_size, fp);
    fclose(fp);
    /* close file */

    if (!br) {
        fprintf(stderr, "No data to read.\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    /* Open file to write data field */
    fopen_s(&fp1, "srecfile\\DataField.txt", "w");
    ret = read_srec_file(buffer, fp1);
    fclose(fp1);
    /* Close file */

    /* Return */
    switch (ret) {
        case NOT_SREC:
            return NOT_SREC;
            break;
        case EXIT_FAILURE:
            free(buffer);
            return EXIT_FAILURE;
            break;
        case SREC_FORMAT:
            fprintf(stderr, "Parse success and write data field to datafiled.txt done\n");
            free(buffer);
            return EXIT_SUCCESS;
    }
}