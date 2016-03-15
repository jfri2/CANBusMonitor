/** @file can.h
 *  @brief Function prototypes for the CAN driver.
 *
 *  This contains the prototypes for the CAN
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author John Fritz
 *  @bug No known bugs.
 */

#ifndef _CAN_H
#define _CAN_H

/* Baud Rate Settings Check*/
#ifndef F_CPU
	#error 'Define CPU clock frequency (F_CPU)'
#elif (F_CPU == 8000000 || F_CPU == 8000000UL || F_CPU == 8000000L)
#else
	#warning 'F_CPU not defined as 8 MHz, CAN baud rate may be incorrect'
#endif

#ifndef CAN_BAUD_RATE_KHz
	#error 'Define CAN baud rate'
#endif

/* Function Prototypes */
uint8_t can_init(uint16_t, uint16_t);
void checkCANInit(uint8_t);

#endif /* _CAN_H */
