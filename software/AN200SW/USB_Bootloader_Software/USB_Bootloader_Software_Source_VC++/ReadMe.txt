Revision History:
08FEB2008-PKC:
	- Updated the version number to 2.0 and rebuilt.
19OCT2007-PKC: 
	-Updated many components to add Surprise removal handling, and to make code 
	 compatible with changes to the USB BL firmware.
	-Updated the UI in the dialog for better usability.
07MAR2007-PKC:
	Updated with the latest USBXpress DLL and SiUSBXp.* files, and rebuilt exe.
05DEC2006-PKC:
	Updated with the latest USBXpress DLL and SiUSBXp.* files
	Replaced the bootloader firmware command codes with macro definitions
	Updated the WritePage function in FirmwareInterface,cpp to work with the
	limited buffer size available in 'F326/7 devices (pages sent in 256-byte
	blocks instead of the previous 512-byte blocks)

13SEP2005-PKC:
	Replaced "F32x_" prefixed function calls with "SI_" prefixed function calls
	Replaced "F32x_" prefixed constants with "SI_" prefixed constants
	Replaced SiF32xUSB.* with SiUSBXp.* (.dll, .h, .lib)
	Replaced occurences of "SiF32xUSB.h" with "SiUSBXp.h"
	Replaced "SiF32xUSB.dll" in Project > Settings > Link with "SiUSBXp.lib"
	Replaced SI_FlsuhBuffers(<handle>) call with SI_FlsuhBuffers(<handle>,1,1)
	Doubled progress bar steps and made the process smoother

========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : USBBootloader
========================================================================


AppWizard has created this USBBootloader application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your USBBootloader application.

USBBootloader.dsp
    This file (the project file) contains information at the project level and
    is used to build a single project or subproject. Other users can share the
    project (.dsp) file, but they should export the makefiles locally.

USBBootloader.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CUSBBootloaderApp application class.

USBBootloader.cpp
    This is the main application source file that contains the application
    class CUSBBootloaderApp.

USBBootloader.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Visual C++.

USBBootloader.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

res\USBBootloader.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file USBBootloader.rc.

res\USBBootloader.rc2
    This file contains resources that are not edited by Microsoft 
	Visual C++.  You should place all resources not editable by
	the resource editor in this file.




/////////////////////////////////////////////////////////////////////////////

AppWizard creates one dialog class:

USBBootloaderDlg.h, USBBootloaderDlg.cpp - the dialog
    These files contain your CUSBBootloaderDlg class.  This class defines
    the behavior of your application's main dialog.  The dialog's
    template is in USBBootloader.rc, which can be edited in Microsoft
	Visual C++.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named USBBootloader.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC42XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC42DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
