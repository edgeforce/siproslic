//-----------------------------------------------------------------------------
// Fnnn_Comm_CommType.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fnnn_Comm_CommType.c
// nnn => Fill-in with the MCU family part number.
// CommType => Fill-in Comm interface name.
// Examples: F50x_Comm_CAN0.c, F34x_Comm_UART0.c
//
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

#include "Fxxx_TargetBL_Config.h"
#include "Fxxx_TargetBL_Interface.h"

#define _INCLUDE_TARGET_ONLY_ITEMS_
#define _INCLUDE_TARGET_BL_ONLY_ITEMS_
#include "Fxxx_BLddd_CommType_Interface.h"  // TODO: Change to actual file name

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------


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
// Comm_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
//
//-----------------------------------------------------------------------------
void Comm_Init (void)
{
   // *** Comm-Specific / Device-Specific ***
   // TODO: Add code here to initialize the Comm Interface
}

//-----------------------------------------------------------------------------
// Comm_Wait_For_Rx_Bytes
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//-----------------------------------------------------------------------------
uint8_t Comm_Wait_For_Rx_Bytes (uint16_t numbytes_to_read, uint16_t rx_buf_index)
{
   // *** Comm-Specific / Device-Specific ***
   // TODO: Add code here to read bytes from the comm interface and store them
   // in the "Rx_Buf" buffer (buffer variable defined elsewhere).
   // Use the rx_buf_index as the starting index when loading Rx_Buf.
   // Return the 1st byet of Rx_Buf as the return value.
   // This should be a blocking function; wait until requested number of bytes
   // have been read from the comm interface.

   return (Rx_Buf[0]); // Return the BL command code, which is always at byte0
}

//-----------------------------------------------------------------------------
// Comm_Send_Tx_Bytes
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Send the data in the buffer using the message object. 
//
//-----------------------------------------------------------------------------
void Comm_Send_Tx_Bytes (uint16_t numbytes_to_send)
{
   // *** Comm-Specific / Device-Specific ***
   // TODO: Add code here to write bytes to the comm interface from
   // the "Tx_Buf" buffer (buffer variable defined elsewhere).
   // This should be a blocking function; wait until ALL of the requested number 
   // of bytes have been sent via the comm interface.
}
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
