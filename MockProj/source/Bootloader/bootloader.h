/*******************************************************************************
* Includes
******************************************************************************/
#ifndef BOOTLOADER_H
#define BOOTLOADER_H

/*!
 * @brief Jump to application
 *
 * This function jump to application at address 0x0000'A000
 *
 */
void jump_to_application (void);

#endif /* BOOTLOADER_H */