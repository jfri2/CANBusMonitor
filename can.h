//******************************************************************************
//! @file $RCSfile: can.h,v $
//!
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes for CAN and eventually any macros,
//!			constants, and/or global variables.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//!
//! @version $Revision: 0.00 $ $Name: John Fritz (jfri2) $
//!
//! @todo	Add function def doc, more other doc, add more fns if necessary
//! @bug
//******************************************************************************
#ifndef _CAN_H
#define _CAN_H

/* Baud Rate Settings Check*/
#ifndef F_CPU
	#error 'Define CPU clock frequency (F_CPU)'
#elif (F_CPU == 8000000 || F_CPU == 8000000UL || F_CPU == 8000000L)
#else
	#warning("F_CPU not defined as 8 MHz, CAN baud rate may be incorrect")
#endif

#ifndef CAN_BAUD_RATE_KHz
	#warning "CAN_BAUD_RATE_KHz not defined in config.h"
#endif

#ifndef CAN_TQ_NS
	#warning "CAN_TQ_NS (Time Quantum) not defined in config.h"
#endif
	
	/* Function Prototypes */

/**
 
	8.000 MHz Clock CAN baud rate settings
	(From Table 19-2 in ATmega16M1/32M1/64M1 Datasheet)
	
	CAN Rate	Sampling	TQ		T	T	T	T	T	CANBT1	CANBT2	CANBT3
	(Kbps)		Point		(us)	bit	prs	ph1	ph2	sjw
	------------------------------------------------------------------------
	1000		63%			0.125	8	3	2	2	1	0x00	0x04	0x12	
	500			69%			0.125	16	7	4	4	1	0x00	0x0C	0x36
				75%			0.250	8	3	2	2	1	0x02	0x04	0x13
	250			75%			0.250	16	7	4	4	1	0x02	0x0C	0x37
				75%			0.500	8	3	2	2	1	0x06	0x04	0x13
	200			75%			0.250	20	8	6	5	1	0x02	0x0E	0x4B
				75%			0.625	8	3	2	2	1	0x08	0x04	0x13
	125			75%			0.500	16	7	4	4	1	0x06	0x0C	0x37
				75%			1.000	8	3	2	2	1	0x0E	0x04	0x13
	100			75%			0.625	16	7	4	4	1	0x08	0x0C	0x37
				75%			1.250	8	3	2	2	1	0x12	0x04	0x13
 
 */
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
uint8_t can_init(uint16_t, uint16_t);

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
#ifdef LOGGING_ACTIVE
void checkCANInit(uint8_t);
#endif

#endif /* _CAN_H */
