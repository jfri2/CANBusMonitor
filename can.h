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

//------------------------------------------------------------------------------
/* Definitions */
//------------------------------------------------------------------------------

/* CANSTMOB CAN MOB STatus register masks */
#define CAN_MOb_MSK_DLC_ERR		(1<<DLCW)		// CAN Message Object CHecK MaSK Data Length Code ERRor (warning, not error)
#define CAN_MOb_MSK_TX_ERR		(1<<TXOK)		// CAN Message Object CHecK MaSK Transmit ERRor
#define CAN_MOb_MSK_RX_ERR		(1<<RXOK)		// CAN Message Object CHecK MaSK Receive ERRor
#define CAN_MOb_MSK_BIT_ERR		(1<<BERR)		// CAN Message Object CHecK MaSK BIT ERRor (only in transmission)
#define CAN_MOb_MSK_BSTF_ERR	(1<<SERR)		// CAN Message Object CHecK MaSK Bit STuFfing ERRor
#define CAN_MOb_MSK_CRC_ERR		(1<<CERR)		// CAN Message Object CHecK MaSK Cyclic Redundancy Check ERRor
#define CAN_MOb_MSK_FORM_ERR	(1<<FERR)		// CAN Message Object CHecK MaSK FORM ERRor (CRC delimiter, ack delimiter, EOF)
#define CAN_MOb_MSK_ACK_ERR		(1<<AERR)		// CAN Message Object CHecK MaSK ACKnowledgment ERRor

/* CAN_MOb_CONFIG_Reg Configuration Options */
#define MOb_OPMode		0	// Message Object OPerating Mode (Position 0 in configuration register)
#define MOb_

//------------------------------------------------------------------------------
/* Macros */
//------------------------------------------------------------------------------

/* Baud Rate Settings Checks*/
#ifndef F_CPU
#	error 'Define CPU clock frequency (F_CPU)'
#elif (F_CPU == 8000000 || F_CPU == 8000000UL || F_CPU == 8000000L)
#else
#	warning("F_CPU not defined as 8 MHz, CAN baud rate may be incorrect")
#endif
#ifndef CAN_BAUD_RATE_KHz
#	warning "CAN_BAUD_RATE_KHz not defined in config.h"
#endif
#ifndef CAN_TQ_NS
#	warning "CAN_TQ_NS (Time Quantum) not defined in config.h"
#endif

/* CANGCON CAN General CONtrol register macros */
#define CAN_RESET()			CANGCON = (1<<SWRES)								// CAN only software reset
#define CAN_ENABLE()		SET_BIT(ENASTB, CANGCON)							// CAN enable
#define CAN_DISABLE()		CLR_BIT(ENASTB, CANGCON)							// CAN standby
#define CAN_ABORT()			SET_BIT(ABRQ, CANGCON); CLR_BIT(ABRQ, CANGCON)		// CAN abort (toggle abort request)
#define CAN_SEND_OVRLD()	SET_BIT(OVRQ, CANGCON)								// CAN send OVeRLoaD frame (traced in CANGSTA reg, bit OVFG)

/* CANGSTA CAN General STAtus register macros */
#define CAN_CHK_TX_BSY()		CHK_BIT(TXBSY, CANGSTA)		// Return 0 if TX free, return 0b00010000 if busy
#define CAN_CHK_RX_BSY()		CHK_BIT(RXBSY, CANGSTA)		// Return 0 if RX free, return 0b00001000 if busy
#define CAN_CHK_OVLD()			CHK_BIT(6, CANGSTA)			// Return 0 if no overload frame, return 0b01000000 if overload frame sent
#define CAN_CHK_EN()			CHK_BIT(ENFG, CANGSTA)		// Return 0 if CAN controller disabled, 0b00000100 if enabled
#define CAN_CHK_BUS()			CHK_BIT(BOFF, CANGSTA)		// Return 0 if no bus off mode, 0b00000010 if bus off mode
#define CAN_CHK_ERR_PASS()		CHK_BIT(ERRP, CANGSTA)		// Return 0 if no error passive mode, 1 if error passive mode

/* CAN Error Counter Check and Reset macros */
#define CAN_CHK_RX_ERR_CNT()	CANREC			// CAN CHecK Receive ERRor CouNTer
#define CAN_RST_RX_ERR_CNT()	CANREC = 0x00	// CAN ReSeT Receive ERRor CouNTer
#define CAN_CHK_TX_ERR_CNT()	CANTEC			// CAN CHecK Transmit ERRor CouNTer
#define CAN_RST_TX_ERR_CNT()	CANTEC = 0x00	// CAN ReSeT Transmit ERRor CouNTer

/* CAN Check MOb macros */
#define CAN_CHK_MOb_0()		CHK_BIT(ENMOB0, CANEN2)		// Returns 0 if MOb is available for new Tx or Rx, 0b00000001 if busy
#define CAN_CHK_MOb_1()		CHK_BIT(ENMOB1, CANEN2)		// Returns 1 if MOb is available for new Tx or Rx, 0b00000010 if busy
#define CAN_CHK_MOb_2()		CHK_BIT(ENMOB2, CANEN2)		// Returns 2 if MOb is available for new Tx or Rx, 0b00000100 if busy
#define CAN_CHK_MOb_3()		CHK_BIT(ENMOB3, CANEN2)		// Returns 3 if MOb is available for new Tx or Rx, 0b00001000 if busy
#define CAN_CHK_MOb_4()		CHK_BIT(ENMOB4, CANEN2)		// Returns 4 if MOb is available for new Tx or Rx, 0b00010000 if busy
#define CAN_CHK_MOb_5()		CHK_BIT(ENMOB5, CANEN2)		// Returns 5 if MOb is available for new Tx or Rx, 0b00100000 if busy


//------------------------------------------------------------------------------
/* Global Variables */
//------------------------------------------------------------------------------
uint8_t CAN_MOb_CONFIG_Reg = 0x00;				// Message Object CONFIGuration Register

//------------------------------------------------------------------------------
/* Function Prototypes */
//------------------------------------------------------------------------------

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
//  @fn can_SetFixedBaudRate
//!
//! This function 
//!
//! @warning none.
//!
//! @param none.
//!
//! @return none.
//!
uint8_t can_SetFixedBaudRate(uint16_t, uint16_t);

//------------------------------------------------------------------------------
//  @fn can_CheckBaudRateErrors
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
void can_CheckBaudRateError(uint8_t);
#endif

//------------------------------------------------------------------------------
//  @fn can_ConfigureChannel
//!
//! This function
//!
//! @warning none.
//!
//! @param	mode
//!				==0: Enabled mode
//!				==1: Standby mode
//!				==2: Listening mode
//!			errorState
//!				==0: Error active (default)
//!				==1: Error passive
//!				==2: Bus Off
//!
//! @return errorFlag
//!				==0: No errors
//!				==1: Invalid mode parameter
//!				==2: Invalid errorState parameter
//!				==3: Invalid mode and errorState parameters
//!
uint8_t can_ConfigureChannel(uint8_t, uint8_t);

//------------------------------------------------------------------------------
//  @fn can_ConfigureMOb
//!
//! This function
//!
//! @warning none.
//!
//! @param	MOb_Number
//!				==0: MOb0
//!				==1: MOb1
//!				==2: MOb2
//!				==3: MOb3
//!				==4: MOb4
//!				==5: MOb5
//!			errorState
//!				==0: Error active (default)
//!				==1: Error passive
//!				==2: Bus Off
//!
//! @return errorFlag
//!				==0: No errors
//!				==1: Invalid MOb number
//!
uint8_t can_ConfigureMOb(uint8_t);

#endif /* _CAN_H */