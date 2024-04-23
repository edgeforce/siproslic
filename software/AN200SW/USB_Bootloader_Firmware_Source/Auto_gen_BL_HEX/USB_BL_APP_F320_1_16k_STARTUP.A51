;******************************************************************************
; Begin custom code for the Application FW project ->
;******************************************************************************

; *** USB_BL_APP_F320_1_16k_STARTUP.A51 ***

; Compiler command line:  DB OE INTVECTOR(0x1400) INTERVAL(3)
; Linker command line: RS(256) PL(68) PW(78) CODE(0x1400-0x3BFD)

;------------------------------------------------------------------------------

; Device Code (Denotes device type)
; 1 byte value
; Stored at the last 5th byte of the last application page
CSEG AT 03BFBh
DEVICE_CODE: DB 081h   ; "C8051F320/1 with 16k Flash"

;==============================================================================

; Application Firmware Version *** INCREMENT FOR NEXT APP FW VERSION ***
; 2 byte value in high-byte, low-byte order
; Stored at the last 3rd and 4th bytes of the last application page
CSEG AT 03BFCh
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
_BLOCK_WRITE   EQU   0416h
_BLOCK_READ   EQU   0716h
USB_SUSPEND   EQU   0974h
USB_DISABLE   EQU   0B9Ch
USB_INT_ENABLE   EQU   0C28h
GET_INTERRUPT_SOURCE   EQU   0C55h
USB_INT_DISABLE   EQU   0C64h
USB_BL_USB_DESCRIPTOR   EQU   0C6Ch
_USB_INIT   EQU   03C00h
USB_CLOCK_START   EQU   03D37h
USB_GET_LIBRARY_VERSION   EQU   03D8Ch

PUBLIC VID
PUBLIC PID
PUBLIC MFRSTR
PUBLIC PRDSTR
PUBLIC MAXPOWER
PUBLIC PWATTRIBUTES
PUBLIC BCDDEVICE
PUBLIC SERIAL
PUBLIC SERIAL_BL
VID EQU 0C6Ch
PID EQU 0C6Eh
MFRSTR EQU 0C70h
PRDSTR EQU 0CA2h
MAXPOWER EQU 0CD4h
PWATTRIBUTES EQU 0CD5h
BCDDEVICE EQU 0CD6h
SERIAL EQU 0CD8h
SERIAL_BL EQU 0CE4h

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

