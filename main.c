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
//! @todo	Lots. Next up: implement CAN, after that implement ADC
//! @bug
//******************************************************************************

/* -- Includes -- */
#include "config.h"

#define DATA_BUFFER_SIZE 8
#define MY_ID 0x11
#define MY_DATA_POS_0 0x79

/* -- Global Variables -- */
uint8_t adcVoltage = 0;
uint8_t canInitFlag;

uint8_t c_status;
uint8_t canDataBuffer[DATA_BUFFER_SIZE];
st_cmd_t message;

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
	canInitFlag = can_init(0);
	logEvent("System initialized can_init returned ");
	printf("%u", canInitFlag);
	
	
	
		
	/************** System Loop **************/	
    while(1) {	
		
		canDataBuffer[0] = MY_ID;
		canDataBuffer[1] = MY_DATA_POS_0;
		
		message.pt_data = &canDataBuffer[0];
		message.ctrl.ide = 0;
		message.dlc = DATA_BUFFER_SIZE;	// bytes of data being sent
		message.id.std = MY_ID;
		message.cmd = CMD_REPLY_MASKED;		// assigned as standard 2.0A reply message object
		
		logEvent("Waiting for MOb to configure...");
		while(can_cmd(&message) != CAN_CMD_ACCEPTED);	// wait for MOb to configure
		logEvent("MOb configured. Waiting for Tx request...");
		while(can_get_status(&message) == CAN_STATUS_NOT_COMPLETED);	// wait for Tx request to come in, then send response
		logEvent("Tx request received, data sent: ");
		printf("%u", canDataBuffer[1]);
		
		/* blink the LED on PORTC7 once per second */
		#ifdef STATUS_LED_ACTIVE
		#ifdef SYSTEM_TIME_ON_TIMER0
		if(LEDBlinkCount >= LED_DELAY_OVF_TIMER0) {
			LEDBlinkCount = 0;
			TGL_BIT(STATUS_LED, STATUS_LED_REG);
		}
		#elsif defined(SYSTEM_TIME_ON_TIMER1)
		if(LEDBlinkCount >= LED_DELAY_OVF_TIMER1) {
			LEDBlinkCount = 0;
			TGL_BIT(STATUS_LED, STATUS_LED_REG);
		}
		#endif		
		#endif
	}
    return 0;
}

void system_init(void) {
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

