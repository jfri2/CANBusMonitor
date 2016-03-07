/** @file uart.c
 *  @brief A console driver.
 *
 *  These empty function definitions are provided
 *  so that stdio will build without complaining.
 *  You will need to fill these functions in. This
 *  is the implementation of the console driver.
 *  Important details about its implementation
 *  should go in these comments.
 *
 *  @author John Fritz
 *  @bug No know bugs.
 *
 *  LINDAT register is uart data register.
 *  LINCR register is lin/uart control register
 *  LINSIR register is LIN status and interrupt register
 *  LINENIR register is LIN enable interrupt register
 *  LINERR register is LIN error register
 *  LINBTR is LIN bit timing register
 *  LINBRR is lin baud rate regiseter
 */
#include "uart.h"
#include "gpio.h"

void uart_init(uint16_t baudRate) {
	/* set uart no parity, 8 data bits, 1 stop bit */
	/* enable lin/uart */
	/* UART Rx and Tx Byte Enable */
	LINCR = 0b00001111;
		
	/* Enable error, transmit performed, recieve performed interrupts */
	//LINENIR |= (1<<LENERR)|(1<<LENTXOK)|(1<<LENRXOK);
		
	/* set baud rate in LINBRR register */	
	/* baud rate is scaled clk / value */
	//baudDivider = (uint16_t)((F_CPU / ((LINBTR & 0b00011111) * baudRate )) - 1);
	LINBRRH = (((F_CPU/baudRate)/32)-1)>>8;
	LINBRRL = (((F_CPU/baudRate)/32)-1);
}

uint8_t checkUartErrorRegister(void) {
	/* Bitmask error register to get specific error
	 * 
	 * No errors: returns 0
	 * Bit7: Abort Flag
	 * Bit6: Frame_time_out error flag
	 * Bit5: Overrun error flag
	 * Bit4: Framing error flag
	 * Bit3: Sync error flag
	 * Bit2: Parity error flag
	 * Bit1: Checksum error flag
	 * Bit0: Bit error flag
	 */
	return LINERR;
}

void uartSendByte(char data) {
	while((LINSIR & (1<<LBUSY)) != 0);	// wait until uart is not busy
	LINDAT = data;	// put data into register to be sent out
}

uint8_t uartGetByte(void) {
	while((LINSIR & (1<<LBUSY)) != 0);	// wait until uart is not busy
	return(LINDAT);	// return data from LINDAT register	
}