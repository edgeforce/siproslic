#pragma OR
/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_USB_Descriptor.c
Project  : USB Bootloader (USB_BL)
Created  : 06 JUL 2004 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the USB Descriptor details that are necessary to call USB_Init().
These variables are shared by the application project.Except for the
Serial string, all the other parameters will remain the same for all
products of the same type.

The compiler directive '#pragma OR' stands for 'ORDER', which directs the
compiler to keep the variables in the file in order in memory, so that they
can be correctly referenced by the application project.

All these constants are absolutely located using the Linker command line
as follows: CODE(?CO?USB_BL_USB_DESCRIPTOR(0xAB6))

Revision History:

01NOV2012-SHY: Add comments for F38x 
08FEB2008-PKC: Reduced the MFR and PRD string lenghts from 100 to 50.
19OCT2007-PKC: Removed "Dev_" prefix from the variable names.
Added 'BOOTLOADER_MODE_SERIAL_STR_LAST_CHAR' macro.
13SEP2005-PKC: Changed MfrStr string from CYGNAL to SILABS

******************************************************************************/

// ===========================================================================
// *** Includes ***
// ===========================================================================
#include "USB_BL_Main.h"
#include "USB_BL_Interface.h"

// ===========================================================================
// *** Global Constants ***
// ===========================================================================

// IMPORTANT: Changes to any of these constant lengths or variable names 
// should be mirrored in the spreadsheet "USB_BL_Function_Mapping.xls".

code const UINT VID          =  0x10C4;
code const UINT PID          =  0xEA61;
code const BYTE MFRSTR[50]  =  {0x0E,0x03,
                                'S',0,'I',0,'L',0,'A',0,'B',0,'S',0};
code const BYTE PRDSTR[50]  =  {0x10,0x03,
                                'U',0,'S',0,'B',0,' ',0,'A',0,'P',0,'I',0};

code const BYTE MAXPOWER     =  15;      // Max current = 30 mA (15 * 2)
code const BYTE PWATTRIBUTES =  0x80;    // Bus-powered, no remote wakeup
code const UINT BCDDEVICE    =  0x100;   // Device release number 1.00

code const BYTE SERIAL[12]   =  {0x0C,0x03,
                                'A',0,'R',0,'5',0,'W',0,'2',0};

code const BYTE SERIAL_BL[14]=  {0x0E,0x03,
                                'A',0,'R',0,'5',0,'W',0,'2',0,
                                 BOOTLOADER_MODE_SERIAL_STR_LAST_CHAR,0};

// Notes: The first byte is the number of characters in the string; 
// More details about the format can be found in Appendix 2 of the
// "USBXpress Development Kit Progammer's Guide".

// The bootloader will use Serial_BL, which is just one additional character
// added as suffix to the Serial used by the application.

// When the user application is active, the SerialString will be "ar5w2"
// When the bootloader is active, the SerialString will be "ar5w2~"

// ===========================================================================
// *** END OF FILE *** USB_BL_USB_Descriptor.c ***
// ===========================================================================