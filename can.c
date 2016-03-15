/** @file can.c
 *  @brief A CAN driver.
 *
 *  comments go here
 *
 *  @author John Fritz
 *  @bug Not Finished
 */

#include "can.h"
#include "event_logger.c"

uint8_t can_init(uint16_t CANBaudRate_kHz, uint16_t tq_ns) {
	uint8_t errorCode = 0;	
	
	switch(CANBaudRate_kHz) {		
		case 1000:		// 1M baud rate
			if(tq_ns == 125) {
				CANBT1 = 0x00;
				CANBT2 = 0x04;
				CANBT3 = 0x12;
				errorCode = 0;
			} else {
				/* tq_ns not correctly defined for 1M baud rate */
				errorCode = 1;
			}
		break;				
		
		case 500:		// 500k baud rate
			if(tq_ns == 125) {
				CANBT1 = 0x00;
				CANBT2 = 0x0C;
				CANBT3 = 0x36;		
			} else if(tq_ns == 250) {
				CANBT1 = 0x02;
				CANBT2 = 0x04;
				CANBT3 = 0x13;
			} else {
				/* tq_ns not correctly defined for 500k baud rate */
				errorCode = 2;
			}
		break;		
		
		case 250:		// 250k baud rate
			if(tq_ns == 250) {
				CANBT1 = 0x02;
				CANBT2 = 0x0C;
				CANBT3 = 0x37;
			} else if(tq_ns == 500) {
				CANBT1 = 0x06;
				CANBT2 = 0x04;
				CANBT3 = 0x13;
			} else {
				/* tq_ns not correctly defined for 250k baud rate */
				errorCode = 3;
			}
		break;		
		
		case 200:		// 200k baud rate
			if(tq_ns == 250) {
				CANBT1 = 0x02;
				CANBT2 = 0x0E;
				CANBT3 = 0x4B;
			} else if(tq_ns == 625) {
				CANBT1 = 0x08;
				CANBT2 = 0x04;
				CANBT3 = 0x13;
			} else {
				/* tq_ns not correctly defined for 200k baud rate */
				errorCode = 4;
			}
		break;		
		
		case 125:		// 125k baud rate
			if(tq_ns == 500) {
				CANBT1 = 0x06;
				CANBT2 = 0x0C;
				CANBT3 = 0x37;
			} else if(tq_ns == 1000) {
				CANBT1 = 0x0E;
				CANBT2 = 0x04;
				CANBT3 = 0x13;
			} else {
				/* tq_ns not correctly defined for 125k baud rate */
				errorCode = 5;
			}
		break;		
		
		case 100:		// 100k baud rate
			if(tq_ns == 625) {
				CANBT1 = 0x08;
				CANBT2 = 0x0C;
				CANBT3 = 0x37;
			} else if(tq_ns == 1250) {
				CANBT1 = 0x12;
				CANBT2 = 0x04;
				CANBT3 = 0x13;
			} else {
				/* tq_ns not correctly defined for 100k baud rate */
				errorCode = 6;
			}
		break;	
			
		default:
			errorCode = 0xFF;
		break;		
	}
	return(errorCode);
}

void checkCANInitError(uint8_t errorCode) {
	switch(errorCode) {
		case 0:
			/* Do nothing if no error */
		break;
		
		case 1:
			logEvent("ERROR: tq_ns not correctly defined for 1M CAN bus baud rate");
			printf(" expected 125");
		break;
		
		case 2:
			logEvent("ERROR: tq_ns not correctly defined for 500k CAN bus baud rate");
			printf(" expected 125 or 250");
		break;
		
		case 3:
			logEvent("ERROR: tq_ns not correctly defined for 250k CAN bus baud rate");
			printf(" expected 250 or 500");
		break;
		
		case 4: 
			logEvent("ERROR: tq_ns not correctly defined for 200k CAN bus baud rate");
			printf( "expected 250 or 625");
		break;
		
		case 5:
			logEvent("ERROR: tq_ns not correctly defined for 125k CAN bus baud rate");
			printf( "expected 500 or 1000");
		break;
		
		case 6:
			logEvent("ERROR: tq_ns not correctly defined for 100k CAN bus baud rate");
			printf( "expected 625 or 1250");
		break;	
		
		case 0xFF:
			logEvent("ERROR: CAN bus baud rate incorrectly defined");
			printf(" expected 1000, 500, 250, 200, 125, 100");
		break;
		
		default:
			logEvent("ERROR: Unknown CAN initialization error");
		break;			
	}
}