//******************************************************************************
//! @file $RCSfile: uart.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Lots
//! @bug
//******************************************************************************

#ifndef _UART_H
#define _UART_H

#include <stdio.h>

#ifndef UART_BAUD_RATE
#warning "UART_BAUD_RATE not defined in config.h"
#endif

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