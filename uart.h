/** @file console.h
 *  @brief Function prototypes for the console driver.
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Harry Q. Bovik (hqbovik)
 *  @author Fred Hacker (fhacker)
 *  @bug No known bugs.
 */

#ifndef _MY_CONSOLE_H
#define _MY_CONSOLE_H

/** @brief Prints character ch at the current location
 *         of the cursor.
 *
 *  If the character is a newline ('\n'), the cursor should
 *  be moved to the next line (scrolling if necessary).  If
 *  the character is a carriage return ('\r'), the cursor
 *  should be immediately reset to the beginning of the current
 *  line, causing any future output to overwrite any existing
 *  output on the line.  If backsapce ('\b') is encountered,
 *  the previous character should be erased (write a space
 *  over it and move the cursor back one column).  It is up
 *  to you how you want to handle a backspace occurring at the
 *  beginning of a line.
 *
 *  @param ch the character to print
 *  @return The input character
 */
void uart_init(uint16_t);

uint8_t checkUartErrorRegister(void);

void uartSendByte(char*);

uint8_t uartGetByte(void);

#endif /* _MY_CONSOLE_H */