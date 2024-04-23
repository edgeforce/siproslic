//-----------------------------------------------------------------------------
// Fxxx_TargetBL_Commands.c
//-----------------------------------------------------------------------------
// Copyright (C) 2010 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// 
//
// How To Test:
//
// 
//
//
// Target:         C8051Fxxx (Any Silicon Labs Flash MCU)
// Tool chain:     Generic
// Command Line:   None
//
//
// Release 1.0 / 01SEP2010 (PKC)
//    -Initial Revision
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include "Fxxx_SFR_Defs_Wrapper.h"     // This header file will include the
                                       // real MCU register definition file

#include "Fxxx_Target_Config.h"
#include "Fxxx_Target_Interface.h"

#include "Fxxx_TargetBL_Config.h"
#include "Fxxx_TargetBL_Interface.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
uint8_t Rx_Buf[RX_BUF_LENGTH];
uint8_t Tx_Buf[TX_BUF_LENGTH];

SI_UU32_t Current_Addr;

uint8_t Flash_Key0 = 0;
uint8_t Flash_Key1 = 0;

#if (TGT_CRC_TYPE & 0x80) == 0 // 16-bit CRC
uint16_t Running_CRC;
#else // 32-bit CRC
uint32_t Runnning_CRC;
#endif

//-----------------------------------------------------------------------------
// Function Prototypes (Local)
//-----------------------------------------------------------------------------


//=============================================================================
// Function Definitions
//=============================================================================

//-----------------------------------------------------------------------------
// Check_App_FW_Validity - Check Signature
//-----------------------------------------------------------------------------
//
// Return Value:  uint8_t - returns value indicating if the App FW is valid.
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
uint8_t Check_App_FW_Validity (void)
{
   uint8_t retval = MODE_APP_FW_INVALID;

   #if CODE_BANKING == 0
   SI_VARIABLE_SEGMENT_POINTER(codeptr, uint8_t, SI_SEG_CODE);

   codeptr = (uint8_t SI_SEG_CODE *)(APP_FW_SIG0_ADDR);

   // The Signature (in Flash) should be valid to allow application FW execution.
   // This is written at the end of the bootloading process by the bootloader.
   if (*codeptr-- == SIG_BYTE0)
   {
     if (*codeptr-- == SIG_BYTE1)
     {
         // All signature bytes match.
         retval = MODE_APP_FW_VALID;
      }
   }
   #else
   if (FLASH_ByteRead(APP_FW_SIG0_ADDR) == SIG_BYTE0)
   {
     if (FLASH_ByteRead(APP_FW_SIG0_ADDR-1) == SIG_BYTE1)
     {
         // All signature bytes match.
         retval = MODE_APP_FW_VALID;
      }
   }   
   #endif // #if CODE_BANKING == 0

   return (retval);
}

//-----------------------------------------------------------------------------
// TGT_Enter_BL_Mode
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Enter_BL_Mode (void)
{
   // Command Format:
   // [0] Command
   // [1] dev_addr0
   // [2] dev_addr1

   // Response:
   // [0] Response code (ACK only; Do not send NACK/ERROR)
   
   #if DEV_SERIAL_CHECK_ENABLED == 1   
   if ((Rx_Buf[1] == TGT_DEVICE_SERIAL0) && (Rx_Buf[2] == TGT_DEVICE_SERIAL1))  
   #endif
   {
      BL_Enabled_Flag = BL_ENABLED;   
      Tx_Buf[0] = TGT_RSP_BL_MODE;
      Comm_Send_Tx_Bytes (1);
   }
}

//-----------------------------------------------------------------------------
// TGT_Get_Info
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Get_Info (void)
{
   // Command Format:
   // [0] Command

   // Response:
   // [0] Response code (ACK/ERROR etc)
   // [1] Numbytes (does not count response code, but includes numbytes itself; = BL infoblock lenght + App infoblock length - 1)
   // [2] BL InfoBlock byte0
   // [3] BL InfoBlock byte1
   // [4] ...
   // [5] App InfoBlock byte0 (the app infoblock length is not repeated here)
   // [6] App InfoBlock byte1
   // [7] ...

   uint8_t numbytes;
   uint8_t i;
   uint8_t index;
   
   #if CODE_BANKING == 0   
   SI_VARIABLE_SEGMENT_POINTER(codeptr, uint8_t, SI_SEG_CODE);
      
   codeptr = (uint8_t SI_SEG_CODE *)(BL_FW_INFOBLOCK_ADDR);
   numbytes = *codeptr;
   codeptr--;
   #else   
   numbytes = FLASH_ByteRead (BL_FW_INFOBLOCK_ADDR);
   #endif   

   Tx_Buf[0] = TGT_RSP_OK;
   Tx_Buf[1] = numbytes; // Will add App InfoBlock length below...
    
   index = 2;
   
   for (i = 0; i < (numbytes-1); i++)
   {
      #if CODE_BANKING == 0
      Tx_Buf[index++] = *codeptr;
      codeptr--;
      #else
      Tx_Buf[index++] = FLASH_ByteRead (BL_FW_INFOBLOCK_ADDR-1-i);
      #endif
   }

   #if CODE_BANKING == 0     
   codeptr = (uint8_t SI_SEG_CODE *)(APP_FW_INFOBLOCK_ADDR);
   numbytes = *codeptr;
   codeptr--;
   #else   
   numbytes = FLASH_ByteRead (APP_FW_INFOBLOCK_ADDR);
   #endif   

   Tx_Buf[1] += (numbytes-1); // Add App InfoBlock length to BL InfoBlock Length (subtract one because we are not using a separate byte for the app FW numbytes value).
     
   for (i = 0; i < (numbytes-1); i++)
   {
      #if CODE_BANKING == 0
      Tx_Buf[index++] = *codeptr;
      codeptr--;
      #else
      Tx_Buf[index++] = FLASH_ByteRead (APP_FW_INFOBLOCK_ADDR-1-i);
      #endif
   }

   Comm_Send_Tx_Bytes (index);
}

//-----------------------------------------------------------------------------
// TGT_Erase_Page
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Erase_Page (void)
{
   // Command Format:
   // [0] Command
   // [1] flash key code0
   // [2] flash key code1
   // [3] addr0 (LSB)
   // [4] addr1
   // [5] addr2
   // [6] addr3 (MSB)
   // [7] RESERVED

   // Response:
   // [0] Response code

   SI_UU32_t addr;

   addr.u8[b0] = Rx_Buf[3];
   addr.u8[b1] = Rx_Buf[4];
   addr.u8[b2] = Rx_Buf[5];
   addr.u8[b3] = Rx_Buf[6];
  
   if ((addr.u32 < APP_FW_START_ADDR) || (addr.u32 >= APP_FW_SIG1_ADDR) ||
      ((addr.u32 & TGT_FLASH_PAGE_ADDR_MASK) != 0))
   {
      // Address out-of-bounds
      Tx_Buf[0] = TGT_RSP_ADDR_INVALID;   
   }
   else
   {
      Current_Addr.u32 = addr.u32;      
      Tx_Buf[0] = TGT_RSP_OK;

      Flash_Key0 = Rx_Buf[1];
      Flash_Key1 = Rx_Buf[2];
      Rx_Buf[1] = 0;
      Rx_Buf[2] = 0;

      #if CODE_BANKING == 0
      FLASH_PageErase (Current_Addr.u16[LSB]);
      #else
      FLASH_PageErase (Current_Addr.u32);
      #endif      

      // Set flash keys to 0
      Flash_Key0 = 0;
      Flash_Key1 = 0;
            
      // If previously valid, re-check if App FW is still valid (==> checks if signature was erased)
      if (Device_Mode != MODE_APP_FW_INVALID)
      {
         Device_Mode = Check_App_FW_Validity();
      }
   }
   
   Comm_Send_Tx_Bytes (1);   
}

//-----------------------------------------------------------------------------
// TGT_Write_Flash
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Write_Flash (void)
{
   SI_UU16_t numbytes;
   uint16_t i;

   // Command Format:
   // [0] Command:Numbytes1[3:0]
   // [1] Numbytes0[7:0] to write
   // [2] flash key code0
   // [3] flash key code1
   // [4] byte0
   // [5] byte1
   // [6] ...
   // [numbytes] byte[numbytes-4]
   // [numbytes+1] xx
   // [numbytes+2] ..
   // [BL_Buf_Length] xx
   
   // Response:
   // [0] Response code

   // Write to flash only if App FW signature was previously erased        
   if (Device_Mode != MODE_APP_FW_INVALID)
   {
      // Error: Signature has not yet been erased
      Tx_Buf[0] = TGT_RSP_SIG_NOT_ERASED;
   }
   else
   {
      numbytes.u8[LSB] = Rx_Buf[1];
      numbytes.u8[MSB] = (Rx_Buf[0] & 0x0F);

      Flash_Key0 = Rx_Buf[2];
      Flash_Key1 = Rx_Buf[3];
      Rx_Buf[2] = 0;
      Rx_Buf[3] = 0;

      if (numbytes.u16 > RX_BUF_LENGTH)
      {
         // Too many bytes!
         Tx_Buf[0] = TGT_RSP_PARAMETER_INVALID;        
      }
      else if ((Current_Addr.u32 < APP_FW_START_ADDR) || 
               ((Current_Addr.u32 + (uint32_t)(numbytes.u16 - 4)) > APP_FW_INFOBLOCK_ADDR))
      {
         // Address out-of-bounds
         // Note: "-4" because the first four bytes in this command are not data bytes
         Tx_Buf[0] = TGT_RSP_ADDR_INVALID;
      }
      else
      {    
         if (numbytes.u16 > TGT_CMD_FIXED_LENGTH)
         {  
            // Get the rest of the bytes
            Comm_Wait_For_Rx_Bytes ((numbytes.u16 - TGT_CMD_FIXED_LENGTH), TGT_CMD_FIXED_LENGTH);
         }

         for (i = 4; i < numbytes.u16; i++)
         {
            #if CODE_BANKING == 0
            FLASH_ByteWrite (Current_Addr.u16[LSB], Rx_Buf[i]);
            Current_Addr.u16[LSB] += 1;
            #else
            FLASH_ByteWrite (Current_Addr.u32, Rx_Buf[i]);
            Current_Addr.u32 += 1;
            #endif
         }      

         // Set flash keys to 0
         Flash_Key0 = 0;
         Flash_Key1 = 0;

         Tx_Buf[0] = TGT_RSP_OK;
      }
   }
         
   Comm_Send_Tx_Bytes (1);   
}

//-----------------------------------------------------------------------------
// TGT_Get_Page_CRC
//-----------------------------------------------------------------------------
// TGT_Get_Page_CRC
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Get_Page_CRC (void)
{
   // Command Format:
   // [0] Command
   // [1] addr0 (LSB)
   // [2] addr1
   // [3] addr2
   // [4] addr3 (MSB)

   // Response:
   // [0] Response code
   // [1] crc0 (LSB)
   // [2] crc1
   // [3] [crc2]
   // [4] [crc3]

   SI_UU32_t addr;
   SI_UU32_t crc;
   uint16_t i;
   
   #if CODE_BANKING == 0
   SI_VARIABLE_SEGMENT_POINTER(codeptr, uint8_t, SI_SEG_CODE);
   #endif   

   addr.u8[b0] = Rx_Buf[1];
   addr.u8[b1] = Rx_Buf[2];
   addr.u8[b2] = Rx_Buf[3];
   addr.u8[b3] = Rx_Buf[4];
  
   if ( (addr.u32 < APP_FW_START_ADDR) || (addr.u32 > APP_FW_END_ADDR) || 
         ((addr.u32 & TGT_FLASH_PAGE_ADDR_MASK) != 0)
      )
   {
      // Address out-of-bounds
      Tx_Buf[0] = TGT_RSP_ADDR_INVALID;  
      // crc bytes sent are "don't care".
   }
   else
   {
      Running_CRC = 0; // Init Running CRC to 0
      
      #if CODE_BANKING == 0
      codeptr = (uint8_t SI_SEG_CODE *)(addr.u16[LSB]);      
      #endif
      
      for (i = 0; i < TGT_FLASH_PAGE_SIZE; i++)
      {
         #if CODE_BANKING == 0
            Update_CRC (*codeptr);
            codeptr++;
         #else
            Update_CRC (FLASH_ByteRead(addr.u32));
            addr.u32++;
         #endif
      }   

      Tx_Buf[0] = TGT_RSP_OK;

      #if (TGT_CRC_TYPE & 0x80) == 0 // 16-bit CRC
         crc.u16[LSB] = Running_CRC;
         Tx_Buf[1] = crc.u8[b0];
         Tx_Buf[2] = crc.u8[b1];
      #else // 32-bit CRC
         crc.u32 = Running_CRC;
         Tx_Buf[3] = crc.u8[b2];
         Tx_Buf[4] = crc.u8[b3];      
      #endif
   }
   
   #if (TGT_CRC_TYPE & 0x80) == 0 // 16-bit CRC
      Comm_Send_Tx_Bytes (3);   
   #else   
      Comm_Send_Tx_Bytes (5);   
   #endif
}

//-----------------------------------------------------------------------------
// TGT_Write_Signature
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Write_Signature (void)
{
   // Command Format:
   // [0] Command
   // [1] flash key code0
   // [2] flash key code1
   // [3] signature byte0
   // [4] signature byte1
   // [5] RESERVED
   // [6] RESERVED
   // [7] RESERVED

   // Response:
   // [0] Response code

   if (Device_Mode != MODE_APP_FW_INVALID)
   {
      // Error: Signature has not yet been erased
      Tx_Buf[0] = TGT_RSP_SIG_NOT_ERASED;
   }
   else
   {
      Flash_Key0 = Rx_Buf[1];
      Flash_Key1 = Rx_Buf[2];

      FLASH_ByteWrite (APP_FW_SIG0_ADDR, Rx_Buf[3]);
      FLASH_ByteWrite (APP_FW_SIG1_ADDR, Rx_Buf[4]);

      // Set flash keys to 0
      Flash_Key0 = 0;
      Flash_Key1 = 0;
      Rx_Buf[1] = 0;
      Rx_Buf[2] = 0;

      Tx_Buf[0] = TGT_RSP_OK;
   }
   
    Comm_Send_Tx_Bytes (1);
}

//-----------------------------------------------------------------------------
// TGT_Reset_MCU
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Reset_MCU (void)
{
   Tx_Buf[0] = TGT_RSP_OK;
   Comm_Send_Tx_Bytes (1);
   
   Reset_MCU_Now (); // *** This function call will reset the MCU ***
}



//-----------------------------------------------------------------------------
// TGT_Unsupported_Cmd
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
//
//
//-----------------------------------------------------------------------------
void TGT_Unsupported_Cmd (void)
{
   Tx_Buf[0] = TGT_RSP_UNSUPPORTED_CMD;
   Comm_Send_Tx_Bytes (1);
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
