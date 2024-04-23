//-----------------------------------------------------------------------------
// Fxxx_TargetBL_Interface.h
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// [*** TEMPLATE INFORMATION ***]
// Filename: Fxxx_TargetBL_Interface.c - DO NOT change this file name.
// xxx => Leave as-is; this means the file is compatible with all C8051F devices.
//
// Content: Publishes the interface used by the bootloader framework. 
// No changes necessary.
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

#ifndef _FXXX_TARGETBL_INTERFACE_H_
#define _FXXX_TARGETBL_INTERFACE_H_

//-----------------------------------------------------------------------------
// Global CONSTANTS - Available to all modules
//-----------------------------------------------------------------------------

// 'Device Mode' Values:
#define MODE_APP_FW_INVALID   0x00
#define MODE_APP_FW_VALID     0x01
#define MODE_BL               0x02
#define MODE_BL_PIN_REQ       0x03
#define MODE_BL_APP_REQ       0x04
#define MODE_APP              0x05

// 'BL_Enabled_Flag' Values:
#define BL_DISABLED           0x00
#define BL_ENABLED            0x01

// Reset Types [return values for Check_Reset_Source()]
#define RESET_NORMAL    0x01
#define RESET_APP_REQ   0x02

// Check_Override_Pin_State return values
#define PIN_DEASSERTED  0x01
#define PIN_ASSERTED    0x02

//-----------------------------------------------------------------------------
// Enums, Structs, Unions and Typedefs - Available to all modules
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// "Public" Global Variables - Externs - Available to all modules
//-----------------------------------------------------------------------------
extern uint8_t Device_Mode;
extern uint8_t BL_Enabled_Flag;

extern uint8_t Rx_Buf[RX_BUF_LENGTH];
extern uint8_t Tx_Buf[TX_BUF_LENGTH];

extern SI_UU32_t Current_Addr;

extern uint8_t Flash_Key0;
extern uint8_t Flash_Key1;

#if (TGT_CRC_TYPE & 0x80) == 0 // 16-bit CRC
extern uint16_t Running_CRC;
#else // 32-bit CRC
extern uint32_t Runnning_CRC;
#endif

//-----------------------------------------------------------------------------
// "Public" Function Prototypes - Externs - Available to all modules
//-----------------------------------------------------------------------------

// This is usually defined in the STARTUP.A51 file.
void START_APPLICATION(void); 

// ---------------------------------
// Device-Specific Functions
// Defined in "Fnnn_TargetBL_DevSpecific.c"
// ---------------------------------
void Disable_Watchdog(void);
void Disable_Global_Interrupts(void);
uint8_t Check_Reset_Source(void);
void Init_Device(void);
void Reset_MCU_Now(void);

#if BOOTLOADER_PIN_OVERRIDE == 1
uint8_t Check_Override_Pin_State(void);	// [OPTIONAL]
#endif // #if BOOTLOADER_PIN_OVERRIDE == 1

uint8_t Check_App_FW_Validity(void);

// ---------------------------------
// Flash Read/Erase/Write Functions
// Defined in "Fnnn_Flash.c"
// ---------------------------------
#if CODE_BANKING == 0
void FLASH_ByteWrite (uint16_t addr, uint8_t byte);
void FLASH_PageErase (uint16_t addr);
// Note: No flash read function is necessary for non-code banked devices
// (because flash reads are performed directly using a CODE pointer).
#else
void FLASH_ByteWrite (uint32_t addr, uint8_t byte);
void FLASH_PageErase (uint32_t addr);
uint8_t FLASH_ByteRead (uint32_t addr);
#endif // #if CODE_BANKING == 0

// ---------------------------------
// Comm Functions
// Defined in "Fnnn_Comm_*.c"
// Comm-specific interface constants defined in "Fxxx_BLddd_*.h"
// ---------------------------------
void Comm_Init (void);
uint8_t Comm_Wait_For_Rx_Bytes (uint16_t numbytes_to_read, uint16_t rx_buf_index);
void Comm_Send_Tx_Bytes (uint16_t numbytes_to_send);

// ---------------------------------
// CRC Functions
// Defined in "Fxxx_CRCddd_*.c"
// ---------------------------------
void Update_CRC (uint8_t newbyte);

// -------------------------------------
// Bootloader Command Processors
// Defined in "Fxxx_TargetBL_Commands.c"
// -------------------------------------
void TGT_Enter_BL_Mode (void);
void TGT_Get_Info (void);
void TGT_Erase_Page (void);
void TGT_Get_Page_CRC (void);
void TGT_Write_Signature (void);
void TGT_Reset_MCU (void);
void TGT_Write_Flash (void);
void TGT_Unsupported_Cmd (void);

//-----------------------------------------------------------------------------
// Header file include-once preprocessor directive
//-----------------------------------------------------------------------------

#endif // #ifndef _FXXX_TARGETBL_INTERFACE_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
