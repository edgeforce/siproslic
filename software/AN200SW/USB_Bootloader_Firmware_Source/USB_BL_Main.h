/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_Main.h
Project  : USB Bootloader (USB_BL)
Created  : 02 JUN 2004 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for the USB Bootloader.

Revision History:

01NOV2012-SHY:
-Changed BL_VERSION value to 2.12
01NOV2012-SHY:
-Changed BL_VERSION value to 2.11
16AUG2012-SHY:
-Add codes for F38x 
-Changed BL_VERSION value to 2.1
08FEB2008-PKC:
-Changed BL_VERSION value to 2.0
03DEC2007-PKC:
-Changed BL_VERSION value to 1.0
19OCT2007-PKC:
-Changed file name to USB_BL_Main.h from USB_BL_Defs.h.
-Changed BL_VERSION to two bytes and set value to 0.1
06JUL2007-PKC:
-Extracted relevant parts to other header files
17NOV2006-PKC:
-Changed BL_VERSION from 0x01 to 0x06 to indicate beta BL version#
-Added BL commands as macros
14APR2006-PKC:
-Added code to conditionally compile code to set queue sizes
13APR2006-PKC: 
-Reduced Rx/TX queue sizes to accomodate reduced XRAM in 'F326/7
-Added code to selectively compile code to set last app page depending on 
 the microcontroller selected
-Added ifndef statement to prevent multiple inclusion of header file
-Included header file MCU_SELECT.h
13SEP2005-PKC: Changed MEM_TXQUEUE from USBINIT_PARAMETERS_SIZE to 0x0000
******************************************************************************/

#ifndef _USB_BL_MAIN_H_
#define _USB_BL_MAIN_H_

// ===========================================================================
// *** Macro Definitions ***
// ===========================================================================

// Bootloader Version (can be read using 'GetVersion' command).
// Version number is decimal. For example:
//    Version High byte  2
//    Version Low  byte  12
// means version 2.12
// This will be the Device-Bootloader combination's version number
// and can be used by Host SW to determine whether a particular firmware
// version is compatible with this D-BL combo.
#define  BL_VERSION_HIGH   2
#define  BL_VERSION_LOW    12

// This macro enables the pin override feature of the bootloader.
// When enabled, the bootloader will check a pin (P3.0) on reset, and if it
// is grounded, then it will unconditionally enter bootload mode.
// To disable this feature, comment out this macro definition.
#define BOOTLOADER_PIN_OVERRIDE

// System Constants
#define  INTOSC         12000000    // Internal Oscillator frequency (Hz)
#define  SYSCLK         24000000    // SYSCLK frequency (Hz)

// Bit masks for the RSTSRC SFR
#define PORSF  0x02
#define FERROR 0x40

// Other Macros
#define DISABLE_WDT()          PCA0MD &= ~0x40

// ===========================================================================
// *** Structs, Unions, Enums and Typedefs ***
// ===========================================================================

// The BYTE and UINT definitions are also present in "USB_API.h"

// BYTE type definition
#ifndef _BYTE_DEF_
#define _BYTE_DEF_
typedef unsigned char BYTE;
#endif   /* _BYTE_DEF_ */

// UINT type definition
#ifndef _UINT_DEF_
#define _UINT_DEF_
typedef unsigned int UINT;
#endif  /* _UINT_DEF_ */

// ===========================================================================
// *** Function Prototypes ***
// ===========================================================================
void GetDeviceInfo (void);
void WritePage(void);
void SetPage(void);
void ErasePage(void);
void CRConPage(void);
void SW_Reset (void);
void SetFlashKeyCodes (void);
void WriteSignature (void);
UINT UpdateCRC(UINT,BYTE);

#endif                        // _USB_BL_MAIN_H_

// ===========================================================================
// *** END OF FILE *** USB_BL_Main.h ***
// ===========================================================================