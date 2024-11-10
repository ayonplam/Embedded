/*******************************************************************************
* Includes
******************************************************************************/
#include "driver_lpuart.h"
#include "queue.h"
#include "srec.h"

/*******************************************************************************
 * Variable
 ******************************************************************************/
/* Variable to store value of OSR and SBR */
static osr_sbr myOSR_SBR;

/* Variable to store a currently line srec */
static record_t rec;

/* Ring Buffer */
static circ_bbuf_t myRingBuffer;

/* Flag = 1 if no_error, = 0 when dectect error when parse a line */
volatile uint8_t no_error = 1;

/* String inform to PC */
const static uint8_t badFormat[] = "BAD FORMAT!";
const static uint8_t badRecord[] = "BAD RECORD!";
const static uint8_t badCount [] = "BAD COUNT!";
const static uint8_t badSum   [] = "BAD CHECK SUM!";
const static uint8_t success  [] = ">>\r\n";

const static size_t s1 = sizeof(badFormat) - 1;
const static size_t s2 = sizeof(badRecord) - 1;
const static size_t s3 = sizeof(badCount) - 1;
const static size_t s4 = sizeof(badSum) - 1;
const static size_t s5 = sizeof(success) - 1;

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    LPUART0_ConfigClockSource ();
    Caculate_OSR_SBR (CLOCK_HZ, BAUD_RATE, &myOSR_SBR);
    LPUART0_Init (&myOSR_SBR);

    ring_buff_init(&myRingBuffer);

    no_error = 1;

    while (no_error)
    {
        if (0 == myRingBuffer.isEmpty)
        {
            ring_buff_pop (&myRingBuffer, &rec);

            switch (rec.result)
            {
            case BAD_FORMAT:
                LPUART0_Write(badFormat, s1);
                no_error = 0;
                break;
            case BAD_RECORD:
                LPUART0_Write(badRecord, s2);
                no_error = 0;
                break;
            case BAD_COUNT:
                LPUART0_Write(badCount, s3);
                no_error = 0;
                break;
            case BAD_CKECKSUM:
                LPUART0_Write(badSum, s4);
                no_error = 0;
                break;
            default:
                LPUART0_Write(success, s5);
            }
        }
    }
}

/* Interrupt when  Receive data buffer full */
void LPUART0_IRQHandler (void)
{
    if (0U == myRingBuffer.isFull) /* Queue not full */
        ring_buff_push(&myRingBuffer); /* Push to queue */
}