//******************************************************************************
//! @file $RCSfile: gpio.c,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************

#ifndef _GPIO_C
#define _GPIO_C

#include "gpio.h"

void gpio_init(void) {
  DDRC = 0xFF;
  PORTC = 0x00;
}
#endif
