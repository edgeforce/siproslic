@ECHO OFF
CD %~pd0
REM rename the actual build file:
COPY /Y USB_BL_Build.txt ..\USB_BL_Build.bat
CD %~pd0\..\
REM call build file with parameter
call USB_BL_Build.bat _C8051F320_1_  %1%
if "%1%" NEQ "FREE_MODE" (MOVE /Y USB_BL_F320_1_16K* .\Auto_gen_BL_HEX\)
REM rename build file extension to prevent accidental launch by user
DEL USB_BL_Build.bat
ECHO.