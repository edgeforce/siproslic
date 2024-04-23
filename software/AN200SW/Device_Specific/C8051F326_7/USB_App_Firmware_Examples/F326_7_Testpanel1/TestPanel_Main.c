//-----------------------------------------------------------------------------
// TestPanel_Main.c
//-----------------------------------------------------------------------------
// Copyright 2012 Silicon Laboratories, Inc.
//
// AUTH: JS
// DATE: 22 FEB 02
//
//
// Target: C8051F32x
// Tool chain: KEIL C51 6.03 / KEIL EVAL C51
//
// REVISIONS:
// 
// 11/22/02 - DM:  Added support for switches and sample USB interrupt appl.
// 4/4/03 - DM:	Ported code to use USB_API.lib instead of custom solution.
// 5/6/03 - DM: Made changes to use new driver with better throughput.
// 13SEP2005-PKC: Added call to USB_Clock_Start()
// 27OCT2006-PKC: Updated to work with 'F326/7 devices.
// 19OCT2007-PKC: Updated code to handle DEVICE_OPEN and DEVICE_CLOSE events
// 08FEB2008-PKC: Removed extern declarations for USB descriptors and added
//                "USB_BL_APP_Shared.h"
// 20DEC2012-SHY: Add #include <si_toolchain.h> to work with new USB_API.h
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include <c8051f326.h>        
#include <stddef.h>       
#include "USB_API.h"
#include "USB_BL_APP_Shared.h"

//-----------------------------------------------------------------------------
// Global CONSTANTS
//-----------------------------------------------------------------------------

sbit Led1 = P2^2;                         // LED='1' means ON
sbit Led2 = P2^3;

#define Sw1 0x01                          // These are the port2 bits for Sw1
#define Sw2 0x02                          // and Sw2 on the development board
BYTE Switch1State = 0;                    // Indicate status of switch 
BYTE Switch2State = 0;                    // starting at 0 == off

BYTE Toggle1 = 0;                         // Variable to make sure each button
BYTE Toggle2 = 0;                         // press and release toggles switch

// NOTE: The 'F326/7 devices do not have analog peripherals. So these values are fixed.
BYTE Potentiometer = 0x00;                // Last read potentiometer value
BYTE Temperature = 0x00;                  // Last read temperature sensor value

BYTE Out_Packet[8] = {0,0,0,0,0,0,0,0};   // Last packet received from host
BYTE In_Packet[8]  = {0,0,0,0,0,0,0,0};   // Next packet to sent to host

// USB Descriptors are now shared with & defined in the Bootloader
// Externs are declared in USB_BL_APP_Shared.h      

// Function prototypes
void Timer_Init(void);
void Port_Init(void);
void Suspend_Device(void);
void Initialize(void);

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main(void) 
{
   unsigned long DelayCount=0;

   USB_Clock_Start();
   USB_Init(VID,PID,MFRSTR,PRDSTR,SERIAL,MAXPOWER,PWATTRIBUTES,BCDDEVICE);
   Initialize();
   USB_Int_Enable();
   
   while (1)
   {
       // It is possible that the contents of the following packets can change
       // while being updated.  This doesn't cause a problem in the sample 
       // application because the bytes are all independent.  If data is NOT 
       // independent, packet update routines should be moved to an interrupt
       // service routine, or interrupts should be disabled during data updates.
      
      if (Out_Packet[0] == 1) Led1 = 1;   // Update status of LED #1
      else Led1 = 0;
      if (Out_Packet[1] == 1) Led2 = 1;   // Update status of LED #2
      else Led2 = 0;
      P0 = (Out_Packet[2] & 0x0F);        // Set Port 0 pins 

      In_Packet[0] = Switch1State;        // Send status of switch 1
      In_Packet[1] = Switch2State;        // and switch 2 to host
      In_Packet[2] = ((P0 & 0xF0) >> 4);  // Port 0 [7-4]

      // NOTE: The 'F326/7 devices do not have analog peripherals. So these values are fixed.
      In_Packet[3] = Potentiometer;       // Potentiometer value ('F326/7: always 0x00)
      In_Packet[4] = Temperature;         // Temperature sensor value ('F326/7: always 0x00)

      if((!(P2 & Sw1) && !(P2 & Sw2)) || (Out_Packet[5] == 0x15) 
         || (DelayCount > 0) )
      {
         In_Packet[5] = 0x05;             // Indicate entering bootload mode
         DelayCount++;
      }

      // Delay so that previous In_Packet can be sent to the PC
      if(DelayCount > 15000)           
      {
         EA = 0;           // Disable all interrupts
         BOOTLOAD_REQ();   // Call bootloader
      }
   }
}

//-----------------------------------------------------------------------------
// Initialization Subroutines
//-----------------------------------------------------------------------------

//-------------------------
// Port_Init
//-------------------------
// Port Initialization
// - Configure the Crossbar and GPIO ports.
//
void Port_Init(void)
{  
   P0MDOUT |= 0x0F;                        // Port 0 pins 0-3 set push-pull digital output
   P0      |= 0xF0;                        // Port 0 pins 7-4 set open-drain digital input
   P2MDOUT |= 0x0C;                        // Port 2 pins 2-3 set push-pull digital output
   P2      |= 0x03;                        // Port 2 pins 0-1 set open-drain digital output
}

//-------------------------
// Timer_Init
//-------------------------
// Timer initialization
// - 8-bit auto reload; used to check switch state.
//
void Timer_Init(void)
{
   TMOD     = 0x20;                    // 8-bit timer with auto reload
   CKCON    = 0x02;                    // Timer1 clocked by SYSCLK/48
   TH1      = 0xF0;                    // Reload value
   TL1      = 0xff;                    // Set to reload immediately
}

//-------------------------
// Suspend_Device
//-------------------------
// Called when a DEV_SUSPEND interrupt is received.
// - Disables all unnecessary peripherals
// - Calls USB_Suspend()
// - Enables peripherals once device leaves suspend state
//
void Suspend_Device(void)
{
   bit ET1_save = ET1;
   
   // Disable peripherals before calling USB_Suspend()
   P2  &= ~0x0C;                        // Switch off LEDs (P2.2, P2.3)
   ET1 = 0;                             // Disable timer 1 Interrupts

   USB_Suspend();                       // Put the device in suspend state

   // Once execution returns from USB_Suspend(), device leaves suspend state.
   // Reenable peripherals
   ET1 = ET1_save;                     // Restore timer 1 Interrupt state
}

//-------------------------
// Initialize
//-------------------------
// Called when a DEV_CONFIGURED interrupt is received.
// - Enables all peripherals needed for the application
//
void Initialize(void)
{
   Port_Init();                           // Initialize crossbar and GPIO
   Timer_Init();                          // Initialize Timer1
}

//-------------------------
// Timer1_ISR
//-------------------------
// Called when timer 1 overflows, check to see if switch is pressed,
// then watch for release.
//
void Timer1_ISR(void) interrupt 3
{
   TF1 = 0;                                // Clear Timer1 interrupt flag
   
   if (!(P2 & Sw1))                      // Check for switch #1 pressed
   {
      if (Toggle1 == 0)                   // Toggle is used to debounce switch
      {                                   // so that one press and release will
         Switch1State = ~Switch1State;    // toggle the state of the switch sent
         Toggle1 = 1;                     // to the host
      }
   }
   else Toggle1 = 0;                      // Reset toggle variable

   if (!(P2 & Sw2))                       // This is the same as above, but for Switch2
   {
      if (Toggle2 == 0)
      {  
         Switch2State = ~Switch2State;
         Toggle2 = 1;
      }
   }
   else Toggle2 = 0;
}

//-------------------------
// USBXpress API ISR
//-------------------------
//	ISR that handles interrupts generated by the USBXpress API
//
void 	USB_API_TEST_ISR(void) interrupt 16
{
	BYTE INTVAL = Get_Interrupt_Source();

	if (INTVAL & RX_COMPLETE)
	{
      Block_Read(Out_Packet, 8);       // Read the received 8-byte packet
      Block_Write(In_Packet, 8);       // Write 8 bytes after receiving a packet
	}

	if (INTVAL & DEV_SUSPEND)
	{
      Suspend_Device();
	}

	if (INTVAL & DEVICE_OPEN)           // Received when a device handle is opened by PC App
	{
      TR1     = 1;                     // Start Timer1
	}

	if (INTVAL & DEVICE_CLOSE)          // Received when a device handle is closed by PC App
	{
      TR1     = 0;                     // Stop Timer1
	}
}