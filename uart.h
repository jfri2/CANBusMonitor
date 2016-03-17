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
//! @todo	Add function prototype documentation. Add more functions if necessary
//! @bug
//******************************************************************************

#ifndef _UART_H
#define _UART_H

#include <stdio.h>

#ifndef UART_BAUD_RATE
#warning "UART_BAUD_RATE not defined in config.h"
#endif

void uart_init(uint16_t);

uint8_t uart_checkErrorRegister(void);

void uart_SendByte(uint8_t);

uint8_t uart_GetByte(void);

void uart_SendByteStream(uint8_t, FILE *stream);

uint8_t uart_GetByteStream(FILE *stream);

#endif /* _UART_H */
