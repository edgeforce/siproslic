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
// 14APR2006-PKC: Ported to work with 'F340
// 19OCT2007-PKC: Updated code to handle DEVICE_OPEN and DEVICE_CLOSE events
// 08FEB2008-PKC: Removed extern declarations for USB descriptors and added
//                "USB_BL_APP_Shared.h"
// 20DEC2012-SHY: Ported to work with 'F38x
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <si_toolchain.h>
#include <c8051f380_defs.h>  
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

BYTE Potentiometer = 0x00;                // Last read potentiometer value
BYTE Temperature = 0x00;                  // Last read temperature sensor value

BYTE Out_Packet[8] = {0,0,0,0,0,0,0,0};   // Last packet received from host
BYTE In_Packet[8]  = {0,0,0,0,0,0,0,0};   // Next packet to sent to host

code const BYTE TEMP_ADD = 112;           // This constant is added to Temperature

// USB Descriptors are now shared with & defined in the Bootloader
// Externs are declared in USB_BL_APP_Shared.h 

// Function prototypes
void Timer_Init(void);
void Adc_Init(void);  
void Port_Init(void);
void Suspend_Device(void);
void Initialize(void);

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main(void) 
{
   unsigned long DelayCount=0;

   PCA0MD &= ~0x40;                       // Disable Watchdog timer

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
      P1 = (Out_Packet[2] & 0x0F);        // Set Port 1 pins 

      In_Packet[0] = Switch1State;        // Send status of switch 1
      In_Packet[1] = Switch2State;        // and switch 2 to host
      In_Packet[2] = (P0 & 0x0F);         // Port 0 [0-3] (make sure j9 & j10 jumpered)
      In_Packet[3] = Potentiometer;       // Potentiometer value
      In_Packet[4] = Temperature;         // Temperature sensor value

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
   P1MDIN   = 0x7F;                        // Port 1 pin 7 set as analog input
   P0MDOUT |= 0x0F;                        // Port 0 pins 0-3 set high impedence
   P1MDOUT |= 0x0F;                        // Port 1 pins 0-3 set high impedence
   P2MDOUT |= 0x0C;                        // Port 2 pins 0,1 set high impedence
   P1SKIP   = 0x80;                        // Port 1 pin 7 skipped by crossbar
   XBR0     = 0x00;						    
   XBR1     = 0x40;                        // Enable Crossbar
}

//-------------------------
// Timer_Init
//-------------------------
// Timer initialization
// - 1 mhz timer 2 reload, used to check if switch pressed on overflow and
// used for ADC continuous conversion
//
void Timer_Init(void)
{
   TMR2CN  = 0x00;                        // Stop Timer2; Clear TF2;

   CKCON  &= ~0xF0;                       // Timer2 clocked based on T2XCLK;
   TMR2RL  = -(24000000 / 12);              // Initialize reload value
   TMR2    = 0xffff;                      // Set to reload immediately
}

//-------------------------
// Adc_Init
//-------------------------
// ADC initialization
// - Configures ADC for single ended continuous conversion or Timer2
//
void Adc_Init(void)
{                 
   REF0CN  = 0x0E;                        // Enable voltage reference VREF
   AMX0P = 0x1E;                        // Positive input starts as temp sensor  
   AMX0N = 0x1F;                        // Single ended mode(negative input = gnd)

   ADC0CF  = 0xF8;                        // SAR Period 0x1F, Right adjusted output

   ADC0CN  = 0xC2;                        // Continuous converion on timer 2 overflow
                                          // with low power tracking mode on
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
   BYTE ADC0CN_save = ADC0CN;
   bit ET2_save = ET2;
   
   // Disable peripherals before calling USB_Suspend()
   P0MDIN = 0x00;                       // Port 0 configured as analog input
   P1MDIN = 0x00;                       // Port 1 configured as analog input
   P2MDIN = 0x00;                       // Port 2 configured as analog input
   P3MDIN = 0x00;                       // Port 3 configured as analog input
   ADC0CN &= ~0x80;                     // Disable ADC0
   ET2 = 0;                             // Disable Timer 2 Interrupts


   USB_Suspend();                       // Put the device in suspend state

   // Once execution returns from USB_Suspend(), device leaves suspend state.
   // Reenable peripherals
   ADC0CN |= (ADC0CN_save & 0x80);     // Restore ADC0 state
   P0MDIN = 0xFF;
   P1MDIN = 0x7F;                       // Port 1 pin 7 set as analog input
   P2MDIN = 0xFF;
   P3MDIN = 0x01;
   ET2 = ET2_save;                     // Restore Timer 2 Interrupt state
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
   Timer_Init();                          // Initialize timer2
   Adc_Init();                            // Initialize ADC
}

//-------------------------
// Timer2_ISR
//-------------------------
// Called when timer 2 overflows, check to see if switch is pressed,
// then watch for release.
//
void Timer2_ISR(void) interrupt 5
{
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

   TF2H = 0;                              // Clear Timer2 interrupt flag
}

//-------------------------
// Adc_ConvComplete_ISR
//-------------------------
// Called after a conversion of the ADC has finished
// - Updates the appropriate variable for either potentiometer or temperature sensor
// - Switches the Adc multiplexor value to switch between the potentiometer and temp sensor
//
void Adc_ConvComplete_ISR(void) interrupt 10
{
   if (AMX0P == 0x1E)                  // This switches the AMUX between
   {                                     // the temperature sensor and the
      Temperature   = ADC0L;             // potentiometer pin after each
      Temperature += TEMP_ADD;
      AMX0P       = 0x04;              // switch to potentiometer
      ADC0CF      = 0xFC;              // place ADC0 in left-adjusted mode
   }
   else
   {
      Potentiometer = ADC0H;
      AMX0P       = 0x1E;             // switch to temperature sensor
      ADC0CF      = 0xF8;             // place ADC0 in right-adjusted mode
   }

   AD0INT = 0;
   Block_Write(In_Packet, 8);
}

//-------------------------
// USBXpress API ISR
//-------------------------
//	ISR that handles interrupts generated by the USBXpress API
//
void 	USB_API_TEST_ISR(void) interrupt 17
{
	BYTE INTVAL = Get_Interrupt_Source();

	if (INTVAL & RX_COMPLETE)
	{
		Block_Read(Out_Packet, 8);
	}

	if (INTVAL & DEV_SUSPEND)
	{
      Suspend_Device();
	}

	if (INTVAL & DEVICE_OPEN)           // Received when a device handle is opened by PC App
	{
      ADC0CN |= 0x80;                  // Enable ADC0 
      EIE1   |= 0x08;                  // Enable ADC conversion complete interrupt
      ET2     = 1;                     // Enable Timer2 interrupts
      TR2     = 1;                     // Start Timer2
	}

	if (INTVAL & DEVICE_CLOSE)          // Received when a device handle is closed by PC App
	{
      EIE1   &= ~0x08;                 // Disable ADC conversion complete interrupt
      ADC0CN &= ~0x80;                 // Disable ADC0
      ET2     = 0;                     // Disable Timer2 interrupts
      TR2     = 0;                     // Stop Timer2
	}
}