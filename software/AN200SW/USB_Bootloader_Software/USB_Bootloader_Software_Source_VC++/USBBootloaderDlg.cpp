// USBBootloaderDlg.cpp : implementation file
//
// Revision history:
// 19OCT2007-PKC: 
// -Updated many components to add Surprise removal handling, and to make code compatible with changes to 
//  the USB BL firmware.
// -Updated the UI in the dialog for better usability.
// 13SEP2005-PKC: Typecasted "offsetHex" to WORD in CUSBBootloaderDlg::ReadHexImage() to eliminate warnings.
// 13SEP2005-PKC: Typecasted "pow(16,i)" to UINT in CUSBBootloaderDlg::HexStringToValue() to eliminate warnings.
// 13SEP2005-PKC: Doubled progress bar steps and made it smoother
// 01NOV2012-SHY: Add 'F38x; Fix the warring of pow()

#include "stdafx.h"
#include "USBBootloader.h"
#include "USBBootloaderDlg.h"
#include "SiUSBXp.h"
#include "SiUSBXp_ThreadSync.h"
#include <math.h>
#include "VersionNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRITICAL_SECTION gCS;	// ***For Surprise Removal Handling***

////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_BL_Ver;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_BL_Ver = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_ABOUT_BL_VER, m_BL_Ver);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	UpdateData(TRUE);
	m_BL_Ver = FILESTR_DISP;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CUSBBootloaderDlg dialog

CUSBBootloaderDlg::CUSBBootloaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUSBBootloaderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUSBBootloaderDlg)
	m_File = _T("");
	m_DeviceCode = _T("");
	m_BL_FW_Ver = _T("");
	m_BL_SW_Ver = _T("");
	m_DevCodeDesc = _T("");
	m_Num_USBX_Devs = _T("");
	m_USBX_DLL_Ver = _T("");
	m_USBX_Driver_Ver = _T("");
	m_USBX_FWLib_Ver = _T("");
	m_Num_BL_Devs = _T("");
	m_Signature_Status = _T("");
	m_USB_SerialString = _T("");
	m_App_FW_Ver = _T("");
	m_App_FW_Ver_HexFile = _T("");
	m_DeviceCode_HexFile = _T("");
	m_DevCodeDesc_HexFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUSBBootloaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUSBBootloaderDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_BUTTON_OPEN, m_OpenClose);
	DDX_Control(pDX, IDC_COMBO_DEVICES, m_DeviceList);
	DDX_Text(pDX, IDC_EDIT_FILE, m_File);
	DDX_Text(pDX, IDC_STATIC_DEVICECODE, m_DeviceCode);
	DDX_Text(pDX, IDC_STATIC_BL_FW_VER, m_BL_FW_Ver);
	DDX_Text(pDX, IDC_STATIC_BL_SW_VER, m_BL_SW_Ver);
	DDX_Text(pDX, IDC_STATIC_DEVCODE_DESC, m_DevCodeDesc);
	DDX_Text(pDX, IDC_STATIC_NUM_USBX_DEVS, m_Num_USBX_Devs);
	DDX_Text(pDX, IDC_STATIC_USBX_DLL_VER, m_USBX_DLL_Ver);
	DDX_Text(pDX, IDC_STATIC_USBX_DRIVER_VER, m_USBX_Driver_Ver);
	DDX_Text(pDX, IDC_STATIC_USBX_FWLIB_VER, m_USBX_FWLib_Ver);
	DDX_Text(pDX, IDC_STATIC_NUM_BL_DEVS, m_Num_BL_Devs);
	DDX_Text(pDX, IDC_STATIC_SIGNATURE_STATUS, m_Signature_Status);
	DDX_Text(pDX, IDC_STATIC_USB_SERIAL_STRING, m_USB_SerialString);
	DDX_Text(pDX, IDC_STATIC_APP_FW_VER, m_App_FW_Ver);
	DDX_Text(pDX, IDC_STATIC_APP_FW_VER_HEX_FILE, m_App_FW_Ver_HexFile);
	DDX_Text(pDX, IDC_STATIC_DEVICECODE_HEXFILE, m_DeviceCode_HexFile);
	DDX_Text(pDX, IDC_STATIC_DEVCODE_DESC_HEXFILE, m_DevCodeDesc_HexFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUSBBootloaderDlg, CDialog)
	//{{AFX_MSG_MAP(CUSBBootloaderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOAD, OnButtonDownload)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_RESET_DEVICE, OnButtonResetDevice)
	ON_BN_CLICKED(IDC_BUTTON_RESET_DEVICE, OnButtonResetDevice)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()	// ***For Surprise Removal Handling***
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUSBBootloaderDlg message handlers

BOOL CUSBBootloaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//Set the handle to the device to INVALID
	m_DeviceHandle = INVALID_HANDLE_VALUE;

	//Set link name to invalid
	m_LinkName = "Invalid";

	// ***For Surprise Removal Handling***
	// Initialize critical section object
	InitializeCriticalSection (&gCS);
	
	// Register for device notification
	RegisterNotification();

	// Set the progress bar to zero
	m_Progress.SetPos(0);
	
	if(CS_SI_SetTimeouts (USBX_READ_TIMEOUT, USBX_WRITE_TIMEOUT) != SI_SUCCESS)
		MessageBox("Unable to set Read/Write Timeouts!");

	FillHostVersionInfo();
	FillDeviceVersionInfo();

	// Fill the list of USBXpress devices
	FillDeviceList();

	//////////////////////////////////////////////////////////

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUSBBootloaderDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// ***For Surprise Removal Handling***
	// Un-register the device notification
	UnregisterNotification();

	// ***For Surprise Removal Handling***
	// Delete critical section object
	DeleteCriticalSection (&gCS);
}

void CUSBBootloaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUSBBootloaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUSBBootloaderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ***For Surprise Removal Handling*** START--->

void CUSBBootloaderDlg::RegisterNotification()
{
	DEV_BROADCAST_DEVICEINTERFACE devIF = {0};
	devIF.dbcc_size = sizeof(devIF);   
	devIF.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;   
	devIF.dbcc_classguid = GUID_INTERFACE_USBXPRESS;

	m_hNotifyDevNode = RegisterDeviceNotification(GetSafeHwnd(), &devIF, DEVICE_NOTIFY_WINDOW_HANDLE);
}

void CUSBBootloaderDlg::UnregisterNotification()
{
	if (m_hNotifyDevNode != NULL)
	{
		UnregisterDeviceNotification(m_hNotifyDevNode);
		m_hNotifyDevNode = NULL;
	}
}

BOOL CUSBBootloaderDlg::OnDeviceChange(UINT nEventType, DWORD dwData)
{ 
	CString openClose;
	CString closedLinkName;

	switch(nEventType)
	{
		case DBT_DEVICEARRIVAL:       
			// A device has been inserted and is now available.
			// Refresh the device list 
			FillDeviceList();
			break;
		case DBT_DEVICEREMOVECOMPLETE:       
			// Device has been removed.

			// Confirm this notification derives from the target device
			if (((DEV_BROADCAST_HDR *)dwData)->dbch_devicetype != DBT_DEVTYP_DEVICEINTERFACE)
				break;
			if (((DEV_BROADCAST_DEVICEINTERFACE *)dwData)->dbcc_classguid != GUID_INTERFACE_USBXPRESS)
				break;

			// Save the "link name" of the device that was removed
			closedLinkName = ((DEV_BROADCAST_DEVICEINTERFACE *)dwData)->dbcc_name;

			m_OpenClose.GetWindowText(openClose);
			if (openClose == "Close" && closedLinkName.CompareNoCase(m_LinkName) == 0)	
			{
				// If the button text is "Close", it means a handle is currently open
				// If the link names match, it means the open device is the one that was removed
				
				if (m_DeviceHandle != INVALID_HANDLE_VALUE)
				{
					// Close handle and clean up
					if(CS_SI_Close(m_DeviceHandle) != SI_SUCCESS)
					{
						MessageBox("Unable to close device handle!");
					}
				}
				m_DeviceHandle = INVALID_HANDLE_VALUE;
				m_LinkName = "Invalid";
				m_OpenClose.SetWindowText("Open");
				m_EndPage = APP_START_PAGE;
				GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_RESET_DEVICE)->EnableWindow(false);
				GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(false);
				GetDlgItem(IDC_EDIT_FILE)->EnableWindow(false);
				GetDlgItem(IDC_COMBO_DEVICES)->EnableWindow(true);
				m_File.Empty();
				m_DeviceCode.Empty();
				UpdateData(FALSE);
				FillDeviceList();
				FillDeviceVersionInfo();
				m_Progress.SetPos(0);
			}
			else
			{
				// This means an USBXpress device was removed, but it is not the one
				// we are holding an open handle to.
				// Call this function to refresh the count of available devices
				FillDeviceList();	
			}
			break;   
		default:       
			break;   
	}   
	return TRUE;
}

// ***For Surprise Removal Handling*** END---<

void CUSBBootloaderDlg::FillDeviceList()
{
	//////////////////////////////////////////////////////////
	//Fill Device List so we can determine which one to use

	CString openClose;
	DWORD BL_DeviceCount = 0;
	
	m_DeviceCount	= 0;
	m_OpenClose.GetWindowText(openClose);

	if (openClose == "Open")
	{
		//Reset the list if no handle is currently open
		m_DeviceList.ResetContent();
	}

	//Get the number of the devices
	if (CS_SI_GetNumDevices(&m_DeviceCount) == SI_SUCCESS)
	{
		SI_DEVICE_STRING devStr;

		//Put the string of each bootloadable device in the list
		for (DWORD i = 0; i < m_DeviceCount; i++)
		{
			if(GetSerialString(i, devStr) == true)
			{
				if (openClose == "Open")
				{
					//Add serial string to list if no handle is currently open
					m_DeviceList.AddString((CString)devStr);
				}
				BL_DeviceCount++;
			}
		}


		if (openClose == "Open")
		{
			// If the button text is "Open", it means no handle is currently open
			if(BL_DeviceCount > 0)
			{
				m_DeviceList.SetCurSel(0);
				GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(true);	// Enable "Open" button
				GetDlgItem(IDC_COMBO_DEVICES)->EnableWindow(true);	// Enable combo box
			}
		}
		else
		{
			// If a handle is already open, do not change combo box state
		}
	}

	UpdateData(TRUE);
	m_Num_USBX_Devs.Format("%d", m_DeviceCount);
	m_Num_BL_Devs.Format("%d", BL_DeviceCount);
	UpdateData(FALSE);

	if(BL_DeviceCount == 0)
	{
		GetDlgItem(IDC_BUTTON_OPEN)->EnableWindow(false);	// Disable "Open" button
		GetDlgItem(IDC_COMBO_DEVICES)->EnableWindow(false); // Disable combo box;
	}
}

void CUSBBootloaderDlg::FillHostVersionInfo()
{
	DWORD hver, lver;
	//m_BL_SW_Ver.Format("%d",
	
	// Get DLL version
	if (CS_SI_GetDLLVersion (&hver, &lver) != SI_SUCCESS)
	{
		MessageBox("Error reading USBXpress DLL version");
	}

	UpdateData(TRUE);
	m_USBX_DLL_Ver.Format("%d.%d.%d.%d", (WORD)(hver >> 16), (WORD)(hver & 0x0000FFFF), (WORD)(lver >> 16), (WORD)(lver & 0x0000FFFF));
	UpdateData(FALSE);

	// Get Driver version
	if (CS_SI_GetDriverVersion (&hver, &lver) != SI_SUCCESS)
	{
		MessageBox("Error reading USBXpress Driver version");
	}

	UpdateData(TRUE);
	m_USBX_Driver_Ver.Format("%d.%d.%d.%d", (WORD)(hver >> 16), (WORD)(hver & 0x0000FFFF), (WORD)(lver >> 16), (WORD)(lver & 0x0000FFFF));
	UpdateData(FALSE);

	UpdateData(TRUE);
	m_BL_SW_Ver = FILEVER_DISP;
	UpdateData(FALSE);
}

bool CUSBBootloaderDlg::FillDeviceVersionInfo()
{
	BYTE deviceEndPage[NUM_DEVICECODES] = {APP_END_PAGE_01,APP_END_PAGE_02,APP_END_PAGE_03,APP_END_PAGE_04,APP_END_PAGE_05,APP_END_PAGE_06};
	CString deviceDesc[NUM_DEVICECODES] = {MCU_DESC_01,MCU_DESC_02,MCU_DESC_03,MCU_DESC_04,MCU_DESC_05,MCU_DESC_06};

	if (m_DeviceHandle != INVALID_HANDLE_VALUE)
	{
		if(!GetDeviceInfo (m_DeviceHandle, &m_DeviceInfo))
		{
			MessageBox ("Error reading device bootloader version");
			return false;
		}
		else
		{
			UpdateData(TRUE);

			m_USBX_FWLib_Ver.Format ("%d.%d", m_DeviceInfo.USBX_FWLib_ver_high, m_DeviceInfo.USBX_FWLib_ver_low);
			m_BL_FW_Ver.Format ("%d.%d", m_DeviceInfo.BL_FW_ver_high, m_DeviceInfo.BL_FW_ver_low);
			
			if(m_DeviceInfo.App_FW_ver_high == 0xFF && m_DeviceInfo.App_FW_ver_low == 0xFF)
			{
				m_App_FW_Ver.Format ("None");
			}
			else
			{
				m_App_FW_Ver.Format ("%d.%d", m_DeviceInfo.App_FW_ver_high, m_DeviceInfo.App_FW_ver_low);
			}

			if(m_DeviceInfo.signature == REF_SIGNATURE)
			{
				m_Signature_Status.Format ("Valid");
			}
			else
			{
				m_Signature_Status.Format ("Invalid");
			}

			UpdateData(FALSE);

			if( (m_DeviceInfo.devCode < MCU_C8051F320_1) || (m_DeviceInfo.devCode > MCU_C8051F320_1+NUM_DEVICECODES-1) )
			{
				MessageBox("This device has a version of the bootloader firmware that is incompatible with this bootloader software");
				return false;
			}
			else
			{					
				UpdateData(TRUE);
				m_DeviceCode.Format("0x%2X", m_DeviceInfo.devCode);
				m_DevCodeDesc.Format("%s", deviceDesc[(m_DeviceInfo.devCode & ~0x80)-1]);
				UpdateData(FALSE);

				m_EndPage = deviceEndPage[(m_DeviceInfo.devCode & ~0x80)-1];
			}
		}
	}
	else
	{
		UpdateData(TRUE);
		m_USB_SerialString = "---";
		m_USBX_FWLib_Ver = "---";
		m_BL_FW_Ver = "---";
		m_App_FW_Ver = "---";
		m_App_FW_Ver_HexFile = "---";
		m_Signature_Status = "---";
		m_DeviceCode = "---";
		m_DevCodeDesc = "---";
		m_DeviceCode_HexFile = "---";
		m_DevCodeDesc_HexFile = "---";
		UpdateData(FALSE);
		return false;
	}

	return true;
}

void CUSBBootloaderDlg::OnButtonOpen() 
{
	// TODO: Add your control notification handler code here
	
	CString openClose;

	//Toggle the device Open or Closed
	m_OpenClose.GetWindowText(openClose);
	m_Progress.SetPos(0);

	if (m_DeviceList.GetCount() > 0)
	{
		if (openClose == "Open")
		{
			//Disable combo box;
			GetDlgItem(IDC_COMBO_DEVICES)->EnableWindow(false);
				
			int serial_len;
			int devSelectedIndex;
			devSelectedIndex = m_DeviceList.GetCurSel();
			serial_len = m_DeviceList.GetLBTextLen(devSelectedIndex);
			m_DeviceList.GetLBText(devSelectedIndex, m_DeviceInfo.SerialString.GetBuffer(serial_len));
			m_DeviceInfo.SerialString.ReleaseBuffer();

			DWORD Num_Devices;
			if (CS_SI_GetNumDevices(&Num_Devices) != SI_SUCCESS)
			{
				MessageBox("Error checking number of USBXpress devices!");
				openClose = "Close";
			}

			SI_DEVICE_STRING devStr;
			DWORD devIndex;
			for(devIndex = 0; devIndex < Num_Devices; devIndex++)
			{
				if(GetSerialString(devIndex, devStr) == true)
				{
					if ((CString)devStr == m_DeviceInfo.SerialString)
						break;
				}
			}

			if (devIndex == Num_Devices)
			{
				MessageBox("Error finding selected device!");
				openClose = "Close";
			}
	
			if (openClose = "Open")
			{
				if (CS_SI_GetProductString(devIndex, m_LinkName.GetBuffer(500), SI_RETURN_LINK_NAME) == SI_SUCCESS)
				{
					m_LinkName.ReleaseBuffer();
					if (CS_SI_Open(devIndex, &m_DeviceHandle) == SI_SUCCESS)
					{
						if(CS_SI_FlushBuffers(m_DeviceHandle,1,1) == SI_SUCCESS)
						{
							if (FillDeviceVersionInfo())
							{
								UpdateData(TRUE);
								m_USB_SerialString = m_DeviceInfo.SerialString;
								UpdateData(FALSE);

								m_OpenClose.SetWindowText("Close");
								GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow(true);
								GetDlgItem(IDC_BUTTON_RESET_DEVICE)->EnableWindow(true);
								GetDlgItem(IDC_EDIT_FILE)->EnableWindow(true);
							}
							else
							{
								MessageBox("Failed to read device info!");
								openClose = "Close";
							}
						}
						else
						{
							MessageBox("Unable to flush device bufers!");
							openClose = "Close";
						}
					}
					else
					{
						MessageBox("Unable to open handle to device!");
						openClose = "Close";
					}
				}
				else
				{
					m_LinkName.ReleaseBuffer();
					MessageBox("Unable to retrive product string!");
					openClose = "Close";
				}			
			}
		}
		
		if (openClose == "Close")
		{
			if (m_DeviceHandle != INVALID_HANDLE_VALUE)
			{
				if(CS_SI_Close(m_DeviceHandle) != SI_SUCCESS)
				{
					MessageBox("Unable to close device handle!");
				}
			}
			m_DeviceHandle = INVALID_HANDLE_VALUE;
			m_LinkName = "Invalid";
			m_OpenClose.SetWindowText("Open");
			m_EndPage = APP_START_PAGE;
			GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_RESET_DEVICE)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(false);
			GetDlgItem(IDC_EDIT_FILE)->EnableWindow(false);
			GetDlgItem(IDC_COMBO_DEVICES)->EnableWindow(true);
			m_File.Empty();
			m_DeviceCode.Empty();
			UpdateData(FALSE);
			FillDeviceList();
			FillDeviceVersionInfo();
			m_Progress.SetPos(0);
		}
	}
	else
	{
		MessageBox("No devices available in bootload mode!");
	}
}

void CUSBBootloaderDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//If we exit, close the device
	if (m_DeviceHandle != INVALID_HANDLE_VALUE)
	{
		if(CS_SI_Close(m_DeviceHandle) != SI_SUCCESS)
		{
			//MessageBox("Unable to close device handle!");
		}
		m_DeviceHandle = INVALID_HANDLE_VALUE;
	}

	//CDialog::OnOK();
	CDialog::OnCancel();
}

void CUSBBootloaderDlg::OnButtonBrowse() 
{
	UINT i;
	BYTE deviceEndPage[NUM_DEVICECODES] = {APP_END_PAGE_01,APP_END_PAGE_02,APP_END_PAGE_03,APP_END_PAGE_04,APP_END_PAGE_05,APP_END_PAGE_06};
	CString deviceDesc[NUM_DEVICECODES] = {MCU_DESC_01,MCU_DESC_02,MCU_DESC_03,MCU_DESC_04,MCU_DESC_05,MCU_DESC_06};
	bool fnStatus = true;
	
	//Pop up a browse dialog for the hex file
	CFileDialog	fileDlg(TRUE, "hex", NULL, OFN_OVERWRITEPROMPT, "Hex Files (*.hex)|*.hex|All Files (*.*)|*.*|");
	
	CDocTemplate* templateID = NULL;

	if (fileDlg.DoModal() == IDOK)	
	{
		m_File = fileDlg.GetPathName();
		UpdateData(FALSE);

		//Clear out all of our software memory
		for (i = 0; i < MEMORY_SIZE; i++)
		{
			m_Memory[i] = 0xFF;
		}

		//Clear out all page flags
		for (i = 0; i < MEMORY_SIZE/PAGE_SIZE; i++)
		{
			m_PageFlags[i] = 0;
		}

		if (ReadHexImage())
		{
			// Find the last page specified by the hex file
			UINT lastHexFilePage;
			for (lastHexFilePage = MEMORY_SIZE/PAGE_SIZE-1; lastHexFilePage > 0; lastHexFilePage--)
			{
				if (m_PageFlags[lastHexFilePage] != 0)
					break;
			}

			// See if the last page specified by the hex file matches any known last pages
			for (i = 0; i < NUM_DEVICECODES; i++)
			{
				if (deviceEndPage[i] == lastHexFilePage)
					break;
			}
			
			if (i == NUM_DEVICECODES)
			{
				// Hex file last page did not match any known device last pages
				MessageBox("The device specified by this hex file is not supported by this bootloader!");
				fnStatus = false;
			}
			else
			{
				m_Dev_Code_HexFile = m_Memory[(((lastHexFilePage+1)*PAGE_SIZE)-5)];
				m_App_FW_Ver_HexFile_high = m_Memory[(((lastHexFilePage+1)*PAGE_SIZE)-4)];
				m_App_FW_Ver_HexFile_low = m_Memory[(((lastHexFilePage+1)*PAGE_SIZE)-3)];

				UpdateData(TRUE);

				if(m_App_FW_Ver_HexFile_high == 0xFF && m_App_FW_Ver_HexFile_low == 0xFF)
				{
					m_App_FW_Ver_HexFile.Format ("None");
				}
				else
				{
					m_App_FW_Ver_HexFile.Format ("%d.%d", m_App_FW_Ver_HexFile_high, m_App_FW_Ver_HexFile_low);
				}
				
				m_DeviceCode_HexFile.Format("0x%2X", m_Dev_Code_HexFile);
				
				if( (m_Dev_Code_HexFile < MCU_C8051F320_1) || (m_Dev_Code_HexFile > MCU_C8051F320_1+NUM_DEVICECODES-1) )
				{
					MessageBox("The selected hex file has a device code that is not recognized by this bootloader software!");
					fnStatus = false;
				}
				else
				{
					m_DevCodeDesc_HexFile.Format("%s", deviceDesc[(m_Dev_Code_HexFile & ~0x80)-1]);

					if (m_Dev_Code_HexFile == m_DeviceInfo.devCode)
					{
						// Enable the "Download" button
						GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(true);
						
						// Reset the progress bar
						m_Progress.SetPos(0);
					}
					else
					{
						MessageBox("The device code in the hex file does not match the selected device!");
						// Do not set fnStatus to false because we still want to display info
						// about this hex file to the user.

						// Disable the "Download" button
						GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(false);
					}
				}
				
				UpdateData(FALSE);
			}
		}
		else
		{
			MessageBox("Error Getting Data From Hex File");
			fnStatus = false;
		}

		if (fnStatus == false)
		{			
			// Disable the "Download" button
			GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(false);

			// Clear display strings
			UpdateData(TRUE);
			m_App_FW_Ver_HexFile = "---";
			m_DeviceCode_HexFile = "---";
			m_DevCodeDesc_HexFile = "---";
			UpdateData(FALSE);
		}
	}
}

/////////////////////////////////////////////////////////
// OnButtonDownload - Begins the Downloading of new firmware
/////////////////////////////////////////////////////////
void CUSBBootloaderDlg::OnButtonDownload() 
{
	// TODO: Add your control notification handler code here
	
	UINT NumPagesToWrite = 0;
	UINT i;
	CString temp;

	UpdateData(TRUE);
	m_Progress.SetPos(0);

	if(m_App_FW_Ver_HexFile_high == 0xFF && m_App_FW_Ver_HexFile_low == 0xFF)
	{
		temp.Format("It appears that the hex file you are trying to download does not have a valid version number.\nAre you sure you want to proceed?");
		if(MessageBox(temp, NULL, MB_YESNO) == IDNO)
		{
			return;
		}
	}
	else if ( (((m_App_FW_Ver_HexFile_high << 8) + m_App_FW_Ver_HexFile_low) 
		< ((m_DeviceInfo.App_FW_ver_high << 8) + m_DeviceInfo.App_FW_ver_low)) 
		&& (((m_DeviceInfo.App_FW_ver_high << 8) + m_DeviceInfo.App_FW_ver_low) != 0xFFFF) )
	{
		temp.Format("It appears that you are trying to update a newer version of the firmware with an older version.\nAre you sure you want to replace device firmware version %d.%d with %d.%d?", 
			m_DeviceInfo.App_FW_ver_high, m_DeviceInfo.App_FW_ver_low,
			m_App_FW_Ver_HexFile_high, m_App_FW_Ver_HexFile_low);
		if(MessageBox(temp, NULL, MB_YESNO) == IDNO)
		{
			return;
		}
	}

	//Count flagged pages to see how many pages need to be written
	for (i = 0; i < MEMORY_SIZE/PAGE_SIZE; i++)
		NumPagesToWrite += m_PageFlags[i];

	m_Progress.SetRange(0, NumPagesToWrite + 2);	// Setup progress bar steps
	m_Progress.SetPos(1);

	//Write out new memory image to flash
	if (WriteFlashMemory())
	{
		m_Progress.SetPos(m_Progress.GetPos() + 1);
		GetDlgItem(IDC_BUTTON_DOWNLOAD)->EnableWindow(false);
		MessageBox("Successfully Loaded Image");
	}
	else
	{
		MessageBox("Failed to Load Image Properly\nPlease Check Settings and Try Again");
	}
}

/////////////////////////////////////////////////////////
// ReadHexImage - Reads the image of a specified hex
//	file and stores it into the software memory (on top
//	of any existing data)
/////////////////////////////////////////////////////////
bool CUSBBootloaderDlg::ReadHexImage()
{
	//////////////////////////////////////////////////////////
	// This will fill our memory array from a hex file

	CFile hexFile;
	bool fnRetVal = true;

	//Open a hex file
	if (hexFile.Open(m_File, CFile::modeRead))
	{
		WORD tmpHex			= 0x0000;
		WORD dataAmountHex	= 0x0000;
		DWORD offsetHex		= 0x00000000;
		WORD checkSumHex	= 0x0000;

		BYTE tmp		= 0x00;
		BYTE dataAmount = 0x00;
		WORD offset		= 0x0000;
		BYTE checkSum	= 0x00;

		BYTE sum = 0x00;

		bool eof = false;

		//Loop through each line until we reach the end of the file
		while (!eof)
		{
			//Read the first byte, which should be a ":" character (0x3A)
			if ((eof = FileRead(&hexFile, &tmp, 1)) == true)
				break;

			if (tmp == 0x3A)
			{
				//Reset sum for our checksum
				sum = 0x00;
				
				//Read in the amount of bytes in the line, the address the line starts at, and the record type
				eof = FileRead(&hexFile, &dataAmountHex, 2);
				eof = FileRead(&hexFile, &offsetHex, 4);
				eof = FileRead(&hexFile, &tmpHex, 2);
				if (eof == true)
					break;
				
				//Convert all ascii into data, and add values to the sum for the checksum
				dataAmount = HexWordToByte(dataAmountHex);
				sum += dataAmount;

				offset = ( HexWordToByte((WORD)(offsetHex)) << 8 ) & 0xFF00;
				sum += offset >> 8;
				offset |= HexWordToByte( (WORD)(offsetHex >> 16) ) & 0xFF;

				sum += offset;
				tmp = HexWordToByte(tmpHex);
				sum += tmp;

				//If the record type was data, then start reading it
				if (tmp == 0x00)
				{
					//Loop through the data and store it in our data array that maps to memory
					for (BYTE i = 0; i < dataAmount; i++)
					{
						if((eof = FileRead(&hexFile, &tmpHex, 2)) == true)
							break;

						tmp = HexWordToByte(tmpHex);

						if (((offset + i) < APP_START_ADDR) || ((offset + i) >= MEMORY_SIZE))
						{
							//MessageBox("Error: Address encountered in hex file that is beyond the allowed application address range!\nHex file processing aborted!");
							fnRetVal = false;
							break;
						}
						m_Memory[offset + i] = tmp;

						m_PageFlags[(offset+i)>>9] = 0x01; // Indicate that some data is specified in the hex file for this page

						sum += tmp;
					}

					if ((fnRetVal == false) || (eof == true))
					{
						// If there was an error detected in the for loop, exit the while loop as well
						break;
					}

					//Finally read the check sum
					if ((eof = FileRead(&hexFile, &checkSumHex, 2)) == true)
						break;

					checkSum = HexWordToByte(checkSumHex);
					sum += checkSum;

					//If the line's checksum isnt 0, then there was an error, close the file and stop reading
					if (sum != 0x00)
					{
						//MessageBox("Checksum failure in hex file");
						fnRetVal = false;
						break; // exit while loop
					}

					//Read the carriage returns to goto the next line
					if ((eof = FileRead(&hexFile, &tmpHex, 2)) == true)
						break;
				}				
				else if (tmp == 0x01)
				{
					//Otherwise, if we have reached the end-of-file record, then exit while loop without setting "eof"
					break;
					TRACE("hexfile parsing complete\n");
				}
				else
				{
					//Unknown record type; return error
					fnRetVal = false;
					break;
				}
			}
			else
			{
				//Otherwise if we didn't see a ":" then set the end of file, there was an error
				eof = true;
				break;
			}
		}
		
		if (eof)
		{
			// If we made it here, then something was wrong, so return error
			fnRetVal = false;
		}
	}
	else
	{
		// Cannot open hex file
		fnRetVal = false;
	}

	hexFile.Close();
	return fnRetVal;
}

/////////////////////////////////////////////////////////
// CheckSoftwareCRCPage - Returns the CRC on a page in
//	the software memory
/////////////////////////////////////////////////////////
UINT CUSBBootloaderDlg::CheckSoftwareCRCPage(BYTE page)
{
	//////////////////////////////////////////////////////////
	// Check the CRC from our memory array by specifying a page

   UINT CRC = 0;

   // Process each byte in the page into the running CRC
   for(UINT i = 0; i < PAGE_SIZE; i++)
   {
      CRC = UpdateCRC (CRC, m_Memory[(page * PAGE_SIZE) + i]);
   }

	return CRC;
}

// ---------------------------------------------------------------------------
// >>> UpdateCRC <<<
//
// This function accepts a CRC argument and a <newbyte> and returns an
// updated CRC value; Does not use a CRC Lookup Table
// ---------------------------------------------------------------------------
UINT CUSBBootloaderDlg::UpdateCRC(UINT crc, BYTE newbyte)
{
   BYTE i;					// loop counter

   #define CRC_POLY 0x8408      // CRC16-CCITT FCS (X^16+X^12+X^5+1)

   crc = crc ^ newbyte;

   for (i = 0; i < 8; i++)
   {
      if (crc & 0x01)
      {
         crc = crc >> 1;
         crc ^= CRC_POLY;
      }
      else
      {
         crc = crc >> 1;
      }
   }
   return crc;
}

/////////////////////////////////////////////////////////
// WriteFlashMemory - Writes the software memory to the
//	hardware flash memory
/////////////////////////////////////////////////////////
bool CUSBBootloaderDlg::WriteFlashMemory()
{
	char buf[10]; //tmp buffer used for itoa function calls

	// Step1: Set the Flash Key Codes to write/erase values
	if (!SetFlashKeyCodes (m_DeviceHandle, FLASH_KEY0, FLASH_KEY1))
	{
		MessageBox("Error setting Flash key codes");
		return false;
	}
	TRACE("flash key codes set\n");

	// Step2: Erase last user page to clear the Validation Signature
	if (!ErasePage (m_DeviceHandle, m_EndPage))
	{
		MessageBox("Error erasing Validation Signature page");
		return false;
	}
	TRACE("last app page erased\n");


	// Step3: Erase/Write/CRC Flash pages
	for (BYTE pageNum = APP_START_PAGE; pageNum <= m_EndPage; pageNum++)
	{	
		UINT pageCRC = 0x0000;

		if (m_PageFlags[pageNum] == 0)
			continue;	// Skip this page because the hex file did not specify any data in this page

		if (!WritePage(m_DeviceHandle, m_Memory, pageNum, &pageCRC))
		{
			MessageBox("Error Writing Page " + (CString)itoa(pageNum, buf, 10));
			return false;
		}
		TRACE("Erased/Written page # %d\n",pageNum);
		if (pageCRC != CheckSoftwareCRCPage (pageNum))
		{
			MessageBox("CRC Mismatch on Page " + (CString)itoa(pageNum, buf, 10));
			return false;
		}
		m_Progress.SetPos(m_Progress.GetPos() + 1);
	}


	// Step4: Write Signature
	if (!WriteSignature (m_DeviceHandle))
	{
		MessageBox("Error writing Validation Signature");
		return false;
	}
	TRACE("Written signature\n");

	// Step5: Read Signature and verify
	FillDeviceVersionInfo (); // This reads signature from device

	if (m_DeviceInfo.signature != REF_SIGNATURE)
	{
		MessageBox("Validation Signature Mismatch");
		return false;
	}

	// Step6: Clear the Flash Key Codes
	if (!SetFlashKeyCodes (m_DeviceHandle, 0x00, 0x00))
	{
		MessageBox("Error clearing Flash key codes");
		return false;
	}
	TRACE("Flash key codes cleared\n");
	
	return true;
}


////////////////////////////////
////// BUTTON FUNCTIONS ////////

void CUSBBootloaderDlg::OnButtonResetDevice() 
{
	// TODO: Add your control notification handler code here
	
	if (!ResetDevice(m_DeviceHandle))
		MessageBox("Error Resetting Firmware");
}



////////////////////////////////
////// FORMAT FUNCTIONS ////////

UINT CUSBBootloaderDlg::HexStringToValue(CString s, int size)
{
	//this function takes a hex string, and converts it
	//to a value
	
	UINT val = 0;

	s.TrimLeft();
	s.TrimRight();
	
	for (int i = s.GetLength(); i < size; i++)
	{
		s = '0' + s;
	}

	for (int i = 0; i < size; i++)
	{
		switch (s.GetAt((size-1)-i))
		{
		case '0' : val += 0*(UINT)(pow(16.0,i)); break;
		case '1' : val += 1*(UINT)(pow(16.0,i)); break;
		case '2' : val += 2*(UINT)(pow(16.0,i)); break;
		case '3' : val += 3*(UINT)(pow(16.0,i)); break;
		case '4' : val += 4*(UINT)(pow(16.0,i)); break;
		case '5' : val += 5*(UINT)(pow(16.0,i)); break;
		case '6' : val += 6*(UINT)(pow(16.0,i)); break;
		case '7' : val += 7*(UINT)(pow(16.0,i)); break;
		case '8' : val += 8*(UINT)(pow(16.0,i)); break;
		case '9' : val += 9*(UINT)(pow(16.0,i)); break;
		case 'A' : val += 10*(UINT)(pow(16.0,i)); break;
		case 'B' : val += 11*(UINT)(pow(16.0,i)); break;
		case 'C' : val += 12*(UINT)(pow(16.0,i)); break;
		case 'D' : val += 13*(UINT)(pow(16.0,i)); break;
		case 'E' : val += 14*(UINT)(pow(16.0,i)); break;
		case 'F' : val += 15*(UINT)(pow(16.0,i)); break;
		}
	}

	return val;
}

BYTE CUSBBootloaderDlg::HexWordToByte(WORD w)
{
	//this function takes a word containing the ascii hex
	//for a byte and returns it, ie. 3245 = 0x2E

	BYTE val = 0x00;

	switch ((w >> 8) & 0xFF)
	{
	case 0x30 : val |= 0x00; break;
	case 0x31 : val |= 0x01; break;
	case 0x32 : val |= 0x02; break;
	case 0x33 : val |= 0x03; break;
	case 0x34 : val |= 0x04; break;
	case 0x35 : val |= 0x05; break;
	case 0x36 : val |= 0x06; break;
	case 0x37 : val |= 0x07; break;
	case 0x38 : val |= 0x08; break;
	case 0x39 : val |= 0x09; break;
	case 0x41 : val |= 0x0A; break;
	case 0x42 : val |= 0x0B; break;
	case 0x43 : val |= 0x0C; break;
	case 0x44 : val |= 0x0D; break;
	case 0x45 : val |= 0x0E; break;
	case 0x46 : val |= 0x0F; break;
	}
	
	switch (w & 0xFF)
	{
	case 0x30 : val |= 0x00; break;
	case 0x31 : val |= 0x10; break;
	case 0x32 : val |= 0x20; break;
	case 0x33 : val |= 0x30; break;
	case 0x34 : val |= 0x40; break;
	case 0x35 : val |= 0x50; break;
	case 0x36 : val |= 0x60; break;
	case 0x37 : val |= 0x70; break;
	case 0x38 : val |= 0x80; break;
	case 0x39 : val |= 0x90; break;
	case 0x41 : val |= 0xA0; break;
	case 0x42 : val |= 0xB0; break;
	case 0x43 : val |= 0xC0; break;
	case 0x44 : val |= 0xD0; break;
	case 0x45 : val |= 0xE0; break;
	case 0x46 : val |= 0xF0; break;
	}

	return val;
}

bool CUSBBootloaderDlg::GetSerialString(DWORD dwDeviceNum, LPVOID lpvDeviceString)
{
	if (CS_SI_GetProductString(dwDeviceNum, lpvDeviceString, SI_RETURN_SERIAL_NUMBER) == SI_SUCCESS)
	{
		int iTemp;
		
		for (iTemp=0; *((char *)lpvDeviceString+iTemp) != '\0'; iTemp++);   //Go to end of string
		
		if(iTemp > 0)
		{
			if(*((char *)lpvDeviceString + iTemp - 1) == BOOTLOADER_MODE_SERIAL_STR_LAST_CHAR)
			{
				return true;
			}
			else
			{
				// return false by default
			}
		}
		else
		{
			// return false by default
		}
	}
	else
	{
		MessageBox("Error retrieving serial string!");
	}

	return false;
}

void CUSBBootloaderDlg::OnButtonHelp() 
{
	MessageBox("Please refer to application note AN200 available at www.silabs.com/MCU \nfor a full description of the USBXpress Bootloader");	
}

bool CUSBBootloaderDlg::FileRead(CFile* file, void* buf, UINT numBytes)
{
	// Returns EOF (end-of-file) status
	// true if end of file was reached during read
	// false if end of file was NOT reached during read

	if (file->Read(buf, numBytes) < numBytes)
	{
		return true;
	}
	else
	{
		return false;
	}
}