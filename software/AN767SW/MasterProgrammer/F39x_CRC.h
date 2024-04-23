//-----------------------------------------------------------------------------
// F39x_CRC.h - SMB_BL - Master_BL_FW
//-----------------------------------------------------------------------------
// Copyright (C) 2009 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// This program performs as the Master for the SMB bootloader.
// PC (Data Source) <--> UART <--> MCU (Master) <--> SMBUS <--> MCU (Target)
//
//
// Target:         C8051F390 
// Tool chain:     Keil C51 9.02 / Keil EVAL C51
// Command Line:   None
//
//
// Release 1.0 / 1Apr2013 (Mark Ding)
//    -Initial Revision
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------
#ifndef F39X_CRC_H
#define F39X_CRC_H

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
U16 Get_Buf_CRC(U8 *ptr, U16 numbytes);
U16 Update_CRC(U16 crc, U8 newbyte);

//-----------------------------------------------------------------------------
// Header File Preprocessor Directive
//-----------------------------------------------------------------------------
#endif

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
