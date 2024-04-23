/******************************************************************************
Copyright (c) 2008, Silicon Laboratories, Inc.

Filename : USB_BL_APP_Shared.h
Project  : USB Bootloader (USB_BL)
Created  : 08 FEB 2008 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for some of the 
components shared between the bootloader firmware and application firmware.

Revision History:

01NOV2012-SHY:	
-Add tempelate to spreadsheet.	
-Generated this full file by spreadsheet.	
08FEB2008-PKC:
-Initial revision
-Generated from USB_BL_Function_Mapping.xls
******************************************************************************/

#ifndef _USB_BL_APP_SHARED_H_
#define _USB_BL_APP_SHARED_H_

// ===========================================================================
// *** Global Variables ***
// ===========================================================================

//******************************************************************************
// Begin externs generated from USB_BL_Function_Mapping.xls
//******************************************************************************

// USB Descriptor locations are declared in USB_BL_APP_*_STARTUP.A51
// The USB Descriptors are defined in USB BL FW's USB_BL_USB_Descriptor.c

extern code const UINT VID;
extern code const UINT PID;
extern code const BYTE MFRSTR[50];
extern code const BYTE PRDSTR[50];
extern code const BYTE MAXPOWER;
extern code const BYTE PWATTRIBUTES;
extern code const UINT BCDDEVICE;
extern code const BYTE SERIAL[12];  // For use by Application FW
extern code const BYTE SERIAL_BL[14];  // For use by Bootloader FW

// Function call to enter bootloader mode
// The function call entry location is declared in USB_BL_APP_*_STARTUP.A51
// Note: This essentially causes a Flash Error Reset to enter bootload mode

extern void BOOTLOAD_REQ (void);

//******************************************************************************
// End generated externs <-
//******************************************************************************

#endif                        // _USB_BL_APP_SHARED_H_

// ===========================================================================
// *** END OF FILE *** USB_BL_APP_Shared.h ***
// ===========================================================================