/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef QUEUE_H
#define QUEUE_H

/*******************************************************************************
* Includes
******************************************************************************/
#include "common.h"
#include "srec.h"

/*******************************************************************************
 * Function Prototype
 ******************************************************************************/

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