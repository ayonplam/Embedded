/*******************************************************************************
* Includes
******************************************************************************/
#include "driver_lpuart.h"
#include "driver_button.h"
#include "manager.h"
#include "bootloader.h"
#include "flash.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/
static uint8_t busy; /* busy = 0 when dectect error when flash complete */

/* String inform to PC */
const static uint8_t badFormat[] = "BAD FORMAT!. Reset and try to flash again";
const static uint8_t badRecord[] = "BAD RECORD!. Reset and try to flash again";
const static uint8_t badCount [] = "BAD COUNT!. Reset and try to flash again";
const static uint8_t badSum   [] = "BAD CHECK SUM!. Reset and try to flash again";
const static uint8_t success  [] = ">>\r\n";
const static uint8_t request  [] = "Please send file\r\n";
const static uint8_t complete [] = "FLASH COMPLETE!. Reset to continue";

const static size_t s1 = sizeof(badFormat) - 1;
const static size_t s2 = sizeof(badRecord) - 1;
const static size_t s3 = sizeof(badCount)  - 1;
const static size_t s4 = sizeof(badSum)    - 1;
const static size_t s5 = sizeof(success)   - 1;
const static size_t s6 = sizeof(request)   - 1;
const static size_t s7 = sizeof(complete)  - 1;

/*******************************************************************************
 * Prototype
 ******************************************************************************/
/*!
 * @brief Start Flash file
 *
 * This function start UART to receive srec file and flash file to memory
 *
 */
static void UART_start (void);

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* Initialize button SW3 */
    initBtn_SW3 ();

    if (readBtn_SW3() == isPressed) /* Butotn is pressed */
        {
            UART_start(); /* Start UART to receive srec file and flash file to memory */
        }
    else
    {
        jump_to_application(); /* Jump to application at address 0x0000'A000 */
    }
}


/*******************************************************************************
* Definiton
******************************************************************************/
/*!
 * @brief Start Flash file
 *
 * This function start UART to receive srec file and flash file to memory
 *
 */
static void UART_start (void)
{
    /* Init UART */
    LPUART0_ConfigClockSource ();
    Caculate_OSR_SBR (CLOCK_HZ, BAUD_RATE);
    LPUART0_Init ();
    /* Init ring buffer */
    buff_init ();

    /* Set flag to busy */
    busy = 1;

    /* Erase 5 sector after 0xA000 in flash memory */
    Erase_Multi_Sector(0xA000, 5);

    /* Send request file to PC */
    LPUART0_Write(request, s6);

    /* start receive srec file and flash file to memory */
    while (busy)
    {
        if (0 == buff_isEmpty())
        {
            buff_pop (); /* parse a line in srec */

            switch (parse_result())
            {
            case BAD_FORMAT:
                LPUART0_Write(badFormat, s1);
                busy = 0;
                break;
            case BAD_RECORD:
                LPUART0_Write(badRecord, s2);
                busy = 0;
                break;
            case BAD_COUNT:
                LPUART0_Write(badCount, s3);
                busy = 0;
                break;
            case BAD_CKECKSUM:
                LPUART0_Write(badSum, s4);
                busy = 0;
                break;
            case COMPLETE: /* Complete when flash success all data in srec file to flash memory */
                LPUART0_Write(complete, s7);
                busy = 0;
                break;
            default: /* NO_ERROR */
                WrtieFlash(); /* Flash a line to flash memory */
                LPUART0_Write(success, s5);
            }
        }
    }
}