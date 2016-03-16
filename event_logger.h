//******************************************************************************
//! @file $RCSfile: event_logger.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes for the event logger and 
//!			eventually any macros, constants, and/or global variables.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Lots
//! @bug
//******************************************************************************

#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

#ifndef LOGGING_ACTIVE
#warning ("Logging is not active. Define LOGGING_ACTIVE in config.h")
#endif

/* Structs */
typedef struct {
	uint16_t counter;
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint16_t days;
} timeStruct;

/* Variables */
uint16_t LEDBlinkCount = 0; // keeps track of Timer0 overflows
timeStruct systemTime;	


/* Functions */

//------------------------------------------------------------------------------
//  @fn logEvent
//!
//! This function
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
void logEvent(char *);

#endif