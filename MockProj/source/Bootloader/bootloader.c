/*******************************************************************************
* Includes
******************************************************************************/
#include "bootloader.h"
#include "MKE16Z4.h"

/*******************************************************************************
* MACRO
******************************************************************************/
#define OFFSET_VECTOR_TABLE (0xA000 << 7)
#define stackPointer *((uint32_t*)(0xA000))
#define vector_table 0xA000

/*******************************************************************************
* Definition
******************************************************************************/
/*!
 * @brief Jump to application
 *
 * This function jump to application at address 0x0000'A000
 *
 */
void jump_to_application (void)
{
    /* Create the function call to the user application. */
    uint32_t JumpAddress = *((volatile uint32_t*) (vector_table + 4));

    /* Set the VTOR to the application vector table address. */
    SCB->VTOR = (uint32_t)OFFSET_VECTOR_TABLE;

    /* Set stack pointers to the application stack pointer. */
    __set_MSP(stackPointer);

    /* Set pointer Reset_Handler */
    void (*Reset_Handler)(void) = (void (*) (void))(JumpAddress);
    Reset_Handler();
}