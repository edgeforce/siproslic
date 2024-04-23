cd %~pd0
cd .\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel1\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F320_1\USB_App_Firmware_Examples\F320_1_Testpanel2\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel1\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F326_7\USB_App_Firmware_Examples\F326_7_Testpanel2\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel1
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F340_2_4_6\USB_App_Firmware_Examples\F340_2_4_6_Testpanel2
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel1
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F341_3_5_7\USB_App_Firmware_Examples\F341_3_5_7_Testpanel2
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel1
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F380_1_4_5\USB_App_Firmware_Examples\F380_1_4_5_Testpanel2
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel1\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\

cd .\C8051F382_3_6_7\USB_App_Firmware_Examples\F382_3_6_7_Testpanel2\
CALL :CLEAN
cd ..\..\USB_App_Firmware_Startup
CALL :CLEAN
cd ..\..\


goto :END


:CLEAN
@ECHO OFF
ECHO.
ECHO.Cleaning up OBJ and LST files...
DEL *.OBJ
DEL *.#*
DEL tmp.out
DEL *.tmp
DEL cyglink.txt
DEL *.LST
ECHO.Done!
ECHO.
GOTO :EOF

:END
pause


