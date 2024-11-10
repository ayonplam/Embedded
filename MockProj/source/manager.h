#ifndef MANAGER_H
#define MANAGER_H

#include <stdbool.h>
#include "queue.h"
#include "srec.h"

/*!
 * @brief Check buffer is empty
 *
 * @return 0: if buffer not empty, 1: if buffer empty
 */
bool buff_isEmpty (void);

/*!
 * @brief Initialize buffer ready to use
 *
 */
void buff_init (void);

/*!
 * @brief Parse a line srec from queue.
 *
 */
void buff_pop (void);

/*!
 * @brief Get result after parse a srec line
 *
 * @return enum returnResult: result after parse a line
 */
Result parse_result (void);

/*!
 * @brief Write to flash
 *
 */
void WrtieFlash (void );

#endif