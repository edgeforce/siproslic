Copyright (c) 2012, Silicon Laboratories, Inc

USB Bootloader with Shared USBXpress Library
--------------------------------------------
Version 2.12
Release Date: 1 NOV 2012

Relevant devices: C8051F320/1/6/7/'F34x/'F38x

USBXpress driver/DLL/firmware library release used: v3.3.0/v3.1.0/v3.6

The Application Note AN200 (PDF) documents this bootloader. The latest 
information about the USB Bootloader firmware project can be found in USB_BL.txt in 
this folder.

Note: The firmware projects use the Keil tool chain.

***IMPORTANT NOTE*** Run one of the *.bat build files to build the USB_BL project.
If you use the "Build" command in the IDE to build this project, please make
sure you set the parameters of compilers as you want.


-------------------------------------------------------

How to use:

Note: See more detailed steps in AN200SW\Demo.txt.

1. Install the USBXpress device driver. This can be downloaded from here:
   http://www.silabs.com/products/mcu/Pages/USBXpress.aspx
2. Launch the Silicon Labs IDE or the Flash Programming Utility.
3. Erase the entire code space of the target MCU.
4. Download the appropriate OMF/HEX file (based on the target MCU) to the device.
   These files are located at "AN200SW\Device_Specific\C8051F*\USB_BL_Firmware_Image\".
   (In the IDE, use the "Debug > Download Object File..." command).
5. Disconnect from IDE or Flash Programming Utility.
6. Launch the USB Bootloader PC software located here:
   "AN200SWL\USB_Bootloader_Software\USB_Bootloader_Software_Executable\USBBootloader.exe"
7. Open the available device by pressing the "Open" button.
8. Click the "Browse" button and select the appropriate TestPanel1.hex file
   based on the target MCU. These hex files are located at:
   "AN200SW\Device_Specific\C8051F*\USB_App_Firmware_Examples\F*_Testpanel1\TestPanel1.hex"
9. Click the "Download" button to download it to the device. Then press the
   "Reset Device" button to reset the device.
10. Run the TestPanel host software to interact with the device firmware.
    This is located at "AN200SW\USB_App_Software_Example\Testpanel_Application_Executable\USBTestVBNET.exe".
11. To update this TestPanel1 firmware, click the Bootload button. Then 
    follow steps 6 thru 9 to select a TestPanel2 firmware hex file to download
    to the device.

-------------------------------------------------------

CONTACT INFORMATION
Silicon Laboratories Inc.
400 West Cesar Chavez
Austin, TX 78701
Please visit the Silicon Labs Technical Support web page:
https://www.silabs.com/support/pages/contacttechnicalsupport.aspx
and register to submit a technical support request.
=======================================================