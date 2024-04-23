/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_Main.c
Project  : USB Bootloader (USB_BL)
Created  : 02 JUN 2004 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the 'main' function and other function definitions of the USB
Bootloader project.

   Bootloader Commands:

      Get Device Info   - Returns device information (version info)
      Set Page          - Specifes a flash page for following operations
      Erase Page        - Erases the currently selected page
      Write Page        - Writes N bytes of data to currently selected page
      CRC on Page       - Returns 16-bit CRC of currently selected page
      Software Reset    - Causes software reset of device
      Set Flash Keys    - Specifies the Flash Write/Erase key codes
      Write Signature   - Writes the Validation Signature to Flash

Revision History:

01NOV2012-SHY:
-Add codes for F38x 
08FEB2008-PKC:
-Capitalized USB descriptor variable names; Replace USB_BL_USB_Descriptor.h with
USB_BL_APP_Shared.h.
19OCT2007-PKC:
-Made minor changes to code and fixed formatting.
-Added pin-override feature that will force bootload mode by checking a pin on reset.
06JUL2007-PKC:
-Removed "Read Flash Page" command.
-Reorganized the header files.
03MAY2007-PKC:
-Changed "Get Version" command to "Get Device Info".
-Moved CRC function from USB_BL_CRC.c to here.
-Added "Write Signature" command and related changes.
-Added "Set Flash Keys" command and related changes; Improves robustness.
-Disabled "Read Flash Page" command by default.
-Removed "BL_STATUS" and replaced with DEVICE_MODE; Made related changes.
-Modified WritePage() to return CRC after completing page write.
14APR2006-PKC:
-Added new bootloader command "GetDeviceCode" (see switch-case statement)
13APR2006-PKC:
-Included MCU_SELECT.h instead of directly including device header file
-Added code to increase SYSCLK from initial setting to 24 MHz
-Added code to conditionally compile 'disable watchdog' code
24MAR2006-PKC: Updated with USBXpress v2.4 -- Added call to
               USB_Get_Library_Version()
13SEP2005-PKC: Updated with USBXpress v2.3 -- Added call to USB_Clock_Start()

******************************************************************************/

// ===========================================================================
// *** Includes ***
// ===========================================================================
#include "USB_BL_Main.h"
#include "USB_BL_Interface.h"
#include "USB_BL_Startup.h"
#include "USB_BL_QueueMgmt.h"
#include "USB_BL_APP_Shared.h"
#include "USB_API.h"

// ===========================================================================
// *** Global Variables ***
// ===========================================================================
UINT  data  gPageBase;                 // 16-bit addr of lowest byte in a page
BYTE  data  gFlash_Key_Code0;          // Holds Flash Key Code 0
BYTE  data  gFlash_Key_Code1;          // Holds Flash Key Code 1

// ===========================================================================
// *** Main ***
// ===========================================================================
void main (void)
{
   BYTE data command_code;

   #ifndef _C8051F326_7_
   DISABLE_WDT();                       // Disable watchdog timer
   #endif

   VDM0CN = 0x80;                      // Enable VDD Monitor

   // Set VDD Monitor and Missing Clock Detector as reset sources
   // Note: RSTSRC is two registers -- the write is independent of the read
   RSTSRC = 0x06;

   // The DEVICE_MODE bit variable is declared in USB_BL_STARTUP.A51
   // It is used to redirect the USBXpress API ISR to one of these:
   //    1. the USB_API_ISR in the Bootloader FW.
   //    2. the USB_API_ISR in the Application FW.

   // Check the Bootloader-Override Pin on the device if this feature is enabled
   #if defined(BOOTLOADER_PIN_OVERRIDE)
   if ((P3 & 0x01) == 0x00)            // Check P3.0 on 'F320/1/6/7'F34x/'F38x
   {
      // If pin is 0, enter bootload mode and ignore other conditions.
      DEVICE_MODE = BOOTLOADER_MODE;
   }
   else
   {
   #endif

      // The Signature (in Flash) should be valid to allow application FW execution.
      // This is written at the end of the bootloading process by the bootloader.

      if (*(UINT code*)(SIGNATURE_ADDR) != REF_SIGNATURE)
      {
            // If the signature is invalid, force bootloader mode.
            DEVICE_MODE = BOOTLOADER_MODE;
      }
      else
      {
         // Signature is valid; the next step is to check the Reset Source:

         if (((RSTSRC & PORSF) == 0) && ((RSTSRC & FERROR) != 0))
         {
            // If the Power-on/Brown-out flag is NOT set,
            // AND if the Flash Error Reset flag is set,
            // this indicates a bootloader request from application firmware
            DEVICE_MODE = BOOTLOADER_MODE;
         }
         else
         {
            // In all other cases, jump to the application FW
            DEVICE_MODE = APPLICATION_MODE;
            START_APPLICATION();          // Jump to Application FW
         }
      }

   #if defined(BOOTLOADER_PIN_OVERRIDE)
   }
   #endif

   // Initialize Flash Write/Erase Key Codes to zero
   // The actual codes will be set by the BL SW before calling any write/erase commands
   gFlash_Key_Code0 = 0x00;
   gFlash_Key_Code1 = 0x00;

   // Initialize the TX and RX queues
   InitQueues();

   gPageBase = (UINT)(APP_START_PAGE << 9); // convert to 16-bit addr

   // Start the USBXpress API
   USB_Clock_Start();
   USB_Init(VID,PID,MFRSTR,PRDSTR,SERIAL_BL,MAXPOWER,PWATTRIBUTES,BCDDEVICE);
   CLKSEL |= 0x02;                     // Set SYSCLK to 24 MHz

   USB_Int_Enable();

   while(1)                            // Main Command Processor
   {
      command_code = GetNextRxByte();

      switch(command_code)
      {
         case CMD_GET_DEVICE_INFO:
            GetDeviceInfo ();
            break;
         case CMD_SET_PAGE:
            SetPage();
            break;
         case CMD_ERASE_PAGE:
            ErasePage();
            break;
         case CMD_WRITE_PAGE:
            WritePage();
            break;
         case CMD_CRC_PAGE:
            CRConPage();
            break;
         case CMD_SW_RESET:
            SW_Reset();
            break;
         case CMD_SET_FLASH_KEYS:
            SetFlashKeyCodes ();
            break;
         case CMD_WRITE_SIGNATURE:
            WriteSignature ();
            break;
         default:
            EnTxQueue(UNKNOWN_COMMAND);
            SendTxQueue();
            break;
      }
   }
}

// ===========================================================================
// *** Function Definitions ***
// ===========================================================================

void GetDeviceInfo (void)
{
   UINT USBX_FWLib_version;

   // Bootloader Version
   EnTxQueue (BL_VERSION_HIGH);
   EnTxQueue (BL_VERSION_LOW);
   // USBXpress Firmware Library Version
   USBX_FWLib_version = USB_Get_Library_Version ();
   EnTxQueue ((BYTE)(USBX_FWLib_version >> 8));
   EnTxQueue ((BYTE)(USBX_FWLib_version & 0xFF));
   // Application FW Version
   EnTxQueue(*(BYTE code*)(APP_FW_VER_ADDR));
   EnTxQueue(*(BYTE code*)(APP_FW_VER_ADDR+1));
   // CRC or Validation Signature
   EnTxQueue(*(BYTE code*)(SIGNATURE_ADDR));
   EnTxQueue(*(BYTE code*)(SIGNATURE_ADDR+1));
   // Device Code
   EnTxQueue (DEVICE_CODE);
   SendTxQueue ();
}

// ---------------------------------------------------------------------------
// >>> SetPage <<<
//
// Sets the global variable gPageBase. gPageBase is the 16-bit address of the
// first byte of the Flash page.  The content of gPageBase is used as the
// target Flash page for the following operations: ErasePage, WritePage,
// CRConPage and ReadFlashPage
// ---------------------------------------------------------------------------
void SetPage(void)
{
   BYTE page;

   page = GetNextRxByte();   // Get Page Number

   if( (page < APP_START_PAGE) || (page > APP_END_PAGE) )
   {
      // Page is not within write-allowed area!
      EnTxQueue(COMMAND_FAILED);
      SendTxQueue();
   }
   else
   {
      gPageBase = (UINT)(page << 9); // convert to 16-bit addr
      EnTxQueue(COMMAND_OK);
      SendTxQueue();
   }
   return;
}

// ---------------------------------------------------------------------------
// >>> ErasePage <<<
//
// The ErasePage routine enables flash erases, writes a dummy data byte
// to the currently selected flash page and then disables flash erases.
// Note the "address" parameter is of type xdata.  This tricks the compiler
// into using MOVX which is required to write to flash in C8051Fxxx devices.
//
// It is assumed the flash prescaler has been configured properly for the
// current system clock frequency before calling this routine.
// ---------------------------------------------------------------------------
void ErasePage(void)
{
   BYTE xdata * FlashAddress;

   // Flash key codes should be set before ErasePage is called
   if (gFlash_Key_Code0 == 0x00 || gFlash_Key_Code1 == 0x00)
   {
      // Flash key codes have not been set
      EnTxQueue(FLASH_KEYS_NOT_SET);
      SendTxQueue();
      return;
   }

   // Ensure we don't erase the bootloader.  Although bounds checking is
   // performed in the SetPage command, this is just extra security.
   if( (gPageBase < (APP_START_PAGE * PAGE_SIZE)) ||
       (gPageBase > (APP_END_PAGE * PAGE_SIZE))       )
   {
      // Page is not within write-allowed area!
      EnTxQueue(COMMAND_FAILED);
      SendTxQueue();
      return;
   }

   // Erasing page...
   EA = 0;                    // Disable interrupts during erase
   FlashAddress = (BYTE xdata *)gPageBase;
   PSCTL = 0x03;              // enable writes (PSWE) and page erase (PSEE)
   FLKEY = gFlash_Key_Code0;
   FLKEY = gFlash_Key_Code1;              // Flash Key sequence
   VDM0CN = 0x80;             // Enable VDD Monitor
   RSTSRC = 0x06;             // Set VDD Monitor and missing clock detector
                              // as reset sources

   *FlashAddress = 0x00;      // dummy write to page to initiate erase

                              // Erasing done!
   PSCTL = 0x00;              // disable writes and paqe erase
   EA = 1;                    // Enable interrupts

   EnTxQueue(COMMAND_OK);
   SendTxQueue();
   return;
}

// ---------------------------------------------------------------------------
// >>> WritePage <<<
//
// WritePage() programs PAGE_SIZE/2 bytes of data to the currently selected
// Flash page starting at the beginning of the page (lowest address) if
// PageHalf is set to 0x00, or starting at a 256-byte offset from the lowest
// address of the page if PageHalf is set to 0x01.  If gPageBase is valid,
// the Flash write operation is setup and COMMAND_OK is sent back to signal we
// are ready to receive the download.  Once the programming is complete, an
// additional COMMAND_OK is sent to signal the end of the operation.
//
// Note1: This routine writes PAGE_SIZE/2 instead of PAGE_SIZE to reduce the
// required size of the receive buffer (primarily for the sake of 'F326/7
// devices that have lesser RAM compared to 'F320/1 or 'F34x/'F38x)
//
// Note2: At the end of writing the 2nd half of a page, this calls CRConPage
// to reduce the number of commands sent by the PC BL SW.
//
// It is assumed FLASCL is configured appropriately for the system clock.
// ---------------------------------------------------------------------------
void WritePage(void)
{

   UINT i;
   BYTE xdata * FlashAddress;
   BYTE ByteToWrite;
   BYTE pageHalf;

   pageHalf = GetNextRxByte();   // Receive 'PageHalf' indicator

   // Flash key codes should be set before WritePage is called
   if (gFlash_Key_Code0 == 0x00 || gFlash_Key_Code1 == 0x00)
   {
      // Flash key codes have not been set
      EnTxQueue(FLASH_KEYS_NOT_SET);
      SendTxQueue();
      return;
   }
   // Check if the Validation Signature has been erased
   else if (*(UINT code *)(SIGNATURE_ADDR) != 0xFFFF)
   {
      // Validation Signature has not been erased to 0xFFFF
      EnTxQueue(SIGNATURE_NOT_ERASED);
      SendTxQueue();
      return;
   }
   // Ensure we don't erase the bootloader.  Although bounds checking is
   // performed in the SetPage command, this is just extra security.
   else if( (gPageBase < (APP_START_PAGE * PAGE_SIZE)) ||
       (gPageBase > (APP_END_PAGE * PAGE_SIZE))       )
   {
      // Page is not within write-allowed area!
      EnTxQueue(COMMAND_FAILED);
      SendTxQueue();
      return;
   }

   FlashAddress = (BYTE xdata *)gPageBase;              // Start at preset address

   // Second byte of command is the 'PageHalf' indicator
   // 0x00 for first half, 0x01 for second half; other values are invalid.
   if( pageHalf == 0x01 )
   {
      FlashAddress += (UINT)(PAGE_SIZE/2); // Add PAGE_SIZE/2 for second half
   }

   if( (pageHalf & 0xFE) != 0x00 )
   {
      EnTxQueue(COMMAND_FAILED);          // Invalid (if not 0x00 or 0x01)
      SendTxQueue();
   }
   else
   {
      EnTxQueue(COMMAND_OK);
      SendTxQueue();

      // Download to Flash...
      for( i = 0; i < (PAGE_SIZE/2); i++)
      {
         ByteToWrite = GetNextRxByte();   // Get the next byte to
                                          // write to FLASH
         EA = 0;                          // Disable interrupts
                                          // during FLASH write
         FLKEY = gFlash_Key_Code0;
         FLKEY = gFlash_Key_Code1;
         PSCTL = 0x01;                    // enable writes
         VDM0CN = 0x80;                   // enable VDD Monitor
         RSTSRC = 0x06;                   // VDD Monitor and missing clock
                                          // detector set as reset sources
         *FlashAddress++ = ByteToWrite;
         PSCTL = 0x00;                    // disable writes
         EA = 1;                          // reenable interrupts
      }
      EnTxQueue(COMMAND_OK);              // signal end of download
      SendTxQueue();

      if (pageHalf == 0x01)               // If 2nd half of page was written:
      {
         CRConPage ();                    // Return page CRC
      }
   }
   return;
}

// ---------------------------------------------------------------------------
// >>> CRConPage <<<
//
// Returns a 16-bit CRC on the currently selected PAGE_SIZE-byte Flash page.
// The high byte is sent first followed by the lower byte of the CRC.
// No additional response is transmitted.
// ---------------------------------------------------------------------------
void CRConPage(void)
{
   UINT i, CRC;
   BYTE code * data FlashPtr;

   FlashPtr = (BYTE code *)gPageBase;
   CRC = 0x0000;

   // Process each byte in the page into the running CRC
   for( i = 0; i < PAGE_SIZE; i++)
   {
      CRC = UpdateCRC (CRC, *FlashPtr);
      FlashPtr++;
   }

   // Send back the calculated CRC
   EnTxQueue((BYTE)(CRC >> 8));
   EnTxQueue((BYTE)(CRC & 0x00FF));
   SendTxQueue();
   return;
}

// ---------------------------------------------------------------------------
// >>> UpdateCRC <<<
//
// This function accepts a CRC argument and a <newbyte> and returns an
// updated CRC value; Does not use a CRC Lookup Table
// ---------------------------------------------------------------------------
UINT UpdateCRC (UINT crc, BYTE newbyte)
{
   unsigned char i;                    // loop counter

   #define POLY 0x8408                 // CRC16-CCITT FCS (X^16+X^12+X^5+1)

   crc = crc ^ newbyte;

   for (i = 0; i < 8; i++)
   {
      if (crc & 0x01)
      {
         crc = crc >> 1;
         crc ^= POLY;
      }
      else
      {
         crc = crc >> 1;
      }
   }
   return crc;
}


// ---------------------------------------------------------------------------
// >>> SetFlashKeyCodes <<<
//
// Receives and sets the Flash Key Codes in a global variable
// ---------------------------------------------------------------------------
void SetFlashKeyCodes (void)
{
   gFlash_Key_Code0 = GetNextRxByte ();
   gFlash_Key_Code1 = GetNextRxByte ();

   EnTxQueue (COMMAND_OK);
   SendTxQueue ();
   return;
}

// ---------------------------------------------------------------------------
// >>> WriteSignature <<<
//
// Writes the Validation Signature to Flash at the last two bytes of application
// firmware space
// ---------------------------------------------------------------------------
void WriteSignature (void)
{
   BYTE xdata * FlashAddress = SIGNATURE_ADDR;
   BYTE data signature_buf[2];
   BYTE i;

   signature_buf[0] = GetNextRxByte ();
   signature_buf[1] = GetNextRxByte ();

   // Check if the Validation Signature has been erased using ErasePage
   if (*(UINT code *)(SIGNATURE_ADDR) != 0xFFFF)
   {
      // Validation Signature has not been erased to 0xFFFF
      EnTxQueue(SIGNATURE_NOT_ERASED);
      SendTxQueue();
      return;
   }

   EA = 0;                             // Disable interrupts
                                       // during FLASH write
   for (i = 2; i > 0; i--)
   {
      FLKEY = gFlash_Key_Code0;
      FLKEY = gFlash_Key_Code1;      // Set Flash Key Codes

      PSCTL = 0x01;                    // enable writes
      VDM0CN = 0x80;                   // enable VDD Monitor
      RSTSRC = 0x06;                   // VDD Monitor and missing clock
                                       // detector set as reset sources
      *FlashAddress++ = signature_buf[i-1];

      PSCTL = 0x00;                    // disable writes
   }

   EA = 1;                          // reenable interrupts

   EnTxQueue (COMMAND_OK);
   SendTxQueue ();
   return;
}

// ---------------------------------------------------------------------------
// >>> SW_Reset <<<
//
// Causes Software Reset with VDD Monitor Enabled
// ---------------------------------------------------------------------------
void SW_Reset (void)
{
   RSTSRC = 0x12;    // cause software reset with vdd monitor enabled

   // the following functions are never called in the bootloader; But they are
   // present here so that the compiler includes them in the BL build from the
   // USBX Library, thus allowing the application FW to make calls to them.
   USB_Disable();
   USB_Int_Disable();
}

// ===========================================================================
// *** END OF FILE *** USB_BL_Main.c ***
// ===========================================================================