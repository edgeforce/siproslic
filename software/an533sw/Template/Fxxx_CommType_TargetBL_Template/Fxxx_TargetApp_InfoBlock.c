//-----------------------------------------------------------------------------
// Fxxx_TargetApp_InfoBlock.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This should be added to the application project and included in that build.
// 
// This should be located at the end of the target application flash area using
// compiler/linker directives.
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

#include "Fxxx_Target_Config.h"
#include "Fxxx_TargetApp_Config.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

/*****************************************
Target App FW InfoBlock Format
Byte offset (from last byte) - Field

0	Signature Byte0 (sig bytes are added by the bootloader after successful programming)
-1	Signature Byte1
-2	InfoBlock Length = 8 (for CAN BL; count includes this length byte)
-3	Product Code
-4	BL Type
-5	Flash Page Size Code
-6	Application FW Version Low (0)
-7	Application FW Version High (1)
-8 Device Serial Number Byte0 (0)
-9 Device Serial Number Byte1 (1)
-10 [OPTIONAL] Add BL-specific bytes here
-11 ...
*****************************************/

SI_SEGMENT_VARIABLE(TGT_App_InfoBlock[], const uint8_t, SI_SEG_CODE) =
{
   // [Optional] Add BL-specific bytes here
   TGT_DEVICE_SERIAL1,
   TGT_DEVICE_SERIAL0,
	TGT_APP_FW_VERSION_HIGH,
	TGT_APP_FW_VERSION_LOW,
	TGT_FLASH_PAGE_SIZE_CODE,
	TGT_BL_TYPE,
	TGT_PRODUCT_CODE,
	TGT_APP_FW_INFOBLOCK_LENGTH
};

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------