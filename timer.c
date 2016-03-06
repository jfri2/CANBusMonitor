/**
 * Timer0 used for general subsystem polling
 *
 * 8MHz system clock scaled down to clk/1:
 * Timer0 runs at 8MHz. OVF Period of 32usec.
 *
 * TCNT0 register holds current value of timer
 * Available for both read and write operations. 
 */
#include "timer.h"

#if PRESCALE != 1
#error "Timer0 Prescalar currently set at 1 in timer0_init"
#endif

#if defined(ATmega32M1)
void timer0_init(void) {
	/* Set Prescalar to clk/1 */
	SET_BIT(CS00,TCCR0B);
	
	/* Enable Overflow Interrupt */
	SET_BIT(TOIE0, TIMSK0);
}
#endif

#if defined(ATmega32A)
void timer0_init(void) {
	/* Set Prescalar to clk/1 */
	SET_BIT(CS00,TCCR0);
		
	/* Enable Overflow Interrupt */
	SET_BIT(TOIE0, TIMSK);
}
#endif