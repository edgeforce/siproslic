/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_ISR.h
Project  : USB Bootloader (USB_BL)
Created  : 06 JUL 2007 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for the USB Bootloader.

Revision History:

01NOV2012-SHY:
-Add codes for F38x 
06JUL2007-PKC:
-Initial revision
-Extracted macros related to USB_BL_ISR.c from the older USB_BL_Defs.h
******************************************************************************/

#ifndef _USB_BL_ISR_H_
#define _USB_BL_ISR_H_

// ===========================================================================
// *** Macro Definitions ***
// ===========================================================================

// BULK_PACKET_SIZE, MEM_OUT_PACKET, and MEM_IN_PACKET are defined 
// in "USB_BL_QueueMgmt.h"

// ===========================================================================
// *** Function Prototypes ***
// ===========================================================================
void Handle_In1(void);        // Handle IN packet on Endpoint 1
void Handle_Out2(void);       // Handle OUT packet on Endpoint 2

#endif                        // _USB_BL_ISR_H_

// ===========================================================================
// *** END OF FILE *** USB_BL_ISR.h ***
// ===========================================================================