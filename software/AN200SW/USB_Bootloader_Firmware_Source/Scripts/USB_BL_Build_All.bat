@ECHO OFF
ECHO All output will be redirected to USB_BL_BuildLog.txt
ECHO.
ECHO %DATE% %TIME% > %~pd0\USB_BL_BuildLog.txt

ECHO Building for 'F320_16K...
CALL %~pd0\USB_BL_Build_F320_16K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

ECHO Building for 'F326_16K...
CALL %~pd0\USB_BL_Build_F326_16K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

ECHO Building for 'F340_32K...
CALL %~pd0\USB_BL_Build_F34X_32K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

ECHO Building for 'F340_64K...
CALL %~pd0\USB_BL_Build_F34X_64K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

ECHO Building for 'F380_32K...
CALL %~pd0\USB_BL_Build_F38X_32K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

ECHO Building for 'F380_64K...
CALL %~pd0\USB_BL_Build_F38X_64K.bat >> %~pd0\USB_BL_BuildLog.txt
ECHO Ok

CALL cleanup.bat >> %~pd0\USB_BL_BuildLog.txt

ECHO %DATE% %TIME% >> %~pd0\USB_BL_BuildLog.txt
ECHO.
ECHO All done! See USB_BL_BuildLog.txt for details.
ECHO.
PAUSE