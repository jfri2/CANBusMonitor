//******************************************************************************
//! @file $RCSfile: main.c,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief A CAN bus monitor
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Lots. ADC, CAN, merge event_logger and timer files
//! @bug
//******************************************************************************

/* -- Includes -- */
#include "config.h"

#define DATA_BUFFER_SIZE 8
#define MY_CAN_ID 0x012
#define ABORT_ACTIVE

/* -- Global Variables -- */
uint8_t adcVoltage = 0;
uint8_t canInitFlag;

uint16_t countTilAbort = 0;
uint16_t abortCountThreshold = 5000;
uint8_t abortFlag = 0;

uint8_t c_status;
uint8_t canDataBuffer[DATA_BUFFER_SIZE];
st_cmd_t message;

timeStruct oldSystemTime;

/* -- ISRs -- */
/* Timer0 overflow ISR now defined in event_logger.h */

/* -- main -- */
int main(void) {			
    /********** System Initilization **********/
	timer1_init();
    gpio_init();	
	uart_init(UART_BAUD_RATE);
	system_init();
	sei();
	logEvent("Beginning CAN initialization...");
	canInitFlag = can_init(0);
	logEvent("System initialized can_init returned ");
	printf("%u", canInitFlag);
		
		
	/************** System Loop **************/	
    while(1) {			
		
		if(abortFlag == 0) {
			message.pt_data = &canDataBuffer[0];	
			message.dlc = DATA_BUFFER_SIZE;
			message.ctrl.ide = 0;
			message.id.std = MY_CAN_ID;
			message.cmd = CMD_REPLY_MASKED;
			
			if(can_cmd(&message) == CAN_CMD_REFUSED) {
				logEvent("CAN_CMD_REFUSED");
				#ifdef ABORT_ACTIVE
				countTilAbort++;
				if(countTilAbort > abortCountThreshold) {
					/* abort message, try again later */
					abortFlag = 0x01;
					logEvent("CAN ABORT");
					message.cmd = CMD_ABORT;
					can_cmd(&message);
				}
				#endif
			} else {
				c_status = can_get_status(&message);
				switch (c_status) {
					case CAN_STATUS_COMPLETED:
						logEvent("CAN_STATUS_COMPLETED");
						break;
					case CAN_STATUS_NOT_COMPLETED:
						logEvent("CAN_STATUS_NOT_COMPLETED");
						break;
					case CAN_STATUS_ERROR:
						logEvent("CAN_STATUS_ERROR");
						break;	
					default:
						logEvent("Unknown Error, can_get_status returned: ");
						printf("%u", c_status);
						break;
				}
			}
			
		}				
		/* blink the LED on PORTC7 once per second */		
		#ifdef STATUS_LED_ACTIVE
			#ifdef SYSTEM_TIME_ON_TIMER0
				if(LEDBlinkCount >= LED_DELAY_OVF_TIMER0) {
					LEDBlinkCount = 0;
					TGL_BIT(STATUS_LED, STATUS_LED_REG);
				}
			#elif defined(SYSTEM_TIME_ON_TIMER1)
				if(LEDBlinkCount >= LED_DELAY_TIMER1) {
					LEDBlinkCount = 0;
					TGL_BIT(STATUS_LED, STATUS_LED_REG);
				}
			#endif
		#endif		
	}
    return 0;
}

void system_init(void) {
	//PRR = 0x00;   // Individual peripheral clocks enabled
	/* initialize system time to zero */
	systemTime.counter = 0;
	systemTime.milliseconds = 0;
	systemTime.seconds = 0;
	systemTime.minutes = 0;
	systemTime.hours = 0;
	systemTime.days = 0;
	
	printf("\n");
	printf("\n===============================================");
	printf("\n=============== CAN BUS MONITOR ===============");
	printf("\n===============================================");
}
