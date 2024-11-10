/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

/*******************************************************************************
* Includes
******************************************************************************/
#include "driver_lpuart.h"
#include "srec.h"
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Macro
 ******************************************************************************/
#define QUEUE_LEN 4 /* Queue has 4 elements */

/*******************************************************************************
 * Define a new struct or data type
 ******************************************************************************/
/* Struct manage a queue */
typedef struct circ_bbuf_t{
    uint8_t buffer[QUEUE_LEN][256];
    uint16_t head;  /* increase head when push a new line */
    uint16_t tail;  /* increse tail when pop a new line */
    uint16_t index; /* current index in a elemnent */
    bool isFull;    /* flag check queue is full, = 1 */
    bool isEmpty;   /* flag check queue is empty, = 1 */
} circ_bbuf_t;

/*!
 * @brief Push data to queue
 *
 * This function push data from receiver DATA register.
 *
 * @param my_buff .
 *
 */
void ring_buff_push (circ_bbuf_t * my_buff);

/*!
 * @brief Pop data from queue
 *
 * This function parse a line srec from queue.
 *
 * @param my_buff .
 * @param rec A line is parsed at that time.
 */
void ring_buff_pop (circ_bbuf_t * my_buff, record_t * rec);

/*!
 * @brief Initialize queue
 *
 * This function Initialize default value.
 *
 * @param my_buff .
 */
void ring_buff_init(circ_bbuf_t * my_buff);

#endif /* QUEUE_H */