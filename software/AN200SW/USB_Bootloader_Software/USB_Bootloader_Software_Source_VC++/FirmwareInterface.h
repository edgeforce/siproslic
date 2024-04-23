#ifndef FIRMWAREINTERFACE_H
#define FIRMWAREINTERFACE_H

// Note: Most of the declarations related to the firmware interface
// can be found in USB_BL_Interface.h

// USBXpress Read/Write Timeouts (in ms)
#define USBX_READ_TIMEOUT	500
#define USBX_WRITE_TIMEOUT	500

// CheckRxQueue timeout (in ms)
// This timeout is used to expire waiting for data to arrive from device
// because the SI_CheckRxQueue function always returns SI_SUCCESS even after the
// device has been removed (in case of surprise removal).
#define	USBX_CHECKRXQUEUE_TIMEOUT 100

/////////////////////////////////////////////////////////
// Firmware Interface Functions -- Each of these
//	functions communicate directly with the firmware.
/////////////////////////////////////////////////////////

bool GetDeviceInfo(HANDLE& deviceHandle, DEVICE_INFO_BLOCK *devInfo);
bool SetPage(HANDLE& deviceHandle, BYTE page);
bool ErasePage(HANDLE& deviceHandle, BYTE page);
bool WritePage(HANDLE& deviceHandle, BYTE* data, BYTE page, UINT* pageCRC);
bool CheckCRCPage(HANDLE& deviceHandle, BYTE page, WORD* pageCRC);
bool ResetDevice(HANDLE& deviceHandle);
bool SetFlashKeyCodes (HANDLE& deviceHandle, BYTE key0, BYTE key1);
bool WriteSignature (HANDLE& deviceHandle);

/////////////////////////////////////////////////////////
// External Global Variables
/////////////////////////////////////////////////////////

extern CRITICAL_SECTION gCS;

#endif // FIRMWAREINTERFACE_H