object Form1: TForm1
  Left = 400
  Top = 198
  Width = 1032
  Height = 736
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  OnCreate = FormCreate
  OnPaint = FormPaint
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 0
    Top = 53
    Width = 1
    Height = 500
    Align = alLeft
  end
  object PaintBox1: TPaintBox
    Left = 497
    Top = 53
    Width = 519
    Height = 500
    Cursor = crHandPoint
    Align = alClient
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
  end
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 1016
    Height = 53
    AutoSize = True
    Bands = <
      item
        Control = ToolBar2
        ImageIndex = -1
        MinHeight = 22
        Width = 1012
      end
      item
        Control = ToolBar1
        ImageIndex = -1
        Width = 1012
      end>
    object ToolBar2: TToolBar
      Left = 9
      Top = 0
      Width = 999
      Height = 22
      AutoSize = True
      ButtonWidth = 117
      Caption = 'ToolBar2'
      EdgeBorders = []
      Flat = True
      Images = ImageList1
      List = True
      ShowCaptions = True
      TabOrder = 0
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 113
        Height = 22
        BevelOuter = bvLowered
        Caption = #35270#35282
        Color = clSkyBlue
        TabOrder = 1
      end
      object ToolButton8: TToolButton
        Left = 113
        Top = 0
        Width = 8
        Caption = 'ToolButton8'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object Panel5: TPanel
        Left = 121
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'X'#36724#36716#21160
        Color = clLime
        TabOrder = 2
      end
      object ToolButton6: TToolButton
        Left = 194
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton6Click
      end
      object ToolButton7: TToolButton
        Left = 228
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton7Click
      end
      object Panel6: TPanel
        Left = 262
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'Y'#36724#36716#21160
        Color = clRed
        TabOrder = 3
      end
      object ToolButton9: TToolButton
        Left = 335
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton9Click
      end
      object ToolButton10: TToolButton
        Left = 369
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton10Click
      end
      object Panel8: TPanel
        Left = 403
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'Z'#36724#36716#21160
        Color = clBlue
        TabOrder = 4
      end
      object ToolButton1: TToolButton
        Left = 476
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton1Click
      end
      object ToolButton2: TToolButton
        Left = 510
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton2Click
      end
      object Panel2: TPanel
        Left = 544
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32553#25918
        Color = clWhite
        TabOrder = 0
      end
      object ToolButton3: TToolButton
        Left = 617
        Top = 0
        AutoSize = True
        ImageIndex = 0
        OnClick = ToolButton3Click
      end
      object ToolButton4: TToolButton
        Left = 651
        Top = 0
        AutoSize = True
        ImageIndex = 1
        OnClick = ToolButton4Click
      end
      object ToolButton5: TToolButton
        Left = 685
        Top = 0
        Width = 8
        Caption = 'ToolButton5'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object ToolButton11: TToolButton
        Left = 693
        Top = 0
        Caption = #36816#21160#20998#26512'('#20463#20208#35282')'
        ImageIndex = 2
        OnClick = ToolButton11Click
      end
      object ToolButton12: TToolButton
        Left = 810
        Top = 0
        Caption = #36816#21160#20998#26512'('#20559#33322#35282')'
        ImageIndex = 3
        OnClick = ToolButton12Click
      end
    end
    object ToolBar1: TToolBar
      Left = 9
      Top = 24
      Width = 999
      Height = 25
      ButtonWidth = 87
      Caption = 'ToolBar1'
      EdgeBorders = []
      Flat = True
      Images = ImageList1
      List = True
      ShowCaptions = True
      TabOrder = 1
      object Panel9: TPanel
        Left = 0
        Top = 0
        Width = 113
        Height = 22
        BevelOuter = bvLowered
        Caption = #26426#22120#20154#25511#21046
        Color = clSkyBlue
        TabOrder = 0
      end
      object ToolButton13: TToolButton
        Left = 113
        Top = 0
        Width = 8
        Caption = 'ToolButton13'
        Style = tbsDivider
      end
      object BtnRobotReset: TToolButton
        Left = 121
        Top = 0
        Caption = #26426#22120#20154#22797#20301
        ImageIndex = 9
        OnClick = BtnRobotResetClick
      end
      object ToolButton14: TToolButton
        Left = 208
        Top = 0
        Width = 8
        Caption = 'ToolButton14'
        ImageIndex = 10
        Style = tbsSeparator
      end
      object RadioButton1: TRadioButton
        Left = 216
        Top = 0
        Width = 81
        Height = 22
        Caption = #36816#21160#27169#25311
        Checked = True
        TabOrder = 1
        TabStop = True
      end
      object RadioButton2: TRadioButton
        Left = 297
        Top = 0
        Width = 113
        Height = 22
        Caption = #30452#25509#20301#23039#25511#21046
        TabOrder = 2
      end
      object RadioButton3: TRadioButton
        Left = 410
        Top = 0
        Width = 113
        Height = 22
        Caption = #30452#25509#30005#32568#25511#21046
        TabOrder = 3
      end
    end
  end
  object Panel1: TPanel
    Left = 1
    Top = 53
    Width = 496
    Height = 500
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 0
      Top = 0
      Width = 496
      Height = 377
      ActivePage = TabSheetServo
      Align = alTop
      MultiLine = True
      TabIndex = 2
      TabOrder = 0
      object TabSheet1: TTabSheet
        Caption = #21442#25968#35774#32622
        object GroupBox1: TGroupBox
          Left = 0
          Top = 0
          Width = 488
          Height = 404
          Align = alTop
          Caption = #26426#22120#20154#21442#25968
          TabOrder = 0
          object LabeledEdit1: TLabeledEdit
            Left = 16
            Top = 40
            Width = 145
            Height = 21
            EditLabel.Width = 120
            EditLabel.Height = 12
            EditLabel.Caption = #19978#24179#21488#38271#33218#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 0
            Text = '2.25'
          end
          object LabeledEdit2: TLabeledEdit
            Left = 16
            Top = 88
            Width = 145
            Height = 21
            EditLabel.Width = 120
            EditLabel.Height = 12
            EditLabel.Caption = #19978#24179#21488#30701#33218#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 1
            Text = '0.1'
          end
          object LabeledEdit3: TLabeledEdit
            Left = 16
            Top = 240
            Width = 145
            Height = 21
            EditLabel.Width = 108
            EditLabel.Height = 12
            EditLabel.Caption = #36830#26438#26368#30701#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 4
            Text = '6'
          end
          object LabeledEdit4: TLabeledEdit
            Left = 16
            Top = 288
            Width = 145
            Height = 21
            EditLabel.Width = 108
            EditLabel.Height = 12
            EditLabel.Caption = #36830#26438#26368#38271#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 5
            Text = '11'
          end
          object LabeledEdit5: TLabeledEdit
            Left = 16
            Top = 136
            Width = 145
            Height = 21
            EditLabel.Width = 120
            EditLabel.Height = 12
            EditLabel.Caption = #19979#24179#21488#38271#33218#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 2
            Text = '3.5'
          end
          object LabeledEdit6: TLabeledEdit
            Left = 16
            Top = 184
            Width = 145
            Height = 21
            EditLabel.Width = 120
            EditLabel.Height = 12
            EditLabel.Caption = #19979#24179#21488#30701#33218#38271#24230'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 3
            Text = '0.1'
          end
          object LabeledEdit7: TLabeledEdit
            Left = 16
            Top = 336
            Width = 145
            Height = 21
            EditLabel.Width = 84
            EditLabel.Height = 12
            EditLabel.Caption = #36830#26438#30452#24452'(mm)'#65306
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 6
            Text = '0.05'
          end
          object BtnSettings: TButton
            Left = 16
            Top = 368
            Width = 75
            Height = 25
            Caption = #35774#32622
            TabOrder = 7
            OnClick = BtnSettingsClick
          end
        end
        object GroupBox3: TGroupBox
          Left = 0
          Top = 404
          Width = 488
          Height = 87
          Align = alTop
          Caption = #36733#33655
          TabOrder = 1
          object Label7: TLabel
            Left = 16
            Top = 24
            Width = 84
            Height = 14
            Caption = #36733#33655#37325#37327'('#21544')'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object CSpinEdit7: TCSpinEdit
            Left = 16
            Top = 40
            Width = 121
            Height = 22
            TabOrder = 0
            Value = 16
            OnChange = CSpinEditXChange
          end
        end
      end
      object TabSheetRobot: TTabSheet
        Caption = #36870#21521#36816#21160#23398#35745#31639#19982#25511#21046
        ImageIndex = 1
        object Bevel1: TBevel
          Left = 0
          Top = 0
          Width = 488
          Height = 9
          Align = alTop
          Shape = bsSpacer
        end
        object GroupBox2: TGroupBox
          Left = 0
          Top = 9
          Width = 488
          Height = 217
          Align = alTop
          Caption = #19978#24179#21488#36816#21160
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object Label1: TLabel
            Left = 16
            Top = 104
            Width = 42
            Height = 14
            Caption = 'X (mm)'
          end
          object Label2: TLabel
            Left = 112
            Top = 104
            Width = 42
            Height = 14
            Caption = 'Y (mm)'
          end
          object Label3: TLabel
            Left = 208
            Top = 104
            Width = 42
            Height = 14
            Caption = 'Z (mm)'
          end
          object Label4: TLabel
            Left = 16
            Top = 160
            Width = 21
            Height = 14
            Caption = 'Yaw'
          end
          object Label5: TLabel
            Left = 112
            Top = 160
            Width = 35
            Height = 14
            Caption = 'Pitch'
          end
          object Label6: TLabel
            Left = 208
            Top = 160
            Width = 28
            Height = 14
            Caption = 'Roll'
          end
          object CSpinEditX: TCSpinEdit
            Left = 16
            Top = 120
            Width = 89
            Height = 23
            TabOrder = 0
            OnChange = CSpinEditXChange
          end
          object CSpinEditY: TCSpinEdit
            Left = 112
            Top = 120
            Width = 89
            Height = 23
            TabOrder = 1
            OnChange = CSpinEditXChange
          end
          object CSpinEditZ: TCSpinEdit
            Left = 208
            Top = 120
            Width = 89
            Height = 23
            TabOrder = 2
            Value = 500
            OnChange = CSpinEditXChange
          end
          object CSpinEditYaw: TCSpinEdit
            Left = 16
            Top = 176
            Width = 89
            Height = 23
            TabOrder = 3
            OnChange = CSpinEditXChange
          end
          object CSpinEditPitch: TCSpinEdit
            Left = 112
            Top = 176
            Width = 89
            Height = 23
            TabOrder = 4
            OnChange = CSpinEditXChange
          end
          object CSpinEditRoll: TCSpinEdit
            Left = 208
            Top = 176
            Width = 89
            Height = 23
            TabOrder = 5
            OnChange = CSpinEditXChange
          end
          object LabeledEdit8: TLabeledEdit
            Left = 16
            Top = 48
            Width = 121
            Height = 22
            EditLabel.Width = 108
            EditLabel.Height = 12
            EditLabel.Caption = #19978#24179#21488#26368#20302#39640#24230'(mm)'
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 6
            Text = '2.25'
          end
          object LabeledEdit9: TLabeledEdit
            Left = 152
            Top = 48
            Width = 121
            Height = 22
            EditLabel.Width = 108
            EditLabel.Height = 12
            EditLabel.Caption = #19978#24179#21488#26368#20302#39640#24230'(mm)'
            EditLabel.Font.Charset = ANSI_CHARSET
            EditLabel.Font.Color = clWindowText
            EditLabel.Font.Height = -12
            EditLabel.Font.Name = #23435#20307
            EditLabel.Font.Style = []
            EditLabel.ParentFont = False
            LabelPosition = lpAbove
            LabelSpacing = 3
            TabOrder = 7
            Text = '2.25'
          end
        end
        object Memo1: TMemo
          Left = 0
          Top = 496
          Width = 368
          Height = 282
          Align = alCustom
          Lines.Strings = (
            #26438#38271)
          TabOrder = 1
        end
      end
      object TabSheetServo: TTabSheet
        Caption = #30452#25509#30005#32568#25511#21046
        ImageIndex = 2
        object GroupBox4: TGroupBox
          Left = 0
          Top = 0
          Width = 488
          Height = 137
          Align = alTop
          Caption = #19978#24179#21488#36816#21160
          TabOrder = 0
          object Label8: TLabel
            Left = 16
            Top = 32
            Width = 37
            Height = 13
            Caption = 'L1 (mm)'
          end
          object Label9: TLabel
            Left = 112
            Top = 32
            Width = 37
            Height = 13
            Caption = 'L2 (mm)'
          end
          object Label10: TLabel
            Left = 208
            Top = 32
            Width = 37
            Height = 13
            Caption = 'L3 (mm)'
          end
          object Label11: TLabel
            Left = 16
            Top = 88
            Width = 34
            Height = 13
            Caption = 'L4(mm)'
          end
          object Label12: TLabel
            Left = 112
            Top = 88
            Width = 34
            Height = 13
            Caption = 'L5(mm)'
          end
          object Label13: TLabel
            Left = 208
            Top = 88
            Width = 34
            Height = 13
            Caption = 'L6(mm)'
          end
          object CSpinEdit8: TCSpinEdit
            Left = 16
            Top = 48
            Width = 89
            Height = 22
            TabOrder = 0
            Value = 900
            OnChange = CSpinEdit8Change
          end
          object CSpinEdit9: TCSpinEdit
            Left = 112
            Top = 48
            Width = 89
            Height = 22
            TabOrder = 1
            Value = 900
            OnChange = CSpinEdit8Change
          end
          object CSpinEdit10: TCSpinEdit
            Left = 208
            Top = 48
            Width = 89
            Height = 22
            TabOrder = 2
            Value = 900
            OnChange = CSpinEdit8Change
          end
          object CSpinEdit11: TCSpinEdit
            Left = 16
            Top = 104
            Width = 89
            Height = 22
            TabOrder = 3
            Value = 900
            OnChange = CSpinEdit8Change
          end
          object CSpinEdit12: TCSpinEdit
            Left = 112
            Top = 104
            Width = 89
            Height = 22
            TabOrder = 4
            Value = 900
            OnChange = CSpinEdit8Change
          end
          object CSpinEdit13: TCSpinEdit
            Left = 208
            Top = 104
            Width = 89
            Height = 22
            TabOrder = 5
            Value = 900
            OnChange = CSpinEdit8Change
          end
        end
        object ListView4: TListView
          Left = 0
          Top = 137
          Width = 488
          Height = 212
          Align = alClient
          Columns = <
            item
              Caption = #36890#36947
              Width = 85
            end
            item
              Caption = 'Value'
              Width = 100
            end
            item
              Caption = 'Pulse'
              Width = 100
            end>
          GridLines = True
          Items.Data = {
            B60000000600000000000000FFFFFFFFFFFFFFFF0200000000000000024C3100
            0000000000FFFFFFFFFFFFFFFF0200000000000000024C32000000000000FFFF
            FFFFFFFFFFFF0200000000000000024C33000000000000FFFFFFFFFFFFFFFF02
            00000000000000024C34000000000000FFFFFFFFFFFFFFFF0200000000000000
            024C35000000000000FFFFFFFFFFFFFFFF0200000000000000024C360000FFFF
            FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
          ReadOnly = True
          TabOrder = 1
          ViewStyle = vsReport
        end
      end
      object TabSheet2: TTabSheet
        Caption = #36816#21160#27169#25311
        ImageIndex = 3
        object GroupBox7: TGroupBox
          Left = 0
          Top = 33
          Width = 488
          Height = 144
          Align = alTop
          Caption = #39134#26426#21152#36895#24230
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object ListView1: TListView
            Left = 2
            Top = 16
            Width = 484
            Height = 126
            Align = alClient
            Columns = <
              item
                Caption = #36890#36947
                Width = 100
              end
              item
                Caption = 'Value'
                Width = 150
              end>
            GridLines = True
            Items.Data = {
              BC0000000600000000000000FFFFFFFFFFFFFFFF01000000000000000858286D
              2F735E32290000000000FFFFFFFFFFFFFFFF01000000000000000859286D2F73
              5E32290000000000FFFFFFFFFFFFFFFF0100000000000000085A286D2F735E32
              290000000000FFFFFFFFFFFFFFFF0100000000000000035961770000000000FF
              FFFFFFFFFFFFFF01000000000000000550697463680000000000FFFFFFFFFFFF
              FFFF010000000000000004526F6C6C00FFFFFFFFFFFFFFFFFFFFFFFF}
            ReadOnly = True
            TabOrder = 0
            ViewStyle = vsReport
          end
        end
        object Button1: TButton
          Left = 208
          Top = 304
          Width = 75
          Height = 25
          Caption = 'Button1'
          TabOrder = 1
        end
        object Panel49: TPanel
          Left = 0
          Top = 0
          Width = 488
          Height = 33
          Align = alTop
          BevelOuter = bvLowered
          TabOrder = 2
          object CheckBox1: TCheckBox
            Left = 8
            Top = 8
            Width = 97
            Height = 17
            Caption = #30001'FSX'#25511#21046
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -16
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
            TabOrder = 0
          end
        end
        object Button2: TButton
          Left = 296
          Top = 304
          Width = 75
          Height = 25
          Caption = 'Button2'
          TabOrder = 3
          OnClick = Button2Click
        end
        object GroupBox9: TGroupBox
          Left = 0
          Top = 177
          Width = 488
          Height = 112
          Align = alTop
          Caption = #32473#23450#21152#36895#24230
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 4
          object Label14: TLabel
            Left = 16
            Top = 32
            Width = 84
            Height = 14
            Caption = 'X (0.1m/s^2)'
          end
          object Label15: TLabel
            Left = 16
            Top = 56
            Width = 84
            Height = 14
            Caption = 'Y (0.1m/s^2)'
          end
          object Label16: TLabel
            Left = 16
            Top = 80
            Width = 84
            Height = 14
            Caption = 'Z (0.1m/s^2)'
          end
          object Label17: TLabel
            Left = 184
            Top = 32
            Width = 112
            Height = 14
            Caption = 'Yaw (0.1deg/s^2)'
          end
          object Label18: TLabel
            Left = 184
            Top = 56
            Width = 126
            Height = 14
            Caption = 'Pitch (0.1deg/s^2)'
          end
          object Label19: TLabel
            Left = 184
            Top = 80
            Width = 119
            Height = 14
            Caption = 'Roll (0.1deg/s^2)'
          end
          object CSpinEdit1: TCSpinEdit
            Left = 104
            Top = 25
            Width = 73
            Height = 23
            TabOrder = 0
          end
          object CSpinEdit2: TCSpinEdit
            Left = 104
            Top = 49
            Width = 73
            Height = 23
            TabOrder = 1
          end
          object CSpinEdit3: TCSpinEdit
            Left = 104
            Top = 73
            Width = 73
            Height = 23
            TabOrder = 2
          end
          object CSpinEdit4: TCSpinEdit
            Left = 312
            Top = 25
            Width = 73
            Height = 23
            TabOrder = 3
          end
          object CSpinEdit5: TCSpinEdit
            Left = 312
            Top = 49
            Width = 73
            Height = 23
            TabOrder = 4
          end
          object CSpinEdit6: TCSpinEdit
            Left = 312
            Top = 73
            Width = 73
            Height = 23
            TabOrder = 5
          end
        end
        object Button3: TButton
          Left = 136
          Top = 304
          Width = 75
          Height = 25
          Caption = 'Button3'
          TabOrder = 5
          OnClick = Button3Click
        end
        object Edit1: TEdit
          Left = 8
          Top = 304
          Width = 121
          Height = 21
          TabOrder = 6
          Text = 'Edit1'
        end
      end
    end
    object GroupBox6: TGroupBox
      Left = 0
      Top = 521
      Width = 496
      Height = 144
      Align = alTop
      Caption = #19978#24179#21488#20301#32622
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object ListView2: TListView
        Left = 2
        Top = 16
        Width = 492
        Height = 126
        Align = alClient
        Columns = <
          item
            Caption = #36890#36947
            Width = 100
          end
          item
            Caption = #32473#23450#20301#23039
            Width = 120
          end
          item
            Caption = #27491#21521#36816#21160#20301#23039
            Width = 120
          end>
        GridLines = True
        Items.Data = {
          CE0000000600000000000000FFFFFFFFFFFFFFFF02000000000000000858286D
          2F735E3229000000000000FFFFFFFFFFFFFFFF02000000000000000859286D2F
          735E3229000000000000FFFFFFFFFFFFFFFF0200000000000000085A286D2F73
          5E3229000000000000FFFFFFFFFFFFFFFF020000000000000003596177000000
          000000FFFFFFFFFFFFFFFF0200000000000000055069746368000000000000FF
          FFFFFFFFFFFFFF020000000000000004526F6C6C0000FFFFFFFFFFFFFFFFFFFF
          FFFFFFFFFFFFFFFFFFFFFFFFFFFF}
        ReadOnly = True
        TabOrder = 0
        ViewStyle = vsReport
      end
    end
    object GroupBox10: TGroupBox
      Left = 0
      Top = 377
      Width = 496
      Height = 144
      Align = alTop
      Caption = #36830#26438#38271#24230
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object ListView3: TListView
        Left = 2
        Top = 16
        Width = 492
        Height = 126
        Align = alClient
        Columns = <
          item
            Caption = #36890#36947
          end
          item
            Caption = 'Len(mm)'
            Width = 75
          end
          item
            Caption = 'Pulse'
            Width = 75
          end
          item
            Caption = 'Spd(rpm)'
            Width = 75
          end
          item
            Caption = 'Dir'
          end
          item
            Caption = 'Dst'
            Width = 75
          end
          item
            Caption = 'Cur'
            Width = 75
          end>
        GridLines = True
        ReadOnly = True
        TabOrder = 0
        ViewStyle = vsReport
      end
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 553
    Width = 1016
    Height = 126
    Align = alBottom
    Caption = 'Panel3'
    TabOrder = 2
    object Chart1: TChart
      Left = 186
      Top = 1
      Width = 829
      Height = 124
      BackWall.Brush.Color = clWhite
      BackWall.Brush.Style = bsClear
      Title.Text.Strings = (
        'TChart')
      Title.Visible = False
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Maximum = 30
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Maximum = 0.5
      LeftAxis.Minimum = -0.5
      Legend.Visible = False
      View3D = False
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      object Series1: TFastLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clRed
        LinePen.Color = clRed
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
      object Series2: TFastLineSeries
        Marks.ArrowLength = 8
        Marks.Visible = False
        SeriesColor = clGreen
        LinePen.Color = clGreen
        XValues.DateTime = False
        XValues.Name = 'X'
        XValues.Multiplier = 1
        XValues.Order = loAscending
        YValues.DateTime = False
        YValues.Name = 'Y'
        YValues.Multiplier = 1
        YValues.Order = loNone
      end
    end
    object Panel7: TPanel
      Left = 1
      Top = 1
      Width = 185
      Height = 124
      Align = alLeft
      TabOrder = 1
      object Label20: TLabel
        Left = 16
        Top = 16
        Width = 84
        Height = 13
        Caption = #21152#36895#24230#26354#32447#23545#35937
      end
      object ComboBox1: TComboBox
        Left = 16
        Top = 32
        Width = 145
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'X'#36724
        Items.Strings = (
          'X'#36724
          'Y'#36724
          'Z'#36724
          #20559#33322
          #20463#20208
          #28378#36716)
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 679
    Width = 1016
    Height = 19
    Panels = <
      item
        Width = 100
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object ImageList1: TImageList
    Left = 536
    Top = 224
    Bitmap = {
      494C01010A000E00040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF00000000007F7F7F00000000007F7F7F00000000000000FF000000
      FF000000FF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      000000000000000000007F7F7F00000000007F7F7F0000000000000000000000
      00000000FF000000FF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000008000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000008000000000000000000000000000000000FF000000FF00000000000000
      000000000000000000007F7F7F00000000007F7F7F0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000000000000000000000000000000000000000FF000000FF00000000000000
      0000000000000000000000008000000000000000800000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000008000000000
      0000000000000000000000000000000000000000FF000000FF00000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000FF000000FF000000
      FF00000000000000000000000000000000000000000000000000000000000000
      00000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000FF000000
      FF000000FF00000000007F7F7F00000000007F7F7F00000000000000FF000000
      FF000000FF000000FF000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      FF000000FF000000FF000000FF000000FF000000FF000000FF000000FF000000
      FF0000000000000000000000FF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000FF000000FF000000FF000000FF000000FF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000 000000000000000008000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      0000000000000000000000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      00000000000000FFFF00FFFFFF0000FFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000080000000800000008000000080000000800000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      000000000000FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008000000080000000800000008000000080000000800000008000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000080000000800000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      00000000000000FFFF00FFFFFF0000FFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008000000080000000800000008000000080000000800000008000000080
      000000800000000000000000000000000000000000000000000000000000FFFF
      000000000000FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      000000800000000000000000000000000000000000000000000000000000FFFF
      00000000000000FFFF00FFFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008000000080000000800000008000000080000000800000008000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000008000000080000000800000008000000080000000800000008000000080
      0000008000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF00FFFFFF0000FFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000080000000800000008000000080000000800000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000080000000800000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000008000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF000000000000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFF000000000000FFFF000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFF0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F7F007F7F
      7F007F7F7F0000000000FFFF0000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF0000000000000000000000000000000000007F7F
      7F000000000000000000000000007F7F7F000000000000FFFF007F7F7F000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F000000000000000000000000007F7F7F000000000000FFFF007F7F7F000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF0000000000000000000000000000000000007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00000000000000000000FFFF000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F00000000000000000000FFFF000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF00000000000000000000000000007F7F7F00FFFF
      FF00BFBFBF00FFFFFF00BFBFBF00FFFFFF007F7F7F0000000000000000000000
      00000000000000000000000000000000000000000000000000007F7F7F00BFBF
      BF00FFFFFF00BFBFBF00FFFFFF00BFBFBF007F7F7F0000000000000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF0000000000007F7F7F007F7F7F00FFFFFF00BFBF
      BF00FFFFFF000000FF00FFFFFF00BFBFBF00FFFFFF007F7F7F007F7F7F000000
      0000000000000000000000000000000000007F7F7F007F7F7F00BFBFBF00FFFF
      FF00BFBFBF00FFFFFF00BFBFBF00FFFFFF00BFBFBF007F7F7F007F7F7F000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000000000007F7F7F00BFBFBF00FFFF
      FF00BFBFBF000000FF00BFBFBF00FFFFFF00BFBFBF007F7F7F00000000000000
      000000000000000000000000000000000000000000007F7F7F00FFFFFF00BFBF
      BF00FFFFFF00BFBFBF00FFFFFF00BFBFBF00FFFFFF007F7F7F00000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000000000007F7F7F00FFFFFF000000
      FF000000FF000000FF000000FF000000FF00FFFFFF007F7F7F00000000000000
      000000000000000000000000000000000000000000007F7F7F00BFBFBF000000
      FF000000FF000000FF000000FF000000FF00BFBFBF007F7F7F00000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000000000007F7F7F00BFBFBF00FFFF
      FF00BFBFBF000000FF00BFBFBF00FFFFFF00BFBFBF007F7F7F00000000000000
      000000000000000000000000000000000000000000007F7F7F00FFFFFF00BFBF
      BF00FFFFFF00BFBFBF00FFFFFF00BFBFBF00FFFFFF007F7F7F00000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF0000000000007F7F7F007F7F7F00FFFFFF00BFBF
      BF00FFFFFF000000FF00FFFFFF00BFBFBF00FFFFFF007F7F7F007F7F7F000000
      0000000000000000000000000000000000007F7F7F007F7F7F00BFBFBF00FFFF
      FF00BFBFBF00FFFFFF00BFBFBF00FFFFFF00BFBFBF007F7F7F007F7F7F000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF000000000000FFFF000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      00007F7F7F0000000000FFFF00000000000000000000000000007F7F7F00FFFF
      FF00BFBFBF00FFFFFF00BFBFBF00FFFFFF007F7F7F0000000000000000000000
      00000000000000000000000000000000000000000000000000007F7F7F00BFBF
      BF00FFFFFF00BFBFBF00FFFFFF00BFBFBF007F7F7F0000000000000000000000
      000000000000000000000000000000000000FFFF000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFF000000000000FFFF000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0000000000FFFF0000000000000000000000000000000000007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F007F7F7F007F7F7F007F7F7F007F7F7F000000000000000000000000000000
      000000000000000000000000000000000000FFFF000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFF000000000000FFFF000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000FFFF0000000000000000000000000000000000007F7F
      7F000000000000000000000000007F7F7F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000007F7F
      7F000000000000000000000000007F7F7F000000000000000000000000000000
      000000000000000000000000000000000000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF000000000000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
      0000FFFF0000FFFF0000FFFF000000000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FFFFFFFF00000000FFFFF83F00000000
      FFFFE00F00000000FF7FC44700000000FF3F8C6300000000FF1F9C7300000000
      C00F3FF900000000C0073EF900000000C0033C7F00000000C0073C7F00000000
      C00F3C4100000000FF1F9C6100000000FF3F8C7100000000FF7FC44100000000
      FFFFE00D00000000FFFFF83F00000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      1FFFF83FFEFFFFFF041FF83FFC7FFEFF000FF83FF83FFCFF000FF83FF01FF8FF
      0007F83FE00FF0030001F83FC007E0030000C007F83FC0030001E00FF83FE003
      003FF01FF83FF003FC7FF83FF83FF8FFFFFFFC7FF83FFCFFFFFFFEFFF83FFEFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFDFFFDFFFFFFFFFFF8FFF800010001
      FFF1FFF100010001FFE3FFE300010001FFC7FFC71FF11FF1E08FE08F1DF11FF1
      C01FC01F1CF11931803F803F1C711931001F001F1C311931001F001F1C711931
      001F001F1CF11931001F001F1DF11FF1001F001F1FF11FF1803F803F00010001
      C07FC07F00010001E0FFE0FF0001000100000000000000000000000000000000
      000000000000}
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 20
    Left = 400
    Top = 48
  end
  object Timer2: TTimer
    Enabled = False
    Interval = 20
    OnTimer = Timer2Timer
    Left = 432
    Top = 48
  end
  object Timer3: TTimer
    Enabled = False
    Interval = 50
    OnTimer = Timer3Timer
    Left = 464
    Top = 48
  end
end
