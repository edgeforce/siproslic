/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_QueueMgmt.h
Project  : USB Bootloader (USB_BL)
Created  : 06 JUL 2007 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains the macro definitions and function prototypes for the USB Bootloader.

Revision History:
 
 
01NOV2012-SHY:
-Add comments for F38x 
 
18FEB2008-PKC:
-Updated xdata variable location macros to constants because older versions of
 Keil C51 do not accept macro definitions that use other macros.

06JUL2007-PKC:
-Initial revision
-Extracted macros related to USB_BL_USB_QueueMgmt.c from the older USB_BL_Defs.h
******************************************************************************/

#ifndef _USB_BL_QUEUEMGMT_H_
#define _USB_BL_QUEUEMGMT_H_

// ===========================================================================
// *** Macro Definitions ***
// ===========================================================================

// BL FW Internal Constants
#define BULK_PACKET_SIZE	   0x40     // 64 bytes (max for full-speed USB)

// Circular Buffer Sizes
#define  RX_MAX_QUEUE		   0x180    // 384 bytes
#define	TX_MAX_QUEUE		   0x180    // 384 bytes

// Data variable locations
#define MEM_RXHEAD				0x30
#define MEM_RXTAIL				0x32
#define MEM_TXHEAD				0x34
#define MEM_TXTAIL				0x36

// Xdata variable locations
#define MEM_TXQUEUE				0x0000
#define MEM_RXQUEUE				0x0180   // TX_MAX_QUEUE + MEM_TXQUEUE
#define MEM_OUT_PACKET			0x0300   // TX_MAX_QUEUE + RX_MAX_QUEUE + MEM_TXQUEUE
#define MEM_IN_PACKET			0x0340   // MEM_OUT_PACKET + BULK_PACKET_SIZE

// Queue Management Macros
#define _InitRxQueue          RxHead = RxTail = (RX_MAX_QUEUE - 1)
#define _RxQueueFull          (RxHead == ((RxTail == (RX_MAX_QUEUE - 1)) ? 0 : (RxTail + 1))) 
#define _RxQueueEmpty         (RxHead == RxTail)
#define _EnRxQueue(x)         RxQueue[(RxTail = ((RxTail == (RX_MAX_QUEUE - 1)) ? 0 : (RxTail + 1)))] = x
#define _WaitRxQueueNotEmpty  while(_RxQueueEmpty)

#define _InitTxQueue          TxHead = TxTail = (TX_MAX_QUEUE - 1)
#define _TxQueueFull          (TxHead == ((TxTail == (TX_MAX_QUEUE - 1)) ? 0 : (TxTail + 1))) 
#define _TxQueueEmpty         (TxHead == TxTail)
#define _EnTxQueue(x)         TxQueue[(TxTail = ((TxTail == (TX_MAX_QUEUE - 1)) ? 0 : (TxTail + 1)))] = x
#define _WaitTxQueueNotEmpty  while(_TxQueueEmpty)

// ===========================================================================
// *** Global Variables ***
// ===========================================================================
extern volatile BYTE xdata    RxQueue[RX_MAX_QUEUE];
extern volatile BYTE xdata    TxQueue[TX_MAX_QUEUE];
extern volatile UINT data     RxHead, RxTail, TxHead, TxTail;

// ===========================================================================
// *** Function Prototypes ***
// ===========================================================================
void InitQueues(void);
void EnRxQueue(BYTE);
void EnTxQueue(BYTE);
void SendTxQueue(void);
BYTE GetNextRxByte(void);
BYTE GetNextTxByte(void);

#endif                        // _USB_BL_QUEUEMGMT_H_

// ===========================================================================
// *** END OF FILE *** USB_BL_Defs.h ***
// ===========================================================================