/** @file CANBusMonitor.h
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author John Fritz
 *  @bug No known bugs.
 */

#ifndef _CANBusMonitor_H
#define _CANBusMonitor_H

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.c"
#include "timer.c"
#include "uart.c"

#define LED_DELAY_OVF		15625	// Number of Timer0 overflows to toggle STATUS_LED
#define DELAY_1SEC_OVF		31250	// Number of Timer0 overflows in 1 second. 
#define STATUS_LED			PORTC7
#define STATUS_LED_REG		PORTC
#define BAUD_RATE			9600

/* Structs */
typedef struct {
	uint16_t counter;
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint16_t days;
} timeStruct;

#endif /* _CANBUSMonitor_H */