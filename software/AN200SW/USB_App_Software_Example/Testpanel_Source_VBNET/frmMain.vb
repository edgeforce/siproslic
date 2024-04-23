Imports System.Runtime.InteropServices

Public Class frmMain
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox3 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox4 As System.Windows.Forms.GroupBox
    Friend WithEvents cmdExit As System.Windows.Forms.Button
    Friend WithEvents GroupBox5 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox6 As System.Windows.Forms.GroupBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents chkLED1 As System.Windows.Forms.CheckBox
    Friend WithEvents chkLED2 As System.Windows.Forms.CheckBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents chkP0B3 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP0B2 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP0B1 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP0B0 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP1B0 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP1B1 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP1B2 As System.Windows.Forms.CheckBox
    Friend WithEvents chkP1B3 As System.Windows.Forms.CheckBox
    Friend WithEvents pbAnalog1 As System.Windows.Forms.ProgressBar
    Friend WithEvents pbAnalog2 As System.Windows.Forms.ProgressBar
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents lblAnalog1 As System.Windows.Forms.Label
    Friend WithEvents lblAnalog2 As System.Windows.Forms.Label
    Friend WithEvents chkButton2 As System.Windows.Forms.CheckBox
    Friend WithEvents chkButton1 As System.Windows.Forms.CheckBox
    Friend WithEvents Bootload As System.Windows.Forms.Button
    Friend WithEvents chkButton3 As System.Windows.Forms.CheckBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.chkButton2 = New System.Windows.Forms.CheckBox
        Me.chkButton1 = New System.Windows.Forms.CheckBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.GroupBox2 = New System.Windows.Forms.GroupBox
        Me.chkP0B0 = New System.Windows.Forms.CheckBox
        Me.chkP0B1 = New System.Windows.Forms.CheckBox
        Me.chkP0B2 = New System.Windows.Forms.CheckBox
        Me.chkP0B3 = New System.Windows.Forms.CheckBox
        Me.GroupBox3 = New System.Windows.Forms.GroupBox
        Me.chkLED2 = New System.Windows.Forms.CheckBox
        Me.chkLED1 = New System.Windows.Forms.CheckBox
        Me.GroupBox4 = New System.Windows.Forms.GroupBox
        Me.chkP1B0 = New System.Windows.Forms.CheckBox
        Me.chkP1B1 = New System.Windows.Forms.CheckBox
        Me.chkP1B2 = New System.Windows.Forms.CheckBox
        Me.chkP1B3 = New System.Windows.Forms.CheckBox
        Me.cmdExit = New System.Windows.Forms.Button
        Me.GroupBox5 = New System.Windows.Forms.GroupBox
        Me.lblAnalog1 = New System.Windows.Forms.Label
        Me.Label4 = New System.Windows.Forms.Label
        Me.pbAnalog1 = New System.Windows.Forms.ProgressBar
        Me.GroupBox6 = New System.Windows.Forms.GroupBox
        Me.lblAnalog2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.pbAnalog2 = New System.Windows.Forms.ProgressBar
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Bootload = New System.Windows.Forms.Button
        Me.chkButton3 = New System.Windows.Forms.CheckBox
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox3.SuspendLayout()
        Me.GroupBox4.SuspendLayout()
        Me.GroupBox5.SuspendLayout()
        Me.GroupBox6.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.chkButton2)
        Me.GroupBox1.Controls.Add(Me.chkButton1)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Controls.Add(Me.Label1)
        Me.GroupBox1.Location = New System.Drawing.Point(16, 8)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(136, 80)
        Me.GroupBox1.TabIndex = 1
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Buttons"
        '
        'chkButton2
        '
        Me.chkButton2.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkButton2.Enabled = False
        Me.chkButton2.Location = New System.Drawing.Point(24, 48)
        Me.chkButton2.Name = "chkButton2"
        Me.chkButton2.Size = New System.Drawing.Size(24, 24)
        Me.chkButton2.TabIndex = 3
        '
        'chkButton1
        '
        Me.chkButton1.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkButton1.Enabled = False
        Me.chkButton1.Location = New System.Drawing.Point(24, 16)
        Me.chkButton1.Name = "chkButton1"
        Me.chkButton1.Size = New System.Drawing.Size(24, 24)
        Me.chkButton1.TabIndex = 2
        '
        'Label2
        '
        Me.Label2.Location = New System.Drawing.Point(56, 56)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(56, 16)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "Button 2"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(56, 24)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(56, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Button 1"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.chkP0B0)
        Me.GroupBox2.Controls.Add(Me.chkP0B1)
        Me.GroupBox2.Controls.Add(Me.chkP0B2)
        Me.GroupBox2.Controls.Add(Me.chkP0B3)
        Me.GroupBox2.Location = New System.Drawing.Point(16, 96)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(136, 80)
        Me.GroupBox2.TabIndex = 2
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "Port 0"
        '
        'chkP0B0
        '
        Me.chkP0B0.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP0B0.Location = New System.Drawing.Point(88, 32)
        Me.chkP0B0.Name = "chkP0B0"
        Me.chkP0B0.Size = New System.Drawing.Size(24, 24)
        Me.chkP0B0.TabIndex = 3
        Me.chkP0B0.Text = "0"
        '
        'chkP0B1
        '
        Me.chkP0B1.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP0B1.Location = New System.Drawing.Point(64, 32)
        Me.chkP0B1.Name = "chkP0B1"
        Me.chkP0B1.Size = New System.Drawing.Size(24, 24)
        Me.chkP0B1.TabIndex = 2
        Me.chkP0B1.Text = " 1"
        '
        'chkP0B2
        '
        Me.chkP0B2.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP0B2.Location = New System.Drawing.Point(40, 32)
        Me.chkP0B2.Name = "chkP0B2"
        Me.chkP0B2.Size = New System.Drawing.Size(24, 24)
        Me.chkP0B2.TabIndex = 1
        Me.chkP0B2.Text = " 2"
        '
        'chkP0B3
        '
        Me.chkP0B3.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP0B3.Location = New System.Drawing.Point(16, 32)
        Me.chkP0B3.Name = "chkP0B3"
        Me.chkP0B3.Size = New System.Drawing.Size(24, 24)
        Me.chkP0B3.TabIndex = 0
        Me.chkP0B3.Text = " 3"
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.chkLED2)
        Me.GroupBox3.Controls.Add(Me.chkLED1)
        Me.GroupBox3.Location = New System.Drawing.Point(168, 8)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(136, 80)
        Me.GroupBox3.TabIndex = 3
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "LEDs"
        '
        'chkLED2
        '
        Me.chkLED2.Location = New System.Drawing.Point(24, 48)
        Me.chkLED2.Name = "chkLED2"
        Me.chkLED2.Size = New System.Drawing.Size(88, 24)
        Me.chkLED2.TabIndex = 1
        Me.chkLED2.Text = "LED 2"
        '
        'chkLED1
        '
        Me.chkLED1.Location = New System.Drawing.Point(24, 16)
        Me.chkLED1.Name = "chkLED1"
        Me.chkLED1.Size = New System.Drawing.Size(88, 24)
        Me.chkLED1.TabIndex = 0
        Me.chkLED1.Text = "LED 1"
        '
        'GroupBox4
        '
        Me.GroupBox4.Controls.Add(Me.chkP1B0)
        Me.GroupBox4.Controls.Add(Me.chkP1B1)
        Me.GroupBox4.Controls.Add(Me.chkP1B2)
        Me.GroupBox4.Controls.Add(Me.chkP1B3)
        Me.GroupBox4.Location = New System.Drawing.Point(168, 96)
        Me.GroupBox4.Name = "GroupBox4"
        Me.GroupBox4.Size = New System.Drawing.Size(136, 80)
        Me.GroupBox4.TabIndex = 4
        Me.GroupBox4.TabStop = False
        Me.GroupBox4.Text = "Port 1"
        '
        'chkP1B0
        '
        Me.chkP1B0.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP1B0.Location = New System.Drawing.Point(92, 32)
        Me.chkP1B0.Name = "chkP1B0"
        Me.chkP1B0.Size = New System.Drawing.Size(24, 24)
        Me.chkP1B0.TabIndex = 7
        Me.chkP1B0.Text = "0"
        '
        'chkP1B1
        '
        Me.chkP1B1.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP1B1.Location = New System.Drawing.Point(68, 32)
        Me.chkP1B1.Name = "chkP1B1"
        Me.chkP1B1.Size = New System.Drawing.Size(24, 24)
        Me.chkP1B1.TabIndex = 6
        Me.chkP1B1.Text = " 1"
        '
        'chkP1B2
        '
        Me.chkP1B2.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP1B2.Location = New System.Drawing.Point(44, 32)
        Me.chkP1B2.Name = "chkP1B2"
        Me.chkP1B2.Size = New System.Drawing.Size(24, 24)
        Me.chkP1B2.TabIndex = 5
        Me.chkP1B2.Text = " 2"
        '
        'chkP1B3
        '
        Me.chkP1B3.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkP1B3.Location = New System.Drawing.Point(20, 32)
        Me.chkP1B3.Name = "chkP1B3"
        Me.chkP1B3.Size = New System.Drawing.Size(24, 24)
        Me.chkP1B3.TabIndex = 4
        Me.chkP1B3.Text = " 3"
        '
        'cmdExit
        '
        Me.cmdExit.Location = New System.Drawing.Point(488, 8)
        Me.cmdExit.Name = "cmdExit"
        Me.cmdExit.TabIndex = 5
        Me.cmdExit.Text = "Exit"
        '
        'GroupBox5
        '
        Me.GroupBox5.Controls.Add(Me.lblAnalog1)
        Me.GroupBox5.Controls.Add(Me.Label4)
        Me.GroupBox5.Controls.Add(Me.pbAnalog1)
        Me.GroupBox5.Location = New System.Drawing.Point(320, 40)
        Me.GroupBox5.Name = "GroupBox5"
        Me.GroupBox5.Size = New System.Drawing.Size(248, 64)
        Me.GroupBox5.TabIndex = 6
        Me.GroupBox5.TabStop = False
        Me.GroupBox5.Text = "Analog 1"
        '
        'lblAnalog1
        '
        Me.lblAnalog1.Location = New System.Drawing.Point(96, 40)
        Me.lblAnalog1.Name = "lblAnalog1"
        Me.lblAnalog1.Size = New System.Drawing.Size(40, 16)
        Me.lblAnalog1.TabIndex = 3
        Me.lblAnalog1.Text = "0"
        '
        'Label4
        '
        Me.Label4.Location = New System.Drawing.Point(16, 40)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(80, 16)
        Me.Label4.TabIndex = 2
        Me.Label4.Text = "Potentiometer:"
        '
        'pbAnalog1
        '
        Me.pbAnalog1.Location = New System.Drawing.Point(16, 16)
        Me.pbAnalog1.Maximum = 255
        Me.pbAnalog1.Name = "pbAnalog1"
        Me.pbAnalog1.Size = New System.Drawing.Size(216, 16)
        Me.pbAnalog1.Step = 1
        Me.pbAnalog1.TabIndex = 0
        '
        'GroupBox6
        '
        Me.GroupBox6.Controls.Add(Me.lblAnalog2)
        Me.GroupBox6.Controls.Add(Me.Label3)
        Me.GroupBox6.Controls.Add(Me.pbAnalog2)
        Me.GroupBox6.Location = New System.Drawing.Point(320, 112)
        Me.GroupBox6.Name = "GroupBox6"
        Me.GroupBox6.Size = New System.Drawing.Size(248, 64)
        Me.GroupBox6.TabIndex = 7
        Me.GroupBox6.TabStop = False
        Me.GroupBox6.Text = "Analog 2"
        '
        'lblAnalog2
        '
        Me.lblAnalog2.Location = New System.Drawing.Point(96, 40)
        Me.lblAnalog2.Name = "lblAnalog2"
        Me.lblAnalog2.Size = New System.Drawing.Size(40, 16)
        Me.lblAnalog2.TabIndex = 4
        Me.lblAnalog2.Text = "0"
        '
        'Label3
        '
        Me.Label3.Location = New System.Drawing.Point(16, 40)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(72, 16)
        Me.Label3.TabIndex = 1
        Me.Label3.Text = "Temperature:"
        '
        'pbAnalog2
        '
        Me.pbAnalog2.Location = New System.Drawing.Point(16, 16)
        Me.pbAnalog2.Maximum = 255
        Me.pbAnalog2.Name = "pbAnalog2"
        Me.pbAnalog2.Size = New System.Drawing.Size(216, 16)
        Me.pbAnalog2.Step = 1
        Me.pbAnalog2.TabIndex = 0
        '
        'Timer1
        '
        Me.Timer1.Enabled = True
        Me.Timer1.Interval = 50
        '
        'Bootload
        '
        Me.Bootload.Location = New System.Drawing.Point(392, 8)
        Me.Bootload.Name = "Bootload"
        Me.Bootload.TabIndex = 5
        Me.Bootload.Text = "Bootload"
        '
        'chkButton3
        '
        Me.chkButton3.Appearance = System.Windows.Forms.Appearance.Button
        Me.chkButton3.BackColor = System.Drawing.SystemColors.Control
        Me.chkButton3.Enabled = False
        Me.chkButton3.Location = New System.Drawing.Point(328, 8)
        Me.chkButton3.Name = "chkButton3"
        Me.chkButton3.Size = New System.Drawing.Size(16, 16)
        Me.chkButton3.TabIndex = 2
        '
        'frmMain
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(584, 189)
        Me.ControlBox = False
        Me.Controls.Add(Me.GroupBox6)
        Me.Controls.Add(Me.GroupBox5)
        Me.Controls.Add(Me.cmdExit)
        Me.Controls.Add(Me.GroupBox4)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.Bootload)
        Me.Controls.Add(Me.chkButton3)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmMain"
        Me.Text = "USB Test"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox4.ResumeLayout(False)
        Me.GroupBox5.ResumeLayout(False)
        Me.GroupBox6.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub frmMain_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        'on each timer tick we will send out the data from the
        'program to the board and set the appropriate values to
        'the board then, we will read in the data from the board
        'and set the appropriate values to the program

        Call SendReceive(False)

    End Sub

    Private Sub cmdExit_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdExit.Click

        'close usb device and exit program
        Status = SI_Close(hUSBDevice)
        End

    End Sub

    Private Sub Bootload_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Bootload.Click

        Timer1.Stop()

        MsgBox("Requesting device firmware update...")
        Call SendReceive(True)

    End Sub

    Private Sub SendReceive(ByVal boolBootload As Boolean)
        'on each timer tick we will send out the data from the
        'program to the board and set the appropriate values to
        'the board then, we will read in the data from the board
        'and set the appropriate values to the program

        'for the buffer, VBIOBuf is for visual basic only, the IntPtr IOBuf
        'is used to copy the VBIOBuf into something readable by c++ unmanaged code
        'Dim IOBufSize As Int32 = 12
        'Dim VBIOBuf(IOBufSize) As Byte
        'Dim IOBuf As IntPtr = Marshal.AllocCoTaskMem(Marshal.SizeOf(IOBufSize) * VBIOBuf.Length())
        Dim IOBufSize As Integer = 12
        Dim IOBuf(IOBufSize) As Byte

        'io buffer; bits are defined as follows:
        'VBIOBuf(0) = LED1
        'VBIOBuf(1) = LED2
        'VBIOBuf(2) = Port
        'VBIOBuf(3) = Analog1
        'VBIOBuf(4) = Analog2
        'VBIOBuf(5) = Used to send bootload command to device firmware
        'VBIOBuf(6,7) = Unused
        'VBIOBuf(8,9,10,11) = Number Of Interrupts

        'set the first two bytes of the array to the led values
        If chkLED1.Checked() Then
            IOBuf(0) = 1
        Else
            IOBuf(0) = 0
        End If

        If chkLED2.Checked() Then
            IOBuf(1) = 1
        Else
            IOBuf(1) = 0
        End If

        Dim B0, B1, B2, B3
        Dim P1

        'bits for each of the bits represented in port 1
        B0 = chkP1B0.Checked
        B1 = chkP1B1.Checked * 2   'shift left 1
        B2 = chkP1B2.Checked * 4   'shift left 2
        B3 = chkP1B3.Checked * 8   'shift left 3
        P1 = (B0 + B1 + B2 + B3) 'or all of the bits together to get the byte value
        P1 = P1 And &HF          'and then with &h0F to get the low 4 bits
        IOBuf(2) = P1            'set the third element to this value to send out

        If boolBootload = True Then
            IOBuf(5) = &H15
        Else
            IOBuf(5) = &H0
        End If

        Dim BytesSucceed As Integer
        Dim BytesWriteRequest As Integer
        Dim BytesReadRequest As Integer

        BytesSucceed = 0
        BytesWriteRequest = IOBufSize - 4
        BytesReadRequest = IOBufSize - 4

        'send data to the board, use the marshal copy to put it into
        'a buffer that is readable by c++ unmanaged code
        'Marshal.Copy(IOBuf, 0, IOBuf, IOBufSize)
        Status = SI_Write(hUSBDevice, IOBuf(0), BytesWriteRequest, BytesSucceed, 0)

        If (BytesSucceed <> BytesWriteRequest) Or (Status <> SI_SUCCESS) Then
            Timer1.Stop()
            MsgBox("Error writing to USB. Wrote " + Str(BytesSucceed) + " of " + Str(BytesWriteRequest) + " bytes. Application is aborting. Reset hardware and try again.")
            End
        End If

        'Read once if not requesting bootload mode; 
        'otherwise keep reading till bootload ack is received
        Do
            'clear out the iobuf and bytessucceed for the next read
            BytesSucceed = 0

            'read data from the board
            Status = SI_Read(hUSBDevice, IOBuf(0), BytesReadRequest, BytesSucceed, 0)

            If (BytesSucceed <> BytesReadRequest) Or (Status <> SI_SUCCESS) Then
                Timer1.Stop()
                MsgBox("Error writing to USB. Read " + Str(BytesSucceed) + " of " + Str(BytesReadRequest) + " bytes. Application is aborting. Reset hardware and try again.")
                End
            End If

            'take the newly received array and put it back into
            'vb form
            'Marshal.Copy(IOBuf, VBIOBuf, 0, IOBufSize)
            'Marshal.FreeCoTaskMem(IOBuf)

            'Check byte #5 in IOBuf; If &H5, then device is about to enter BL mode
            If IOBuf(5) = &H5 Then
                Timer1.Stop()

                MsgBox("User request for firmware update has been received by device" & vbCrLf _
                & "Please use Bootloader host software to update firmware")

                'close usb device and exit program
                Status = SI_Close(hUSBDevice)
                End '*** END THE APPLICATION ***
            End If

            'If we are expecting the device to enter bootload mode, then 
            ' we don't need to do the following
            If boolBootload = False Then

                'the first two elements have the button status
                chkButton1.Checked() = IOBuf(0)
                chkButton2.Checked() = IOBuf(1)

                Dim P0
                P0 = IOBuf(2) And &HF            'and the value with &h0F to get the low 4 bits
                chkP0B0.Checked = P0 And &H1       'check first bit by anding with 1, and if it is true, set the check box
                chkP0B1.Checked = (P0 \ 2) And &H1 'shift right 1, and check if its true, set the check box
                chkP0B2.Checked = (P0 \ 4) And &H1 'shift right 2, and check if its true, set the check box
                chkP0B3.Checked = (P0 \ 8) And &H1 'shift right 3, and check if its true, set the check box

                lblAnalog1.Text = IOBuf(3) 'set each analog label to the corresponding value
                lblAnalog2.Text = IOBuf(4)
                pbAnalog1.Value = IOBuf(3)    'set each analog graphic as well
                pbAnalog2.Value = IOBuf(4)

                'Added code to process the 6th byte sent by the updated Testpanel2 FW
                'Testpanel1 will always send this as '0'
                'This is to demonstrate that the FW has been updated
                If (IOBuf(6) = 1) Then
                    chkButton3.BackColor = Color.Green
                    chkButton3.Checked() = True
                ElseIf (IOBuf(6) = 2) Then
                    chkButton3.BackColor = Color.Lime
                    chkButton3.Checked() = False
                End If

            End If

        Loop While (boolBootload = True)

    End Sub
End Class
