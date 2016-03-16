//******************************************************************************
//! @file $RCSfile: timer.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes for timers and eventually any 
//!			macros, constants, and/or global variables.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Lots
//! @bug
//******************************************************************************

#ifndef _TIMER_H
#define _TIMER_H

#ifndef TIMER0_PRESCALE
#warning "Define TIMER0_PRESCALE in config.h"
#elif TIMER0_PRESCALE != 1
#warning "Timer0 Prescalar value not supported. Change prescale value to 1"
#endif

//------------------------------------------------------------------------------
//  @fn timer0_init
//!
//! This function
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
void timer0_init(void);

#endif