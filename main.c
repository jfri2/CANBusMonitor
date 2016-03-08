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
uint16_t LogBlinkCount = 0;
timeStruct systemTime;

/* ISRs */
ISR(TIMER0_OVF_vect) {
	/* Update LED Flash Counter */
	LEDBlinkCount++;
	LogBlinkCount++;
	
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
    /* initialize timers, gpio, uart, system */
	timer0_init();
    gpio_init();	
	uart_init(BAUD_RATE);
	system_init();

	/* enable global interrupts */
	sei();
		
    while(1) {

		/* blink the LED on PORTC7 once per second, display sys time */
		if(LEDBlinkCount >= LED_DELAY_OVF) {
			LEDBlinkCount = 0;
			TGL_BIT(STATUS_LED, STATUS_LED_REG);
		}
		if(LogBlinkCount >= DELAY_1SEC_OVF) {
			LogBlinkCount = 0;
			logEvent("");
		}
	}
    return 0;
}

void logEvent(char *str) {
	//uartSendByte(13); //ascii carrige return
	printf("\n%02u:%02u:%02u ", systemTime.hours, systemTime.minutes, systemTime.seconds);
	printf(str);	
}

void system_init(void) {
	/* initialize system time to zero */
	systemTime.counter = 0;
	systemTime.seconds = 0;
	systemTime.minutes = 0;
	systemTime.hours = 0;
	systemTime.days = 0;
	
	printf("\n");
	printf("\n===============================================");
	printf("\n=============== CAN BUS MONITOR ===============");
	printf("\n===============================================");
	logEvent("System initialized");
}