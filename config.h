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

#ifndef _CONFIG_H
#define _CONFIG_H

#define F_CPU 8000000

#define LED_DELAY_OVF			15625	// Number of Timer0 overflows to toggle STATUS_LED
#define DELAY_1SEC_OVF			31250	// Number of Timer0 overflows in 1 second.
#define STATUS_LED				PORTC7	// Status LED location in register
#define STATUS_LED_REG			PORTC	// Status LED register
#define UART_BAUD_RATE			9600	// UART baud rate in Hz
#define CAN_BAUD_RATE_KHz		100		// CAN baud rate in kHz
#define CAN_TQ_NS				625		// CAN propagation delay time in nanoseconds

#define SYSTEM_TIME_ON_TIMER0			// Enables system time tracking using TIMER0 (timer.h and event_logger.h)
#define STATUS_LED_ACTIVE				// Enables status LED to blink once per second (event_logger.h)
#define LOGGING_ACTIVE					// Enables logging on UART

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.c"
#include "timer.c"
#include "uart.c"
#include "can.c"

/* Function Prototypes */
void system_init(void);

#endif /* _CANBUSMonitor_H */