//******************************************************************************
//! @file $RCSfile: config.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains 
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************

#ifndef _CONFIG_H
#define _CONFIG_H

//------------------------------------------------------------------------------
/* Definitions */
//------------------------------------------------------------------------------
#define F_CPU 8000000

#define SYSTEM_TIME_ON_TIMER0			// Enables system time tracking using TIMER0 (timer.h and event_logger.h)
#define STATUS_LED_ACTIVE				// Enables status LED to blink once per second (event_logger.h)
#define LOGGING_ACTIVE					// Enables logging on UART

#define LED_DELAY_OVF			15625	// Number of Timer0 overflows to toggle STATUS_LED
#define DELAY_1SEC_OVF			31250	// Number of Timer0 overflows in 1 second with 8 MHz F_CPU and prescale = clk/1
#define STATUS_LED				PORTC7	// Status LED location in register
#define STATUS_LED_REG			PORTC	// Status LED register
#define TIMER0_PRESCALE			1		// Timer0 prescalar
#define UART_BAUD_RATE			9600	// UART baud rate in Hz
#define CAN_BAUD_RATE_KHz		100		// CAN baud rate in kHz
#define CAN_TQ_NS				625		// CAN Time Quantum in nanoseconds. Smallest discrete timing resolution used by a CAN node

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.c"
#include "timer.c"
#include "uart.c"
#include "can.c"

//------------------------------------------------------------------------------
/* Function Prototypes */
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//  @fn can_init
//!
//! This function
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
void system_init(void);

#endif /* _CANBUSMonitor_H */
