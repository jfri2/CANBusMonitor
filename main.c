/** @file CANBusMonitor.c
 *  @brief An initial CANBusMonitor.c
 *
 *  This file contains the main()
 *  function.
 *
 *  @author John Fritz
 *  @bug No known bugs.
 */

/* -- Includes -- */
#include "CANBusMonitor.h"

/* Global Variables */
uint16_t LEDBlinkCount = 0; //keeps track of Timer0 overflows
timeStruct systemTime;
char sendThisByte;

/* ISRs */
ISR(TIMER0_OVF_vect) {
	/* Update LED Flash Counter */
	LEDBlinkCount++;
	
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

/* main */
int main(void) {
	/* initialize system time to zero */
	systemTime.counter = 0;
	systemTime.seconds = 0;
	systemTime.minutes = 0;
	systemTime.hours = 0;
	systemTime.days = 0;
	
	sendThisByte = 0x51;
		
    /* initialize timers and gpio */
	timer0_init();
    gpio_init();	
	uart_init(BAUD_RATE);

	/* enable global interrupts */
	sei();
		
    while(1) {
		/* send one byte continuously over the UART */

		/* blink the LED on PORTC7 once per second */
		if(LEDBlinkCount >= LED_DELAY_OVF) {
			TGL_BIT(STATUS_LED, STATUS_LED_REG);
			LEDBlinkCount = 0;
			printf("\nCurrent System Time: HH:MM:SS is: %2u:%2u:%2u", systemTime.hours, systemTime.minutes, systemTime.seconds);
		}
				
	}
    return 0;
}
