/** @file uart.h
 *  @brief Function prototypes for the uart driver.
 *
 *  This contains the prototypes for the uart
 *  driver and eventually any macros, constants,
 *  or global variables needed
 *
 *  @author John Fritz
 *  @bug No known bugs.
 */

#ifndef _UART_H
#define _UART_H

#include <stdio.h>

/** @brief Prints character ch at the current location
 *         of the cursor.
 *
 *
 *  @param ch the character to print
 *  @return The input character
 */

void uart_init(uint16_t);

uint8_t checkUartErrorRegister(void);

void uartSendByte(uint8_t);

uint8_t uartGetByte(void);

void uartSendByteStream(uint8_t, FILE *stream);

uint8_t uartGetByteStream(FILE *stream);

#endif /* _UART_H */