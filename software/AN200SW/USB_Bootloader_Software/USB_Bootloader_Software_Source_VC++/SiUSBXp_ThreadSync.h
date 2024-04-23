// SiUSBXp_ThreadSync.h	***For Surprise Removal Handling***

#ifndef SIUSBXP_THREADSYNC_H
#define SIUSBXP_THREADSYNC_H

#ifdef __cplusplus
extern "C" {
#endif


SI_STATUS CS_SI_GetNumDevices(
	LPDWORD lpdwNumDevices
	);


SI_STATUS CS_SI_GetProductString(
	DWORD dwDeviceNum,
	LPVOID lpvDeviceString,
	DWORD dwFlags
	);


SI_STATUS CS_SI_Open(
	DWORD dwDevice,
	HANDLE* cyHandle
	); 


SI_STATUS CS_SI_Close(
	HANDLE cyHandle
	);


SI_STATUS CS_SI_Read(
	HANDLE cyHandle,
	LPVOID lpBuffer,
	DWORD dwBytesToRead,
	LPDWORD lpdwBytesReturned,
	OVERLAPPED* o = NULL
	);

 
SI_STATUS CS_SI_Write(
	HANDLE cyHandle,
	LPVOID lpBuffer,
	DWORD dwBytesToWrite,
	LPDWORD lpdwBytesWritten,
	OVERLAPPED* o = NULL
	);

 
SI_STATUS CS_SI_DeviceIOControl(
	HANDLE cyHandle,
	DWORD dwIoControlCode,
	LPVOID lpInBuffer,
	DWORD dwBytesToRead,
	LPVOID lpOutBuffer,
	DWORD dwBytesToWrite,
	LPDWORD lpdwBytesSucceeded
	);

 
SI_STATUS CS_SI_FlushBuffers(
	HANDLE cyHandle, 
	BYTE FlushTransmit,
	BYTE FlushReceive
	);

 
SI_STATUS CS_SI_SetTimeouts(
	DWORD dwReadTimeout,
	DWORD dwWriteTimeout
	);

 
SI_STATUS CS_SI_GetTimeouts(
	LPDWORD lpdwReadTimeout,
	LPDWORD lpdwWriteTimeout
	);

 
SI_STATUS CS_SI_CheckRXQueue(
	HANDLE cyHandle,
	LPDWORD lpdwNumBytesInQueue,
	LPDWORD lpdwQueueStatus
	);


SI_STATUS	CS_SI_SetBaudRate(
	HANDLE cyHandle,
	DWORD dwBaudRate
	);


SI_STATUS	CS_SI_SetBaudDivisor(
	HANDLE cyHandle,
	WORD wBaudDivisor
	);


SI_STATUS	CS_SI_SetLineControl(
	HANDLE cyHandle, 
	WORD wLineControl
	);


SI_STATUS	CS_SI_SetFlowControl(
	HANDLE cyHandle, 
	BYTE bCTS_MaskCode, 
	BYTE bRTS_MaskCode, 
	BYTE bDTR_MaskCode, 
	BYTE bDSR_MaskCode, 
	BYTE bDCD_MaskCode, 
	BOOL bFlowXonXoff
	);


SI_STATUS CS_SI_GetModemStatus(
	HANDLE cyHandle, 
	PBYTE ModemStatus
	);


SI_STATUS CS_SI_SetBreak(
	HANDLE cyHandle, 
	WORD wBreakState
	);

 
SI_STATUS CS_SI_ReadLatch(
	HANDLE cyHandle,
	LPBYTE	lpbLatch
	);

 
SI_STATUS CS_SI_WriteLatch(
	HANDLE cyHandle,
	BYTE	bMask,
	BYTE	bLatch
	);


 
SI_STATUS CS_SI_GetPartNumber(
	HANDLE cyHandle,
	LPBYTE	lpbPartNum
	);

 
SI_STATUS CS_SI_GetDLLVersion(
	DWORD* HighVersion,
	DWORD* LowVersion
	);

 
SI_STATUS CS_SI_GetDriverVersion(
	DWORD* HighVersion,
	DWORD* LowVersion
	);

#ifdef __cplusplus
}
#endif

#endif // SIUSBXP_THREADSYNC_H