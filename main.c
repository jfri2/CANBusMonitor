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
//! @todo	ADC and CAN out 
//! @bug
//******************************************************************************

/* -- Includes -- */
#include "config.h"

#define DATA_BUFFER_SIZE 8

/* -- Global Variables -- */
uint8_t adcVoltage = 0;
uint8_t canInitFlag;

uint8_t c_status;
uint8_t canDataBuffer[DATA_BUFFER_SIZE];
st_cmd_t message;

uint8_t u8_temp;


/* -- ISRs -- */
/* Timer0 overflow ISR now defined in event_logger.h */

/* -- Function Prototypes -- */
void can_logEvent(st_cmd_t *msg);

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
		/* Init Rx Data */
		message.pt_data = &canDataBuffer[0];
		for(uint8_t i=0; i < DATA_BUFFER_SIZE; i++) {
			canDataBuffer[i] = 0;
		}
		/* Set to Rx Command */
		message.cmd = CMD_RX;
		
		/* Enable Rx */
		while(can_cmd(&message) != CAN_CMD_ACCEPTED);
		
		/* Wait for Rx Complete */
		while(1) {
			u8_temp = can_get_status(&message);
			if(u8_temp != CAN_STATUS_NOT_COMPLETED) break;	// break out of loop
		}
		if(u8_temp == CAN_STATUS_ERROR) break;	// break out of function
		
		//logEvent("CAN Message Received");
		can_logEvent(&message);
		
		if((message.id.ext == 0) || (message.id.std == 0)) {
			logEvent("CAN ERROR Simulation, broke out of loop");
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

void can_logEvent(st_cmd_t *msg) {
	uint8_t indx;
	logEvent("");
	if (msg->ctrl.ide) {
		printf(" RxCAN @ %02X%02X: 0x%08lX(Ext.), L=%d, ", CANSTMH, CANSTML, msg->id.ext, msg->dlc);
		} else {
		printf(" RxCAN @ %02X%02X:      0x%03X(Std.), L=%d, ", CANSTMH, CANSTML, msg->id.std, msg->dlc);
	}
	if (msg->ctrl.rtr) {
		printf("Remote\r\n");
		} else {
		for(indx=0; indx< (msg->dlc-1); indx++) {
			printf ("%02X-", *(msg->pt_data + indx));
		}
		printf ("%02X\r", *(msg->pt_data + indx));
	}
}