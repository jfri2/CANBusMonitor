#include "event_logger.h"
#include "uart.c"

#ifdef LOGGING_ACTIVE
void logEvent(char *str) {
	//uartSendByte(13); //ascii carrige return
	printf("\n%03u %02u:%02u:%02u  ", systemTime.days, systemTime.hours, systemTime.minutes, systemTime.seconds);
	printf(str);
}
#endif

#ifdef SYSTEM_TIME_ON_TIMER0
ISR(TIMER0_OVF_vect) {
	#ifdef STATUS_LED_ACTIVE
	/* Update LED Flash Counter */
	LEDBlinkCount++;
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
}
#endif