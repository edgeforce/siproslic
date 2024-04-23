// USBBootloader.h : main header file for the USBBOOTLOADER application
//

#if !defined(AFX_USBBOOTLOADER_H__08766E97_D9B5_42C0_B779_A3D490207DE1__INCLUDED_)
#define AFX_USBBOOTLOADER_H__08766E97_D9B5_42C0_B779_A3D490207DE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUSBBootloaderApp:
// See USBBootloader.cpp for the implementation of this class
//

class CUSBBootloaderApp : public CWinApp
{
public:
	CUSBBootloaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUSBBootloaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUSBBootloaderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBBOOTLOADER_H__08766E97_D9B5_42C0_B779_A3D490207DE1__INCLUDED_)
