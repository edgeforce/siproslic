// SiUSBXp_ThreadSync.cpp
//
// This file contains wrapper funtions for the USBXpress API functions;
// Access to the functions are controlled by a Critical Section object.

#include "stdafx.h"
#include "SiUSBXp.h"
#include "USB_BL_Interface.h"
#include "FirmwareInterface.h"
#include "SiUSBXp_ThreadSync.h"	// ***For Surprise Removal Handling***
#include <dbt.h>				// ***For Surprise Removal Handling***
#include <initguid.h>			// ***For Surprise Removal Handling***
#include <windows.h>			// ***For Surprise Removal Handling***

SI_STATUS CS_SI_GetNumDevices(LPDWORD lpdwNumDevices)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetNumDevices(lpdwNumDevices);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_GetProductString(DWORD dwDeviceNum, LPVOID lpvDeviceString, DWORD dwFlags)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetProductString(dwDeviceNum, lpvDeviceString, dwFlags);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_Open(DWORD dwDevice, HANDLE* cyHandle)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_Open(dwDevice, cyHandle);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_Close(HANDLE cyHandle)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_Close(cyHandle);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_Read(HANDLE cyHandle, LPVOID lpBuffer, DWORD dwBytesToRead, LPDWORD lpdwBytesReturned, OVERLAPPED* o)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_Read(cyHandle, lpBuffer, dwBytesToRead, lpdwBytesReturned, o);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_Write(HANDLE cyHandle, LPVOID lpBuffer, DWORD dwBytesToWrite, LPDWORD lpdwBytesWritten, OVERLAPPED* o)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_Write(cyHandle, lpBuffer, dwBytesToWrite, lpdwBytesWritten, o);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_DeviceIOControl(HANDLE cyHandle, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD dwBytesToRead, LPVOID lpOutBuffer, DWORD dwBytesToWrite, LPDWORD lpdwBytesSucceeded)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_DeviceIOControl(cyHandle, dwIoControlCode, lpInBuffer, dwBytesToRead, lpOutBuffer, dwBytesToWrite, lpdwBytesSucceeded);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_FlushBuffers(HANDLE cyHandle, BYTE FlushTransmit, BYTE FlushReceive)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_FlushBuffers(cyHandle, FlushTransmit, FlushReceive);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_SetTimeouts(DWORD dwReadTimeout, DWORD dwWriteTimeout)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetTimeouts(dwReadTimeout, dwWriteTimeout);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_GetTimeouts(LPDWORD lpdwReadTimeout, LPDWORD lpdwWriteTimeout)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetTimeouts(lpdwReadTimeout, lpdwWriteTimeout);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_CheckRXQueue(HANDLE cyHandle, LPDWORD lpdwNumBytesInQueue, LPDWORD lpdwQueueStatus)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_CheckRXQueue(cyHandle, lpdwNumBytesInQueue, lpdwQueueStatus);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_SetBaudRate(HANDLE cyHandle, DWORD dwBaudRate)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetBaudRate(cyHandle, dwBaudRate);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_SetBaudDivisor(HANDLE cyHandle, WORD wBaudDivisor)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetBaudDivisor(cyHandle, wBaudDivisor);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_SetLineControl(HANDLE cyHandle, WORD wLineControl)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetLineControl(cyHandle, wLineControl);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_SetFlowControl(HANDLE cyHandle, BYTE bCTS_MaskCode, BYTE bRTS_MaskCode, BYTE bDTR_MaskCode, BYTE bDSR_MaskCode, BYTE bDCD_MaskCode, BOOL bFlowXonXoff)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetFlowControl(cyHandle, bCTS_MaskCode, bRTS_MaskCode, bDTR_MaskCode, bDSR_MaskCode, bDCD_MaskCode, bFlowXonXoff);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_GetModemStatus(HANDLE cyHandle, PBYTE ModemStatus)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetModemStatus(cyHandle, ModemStatus);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


SI_STATUS CS_SI_SetBreak(HANDLE cyHandle, WORD wBreakState)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_SetBreak(cyHandle, wBreakState);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_ReadLatch(HANDLE cyHandle, LPBYTE lpbLatch)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_ReadLatch(cyHandle,lpbLatch);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_WriteLatch(HANDLE cyHandle, BYTE bMask, BYTE bLatch)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_WriteLatch(cyHandle, bMask, bLatch);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}


 
SI_STATUS CS_SI_GetPartNumber(HANDLE cyHandle, LPBYTE lpbPartNum)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetPartNumber(cyHandle, lpbPartNum);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_GetDLLVersion(DWORD* HighVersion, DWORD* LowVersion)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetDLLVersion(HighVersion, LowVersion);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}

 
SI_STATUS CS_SI_GetDriverVersion(DWORD* HighVersion, DWORD* LowVersion)
{
	SI_STATUS tempstat;
	EnterCriticalSection(&gCS);
	tempstat = SI_GetDriverVersion(HighVersion, LowVersion);
	LeaveCriticalSection(&gCS);
	return (tempstat);
}