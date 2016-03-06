/** @file gpio.h
 *  @brief Function prototypes for gpio functions.
 *
 *  This contains the prototypes for the gpio 
 *  and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author John Fritz
 *  @bug Not finished.
 */

#ifndef _GPIO_H
#define _GPIO_H

/** @brief Set bit macro
 *
 *  Sets a bit defined by a position in a
 *  register.
 *
 *  @param bit position of bit in register
 *  @param reg register bit is located in
 */
#define	SET_BIT(bit, reg)	reg = reg | (1<<bit)

/** @brief Clear bit macro
 *
 *  Clears a bit defined by a position in a
 *  register.
 *
 *  @param bit position of bit in register
 *  @param reg register bit is located in 
 */
#define CLR_BIT(bit, reg)	reg = reg & ~(1<<bit)


/** @brief Toggle bit macro
 *
 *  Toggles a bit defined by a position in a
 *  register.
 *
 *  @param bit position of bit in register
 *  @param reg register bit is located in 
 */
#define TGL_BIT(bit, reg)	reg = reg ^ (1<<bit)

/** @brief Check the value of a bit macro
 *
 *  Extracts the value of a bit in a register
 *  and returns it. 
 *
 *  @param bit position of bit in register
 *  @param reg register bit is located in 
 *  @return value of bit in register
 */
#define CHK_BIT(bit, reg)	reg = ((reg >> bit) & 1)

/** @brief Initializes GPIO pins of PORTC.
 *
 *  Sets PORTC data direction to output. Sets all
 *  bits in PORTC to low. 
 *
 *  @param None
 *  @return No Return
 */
void gpio_init(void);

#endif /* _MY_CONSOLE_H */