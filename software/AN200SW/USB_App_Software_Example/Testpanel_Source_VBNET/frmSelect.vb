Public Class frmSelect
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
    Friend WithEvents cmbDevice As System.Windows.Forms.ComboBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents cmdOK As System.Windows.Forms.Button
    Friend WithEvents cmdCancel As System.Windows.Forms.Button
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.cmbDevice = New System.Windows.Forms.ComboBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.cmdOK = New System.Windows.Forms.Button()
        Me.cmdCancel = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'cmbDevice
        '
        Me.cmbDevice.Location = New System.Drawing.Point(80, 16)
        Me.cmbDevice.Name = "cmbDevice"
        Me.cmbDevice.Size = New System.Drawing.Size(304, 21)
        Me.cmbDevice.TabIndex = 0
        Me.cmbDevice.Text = "ComboBox1"
        '
        'Label1
        '
        Me.Label1.Location = New System.Drawing.Point(24, 24)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(48, 16)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Device:"
        '
        'cmdOK
        '
        Me.cmdOK.Location = New System.Drawing.Point(96, 56)
        Me.cmdOK.Name = "cmdOK"
        Me.cmdOK.TabIndex = 2
        Me.cmdOK.Text = "OK"
        '
        'cmdCancel
        '
        Me.cmdCancel.Location = New System.Drawing.Point(248, 56)
        Me.cmdCancel.Name = "cmdCancel"
        Me.cmdCancel.TabIndex = 3
        Me.cmdCancel.Text = "Cancel"
        '
        'frmSelect
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(440, 93)
        Me.ControlBox = False
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.cmdCancel, Me.cmdOK, Me.Label1, Me.cmbDevice})
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "frmSelect"
        Me.Text = "Select Device"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        'device number, device string, and temp var newdevstring
        Dim DevNum, RealDevNum As Integer
        Dim DevStr(SI_MAX_DEVICE_STRLEN) As Byte
        Dim i As Integer

        'clear the combo box
        cmbDevice.Items.Clear()

        'determine how many devices are hooked up
        Status = SI_GetNumDevices(DevNum)

        'if we find a device, obtain the name of each device
        'and convert the string to a vb string to add to the
        'combo list, otherwise display the error and close the
        'application

        RealDevNum = DevNum
        If Status = SI_SUCCESS Then
            For i = 0 To DevNum - 1
                Status = SI_GetProductString(i, DevStr(0), SI_RETURN_SERIAL_NUMBER)
                'check if the last character in the serial string is a '~'
                If Mid(ConvertToVBString(DevStr), Len(ConvertToVBString(DevStr))) = "~" Then
                    'device is in bootload mode
                    RealDevNum = RealDevNum - 1
                Else
                    'device is NOT in bootload mode
                    cmbDevice.Items.Add(ConvertToVBString(DevStr))
                End If
            Next i
            If RealDevNum > 0 Then
                cmbDevice.SelectedIndex() = 0 'then set combo list to first item
            End If
        End If

        If Status <> SI_SUCCESS Then
            Me.Hide()
            MsgBox("Error finding USB device. Aborting application.")
            End
        End If

        If RealDevNum = 0 Then
            Me.Hide()
            MsgBox("USB device found in Firmware Update Mode" & vbCrLf _
            & "Please use Bootloader host software to update firmware")
            End
        End If
    End Sub

    Private Sub cmdOK_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdOK.Click

        'device number, device string, and temp var newdevstring
        Dim DevNum As Integer
        Dim DevStr(SI_MAX_DEVICE_STRLEN) As Byte
        Dim i As Integer


        'when ok is clicked, set the timeouts on the device
        'and open the device
        Status = SI_SetTimeouts(1000, 1000)

        If Status = SI_SUCCESS Then

            'determine how many devices are hooked up
            Status = SI_GetNumDevices(DevNum)

            If Status = SI_SUCCESS Then
                For i = 0 To DevNum - 1
                    Status = SI_GetProductString(i, DevStr(0), SI_RETURN_SERIAL_NUMBER)
                    If ConvertToVBString(DevStr) = cmbDevice.SelectedItem Then
                        hUSBDevice = Convert.ToUInt32(0)
                        Status = SI_Open(Convert.ToUInt32(i), hUSBDevice)
                        If Status <> SI_SUCCESS Or Convert.ToDouble(hUSBDevice) = 0 Then
                            frmSelect.ActiveForm.Visible = False
                            MsgBox("Error opening device: " + cmbDevice.Text + ". Application is aborting. Reset hardware and try again.")
                            End
                        Else
                            'create a new main form and show it
                            Dim MainForm As New frmMain
                            Me.Hide()
                            MainForm.Show()
                        End If
                    End If
                Next i
            End If

            If i = DevNum + 1 Then
                frmSelect.ActiveForm.Visible = False
                MsgBox("Error finding device: " + cmbDevice.Text + ". Application is aborting. Reset hardware and try again.")
                End
            End If
        End If

    End Sub

    Private Sub cmdCancel_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles cmdCancel.Click

        Me.Hide()
        End

    End Sub
End Class
