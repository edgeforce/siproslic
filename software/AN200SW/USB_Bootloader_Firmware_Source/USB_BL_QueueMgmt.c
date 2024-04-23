/******************************************************************************
Copyright (c) 2012, Silicon Laboratories, Inc.

Filename : USB_BL_QueueMgmt.c
Project  : USB Bootloader (USB_BL)
Created  : 02 JUN 2004 / PKC
Devices  : C8051F320/1/6/7/'F34x/'F38x
Toolchain: Keil

Description:
Contains functions to manage the transmit and receive circular FIFOs
of the USB Bootloader project.

Revision History:
01DEC2012-SHY:
-Add bug fix to GetNextRxByte()
01NOV2012-SHY:
-Add comments for F38x 
02JUN2004-PKC 
-Initial Revision

******************************************************************************/

// ===========================================================================
// *** Includes ***
// ===========================================================================
#include "USB_BL_Main.h"
#include "USB_BL_QueueMgmt.h"
#include "USB_BL_ISR.h"

// ===========================================================================
// *** Global Variables ***
// ===========================================================================
volatile BYTE  xdata RxQueue[RX_MAX_QUEUE]   _at_ MEM_RXQUEUE;
volatile BYTE  xdata TxQueue[TX_MAX_QUEUE]   _at_ MEM_TXQUEUE;

volatile UINT  data  RxHead                  _at_ MEM_RXHEAD;
volatile UINT  data  RxTail                  _at_ MEM_RXTAIL;
volatile UINT  data  TxHead                  _at_ MEM_TXHEAD;
volatile UINT  data  TxTail                  _at_ MEM_TXTAIL;

// ===========================================================================
// *** Function Definitions ***
// ===========================================================================

// ---------------------------------------------------------------------------
// >>> InitQueues <<<
//
// Initializes the RxQueue and TxQueue
// ---------------------------------------------------------------------------
void InitQueues(void)
{
   RxHead = RxTail = (RX_MAX_QUEUE - 1);
   TxHead = TxTail = (TX_MAX_QUEUE - 1);
}

// ---------------------------------------------------------------------------
// >>> EnRxQueue <<<
//
// Enqueues data in the RxQueue
// ---------------------------------------------------------------------------
void EnRxQueue(BYTE x)
{
   _EnRxQueue(x); //This macro was replaced by the function to reduce size
}

// ---------------------------------------------------------------------------
// >>> EnTxQueue <<<
//
// Enqueues data in the TxQueue
// ---------------------------------------------------------------------------
void EnTxQueue(BYTE x)
{
   _EnTxQueue(x); //This macro was replaced by the function to reduce size
}

// ---------------------------------------------------------------------------
// >>> SendTxQueue <<<
//
// Sends data in TXQueue to the host across the USB
// ---------------------------------------------------------------------------
void SendTxQueue(void)
{
   while(!_TxQueueEmpty)   // keep sending till tx queue is empty
   {
      Handle_In1();
   }
}

// ---------------------------------------------------------------------------
// >>> GetNextRxByte <<<
//
// Polls CommandQueue until there is a byte in the queue, then returns
// that byte
// ---------------------------------------------------------------------------
BYTE GetNextRxByte(void)
{
   bit rxQueueEmpty = 1;
   while (rxQueueEmpty)
   {
     _WaitRxQueueNotEmpty;   // Wait till the RxQueue gets something

     // Test variables again because the mismatch might have been because of non-atomic access
     if (RxHead != RxTail)
     {
       rxQueueEmpty = 0;
     }
   }
   RxHead = ((RxHead == (RX_MAX_QUEUE - 1)) ? 0 : (RxHead + 1));
   return RxQueue[RxHead];
}

// ---------------------------------------------------------------------------
// >>> GetNextTxByte <<<
//
// Returns the next byte in TxQueue if TxQueue is not empty. Should check to
// make sure that the TxQueue is not empty before calling this function
// (use the _TxQueueEmpty macro to check)
// ---------------------------------------------------------------------------
BYTE GetNextTxByte(void)
{
   if(!_TxQueueEmpty)
   {
      TxHead = ((TxHead == (TX_MAX_QUEUE - 1)) ? 0 : (TxHead + 1));
      return TxQueue[TxHead];
   }
   return 0;
}

// ===========================================================================
// *** END OF FILE *** USB_BL_QueueMgmt.c ***
// ===========================================================================