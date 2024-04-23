// USBBootloaderDlg.h : header file
//

#if !defined(AFX_USBBOOTLOADERDLG_H__514808EC_4B71_43FB_B360_308552535082__INCLUDED_)
#define AFX_USBBOOTLOADERDLG_H__514808EC_4B71_43FB_B360_308552535082__INCLUDED_

#include "USB_BL_Interface.h"
#include "FirmwareInterface.h"
#include <dbt.h>				// ***For Surprise Removal Handling***
#include <initguid.h>			// ***For Surprise Removal Handling***
#include <windows.h>			// ***For Surprise Removal Handling***

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ***For Surprise Removal Handling*** (USBXpress GUID)
DEFINE_GUID(GUID_INTERFACE_USBXPRESS, 0x3C5E1462L, 0x5695, 0x4E18, \
            0x87, 0x6B, 0xF3, 0xF3, 0xD0, 0x8A, 0xAF, 0x18);

/////////////////////////////////////////////////////////////////////////////
// CUSBBootloaderDlg dialog

class CUSBBootloaderDlg : public CDialog
{
// Construction
public:
	
	HANDLE m_DeviceHandle;
	DWORD m_DeviceCount;
	DEVICE_INFO_BLOCK m_DeviceInfo;
	CString m_LinkName;

	void FillHostVersionInfo();
	bool FillDeviceVersionInfo();
	bool GetSerialString(DWORD dwDeviceNum, LPVOID lpvDeviceString);

	void FillDeviceList();

	BYTE m_Memory[MEMORY_SIZE];
	BYTE m_PageFlags[MEMORY_SIZE/PAGE_SIZE];
	BYTE m_EndPage;

	BYTE m_Dev_Code_HexFile;
	BYTE m_App_FW_Ver_HexFile_high;
	BYTE m_App_FW_Ver_HexFile_low;
	bool ReadHexImage();
	
	UINT CheckSoftwareCRCPage(BYTE page);
	
	bool WriteFlashMemory();
	
	UINT CUSBBootloaderDlg::UpdateCRC(UINT crc, BYTE newbyte);
	BYTE HexWordToByte(WORD w);
	UINT HexStringToValue(CString s, int size);
	bool CUSBBootloaderDlg::FileRead(CFile* file, void* buf, UINT numBytes);
	
	CUSBBootloaderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUSBBootloaderDlg)
	enum { IDD = IDD_USBBOOTLOADER_DIALOG };
	CProgressCtrl	m_Progress;
	CButton	m_OpenClose;
	CComboBox	m_DeviceList;
	CString	m_File;
	CString	m_DeviceCode;
	CString	m_BL_FW_Ver;
	CString	m_BL_SW_Ver;
	CString	m_DevCodeDesc;
	CString	m_Num_USBX_Devs;
	CString	m_USBX_DLL_Ver;
	CString	m_USBX_Driver_Ver;
	CString	m_USBX_FWLib_Ver;
	CString	m_Num_BL_Devs;
	CString	m_Signature_Status;
	CString	m_USB_SerialString;
	CString	m_App_FW_Ver;
	CString	m_App_FW_Ver_HexFile;
	CString	m_DeviceCode_HexFile;
	CString	m_DevCodeDesc_HexFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSBBootloaderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUSBBootloaderDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOpen();
	virtual void OnOK();
	afx_msg void OnButtonBrowse();
	afx_msg void OnButtonDownload();
	afx_msg void OnDestroy();
	afx_msg void OnButtonResetDevice();
	afx_msg void OnButtonHelp();
	//}}AFX_MSG
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData); // ***For Surprise Removal Handling***
	DECLARE_MESSAGE_MAP()

private:
	void RegisterNotification();	// ***For Surprise Removal Handling***
	void UnregisterNotification();	// ***For Surprise Removal Handling***
	HDEVNOTIFY m_hNotifyDevNode;	// ***For Surprise Removal Handling***
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBBOOTLOADERDLG_H__514808EC_4B71_43FB_B360_308552535082__INCLUDED_)
