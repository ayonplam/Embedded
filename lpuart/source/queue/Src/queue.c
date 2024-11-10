#include "queue.h"

/*******************************************************************************
* Variables
******************************************************************************/
static const uint8_t full[] = "full buffer\n";

/*!
 * @brief Push data to queue
 *
 * This function push data from receiver DATA register.
 *
 * @param my_buff .
 *
 */
void ring_buff_push (circ_bbuf_t * my_buff)
{
    /* Load data */
    LPUART0_Read((*(my_buff->buffer+my_buff->head)+my_buff->index));

    /* if data = '\n' next new line , increase head */
    if (my_buff->buffer[my_buff->head][my_buff->index] == '\n')
    {
        /* clear empty flag */
        my_buff->isEmpty = 0;

        /* new line */
        my_buff->head++;
        my_buff->index = 0;
        if (my_buff->head >= QUEUE_LEN)
        {
            my_buff->head = 0;
        }

        /* check buffer is full */
        if (my_buff->head == my_buff->tail)
        {
            my_buff->isFull = 1; /* raise full flag */
            LPUART0_Write(full, sizeof(full));
        }
    }
    else
    {
        my_buff->index++;
    }

}

/*!
 * @brief Pop data from queue
 *
 * This function parse a line srec from queue.
 *
 * @param my_buff .
 * @param rec A line is parsed at that time.
 */
void ring_buff_pop (circ_bbuf_t * my_buff, record_t * rec)
{
    /* parse a line */
    *rec = parse_record (my_buff->buffer[my_buff->tail]);

    /* increase tail */
    my_buff->tail++;
    if (my_buff->tail >= QUEUE_LEN)
        {
            my_buff->tail = 0;
        }

    /* check buffer is empty */
    if (my_buff->head == my_buff->tail)
        {
            my_buff->isEmpty = 1; /* raise empty flag */
        }
}

/*!
 * @brief Initialize queue
 *
 * This function Initialize default value.
 *
 * @param my_buff .
 */
void ring_buff_init(circ_bbuf_t *my_buff)
{
    my_buff->head = 0;
    my_buff->tail = 0;
    my_buff->index = 0;
    my_buff->isFull = 0;
    my_buff->isEmpty = 1;
}