//-----------------------------------------------------------------------------
// Fxxx_TargetBL_Main.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// The main routine for the Target Bootloader Firmware.
//
// 
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



//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
uint8_t Device_Mode = MODE_APP_FW_INVALID;
uint8_t BL_Enabled_Flag = BL_DISABLED;

//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------


//=============================================================================
// Main Routine
//=============================================================================
void main (void)
{
   //---------------------------------------
   // Local Variable Definitions
   //---------------------------------------
   uint8_t cmd_code;

   //---------------------------------------
   // Perform basic MCU initialization
   //---------------------------------------

   Disable_Watchdog();
   Disable_Global_Interrupts();

   //---------------------------------------
   // Check App FW Signature/CRC
   //---------------------------------------

   if (Check_App_FW_Validity() == MODE_APP_FW_VALID)
   {
      Device_Mode = MODE_APP_FW_VALID;
   }
   else
   {
      Device_Mode = MODE_BL;
   }

   //---------------------------------------
   // Check the override pin, if enabled
   //---------------------------------------

   // Check the Bootloader-Override Pin on the device if this feature is enabled
   #if BOOTLOADER_PIN_OVERRIDE == 1
      if (Check_Override_Pin_State() == PIN_ASSERTED)
      {
         // If pin is asserted, enter bootload mode and ignore other conditions.
         Device_Mode = MODE_BL_PIN_REQ;
      }
   #endif

   //---------------------------------------
   // Check the reset source
   //---------------------------------------

   // If the mode has not already been decided by the pin state
   // and if the App FW is valid, check the reset source
   if (Device_Mode == MODE_APP_FW_VALID)
   {
      if (Check_Reset_Source() == RESET_APP_REQ)
      {
         // If the reset was a App BL request, stay in BL mode
         Device_Mode = MODE_BL_APP_REQ;
      }
      else
      {
         // If the reset was not due to a App BL request, jump to the application FW
         Device_Mode = MODE_APP;       // Setting this variable here is not necessary
         START_APPLICATION ();         // Jump to Application FW
      }
   }

   //-------------------------------------------
   // ** BL Mode ** Initialize MCU and Variables
   //-------------------------------------------

   Init_Device();
   Current_Addr.u32 = APP_FW_INFOBLOCK_ADDR;

   //-------------------------------------------
   // Main Loop
   //-------------------------------------------

   while(1)
   {
      // Wait until a command is received
      cmd_code = Comm_Wait_For_Rx_Bytes (TGT_CMD_FIXED_LENGTH, 0);

      if ((cmd_code & 0xF0) == TGT_CMD_WRITE_FLASH_BYTES)
      {
         cmd_code = TGT_CMD_WRITE_FLASH_BYTES; // TGT_Write_Flash command => 0x7y, where = numbytes1[3:0]
      }

      // Process command
      if (cmd_code == TGT_CMD_ENTER_BL_MODE)
      {
         // Will enter BL Mode only if device serial is matched (if that feature is enabled)
         TGT_Enter_BL_Mode ();
         // Will not send any response to any commands until this command has been issued at least once while in bootload mode.
      }
      else if (BL_Enabled_Flag == BL_ENABLED)
      {
         switch (cmd_code)
         {
            case TGT_CMD_GET_INFO:
               TGT_Get_Info ();
               break;
            case TGT_CMD_ERASE_FLASH_PAGE:
               TGT_Erase_Page ();
               break;
            case TGT_CMD_WRITE_SIGNATURE:
               TGT_Write_Signature ();
               break;
            case TGT_CMD_RESET_MCU:
               TGT_Reset_MCU ();
               break;
            case TGT_CMD_GET_PAGE_CRC:
               TGT_Get_Page_CRC ();
               break;
            case TGT_CMD_WRITE_FLASH_BYTES:
               TGT_Write_Flash ();
               break;
            default:
               TGT_Unsupported_Cmd ();
               break;
         }
      }
   }
}


//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
