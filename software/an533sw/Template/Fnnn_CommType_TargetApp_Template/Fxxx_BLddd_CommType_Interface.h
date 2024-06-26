//-----------------------------------------------------------------------------
// Fxxx_BLddd_CommType_Interface.h
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fxxx_BLddd_CommType_Interface.h
// xxx => Leave as-is; this means the file is compatible with all C8051F devices.
// ddd => Fill-in decimal value of Bootloader Type; The macro 'TGT_BL_TYPE' used
//        in the BL and App InfoBlocks should be defined as this value elsewhere.
//        Note: BL type values 000 and 128 through 255 are reserved for use by 
//        standardized interfaces defined by Silicon Labs; If you make any 
//        modifications to a standardized BL interface, please change the BL type 
//        number to one within the customized range of 001 through 127.
// CommType => Fill-in communication channel type.
// Examples: Fxxx_BL001_BitBang_Interface.h, Fxxx_BL129_CAN_Interface.h, Fxxx_BL128_UART_Interface.h
//
// In a Master project, define "_INCLUDE_MASTER_ONLY_ITEMS_" before including this file.
// In a Target BL/App project, define _INCLUDE_TARGET_ONLY_ITEMS_  before including this file.
// In a Target BL project, define "_INCLUDE_TARGET_BL_ONLY_ITEMS_" before including this file.
// In a Target App project, define "_INCLUDE_TARGET_APP_ONLY_ITEMS_" before including this file.
//
//
// Target:         Any Silicon Labs C8051 MCU
// Tool chain:     Generic
// Command Line:   None
//
//
// Release 1.0 / 01SEP2010 (PKC)
//    -Initial Revision
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#ifndef _FXXX_BLDDD_COMMTYPE_INTERFACE_H_
#define _FXXX_BLDDD_COMMTYPE_INTERFACE_H_

//-----------------------------------------------------------------------------
// Global CONSTANTS - Available to all modules
//-----------------------------------------------------------------------------




//-----------------------------------------------------
// Constants common to Master / Target BL / Target App
//-----------------------------------------------------

// *** Add constants here to be accessed by the Master, Target BL & Target App ***


//---------------------------------------------
// MASTER-only Constants
//---------------------------------------------

#ifdef _INCLUDE_MASTER_ONLY_ITEMS_

// *** Add constants here to be accessed only by the master ***

#endif

//-----------------------------------------------------
// Constants common to Target BL and Target App
//-----------------------------------------------------

#ifdef _INCLUDE_TARGET_ONLY_ITEMS_

// *** Add constants here to be accessed by the target BL & App ***

#endif

//---------------------------------------------
// TARGET BL-only Constants
//---------------------------------------------

#ifdef _INCLUDE_TARGET_BL_ONLY_ITEMS_

// *** Add constants here to be accessed only by the Target BL ***

#endif

//---------------------------------------------
// TARGET App-only Constants
//---------------------------------------------

#ifdef _INCLUDE_TARGET_APP_ONLY_ITEMS_

// *** Add constants here to be accessed only by the Target App ***

//-------------------------------
// Support Function Prototypes
//-------------------------------
void Comm_Init_BL_Support_AddOn (void);
uint8_t Enter_BL_Mode (void);
void Comm_Specific_Support_Function (void); // TODO: Replace with actual function proto

#endif


//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#endif // #ifndef _FXXX_BLDDD_COMMTYPE_INTERFACE_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------