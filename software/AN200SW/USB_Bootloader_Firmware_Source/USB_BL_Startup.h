/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_Startup.h
Project  : USB Bootloader (USB_BL)
Created  : 06 JUL 2007 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for the USB Bootloader.

Revision History:

01NOV2012-SHY:
-Add comments for F38x 
 
06JUL2007-PKC:
-Initial revision
-Extracted macros related to USB_BL_STARTUP.A51 from the older USB_BL_Defs.h
******************************************************************************/

#ifndef _USB_BL_STARTUP_H_
#define _USB_BL_STARTUP_H_

// ===========================================================================
// *** Macro Definitions ***
// ===========================================================================

// DEVICE_MODE DEFINES    (Changes should be mirrored in both STARTUP.A51 files)
#define APPLICATION_MODE      0        // Application Mode (Signature verification passed)
#define BOOTLOADER_MODE       1        // Bootloader Mode (Signature verification failed 
                                       // or bootload mode requested)

// ===========================================================================
// *** Global Variables ***
// ===========================================================================
extern volatile bit  data     DEVICE_MODE; // Variable with current device status
                                           // 0 => App FW Mode; 1 => BL Mode
                                           // Defined in USB_BL_STARTUP.A51

// ===========================================================================
// *** Function Prototypes ***
// ===========================================================================

extern void START_APPLICATION(void);   // Function prototype for app's Reset 
                                       // vector entry point
                                       // Defined in USB_BL_STARTUP.A51

#endif                        // _USB_BL_STARTUP_H_

// ===========================================================================
// *** END OF FILE *** USB_BL_Startup.h ***
// ===========================================================================