cd %~pd0
CALL :CLEAN
GOTO END


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
ECHO.
GOTO :EOF

:END
ECHO.Done!