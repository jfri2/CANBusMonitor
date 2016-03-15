#ifndef _EVENT_LOGGER_H
#define _EVENT_LOGGER_H

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
#ifdef LOGGING_ACTIVE
void logEvent(char *);
#endif

#endif