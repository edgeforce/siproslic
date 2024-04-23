/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_Interface.h
Project  : USB Bootloader (USB_BL)
Created  : 08 MAY 2007 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for the USB Bootloader.
This file is *shared* between the Bootloader device firmware and PC Software.

Revision History:

01NOV2012-SHY:
-Add definitions for F38x 
-Add  #include "si_toolchain.h" for new USB_API.h
19OCT2007-PKC:
-Updated to add App FW Version code address.
08MAY2007-PKC:
-Initial revision.
******************************************************************************/

#ifndef USB_BL_INTERFACE_H
#define USB_BL_INTERFACE_H

// ===========================================================================
// *** Macro Definitions ***
// ===========================================================================

// ----------------------------------------------------------------------------
// Bootloader Serial String Last Character
// Used by the application and bootloader PC software to determine if a
// USBXpress device is in bootload mode. 
#define BOOTLOADER_MODE_SERIAL_STR_LAST_CHAR	'~'
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Bootloader Commands
#define CMD_GET_DEVICE_INFO   0x00  // "Get Device Info" Command
#define CMD_SET_PAGE          0x01  // "Set Page" Command
#define CMD_ERASE_PAGE        0x02  // "Erase Page" Command
#define CMD_WRITE_PAGE        0x03  // "Write Page" Command
#define CMD_CRC_PAGE          0x04  // "CRC on Page" Command
#define CMD_SW_RESET          0x05  // "Device Reset" Command (Software Reset)
#define CMD_SET_FLASH_KEYS    0x06  // "Set Flash Write/Erase Key Codes" Command
#define CMD_WRITE_SIGNATURE   0x07  // "Write Signature to Flash" Command
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// BL FW <-> SW Protocol Constants
#define COMMAND_OK				0x00
#define COMMAND_FAILED			0x01
#define UNKNOWN_COMMAND       0x02
#define SIGNATURE_NOT_ERASED  0x03
#define FLASH_KEYS_NOT_SET    0x04
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Flash Key Codes (to unlock flash writes and erases)
#ifndef __C51__                        // For BL SW only (if NOT Keil compiler)

// Note: The flash key codes are sent to the BL FW by the BL SW during the
// bootload operation. So, the BL FW does not need access to these macro 
// definitions directly.

// Flash Key Codes valid for 'F32x/'F34x/'F38x devices.
#define FLASH_KEY0		0xA5
#define	FLASH_KEY1		0xF1

#endif

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Location and value of the Validation Signature (16-bit value)
// Any changes to these should be reflected in the PC BL Application
#if defined(__C51__)                   // For BL FW only (Keil compiler)
#define APP_FW_VER_ADDR  ((APP_END_PAGE+1) * PAGE_SIZE) - 4
#define SIGNATURE_ADDR  ((APP_END_PAGE+1) * PAGE_SIZE) - 2
#endif

#define REF_SIGNATURE   0x3DC2         // Reference Validation Signature (for comparison)
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Any changes to the following affect the PC BL Application
// Refer to the FillDeviceVersionInfo() function in the PC BL app

// Device Codes and Descriptions
#define NUM_DEVICECODES	0x06

#define MCU_C8051F320_1		0x81
#define MCU_C8051F326_7		0x82
#define MCU_C8051F34X_32K	0x83
#define MCU_C8051F34X_64K	0x84
#define MCU_C8051F38X_32K	0x85
#define MCU_C8051F38X_64K	0x86

#define MCU_DESC_01	"C8051F320/1 with 16k Flash"
#define MCU_DESC_02	"C8051F326/7 with 16k Flash"
#define MCU_DESC_03	"C8051F34x with 32k Flash"
#define MCU_DESC_04	"C8051F34x with 64k Flash"
#define MCU_DESC_05	"C8051F38x with 32k Flash"
#define MCU_DESC_06	"C8051F38x with 64k Flash"


#define APP_END_PAGE_01 0x1D           // Last application page  (page 29)
#define APP_END_PAGE_02 0x1D           // Last application page  (page 29)
#define APP_END_PAGE_03 0x3E           // Last application page  (page 62)
#define APP_END_PAGE_04 0x7C           // Last application page  (page 124)
#define APP_END_PAGE_05 0x3E           // Last application page  (page 62)
#define APP_END_PAGE_06 0x7C           // Last application page  (page 124)

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Changes to APP_START_PAGE should be mirrored in:
// BL FW's STARTUP.A51 (INTVEC_TABLE)
#define APP_START_PAGE        0x0A     // First application page (page 0A)
#define PAGE_SIZE             0x200    // Pages are 512 bytes long
#define APP_START_ADDR        APP_START_PAGE*PAGE_SIZE
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Max memory size
#ifndef __C51__                        // For BL SW only (if NOT Keil compiler)

// Set this to the maximum value of 63kB (for 'F340) because this needs to be 
// known at compile-time. An array of this size is allocated as "m_Memory" in 
// CUSBBootloaderDlg:public CDialog (USBBootloaderDlg.h)
#define MEMORY_SIZE		63*1024

#endif
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// The following macros are used by the BL firmware:
   // Only one of the following should be defined during compile-time
   // This is done via the Keil compiler command line option DEFINE()
   // See the build batch files for details
   // DEFINE(_C8051F320_1_)
   // DEFINE(_C8051F326_7_)
   // DEFINE(_C8051F34X_32K_)
   // DEFINE(_C8051F34X_64K_)
   // DEFINE(_C8051F38X_32K_)
   // DEFINE(_C8051F38X_64K_)
#if defined(__C51__)                   // For BL FW only (Keil compiler)

   #if defined(_C8051F320_1_)
      #define APP_END_PAGE APP_END_PAGE_01
      #define DEVICE_CODE MCU_C8051F320_1
      #include "si_toolchain.h"
      #include "C8051F320.h"
   #elif defined(_C8051F326_7_)
      #define APP_END_PAGE APP_END_PAGE_02
      #define DEVICE_CODE MCU_C8051F326_7
      #include "si_toolchain.h"
      #include "C8051F326.h"
   #elif defined(_C8051F34X_32K_)
      #define APP_END_PAGE APP_END_PAGE_03
      #define DEVICE_CODE MCU_C8051F34X_32K
      #include "si_toolchain.h"
      #include "C8051F340.h"
   #elif defined(_C8051F34X_64K_)
      #define APP_END_PAGE APP_END_PAGE_04
      #define DEVICE_CODE MCU_C8051F34X_64K
      #include "si_toolchain.h"
      #include "C8051F340.h"
   #elif defined(_C8051F38X_32K_)
      #define APP_END_PAGE APP_END_PAGE_05
      #define DEVICE_CODE MCU_C8051F38X_32K
      #include "si_toolchain.h"
      #include "C8051F380_defs.h"
   #elif defined(_C8051F38X_64K_)
      #define APP_END_PAGE APP_END_PAGE_06
      #define DEVICE_CODE MCU_C8051F38X_64K
      #include "si_toolchain.h"
      #include "C8051F380_defs.h"
   #endif

#endif

// ----------------------------------------------------------------------------

// ===========================================================================
// *** Structs, Unions, Enums and Typedefs ***
// ===========================================================================

#ifndef __C51__                        // For BL SW only (if NOT Keil compiler)

// This structure is used only in the BL SW, but it is declared in this file
// to serve as an easy reference for the BL FW programmer when writing the
// code for the GetDeviceInfo () function in USB_BL_Main.c.

#ifndef DEVICEINFOBLOCK_STRUCT
#define DEVICEINFOBLOCK_STRUCT
// Device Info Block Structure
typedef struct DEVICE_INFO_BLOCK
{
   CString SerialString;  // Not sent by device in response to CMD_GET_DEVICE_INFO
   BYTE	BL_FW_ver_high;
   BYTE	BL_FW_ver_low;
   BYTE	USBX_FWLib_ver_high;
   BYTE	USBX_FWLib_ver_low;
   BYTE  App_FW_ver_high;
   BYTE  App_FW_ver_low;
   UINT	signature;
   BYTE	devCode;
} DEVICE_INFO_BLOCK;
#endif // DEVICEINFOBLOCK_STRUCT

// Note: The SerialString variable is loaded by the BL SW based on a lookup table; 
// See FillDeviceVersionInfo() function definition in BL SW for more info.

// The length of the block returned by the BL FW to the BL SW in response to
// the CMD_GET_DEVICE_INFO command; This excludes the CString in the above
// structure.
#define DEVICE_INFO_BLOCK_RET_LENGTH 9

#endif // __C51__

#endif // USB_BL_INTERFACE_H

// ===========================================================================
// *** END OF FILE *** USB_BL_Interface.h ***
// ===========================================================================