//-----------------------------------------------------------------------------
// Fnnn_TargetApp_CommType_BLsupport.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fnnn_TargetApp_CommType_BLsupport.c
// nnn => Fill-in with the MCU family part number.
// CommType => Fill-in Comm interface name.
// Examples: F50x_TargetApp_CAN0_BLsupport.c, F34x_TargetApp_UART0_BLsupport.c
//
// This should typically be added to the application project and 
// included in that build.
// 
// Target Application FW can omit this file from build if 
// BL request via comm interface is not required or if it is implementing this
// functionality using a different mechanism.
//
// Target:         C8051Fxxx (Any Silicon Labs Flash MCU)
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

#include "Fxxx_Target_Config.h"
#include "Fxxx_Target_Interface.h"

#include "Fxxx_TargetApp_Config.h"

#define _INCLUDE_TARGET_ONLY_ITEMS_
#define _INCLUDE_TARGET_APP_ONLY_ITEMS_
#include "Fxxx_BLddd_CommType_Interface.h"  // TODO: Change to actual file name

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

// Reserved space first byte
// *** Device-Specific ***
// TODO: Change this address to point to the first byte in reserved space
#define RESERVED_SPACE_ADDR (63*1024) // 0xFC00

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------


//=============================================================================
// Function Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Comm_Init_AddOn
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//-----------------------------------------------------------------------------
void Comm_Init_BL_Support_AddOn (void)
{
   // *** Comm-Specific / Device-Specific ***
   // TODO: Add code here to initialize the Comm Interface
   // Assume that this will be called from the application's own Comm_Init
   // function where all of the standard comm init will take place.
   
}

//-----------------------------------------------------------------------------
// Enter_BL_Mode
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function will cause a Flash Error Reset to enter BL mode.
//
//-----------------------------------------------------------------------------
uint8_t Enter_BL_Mode (void)
{
   // *** Device-Specific *** Change this as necessary based on MCU.
   // Note: Code-banked devices need additional steps.

   // The return value is just to prevent the compiler from optimizing out
   // the code read

   SI_VARIABLE_SEGMENT_POINTER(codeptr, uint8_t, SI_SEG_CODE);
   codeptr = (uint8_t SI_SEG_CODE *)(RESERVED_SPACE_ADDR);
   
   EA = 0; // Disable global interrupts
   
   return *codeptr; // This will cause a Flash Error Reset
}

//-----------------------------------------------------------------------------
// Comm_Specific_Support_Function
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//-----------------------------------------------------------------------------
void Comm_Specific_Support_Function (void)
{
   // *** Comm-Specific / Device-Specific ***
   // TODO: Add code here as necessary for providing comm-specific support
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
