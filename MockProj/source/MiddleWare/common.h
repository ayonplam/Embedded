/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef COMMON_H
#define COMMON_H

/*******************************************************************************
 * Macro
 ******************************************************************************/
#define QUEUE_LEN 4 /* Queue has 4 elements */

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

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

#endif