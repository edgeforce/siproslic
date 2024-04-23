@ECHO OFF
ECHO.
ECHO.
cd %~pd0\..\Auto_gen_BL_HEX\
set /p COPY_CLEAN_BATCH=Want to copy clean batch files too? (y/Y = OK)   
if %COPY_CLEAN_BATCH% == y (set COPY_CLEAN_BATCH= Y)


ECHO. Copy object files to Device_Specific folders ...

ECHO. Copy F320_1_16K ...
copy /Y USB_BL_F320_1_16K.*     ..\..\Device_Specific\C8051F320_1\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                             ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel1\
copy /Y ..\USB_API.h                             ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel2\
copy /Y USB_BL_F320_1_16K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F320_1_16K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel2\  )



ECHO.
ECHO. Copy F326_7_16K ...
copy /Y USB_BL_F326_7_16K.*     ..\..\Device_Specific\C8051F326_7\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                             ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel1\
copy /Y ..\USB_API.h                             ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel2\
copy /Y USB_BL_F326_7_16K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F326_7_16K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel2\  )



ECHO.
ECHO.
ECHO. Copy F34X_32K ...
copy /Y USB_BL_F34X_32K.*       ..\..\Device_Specific\C8051F341_3_5_7\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel1\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel2\
copy /Y USB_BL_F34X_32K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F34X_32K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel2\ )



ECHO.
ECHO. Copy F34X_64K ...
copy /Y USB_BL_F34X_64K.*       ..\..\Device_Specific\C8051F340_2_4_6\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel1\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel2\
copy /Y USB_BL_F34X_64K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F34X_64K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel2\ )



ECHO.
ECHO.
ECHO. Copy F38X_32K ...
copy /Y USB_BL_F38X_32K.*       ..\..\Device_Specific\C8051F382_3_6_7\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel1\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel2\
copy /Y USB_BL_F38X_32K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F38X_32K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel2\ )



ECHO.
ECHO. Copy F38X_64K ...
copy /Y USB_BL_F38X_64K.*       ..\..\Device_Specific\C8051F380_1_4_5\USB_BL_Firmware_Image\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel1\
copy /Y ..\USB_API.h                           ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel2\
copy /Y USB_BL_F38X_64K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel1\USB_BL_APP_Shared.h
copy /Y USB_BL_F38X_64K_USB_BL_APP_Shared.h    ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel2\USB_BL_APP_Shared.h

if %COPY_CLEAN_BATCH% == Y (
ECHO. Copy clean batch file
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel1\
copy /Y ..\cleanup.bat            ..\..\Device_Specific\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel2\  )

ECHO.
set /p opt=Want copy USB_BL_Interface.h to App downloader application(on PC) project ?  (y/Y = OK)   

if %opt% == Y (goto :COPY_BL_INTERFACE) else if %opt% == y (goto :COPY_BL_INTERFACE) else (goto  :ALL_DONE)


:COPY_BL_INTERFACE
ECHO. Copy USB_BL_Interface.h to App downloader application(on PC) project
copy /Y ..\USB_BL_Interface.h    "..\..\USB_Bootloader_Software\USB_Bootloader_Software_Source_VC++\"

:COPY_CLEAN_BATCH_FILE



:ALL_DONE
pause

ECHO.Done!
ECHO.