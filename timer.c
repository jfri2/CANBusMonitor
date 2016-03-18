//******************************************************************************
//! @file $RCSfile: timer.c,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the function definitions for timers.
//!				- Timer0 used for general subsystem polling
//!				
//!				- 8MHz system clock scaled down to clk/1
//!				- Timer0 runs at 8MHz. OVF Period of 32usec.
//!				
//!				- TCNT0 register holds current value of timer
//!				- Available for both read and write operations.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************


#include "timer.h"
#include "gpio.h"


void timer0_init(void) {
#ifdef TIMER0_PRESCALE	
	#if TIMER0_PRESCALE == 1
		/* Set Prescalar to clk/1 */
		SET_BIT(CS00,TCCR0B);
	
		/* Enable Overflow Interrupt */
		SET_BIT(TOIE0, TIMSK0);
	#endif
#endif	
}

void timer1_init(void) {
#ifdef TIMER1_PRESCALE	
	#if TIMER1_PRESCALE == 8
	
		/* Set output compare of timer1 to 1ms match */
		OCR1A = 1000;
		
		/* Set Prescalar to clk/8, enable CTC on OCR1A */
		TCCR1B |= (1<<CS11)|(1<<WGM12);	

		/* Enable Interrupts on match*/
		TIMSK1 |= (1<<OCIE1A);

	#endif	
#endif
}