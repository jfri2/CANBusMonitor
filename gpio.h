//******************************************************************************
//! @file $RCSfile: gpio.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes for GPIO and eventually any macros,
//!			constants, and/or global variables. 
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************

#ifndef _GPIO_H
#define _GPIO_H

//------------------------------------------------------------------------------
//  @macro can_init
//!
//! This macro
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
#define	SET_BIT(bit, reg)	reg = reg | (1<<bit)

//------------------------------------------------------------------------------
//  @macro can_init
//!
//! This macro
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
#define CLR_BIT(bit, reg)	reg = reg & ~(1<<bit)


//------------------------------------------------------------------------------
//  @macro can_init
//!
//! This macro
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
#define TGL_BIT(bit, reg)	reg = reg ^ (1<<bit)

//------------------------------------------------------------------------------
//  @macro can_init
//!
//! This macro
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
#define CHK_BIT(bit, reg)	((reg >> bit) & 1)

//------------------------------------------------------------------------------
//  @fn can_init
//!
//! This function
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
void gpio_init(void);

#endif /* _MY_CONSOLE_H */
