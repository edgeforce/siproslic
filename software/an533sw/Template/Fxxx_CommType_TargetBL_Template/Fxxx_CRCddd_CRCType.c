//-----------------------------------------------------------------------------
// Fxxx_CRCddd_CCITT16.c
//-----------------------------------------------------------------------------
// Copyright (C) 2009 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fxxx_CRCddd_CRCType.c
// xxx => Leave as-is; this means the file is compatible with all C8051F devices.
//        If using a hardware CRC built into a specific MCU, then this can be 
//        optionally filled-in with that MCU family number.
// ddd => Fill-in decimal value of CRC Type; The macro 'TGT_CRC_TYPE' used
//        in the BL and App InfoBlocks should be defined as this value elsewhere.
//        Bit7 (MSB) of the CRC type value indicates if the CRC is 16-bit or 32-bit.
//        ddd[7]: 0 => 16-bit CRC; 1 => 32-bit CRC.
//        Note: CRC type values 000, 064 through 127, and 192 through 207 (bit6 set to 1) 
//        are reserved for use by standardized CRCs defined by Silicon Labs; If you
//        make any modifications to a standardized CRC interface, please change 
//        the CRC type number to one within the customized range of 001 through 63
//        or 128 through 191 (essentially, bit6 cleared to 0).
// CRCType => Fill-in CRC type.
// Examples: Fxxx_CRC001_CustomCRC16.c, Fxxx_CRC128_CustomCRC32.c, Fxxx_CRC064_CCITT16.c
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
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include "Fxxx_SFR_Defs_Wrapper.h"     // This header file will include the
                                       // real MCU register definition file

#include "Fxxx_TargetBL_Config.h"
#include "Fxxx_TargetBL_Interface.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------


//=============================================================================
// Function Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Update_CRC
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// This function accepts a CRC argument and a <newbyte> and returns an
// updated CRC value
//
//-----------------------------------------------------------------------------
void Update_CRC (uint8_t newbyte)
{

   // TODO: Add code here to update CRC
   // Update the global variable "Running_CRC" (defined elsewhere).

}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
