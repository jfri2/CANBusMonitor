//******************************************************************************
//! @file $RCSfile: event_logger.c,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the function definitions for the event logger
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************

#include "event_logger.h"
#include "uart.c"


void logEvent(char *str) {
#ifdef LOGGING_ACTIVE	
#ifdef TIMER0_ACTIVE
	//uartSendByte(13); //ascii carrige return
	printf("\n%03u %02u:%02u:%02u  ", systemTime.days, systemTime.hours, systemTime.minutes, systemTime.seconds);
	printf(str);
#endif	

#ifdef TIMER1_ACTIVE
//uartSendByte(13); //ascii carrige return
printf("\n%03u %02u:%02u:%02u:%u04  ", systemTime.days, systemTime.hours, systemTime.minutes, systemTime.seconds, systemTime.milliseconds);
printf(str);
#endif
#endif
}

ISR(TIMER1_COMPA_vect) {
	#ifdef SYSTEM_TIME_ON_TIMER1
	#ifdef STATUS_LED_ACTIVE
	/* Update LED Flash Counter */
	LEDBlinkCount++;
	#else
	#pragma message("Status LED is not active")
	#endif
	
	/* Update System Time */
	systemTime.milliseconds++;
	if(systemTime.milliseconds >= 1000) {
		systemTime.seconds++;
		systemTime.milliseconds = 0;
		if(systemTime.seconds >= 60) {
			systemTime.minutes++;
			systemTime.seconds = 0;
			if(systemTime.minutes >= 60) {
				systemTime.hours++;
				systemTime.minutes = 0;
				if(systemTime.hours >= 24) {
					systemTime.days++;
					systemTime.hours = 0;
				}
			}
		}
	}
	#else
	#pragma message("System time on timer1 not active")
	#endif
}



ISR(TIMER0_OVF_vect) {
#ifdef SYSTEM_TIME_ON_TIMER0	
	#ifdef STATUS_LED_ACTIVE
	/* Update LED Flash Counter */
	LEDBlinkCount++;
	#else
	#pragma message("Status LED is not active")
	#endif
	
	/* Update System Time */
	systemTime.counter++;
	if(systemTime.counter >= DELAY_1SEC_OVF) {
		systemTime.seconds++;
		systemTime.counter = 0;
		if(systemTime.seconds >= 60) {
			systemTime.minutes++;
			systemTime.seconds = 0;
			if(systemTime.minutes >= 60) {
				systemTime.hours++;
				systemTime.minutes = 0;
				if(systemTime.hours >= 24) {
					systemTime.days++;
					systemTime.hours = 0;
				}
			}
		}
	}
#else
#pragma message("System time on timer0 not active")	
#endif	
}


