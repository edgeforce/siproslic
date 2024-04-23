$NOMOD51
;------------------------------------------------------------------------------
;  This file is part of the C51 Compiler package
;  Copyright (c) 1988-2005 Keil Elektronik GmbH and Keil Software, Inc.
;  Version 8.01
;
;  *** <<< Use Configuration Wizard in Context Menu >>> ***
;------------------------------------------------------------------------------
;  STARTUP.A51:  This code is executed after processor reset.
;
;  To translate this file use A51 with the following invocation:
;
;     A51 STARTUP.A51
;
;  To link the modified STARTUP.OBJ file to your application use the following
;  Lx51 invocation:
;
;     Lx51 your object file list, STARTUP.OBJ  controls
;
;------------------------------------------------------------------------------
;******************************************************************************
; Filename  : USB_BL_APP_F38x_32k_STARTUP.A51
; Project   : USB Bootloader (USB_BL)
; Created   : 01 NOV 2012 / SHY
; Devices   : C8051F38x(32k)
; Toolchain : Keil
;
; Compiler command line:  See in custom section below.
; Linker command line: See in custom section below.
;
; Description:
; The modifications made to the default Keil STARTUP.A51 enables calls to the 
; shared USBXpress library located within the Bootloader project from 
; Application Firmware.
;
; Revision History:
; 01NOV2012-SHY:
;  Init file for F38x.
;  This file is copied from F34x
;  Updated START_APPLICATION from 1200h to 1400h
;  Updated bootloader and USBXpress publics and function entry points
;  Note: These values were copied from the "F38x_32k" tab of the excel sheet
;******************************************************************************
;
;  User-defined <h> Power-On Initialization of Memory
;
;  With the following EQU statements the initialization of memory
;  at processor reset can be defined:
;
; <o> IDATALEN: IDATA memory size <0x0-0x100>
;     <i> Note: The absolute start-address of IDATA memory is always 0
;     <i>       The IDATA space overlaps physically the DATA and BIT areas.
IDATALEN        EQU     80H
;
; <o> XDATASTART: XDATA memory start address <0x0-0xFFFF> 
;     <i> The absolute start address of XDATA memory
XDATASTART      EQU     0     
;
; <o> XDATALEN: XDATA memory size <0x0-0xFFFF> 
;     <i> The length of XDATA memory in bytes.
XDATALEN        EQU     0      
;
; <o> PDATASTART: PDATA memory start address <0x0-0xFFFF> 
;     <i> The absolute start address of PDATA memory
PDATASTART      EQU     0H
;
; <o> PDATALEN: PDATA memory size <0x0-0xFF> 
;     <i> The length of PDATA memory in bytes.
PDATALEN        EQU     0H
;
;</h>
;------------------------------------------------------------------------------
;
;<h> Reentrant Stack Initialization
;
;  The following EQU statements define the stack pointer for reentrant
;  functions and initialized it:
;
; <h> Stack Space for reentrant functions in the SMALL model.
;  <q> IBPSTACK: Enable SMALL model reentrant stack
;     <i> Stack space for reentrant functions in the SMALL model.
IBPSTACK        EQU     0       ; set to 1 if small reentrant is used.
;  <o> IBPSTACKTOP: End address of SMALL model stack <0x0-0xFF>
;     <i> Set the top of the stack to the highest location.
IBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </h>
;
; <h> Stack Space for reentrant functions in the LARGE model.      
;  <q> XBPSTACK: Enable LARGE model reentrant stack
;     <i> Stack space for reentrant functions in the LARGE model.
XBPSTACK        EQU     0       ; set to 1 if large reentrant is used.
;  <o> XBPSTACKTOP: End address of LARGE model stack <0x0-0xFFFF>
;     <i> Set the top of the stack to the highest location.
XBPSTACKTOP     EQU     0xFFFF +1   ; default 0FFFFH+1 
; </h>
;
; <h> Stack Space for reentrant functions in the COMPACT model.    
;  <q> PBPSTACK: Enable COMPACT model reentrant stack
;     <i> Stack space for reentrant functions in the COMPACT model.
PBPSTACK        EQU     0       ; set to 1 if compact reentrant is used.
;
;   <o> PBPSTACKTOP: End address of COMPACT model stack <0x0-0xFFFF>
;     <i> Set the top of the stack to the highest location.
PBPSTACKTOP     EQU     0xFF +1     ; default 0FFH+1  
; </h>
;</h>
;------------------------------------------------------------------------------
;
;  Memory Page for Using the Compact Model with 64 KByte xdata RAM
;  <e>Compact Model Page Definition
;
;  <i>Define the XDATA page used for PDATA variables. 
;  <i>PPAGE must conform with the PPAGE set in the linker invocation.
;
; Enable pdata memory page initalization
PPAGEENABLE     EQU     0       ; set to 1 if pdata object are used.
;
; <o> PPAGE number <0x0-0xFF> 
; <i> uppermost 256-byte address of the page used for PDATA variables.
PPAGE           EQU     0
;
; <o> SFR address which supplies uppermost address byte <0x0-0xFF> 
; <i> most 8051 variants use P2 as uppermost address byte
PPAGE_SFR       DATA    0A0H
;
; </e>
;------------------------------------------------------------------------------

; Standard SFR Symbols 
ACC     DATA    0E0H
B       DATA    0F0H
SP      DATA    81H
DPL     DATA    82H
DPH     DATA    83H

;******************************************************************************
; Begin custom code for the Application FW project ->
;******************************************************************************

; *** USB_BL_APP_F38x_32k_STARTUP.A51 ***

; Compiler command line:  DB OE INTVECTOR(0x1400) INTERVAL(3)
; Linker command line: RS(256) PL(68) PW(78) CODE(0x1400-0x7DFD)

;------------------------------------------------------------------------------

; Device Code (Denotes device type)
; 1 byte value
; Stored at the last 5th byte of the last application page
CSEG AT 07DFBh
DEVICE_CODE: DB 085h   ; "C8051F38x with 32k Flash"

;==============================================================================

; Application Firmware Version *** INCREMENT FOR NEXT APP FW VERSION ***
; 2 byte value in high-byte, low-byte order
; Stored at the last 3rd and 4th bytes of the last application page
CSEG AT 07DFCh
APP_FW_VER: DB 001h,000h   ; ver 1.0

;==============================================================================

; Entry point of the User Application Firmware
; Change should be mirrored in this project's Compiler & Linker command lines
; Should also be mirrored in BL FW's STARTUP.A51 and USB_BL_Defs.h
; And also in BL SW's FirmwareInterface.h
START_APPLICATION   EQU   01400h

; Location of USB_Init function parameters (passed by compiler)
PUBLIC ?_USB_INIT?BYTE
?_USB_INIT?BYTE   EQU   07AFh

;------------------------------------------------------------------------------
; The following define the entry points of the Bootloader functions
; and is used by the app to call the bootloader

PUBLIC   BOOTLOAD_REQ
PUBLIC   _BLOCK_WRITE
PUBLIC   _BLOCK_READ
PUBLIC   USB_SUSPEND
PUBLIC   USB_DISABLE
PUBLIC   USB_INT_ENABLE
PUBLIC   GET_INTERRUPT_SOURCE
PUBLIC   USB_INT_DISABLE
PUBLIC   USB_BL_USB_DESCRIPTOR
PUBLIC   _USB_INIT
PUBLIC   USB_CLOCK_START
PUBLIC   USB_GET_LIBRARY_VERSION

BOOTLOAD_REQ   EQU   0FFFFh
_BLOCK_WRITE   EQU   0436h
_BLOCK_READ   EQU   0736h
USB_SUSPEND   EQU   0994h
USB_DISABLE   EQU   0BEDh
USB_INT_ENABLE   EQU   0C79h
GET_INTERRUPT_SOURCE   EQU   0CA6h
USB_INT_DISABLE   EQU   0CB5h
USB_BL_USB_DESCRIPTOR   EQU   0CBDh
_USB_INIT   EQU   07E00h
USB_CLOCK_START   EQU   07F37h
USB_GET_LIBRARY_VERSION   EQU   07F8Ah

PUBLIC VID
PUBLIC PID
PUBLIC MFRSTR
PUBLIC PRDSTR
PUBLIC MAXPOWER
PUBLIC PWATTRIBUTES
PUBLIC BCDDEVICE
PUBLIC SERIAL

VID EQU 0CBDh
PID EQU 0CBFh
MFRSTR EQU 0CC1h
PRDSTR EQU 0CF3h
MAXPOWER EQU 0D25h
PWATTRIBUTES EQU 0D26h
BCDDEVICE EQU 0D27h
SERIAL EQU 0D29h
SERIAL_BL EQU 0D35h

;------------------------------------------------------------------------------
   ;This is only to reserve the bit space so that App FW keeps away from this location
   ;The App FW does not have to monitor or change this bit variable

   ;Bit variable holding current device status (0=>App FW Mode; 1=>BL Mode)
   ;[Only RAM variable shared between BL project and App FW project]

   ;DEVICE_MODE DEFINES    (Changes should be mirrored in USB_BL_Defs.h 
   ;                        and App FW's STARTUP.A51 as well)
   ;APPLICATION_MODE EQU 0  ;Application Mode (Signature verification passed)
   ;BOOTLOADER_MODE  EQU 1  ;Bootloader Mode (Signature verification failed)

   ;DEVICE_MODE LOCATION
    MEM_DEVICE_MODE  BIT  07Fh  ;Last bit in bit-addressable space (2F.7h)

   ;DEVICE_MODE SPACE ALLOCATION
    BSEG    AT    MEM_DEVICE_MODE
DEVICE_MODE:  DBIT  1

;******************************************************************************
;End of custom code for the Application FW Project <-
;Original Keil STARTUP.A51 code continues below with one modification ->
;(Changed "CSEG AT 0" to "CSEG AT START_APPLICATION") ->
;******************************************************************************

                NAME    ?C_STARTUP


?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1

                EXTRN CODE (?C_START)
                PUBLIC  ?C_STARTUP

                CSEG    AT      START_APPLICATION  ; *** MODIFIED RESET VECTOR ***
?C_STARTUP:     LJMP    STARTUP1

                RSEG    ?C_C51STARTUP

STARTUP1:

IF IDATALEN <> 0
                MOV     R0,#IDATALEN - 1
                CLR     A
IDATALOOP:      MOV     @R0,A
                DJNZ    R0,IDATALOOP
ENDIF

IF XDATALEN <> 0
                MOV     DPTR,#XDATASTART
                MOV     R7,#LOW (XDATALEN)
  IF (LOW (XDATALEN)) <> 0
                MOV     R6,#(HIGH (XDATALEN)) +1
  ELSE
                MOV     R6,#HIGH (XDATALEN)
  ENDIF
                CLR     A
XDATALOOP:      MOVX    @DPTR,A
                INC     DPTR
                DJNZ    R7,XDATALOOP
                DJNZ    R6,XDATALOOP
ENDIF

IF PPAGEENABLE <> 0
                MOV     PPAGE_SFR,#PPAGE
ENDIF

IF PDATALEN <> 0
                MOV     R0,#LOW (PDATASTART)
                MOV     R7,#LOW (PDATALEN)
                CLR     A
PDATALOOP:      MOVX    @R0,A
                INC     R0
                DJNZ    R7,PDATALOOP
ENDIF

IF IBPSTACK <> 0
EXTRN DATA (?C_IBP)

                MOV     ?C_IBP,#LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
EXTRN DATA (?C_XBP)

                MOV     ?C_XBP,#HIGH XBPSTACKTOP
                MOV     ?C_XBP+1,#LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
EXTRN DATA (?C_PBP)
                MOV     ?C_PBP,#LOW PBPSTACKTOP
ENDIF

                MOV     SP,#?STACK-1

; This code is required if you use L51_BANK.A51 with Banking Mode 4
;<h> Code Banking
; <q> Select Bank 0 for L51_BANK.A51 Mode 4
#if 0   
;     <i> Initialize bank mechanism to code bank 0 when using L51_BANK.A51 with Banking Mode 4.
EXTRN CODE (?B_SWITCH0)
                CALL    ?B_SWITCH0      ; init bank mechanism to code bank 0
#endif
;</h>
                LJMP    ?C_START

                END
