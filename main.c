/** @file CANBusMonitor.c
 *  @brief An initial CANBusMonitor.c
 *
 *  This file contains the main()
 *  function.
 *
 *  @author John Fritz
 *  @bug Not Finished
 */

/* TODO:: DONE 3_14_2016_9:00PM CST
 * Use #defines and #ifdef's to check for error logging functionality 
 * (currently implemented throughout main, can.c, and uart.c).
 * Think about separating these files into separate source and header
 * files that can be included and used with a simple #define in main.
 */

/* -- Includes -- */
#include "config.h"

/* -- Global Variables -- */
uint8_t adcVoltage = 0;

/* -- ISRs -- */
/* Timer0 overflow ISR now defined in event_logger.h */

/* -- main -- */
int main(void) {			
    /********** System Initilization **********/
	timer0_init();
    gpio_init();	
	uart_init(UART_BAUD_RATE);
	system_init();
	sei();
	logEvent("Beginning CAN initialization...");
	checkCANInit(can_init(CAN_BAUD_RATE_KHz, CAN_TQ_NS));
	
	/************** System Loop **************/	
    while(1) {				
		/* blink the LED on PORTC7 once per second */
		#ifdef STATUS_LED_ACTIVE
		if(LEDBlinkCount >= LED_DELAY_OVF) {
			LEDBlinkCount = 0;
			TGL_BIT(STATUS_LED, STATUS_LED_REG);
		}
		#endif		
	}
    return 0;
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
}