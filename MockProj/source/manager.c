/*******************************************************************************
* Includes
******************************************************************************/
#include "manager.h"
#include "driver_lpuart.h"
#include "flash.h"

/*******************************************************************************
* Variables
******************************************************************************/

/* Variable to store a currently line srec */
static record_t g_rec;

/* Ring Buffer */
static circ_bbuf_t g_myRingBuffer;

/* Address to write at */
static uint32_t offset_add = 0xA000;

volatile int i; /* use for loop */

/*******************************************************************************
* Definition
******************************************************************************/
/*!
 * @brief Check buffer is empty
 *
 * @return 0: if buffer not empty, 1: if buffer empty
 */
bool buff_isEmpty (void)
{
    return g_myRingBuffer.isEmpty;
}

/*!
 * @brief Initialize buffer ready to use
 *
 */
void buff_init (void)
{
    /* Constructor default */
    ring_buff_init(&g_myRingBuffer);

    /* Register callback g_myRingBuffer for driver_lpuart.c */
    RegisterCallVariable(&g_myRingBuffer);

    /* Register callback function ring_buff_push() for driver_lpuart.c */
    RegisterCallback(&ring_buff_push);
}

/*!
 * @brief Parse a line srec from queue.
 *
 */
void buff_pop (void)
{
    ring_buff_pop (&g_myRingBuffer, &g_rec);
}

/*!
 * @brief Get result after parse a srec line
 *
 * @return enum returnResult: result after parse a line
 */
Result parse_result (void)
{
    return g_rec.result;
}

/*!
 * @brief Write to flash
 *
 */
void WrtieFlash (void)
{
    switch (g_rec.type)
    {
    case S1:
    case S2:
    case S3:
        if (0x400 != g_rec.address) /* avoid write at address 0x0000'0400 */
        {
            offset_add = g_rec.address;

            /* Write 32 bit to flash */
            for (i = 0; i < g_rec.count; i+=4)
            {
                /* Disable interrupt before write to flash */
                Disable_LPUART0irq ();
                /* Write to flash 32bit */
                Program_LongWord_8B(offset_add, g_rec.data+i);
                /* Enable interrupt before write to flash */
                Enable_LPUART0irq ();
                /* increase address */
                offset_add+=4;
            }
        }
        break;
    default:
        break;
    }
}
