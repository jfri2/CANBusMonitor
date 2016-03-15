/** @file gpio.c
 *  @brief GPIO functions.
 *
 *  Implementation of all basic GPIO
 *  functionality on the ATmega32M1.
 *  
 *
 *  @author John Fritz
 *  @bug Not finished.
 */

#ifndef _GPIO_H
#define _GPIO_H
#include "gpio.h"

void gpio_init(void) {
  DDRC = 0xFF;
  PORTC = 0x00;
}

#endif
