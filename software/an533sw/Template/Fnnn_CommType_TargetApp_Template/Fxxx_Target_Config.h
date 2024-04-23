//-----------------------------------------------------------------------------
// Fxxx_Target_Config.h
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// Configures options that are shared between the target BL & App.
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

#ifndef _FXXX_TARGET_CONFIG_H_
#define _FXXX_TARGET_CONFIG_H_

//-----------------------------------------------------------------------------
// Global CONSTANTS - Available to all modules
//-----------------------------------------------------------------------------

// ------------------------------------------
// Target Config Options (common to BL & App)
// ------------------------------------------

#define TGT_PRODUCT_CODE         0x05  // Company-specific product ID

#define TGT_BL_TYPE              0x81  // BL Type = CAN 
                                       // => "Fxxx_BL129_CAN_Interface.h" should be included.

#define TGT_FLASH_PAGE_SIZE      512   // Number of bytes per flash page
#define TGT_FLASH_PAGE_SIZE_CODE 9     // Code=9 => Page size = 2^9 = 512 bytes.

// Mask to clear out address bits within a page (useful for page boundary check)
// Example: For 512-byte pages, the lower 9 address bits [8:0] represent the bytes within
// a Flash page; so this mask's lower 9 bits would be set => 0x000001FF
#define TGT_FLASH_PAGE_ADDR_MASK 0x000001FF

// Specify 24-bit linear addresses here (do not use banked 16-bit addresses)
#define APP_FW_START_ADDR        0x000600
#define APP_FW_END_ADDR          0x00FBFF

#define APP_FW_SIG0_ADDR         APP_FW_END_ADDR
#define APP_FW_SIG1_ADDR         (APP_FW_END_ADDR-1)
#define APP_FW_INFOBLOCK_ADDR    (APP_FW_END_ADDR-2)   // Points to App InfoBlock length byte

// Target Serial Number Check (for multi-drop buses)
#define DEV_SERIAL_CHECK_ENABLED 1     // 0=Disabled;  1=Enabled.

// ** Ensure a UNIQUE Serial Number for each device on the same bus **
// - These can be set to a fixed value of all 0's for non-bus comm protocols.
// - These are "don't care" if DEV_SERIAL_CHECK_ENABLED is set to 0.
// - These need not be used if device addressing on a bus is handled 
//   at the comm protocol level. 
#define TGT_DEVICE_SERIAL0         0x01     
#define TGT_DEVICE_SERIAL1         0x00        

//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#endif // #ifndef _FXXX_TARGET_CONFIG_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
