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
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************

#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef TIMER0_ACTIVE
#ifndef TIMER0_PRESCALE
#warning "Define TIMER0_PRESCALE in config.h"
#elif TIMER0_PRESCALE != 1
#warning "Timer0 Prescalar value not supported. Change prescale value to 1 in config.h"
#endif
#endif

#ifdef TIMER1_ACTIVE
#ifndef TIMER1_PRESCALE
#warning "Define TIMER1_PRESCALE in config.h"
#elif TIMER1_PRESCALE != 8
#warning "Timer1 Prescalar value not supported. Change prescale value to 8 in config.h"
#endif
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

//------------------------------------------------------------------------------
//  @fn timer1_init
//!
//! This function
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
void timer1_init(void);

#endif 
