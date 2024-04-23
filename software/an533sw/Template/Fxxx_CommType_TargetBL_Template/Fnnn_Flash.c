//-----------------------------------------------------------------------------
// Fnnn_Flash.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fnnn_Flash.c
// nnn => Fill-in with the MCU family part number.
// Examples: F50x_Flash.c, F34x_Flash.c
// 
// Note: Typically, the flash primitive functions from application note AN201
// can be used here with minimal modifications. FLASH_ByteRead is needed only
// for code-banked devices.
//
// Note: Scratchpad memory access is NOT supported.
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



//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------


//=============================================================================
// Function Definitions
//=============================================================================

#if CODE_BANKING == 0

//-----------------------------------------------------------------------------
// FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint16_t addr - address of the byte to write to
//   2) uint8_t byte - byte to write to Flash.
//
// This routine writes <byte> to the linear FLASH address <addr>.
//-----------------------------------------------------------------------------

void FLASH_ByteWrite (uint16_t addr, uint8_t byte)
{

   // *** Device-Specific *** 
   // TODO: Add this based on MCU.

   // ** IMPORTANT ** When modifying flash primitive functions to fit in this 
   // template, it is important to remove the literal flash key values and use 
   // the global variables Flash_Key0 and Flash_Key1 instead.   

}

//-----------------------------------------------------------------------------
// FLASH_PageErase
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint16_t addr - address of any byte in the page to erase
//
// This routine erases the FLASH page containing the linear FLASH address
// <addr>.  Note that the page of Flash containing the Lock Byte cannot be
// erased from application code.
//-----------------------------------------------------------------------------

void FLASH_PageErase (uint16_t addr)
{

   // *** Device-Specific *** 
   // TODO: Add this based on MCU.
   
   // ** IMPORTANT ** When modifying flash primitive functions to fit in this 
   // template, it is important to remove the literal flash key values and use 
   // the global variables Flash_Key0 and Flash_Key1 instead.   
   
}

#else

//-----------------------------------------------------------------------------
// FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint32_t addr - linear address of the byte to write to
//   2) uint8_t byte - byte to write to Flash.
//
// This routine writes <byte> to the linear FLASH address <addr>.
//-----------------------------------------------------------------------------

void FLASH_ByteWrite (uint32_t addr, uint8_t byte)
{

   // *** Device-Specific *** 
   // TODO: Add this based on MCU.

   // ** IMPORTANT ** When modifying flash primitive functions to fit in this 
   // template, it is important to remove the literal flash key values and use 
   // the global variables Flash_Key0 and Flash_Key1 instead.      

}

//-----------------------------------------------------------------------------
// FLASH_PageErase
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint32_t addr - linear address of any byte in the page to erase
//
// This routine erases the FLASH page containing the linear FLASH address
// <addr>.  Note that the page of Flash containing the Lock Byte cannot be
// erased from application code.
//-----------------------------------------------------------------------------

void FLASH_PageErase (uint32_t addr)
{

   // *** Device-Specific *** 
   // TODO: Add this based on MCU.

   // ** IMPORTANT ** When modifying flash primitive functions to fit in this 
   // template, it is important to remove the literal flash key values and use 
   // the global variables Flash_Key0 and Flash_Key1 instead.   
   
}

//-----------------------------------------------------------------------------
// FLASH_ByteRead
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) uint32_t addr - linear address of byte to read
//
// This routine reads a byte from the linear FLASH address <addr>.
//-----------------------------------------------------------------------------
uint8_t FLASH_ByteRead (uint32_t addr)
{
   uint8_t retval;

   // *** Device-Specific *** 
   // TODO: Add this based on MCU.

   // ** IMPORTANT ** When modifying flash primitive functions to fit in this 
   // template, it is important to remove the literal flash key values and use 
   // the global variables Flash_Key0 and Flash_Key1 instead.      
   
   return retval;
}

#endif
//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
