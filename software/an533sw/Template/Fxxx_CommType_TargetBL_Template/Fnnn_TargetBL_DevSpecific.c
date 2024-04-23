//-----------------------------------------------------------------------------
// Fnnn_TargetBL_DevSpecific.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fnnn_TargetBL_DevSpecific.c
// nnn => Fill-in with the MCU family part number.
// Examples: F50x_TargetBL_DevSpecific.c, F34x_TargetBL_DevSpecific.c
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

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

// ------------------------------------------
// *** Device-Specific *** 
// Change this as necessary based on MCU
// ------------------------------------------
#if BOOTLOADER_PIN_OVERRIDE == 1
SI_SBIT(BL_Override_Pin, SFR_P1, 4);
#endif

// Bit masks for the RSTSRC SFR
#define PORSF  0x02
#define FERROR 0x40

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void);
void PORT_Init (void);

//=============================================================================
// Function Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Disable_Watchdog
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void Disable_Watchdog(void)
{
   // *** Device-Specific *** Change this as necessary based on MCU.
   PCA0MD = ~0x40;
}

//-----------------------------------------------------------------------------
// Disable_Global_Interrupts
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void Disable_Global_Interrupts(void)
{
   // *** Device-Specific *** Change this as necessary based on MCU.
   EA = 0;
}

//-----------------------------------------------------------------------------
// Init_Device
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void Init_Device(void)
{
   OSCILLATOR_Init ();
   PORT_Init ();
   Comm_Init ();

   // *** Add calls to any other init functions here as necessary ***
}

#if BOOTLOADER_PIN_OVERRIDE == 1
//-----------------------------------------------------------------------------
// Check_Override_Pin_State
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
uint8_t Check_Override_Pin_State (void)
{
   // *** Device-Specific *** 
   // Change this as necessary based on MCU / external hardware.
   
   if (BL_Override_Pin == 0)
   {
      return (PIN_ASSERTED);
   }
   else
   {
      return (PIN_DEASSERTED);
   }
}
#endif //#if BOOTLOADER_PIN_OVERRIDE == 1

//-----------------------------------------------------------------------------
// Check_Reset_Source
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
uint8_t Check_Reset_Source (void)
{
   // *** Device-Specific *** 
   // Change this as necessary based on MCU.

   if (((RSTSRC & PORSF) == 0) && ((RSTSRC & FERROR) != 0))
   {
      // If the Power-on/Brown-out flag is NOT set,
      // AND if the Flash Error Reset flag is set,
      // this indicates a bootloader request from application firmware
      return (RESET_APP_REQ);
   }
   else
   {
      return (RESET_NORMAL);
   }
}


//-----------------------------------------------------------------------------
// Reset_MCU
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void Reset_MCU_Now (void)
{
   // *** Device-Specific *** 
   // Change this as necessary based on MCU.

   RSTSRC = 0x12;    // Initiate software reset with vdd monitor enabled   
}

//-----------------------------------------------------------------------------
// OSCILLATOR_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This routine initializes the system clock.
//
//-----------------------------------------------------------------------------
void OSCILLATOR_Init (void)
{
   // *** Device-Specific *** 
   // TODO: Add this based on MCU.
}

//-----------------------------------------------------------------------------
// PORT_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure the Crossbar and GPIO ports.
//
//-----------------------------------------------------------------------------
void PORT_Init (void)
{
   // *** Device-Specific *** 
   // TODO: Add this based on MCU.
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
