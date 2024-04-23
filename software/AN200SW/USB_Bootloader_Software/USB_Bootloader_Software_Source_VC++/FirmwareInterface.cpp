// FirmwareInterface.cpp

#include "stdafx.h"
#include "USB_BL_Interface.h"
#include "FirmwareInterface.h"
#include "SiUSBXp.h"
#include "SiUSBXp_ThreadSync.h"
#include "windows.h"

/////////////////////////////////////////////////////////
// Firmware Interface Functions -- Each of these
//	functions communicate directly with the firmware.
/////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// *** GetDeviceInfo ***
//
// Retrieves the Device Info Block data from the device.
//-----------------------------------------------------------------------------
bool GetDeviceInfo(HANDLE& deviceHandle, DEVICE_INFO_BLOCK *devInfo)
{
	BYTE	code = CMD_GET_DEVICE_INFO;
	DWORD	numBytesWritten = 0;
	BYTE	temp_buf[DEVICE_INFO_BLOCK_RET_LENGTH];
	bool	fnRetVal = true;

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		if (CS_SI_Write(deviceHandle, &code, 1, &numBytesWritten) == SI_SUCCESS)
		{
			DWORD numBytesInQueue = 0;
			DWORD queueStatus = 0;
			DWORD start_time = GetTickCount();

			while ( (numBytesInQueue < DEVICE_INFO_BLOCK_RET_LENGTH) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT) )
			{
				if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
				{
					//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
					fnRetVal = false;
					break;
				}
			}
			
			DWORD numBytesRead = 0;

			if ((fnRetVal == true) && (numBytesInQueue >= DEVICE_INFO_BLOCK_RET_LENGTH))
			{
				if (CS_SI_Read(deviceHandle, temp_buf, DEVICE_INFO_BLOCK_RET_LENGTH, &numBytesRead) == SI_SUCCESS)
				{
					devInfo->BL_FW_ver_high = temp_buf[0];
					devInfo->BL_FW_ver_low = temp_buf[1];
                    // Change BCD to hex
					devInfo->USBX_FWLib_ver_high = (temp_buf[2]&0xF0)/16*10 + (temp_buf[2]&0x0F);
					devInfo->USBX_FWLib_ver_low = (temp_buf[3]&0xF0)/16*10 + (temp_buf[3]&0x0F);
                    // If sub-version is 3.60, cut it to 3.6. Keep the same convention as release note
					if (devInfo->USBX_FWLib_ver_low%10 == 0)  devInfo->USBX_FWLib_ver_low /= 10;
					devInfo->App_FW_ver_high = temp_buf[4];
					devInfo->App_FW_ver_low = temp_buf[5];
					devInfo->signature = (UINT)((temp_buf[6] << 8) | temp_buf[7]);
					devInfo->devCode = temp_buf[8];
				}
				else
				{
					//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
					fnRetVal = false;
				}
			}
		}
		else
		{
			//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** SetPage ***
//
// Sets the current page on the device. ErasePage, WritePage, and CRConPage
// functions will operate on this current page.
//-----------------------------------------------------------------------------
bool SetPage(HANDLE& deviceHandle, BYTE page)
{
	BYTE	code[2] = {CMD_SET_PAGE, page};
	DWORD	numBytesWritten = 0;
	bool	fnRetVal = true;

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		//Write a 0x01 to the device to set the current flash page
		if (CS_SI_Write(deviceHandle, code, 2, &numBytesWritten) == SI_SUCCESS)
		{
			DWORD numBytesInQueue = 0;
			DWORD queueStatus = 0;

			DWORD start_time = GetTickCount();

			//Wait til we have data in the queue
			while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
			{
				if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
				{
					//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
					fnRetVal = false;
				}
			}

			BYTE status = COMMAND_FAILED;
			DWORD numBytesRead = 0;

			if ((fnRetVal == true) && (numBytesInQueue >= 1))
			{
				//Read the success of the command
				if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
				{
					if (status != COMMAND_OK)
					{
						//MessageBox(NULL, "Device Failed to Set Page", "Error", MB_OK);
						fnRetVal = false;
					}
				}
				else
				{
					//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
					fnRetVal = false;
				}
			}
		}
		else
		{
			//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** ErasePage ***
//
// Erases the current page; Current page is set by SetPage.
//-----------------------------------------------------------------------------
bool ErasePage(HANDLE& deviceHandle, BYTE page)
{
	BYTE	code = CMD_ERASE_PAGE;
	DWORD	numBytesWritten = 0;
	bool	fnRetVal = true;

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		//Set the current page
		if (SetPage(deviceHandle, page))
		{
			TRACE("Page set to %d\n",page);
			//Write the command to erase the current page
			if (CS_SI_Write(deviceHandle, &code, 1, &numBytesWritten) == SI_SUCCESS)
			{
				DWORD numBytesInQueue = 0;
				DWORD queueStatus = 0;

				TRACE("Written code for ErasePage command\n");

				DWORD start_time = GetTickCount();

				//Wait til we have data in the queue
				while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
				{
					if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
					{
						//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
						fnRetVal = false;
					}
				}
				
				TRACE("Checked queue (ErasePage)\n");

				BYTE status = COMMAND_FAILED;
				DWORD numBytesRead = 0;

				if ((fnRetVal == true) && (numBytesInQueue >= 1))
				{
					//Read the status of the erase
					if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
					{
						TRACE("Read status (ErasePage)\n");

						if (status != COMMAND_OK)
						{
							//MessageBox(NULL, "Device Failed to Erase Page", "Error", MB_OK);
							fnRetVal = false;
						}
					}
					else
					{
						//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
						fnRetVal = false;
					}
				}
			}
			else
			{
				//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
				fnRetVal = false;
			}
		}
		else
		{
			//MessageBox(NULL, "Error Setting Page", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** WritePage ***
//
// Writes the current page and retrievs the CRC of the page; 
// Current page is set by SetPage.
//-----------------------------------------------------------------------------
bool WritePage(HANDLE& deviceHandle, BYTE* data, BYTE page, UINT* pageCRC)
{
	bool	fnRetVal = true;
	DWORD	start_time;

	// 1. Erase page (this command first sets the page).
	// 2. Send Write Page command with first half (pageHalf=0) of the page data.
	// 3. Wait and receive ack from device. This indicates that the device has received the data.
	// 4. Wait and receive 2nd ack from device. This indicates that the device has written the data to flash.
	// 5. Send Write Page command with second half (pageHalf=1) of the page data.
	// 6. Wait and receive ack from device. This indicates that the device has received the data.
	// 7. Wait and receive 2nd ack from device. This indicates that the device has written the data to flash.
	// 8. Wait and receive 2-byte CRC of page from device.

	//Erase the current page
	if (ErasePage(deviceHandle, page))
	{
		for (BYTE pageHalf = 0x00; pageHalf < 0x02; pageHalf++)
		{
			BYTE	code[PAGE_SIZE + 2];
			DWORD	numBytesWritten = 0;

			code[0] = CMD_WRITE_PAGE;
			code[1] = pageHalf;

			//Loop through PAGE_SIZE/2 bytes worth of data
			//and write the new byte
			for (int i = 0; i < PAGE_SIZE/2; i++) 
				code[i+2] = data[(page * PAGE_SIZE) + i + (pageHalf*PAGE_SIZE/2)];

			//Write [0x03, [pageHalf], and [DATA]] to the device
			if (CS_SI_Write(deviceHandle, code, (PAGE_SIZE/2) + 2, &numBytesWritten) == SI_SUCCESS)
			{
				DWORD numBytesInQueue = 0;
				DWORD queueStatus = 0;

				TRACE("Written code for WritePage command\n");

				start_time = GetTickCount();

				//Wait til we have data in the queue
				while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
				{
					if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
					{
						//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
						fnRetVal = false;
					}
				}

				TRACE("Checked queue for initial ack (WritePage)\n");

				BYTE status = COMMAND_FAILED;
				DWORD numBytesRead = 0;

				if ((fnRetVal == true) && (numBytesInQueue >= 1))
				{
					//Read the success of the command
					if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
					{
						TRACE("Read status of initial ack (WritePage)\n");

						if (status == COMMAND_OK)
						{
							numBytesInQueue = 0;
							queueStatus = 0;

							start_time = GetTickCount();

							//Wait til we have data in the queue
							while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
							{
								if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
								{
									//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
									fnRetVal = false;
								}
							}

							TRACE("Checked queue again for write complete (WritePage)\n");

							if ((fnRetVal == true) && (numBytesInQueue >= 1))
							{
								//Read the success of the write
								if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
								{
									TRACE("Read status again for write complete (WritePage)\n");

									if (status == COMMAND_OK)
									{
										if (pageHalf == 0x01)
										{
											start_time = GetTickCount();

											while ((numBytesInQueue < 2) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
											{
												if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
												{
													//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
													fnRetVal = false;
												}
											}
											
											TRACE("Checked queue for CRC (WritePage)\n");

											if ((fnRetVal == true) && (numBytesInQueue >= 2))
											{
												BYTE crc[2] = {0x00, 0x00};
												if (CS_SI_Read(deviceHandle, crc, 2, &numBytesRead) == SI_SUCCESS)
												{
													TRACE("Read 2-byte CRC (WritePage)\n");

													//Convert the firmware CRC
													*pageCRC = (crc[0] << 8) + crc[1];										
												}
												else
												{
													//MessageBox(NULL, "Device Failed to read CRC at the end of page write", "Error", MB_OK);
													fnRetVal = false;
													break; //force exit from for loop
												}
											}
										}
										else
										{
											// Do nothing extra if first half of page
										}
									}
									else
									{
										//MessageBox(NULL, "Device Failed to Write Page", "Error", MB_OK);
										fnRetVal = false;
										break; //force exit from for loop
									}
								}
								else
								{
									//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
									fnRetVal = false;
									break; //force exit from for loop
								}
							}
						}
						else
						{
							//MessageBox(NULL, "Device Failed to Init Data For Page", "Error", MB_OK);
							fnRetVal = false;
							break; //force exit from for loop
						}
					}
					else
					{
						//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
						fnRetVal = false;
						break; //force exit from for loop
					}
				}
			}
			else
			{
				//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
				fnRetVal = false;
				break; //force exit from for loop
			}
		}
	}
	else
	{
		//char	buf[10]; //tmp buffer used for the itoa function call
		//MessageBox(NULL, "Error Erasing Page " + (CString)itoa(page, buf, 10), "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** CheckCRCPage ***
//
// Retrieves the CRC of the current page; Current page is set by SetPage.
//-----------------------------------------------------------------------------
bool CheckCRCPage(HANDLE& deviceHandle, BYTE page, WORD* pageCRC)
{
	bool	fnRetVal = true;
	BYTE	code = CMD_CRC_PAGE;
	DWORD	numBytesWritten = 0;
	
	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		//Set the current page to check CRC on
		if (SetPage(deviceHandle, page))
		{
			//Write the 0x04 to get the current page's CRC
			if (CS_SI_Write(deviceHandle, &code, 1, &numBytesWritten) == SI_SUCCESS)
			{
				DWORD numBytesInQueue = 0;
				DWORD queueStatus = 0;

				DWORD start_time = GetTickCount();

				//Wait til we have data in the queue
				while ((numBytesInQueue < 2) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
				{
					if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
					{
						//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
						fnRetVal = false;
					}
				}

				if ((fnRetVal == true) && (numBytesInQueue >= 2))
				{
					BYTE crc[2] = {0x00, 0x00};			
					DWORD numBytesRead = 0;

					//Read in the two byte CRC
					if (CS_SI_Read(deviceHandle, crc, 2, &numBytesRead) == SI_SUCCESS)
					{
						//Convert the firmware CRC
						*pageCRC = (crc[0] << 8) + crc[1];
					}
					else
					{
						//MessageBox(NULL, "Device Failed to read CRC", "Error", MB_OK);
						fnRetVal = false;
					}
				}
			}
			else
			{
				//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
				fnRetVal = false;
			}
		}
		else
		{
			//MessageBox(NULL, "Error Setting Page", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** ResetDevice ***
//
// Resets the device (device performs a software reset).
//-----------------------------------------------------------------------------
bool ResetDevice(HANDLE& deviceHandle)
{
	bool	fnRetVal = true;
	BYTE	code = CMD_SW_RESET;
	DWORD	numBytesWritten = 0;

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		if (CS_SI_Write(deviceHandle, &code, 1, &numBytesWritten) != SI_SUCCESS)
		{
			//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** SetFlashKeyCodes ***
//
// Sends the Flash key codes to the device; These key codes are required to
// erase or write Flash memory.
//-----------------------------------------------------------------------------
bool SetFlashKeyCodes (HANDLE& deviceHandle, BYTE key0, BYTE key1)
{
	bool	fnRetVal = true;
	BYTE	code[3] = {CMD_SET_FLASH_KEYS, key0, key1};
	DWORD	numBytesWritten = 0;
	BYTE	status;

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		if (CS_SI_Write(deviceHandle, code, 3, &numBytesWritten) == SI_SUCCESS)
		{
			DWORD numBytesInQueue = 0;
			DWORD queueStatus = 0;
			DWORD start_time = GetTickCount();

			while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
			{
				if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
				{
					//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
					fnRetVal = false;
				}
			}
			
			if ((fnRetVal == true) && (numBytesInQueue >= 1))
			{
				DWORD numBytesRead = 0;

				if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
				{
					if (status != COMMAND_OK)
					{
						fnRetVal = false;
					}
					else
					{
						// Do nothing here; return true by default
					}
				}
				else
				{
					//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
					fnRetVal = false;
				}
			}
		}
		else
		{
			//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}

//-----------------------------------------------------------------------------
// *** WriteSignature ***
//
// Writes the 2-byte signature to the device. After the signature is written,
// the application firmware is ready to be executed.
//-----------------------------------------------------------------------------
bool WriteSignature (HANDLE& deviceHandle)
{
	bool	fnRetVal = true;
	BYTE	code[3];
	DWORD	numBytesWritten = 0;
	BYTE	status;

	code[0] = CMD_WRITE_SIGNATURE;
	code[1] = (BYTE)(REF_SIGNATURE & 0x00FF);
	code[2] = (BYTE)((REF_SIGNATURE >> 8) & 0x00FF);

	if (deviceHandle != INVALID_HANDLE_VALUE)
	{
		if (CS_SI_Write(deviceHandle, code, 3, &numBytesWritten) == SI_SUCCESS)
		{
			DWORD numBytesInQueue = 0;
			DWORD queueStatus = 0;
			DWORD start_time = GetTickCount();

			while ((numBytesInQueue < 1) && ((GetTickCount() - start_time) < USBX_CHECKRXQUEUE_TIMEOUT))
			{
				if (CS_SI_CheckRXQueue(deviceHandle, &numBytesInQueue, &queueStatus) != SI_SUCCESS)
				{
					//MessageBox(NULL, "Error Checking Queue", "Error", MB_OK);
					fnRetVal = false;
				}
			}
			
			if ((fnRetVal == true) && (numBytesInQueue >= 1))
			{
				DWORD numBytesRead = 0;

				if (CS_SI_Read(deviceHandle, &status, 1, &numBytesRead) == SI_SUCCESS)
				{
					if (status == SIGNATURE_NOT_ERASED)
					{
						//MessageBox(NULL, "Validation Signature should be erased before attempting to rewrite Signature", "Error", MB_OK);
						fnRetVal = false;
					}
					else if (status != COMMAND_OK)
					{
						//MessageBox(NULL, "Unknown error occured!", "Error", MB_OK);
						fnRetVal = false;
					}
					else
					{
						// Do nothing here (return true by default)
					}
				}
				else
				{
					//MessageBox(NULL, "Error Reading Data", "Error", MB_OK);
					fnRetVal = false;
				}
			}
		}
		else
		{
			//MessageBox(NULL, "Error Sending Code", "Error", MB_OK);
			fnRetVal = false;
		}
	}
	else
	{
		//MessageBox(NULL, "Invalid Device Handle", "Error", MB_OK);
		fnRetVal = false;
	}

	return fnRetVal;
}