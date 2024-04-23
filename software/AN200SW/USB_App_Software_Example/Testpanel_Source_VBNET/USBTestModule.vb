Module USBTestModule

    ' Declare statements for all the functions in the SiF32xUSb DLL
    ' NOTE: These statements assume that the DLL file is located in
    '       the same directory as this project.
    '       If you change the location of the DLL, be sure to change the location
    '       in the declare statements also.
    Public Declare Function SI_GetNumDevices Lib "SiUSBXp.dll" (ByRef lpwdNumDevices As Integer) As Integer
    Public Declare Function SI_GetProductString Lib "SiUSBXp.dll" (ByVal dwDeviceNum As Integer, ByRef lpvDeviceString As Byte, ByVal dwFlags As Integer) As Integer
    Public Declare Function SI_Open Lib "SiUSBXp.dll" (ByVal dwDevice As UInt32, ByRef cyHandle As UInt32) As Integer
    Public Declare Function SI_Close Lib "SiUSBXp.dll" (ByVal cyHandle As UInt32) As Integer
    Public Declare Function SI_Read Lib "SiUSBXp.dll" (ByVal cyHandle As UInt32, ByRef lpBuffer As Byte, ByVal dwBytesToRead As Integer, ByRef lpdwBytesReturned As Integer, ByVal lpOverlapped As Integer) As Integer
    Public Declare Function SI_Write Lib "SiUSBXp.dll" (ByVal cyHandle As UInt32, ByRef lpBuffer As Byte, ByVal dwBytesToWrite As Integer, ByRef lpdwBytesWritten As Integer, ByVal lpOverlapped As Integer) As Integer
    Public Declare Function SI_SetTimeouts Lib "SiUSBXp.dll" (ByVal dwReadTimeout As Integer, ByVal dwWriteTimeout As Integer) As Integer
    Public Declare Function SI_GetTimeouts Lib "SiUSBXp.dll" (ByRef lpdwReadTimeout As Integer, ByRef lpdwWriteTimeout As Integer) As Integer
    Public Declare Function SI_CheckRXQueue Lib "SiUSBXp.dll" (ByVal cyHandle As UInt32, ByRef lpdwNumBytesInQueue As UInt32, ByRef lpdwQueueStatus As UInt32) As Integer

    'Masks for the serial number and description
    Public Const SI_RETURN_SERIAL_NUMBER = &H0
    Public Const SI_RETURN_DESCRIPTION = &H1

    'Masks for return values from the device
    Public Const SI_SUCCESS = &H0
    Public Const SI_DEVICE_NOT_FOUND = &HFF
    Public Const SI_INVALID_HANDLE = &H1
    Public Const SI_READ_ERROR = &H2
    Public Const SI_RX_QUEUE_NOT_READY = &H3
    Public Const SI_WRITE_ERROR = &H4
    Public Const SI_RESET_ERROR = &H5
    Public Const SI_INVALID_BUFFER = &H6
    Public Const SI_INVALID_REQUEST_LENGTH = &H7
    Public Const SI_DEVICE_IO_FAILED = &H8

    Public Const SI_QUEUE_NO_OVERRUN = &H0
    Public Const SI_QUEUE_OVERRUN = &H1
    Public Const SI_QUEUE_READY = &H2

    Public Const SI_MAX_DEVICE_STRLEN = 256
    Public Const SI_MAX_READ_SIZE = 64
    Public Const SI_MAX_WRITE_SIZE = 64

    Public Const INVALID_HANDLE_VALUE = &H1

    Public Const MAX_PACKET_SIZE = &H40
    Public Const MAX_WRITE_PKTS = &H8

    Public Const FT_READ_MSG = &H0
    Public Const FT_WRITE_MSG = &H1
    Public Const FT_READ_ACK = &H2
    Public Const FT_MSG_SIZE = &H3


    Public hUSBDevice As UInt32
    Public Status As Integer
    Public TempString As String

    Public Function ConvertToVBString(ByVal Str)

        Dim NewString As String
        Dim i As Integer

        'for the received string array, loop until we get
        'a 0 char, or until the max length has been obtained
        'then add the ascii char value to a vb string
        i = 0
        Do While (i < SI_MAX_DEVICE_STRLEN) And (Str(i) <> 0)
            NewString = NewString + Chr(Str(i))
            i = i + 1
        Loop

        ConvertToVBString = NewString

    End Function

End Module


