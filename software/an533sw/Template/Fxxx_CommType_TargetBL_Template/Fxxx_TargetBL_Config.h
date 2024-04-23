//-----------------------------------------------------------------------------
// Fxxx_TargetBL_Config.h
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
//
//
// Target:         Any Silicon Labs C8051 MCU
// Tool chain:     Generic
// Command Line:   None
//
//
// Release 1.0 / 01SEP2010 (PKC)
//    -Initial Revision
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#ifndef _FXXX_TARGETBL_CONFIG_H_
#define _FXXX_TARGETBL_CONFIG_H_

//-----------------------------------------------------------------------------
// Global CONSTANTS - Available to all modules
//-----------------------------------------------------------------------------

// ---------------------------------
// General Constants
// ---------------------------------
#define SYSCLK 24000000UL              // SYSCLK frequency in Hz

// ---------------------------------
// Target BL Config Options
// ---------------------------------

#define CODE_BANKING             0     // 0=Disabled;  1=Enabled
#define BOOTLOADER_PIN_OVERRIDE  1     // 0=Disabled;  1=Enabled

#define TGT_BL_FW_INFOBLOCK_LENGTH  16   // See documentation

#define TGT_BL_FW_VERSION_LOW    0x00
#define TGT_BL_FW_VERSION_HIGH   0x01

#define TGT_BL_BUF_SIZE          8     // Size of bootloader RX buffer (bytes)
#define TGT_BL_BUF_SIZE_CODE     0x03  // BL Buffer Size Code: 3; Size = 2^3 = 8 bytes.
                                       // Minimum 8 bytes required; multiples of 8 allowed.
                                       // See documentation for encoding details.

#define TGT_CRC_TYPE             0x40  // CRC Type 064 => CRC-16-CCITT
                                       // bit7=0 => 16-bit CRC; bit7=1 => 32-bit CRC
                                       // => "Fxxx_CRC064_CCITT16.c" should be included

// Specify 24-bit linear addresses here (do not use banked 16-bit addresses)
#define BL_FW_INFOBLOCK_ADDR     0xFCFE   // Points to BL InfoBlock length byte

// Signature Bytes
#define SIG_BYTE0                0x3D
#define SIG_BYTE1                0xC2

// Buffer Lenghts
#define RX_BUF_LENGTH            TGT_BL_BUF_SIZE
#define TX_BUF_LENGTH            ((TGT_BL_FW_INFOBLOCK_LENGTH*2)+2)    // Has to be able to hold Target BL & App Infoblocks PLUS 2 bytes

//-----------------------------------------------------------------------------
// Enums, Structs, Unions and Typedefs - Available to all modules
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// "Public" Global Variables - Externs - Available to all modules
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// "Public" Function Prototypes - Externs - Available to all modules
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#endif // #ifndef _FXXX_TARGETBL_CONFIG_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
