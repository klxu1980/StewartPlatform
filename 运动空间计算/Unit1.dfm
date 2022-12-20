object Form1: TForm1
  Left = 251
  Top = 151
  Width = 1142
  Height = 866
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
    Top = 26
    Width = 1
    Height = 802
    Align = alLeft
  end
  object PaintBox1: TPaintBox
    Left = 377
    Top = 26
    Width = 749
    Height = 802
    Cursor = crHandPoint
    Align = alClient
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
  end
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 1126
    Height = 26
    AutoSize = True
    Bands = <
      item
        Control = ToolBar2
        ImageIndex = -1
        MinHeight = 22
        Width = 1122
      end>
    object ToolBar2: TToolBar
      Left = 9
      Top = 0
      Width = 1109
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
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #35270#35282
        Color = clSkyBlue
        TabOrder = 1
      end
      object ToolButton8: TToolButton
        Left = 73
        Top = 0
        Width = 8
        Caption = 'ToolButton8'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object Panel5: TPanel
        Left = 81
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'X'#36724#36716#21160
        Color = clLime
        TabOrder = 2
      end
      object ToolButton6: TToolButton
        Left = 154
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton6Click
      end
      object ToolButton7: TToolButton
        Left = 188
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton7Click
      end
      object Panel6: TPanel
        Left = 222
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'Y'#36724#36716#21160
        Color = clRed
        TabOrder = 3
      end
      object ToolButton9: TToolButton
        Left = 295
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton9Click
      end
      object ToolButton10: TToolButton
        Left = 329
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton10Click
      end
      object Panel8: TPanel
        Left = 363
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32469'Z'#36724#36716#21160
        Color = clBlue
        TabOrder = 4
      end
      object ToolButton1: TToolButton
        Left = 436
        Top = 0
        AutoSize = True
        ImageIndex = 5
        OnClick = ToolButton1Click
      end
      object ToolButton2: TToolButton
        Left = 470
        Top = 0
        AutoSize = True
        ImageIndex = 6
        OnClick = ToolButton2Click
      end
      object Panel2: TPanel
        Left = 504
        Top = 0
        Width = 73
        Height = 22
        BevelOuter = bvLowered
        Caption = #32553#25918
        Color = clWhite
        TabOrder = 0
      end
      object ToolButton3: TToolButton
        Left = 577
        Top = 0
        AutoSize = True
        ImageIndex = 0
        OnClick = ToolButton3Click
      end
      object ToolButton4: TToolButton
        Left = 611
        Top = 0
        AutoSize = True
        ImageIndex = 1
        OnClick = ToolButton4Click
      end
      object ToolButton5: TToolButton
        Left = 645
        Top = 0
        Width = 8
        Caption = 'ToolButton5'
        ImageIndex = 2
        Style = tbsSeparator
      end
      object ToolButton11: TToolButton
        Left = 653
        Top = 0
        Caption = #36816#21160#20998#26512'('#20463#20208#35282')'
        ImageIndex = 2
        OnClick = ToolButton11Click
      end
      object ToolButton12: TToolButton
        Left = 770
        Top = 0
        Caption = #36816#21160#20998#26512'('#20559#33322#35282')'
        ImageIndex = 3
        OnClick = ToolButton12Click
      end
    end
  end
  object PageControl1: TPageControl
    Left = 1
    Top = 26
    Width = 376
    Height = 802
    ActivePage = TabSheet2
    Align = alLeft
    TabIndex = 3
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = #21442#25968#35774#32622
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 368
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
        Width = 368
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
        Width = 368
        Height = 9
        Align = alTop
        Shape = bsSpacer
      end
      object Bevel2: TBevel
        Left = 0
        Top = 226
        Width = 368
        Height = 9
        Align = alTop
        Shape = bsSpacer
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 9
        Width = 368
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
      object GroupBox5: TGroupBox
        Left = 0
        Top = 235
        Width = 368
        Height = 254
        Align = alTop
        Caption = #19978#24179#21488#36816#21160
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object Panel1: TPanel
          Left = 16
          Top = 32
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'1(mm) '
          TabOrder = 0
        end
        object PnlLinkLen1: TPanel
          Left = 136
          Top = 32
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 1
        end
        object Panel7: TPanel
          Left = 16
          Top = 64
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'2(mm) '
          TabOrder = 2
        end
        object PnlLinkLen2: TPanel
          Left = 136
          Top = 64
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 3
        end
        object Panel10: TPanel
          Left = 16
          Top = 96
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'3(mm) '
          TabOrder = 4
        end
        object PnlLinkLen3: TPanel
          Left = 136
          Top = 96
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 5
        end
        object Panel12: TPanel
          Left = 16
          Top = 128
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'4(mm) '
          TabOrder = 6
        end
        object PnlLinkLen4: TPanel
          Left = 136
          Top = 128
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 7
        end
        object Panel14: TPanel
          Left = 16
          Top = 160
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'5(mm) '
          TabOrder = 8
        end
        object PnlLinkLen5: TPanel
          Left = 136
          Top = 160
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 9
        end
        object Panel16: TPanel
          Left = 16
          Top = 192
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = #36830#26438#38271#24230'6(mm) '
          TabOrder = 10
        end
        object PnlLinkLen6: TPanel
          Left = 136
          Top = 192
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 11
        end
      end
    end
    object TabSheetServo: TTabSheet
      Caption = #27491#21521#36816#21160#23398#35745#31639#19982#25511#21046
      ImageIndex = 2
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 368
        Height = 217
        Align = alTop
        Caption = #19978#24179#21488#36816#21160
        TabOrder = 0
        object Label8: TLabel
          Left = 16
          Top = 104
          Width = 37
          Height = 13
          Caption = 'L1 (mm)'
        end
        object Label9: TLabel
          Left = 112
          Top = 104
          Width = 37
          Height = 13
          Caption = 'L2 (mm)'
        end
        object Label10: TLabel
          Left = 208
          Top = 104
          Width = 37
          Height = 13
          Caption = 'L3 (mm)'
        end
        object Label11: TLabel
          Left = 16
          Top = 160
          Width = 34
          Height = 13
          Caption = 'L4(mm)'
        end
        object Label12: TLabel
          Left = 112
          Top = 160
          Width = 34
          Height = 13
          Caption = 'L5(mm)'
        end
        object Label13: TLabel
          Left = 208
          Top = 160
          Width = 34
          Height = 13
          Caption = 'L6(mm)'
        end
        object CSpinEdit8: TCSpinEdit
          Left = 16
          Top = 120
          Width = 89
          Height = 22
          TabOrder = 0
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object CSpinEdit9: TCSpinEdit
          Left = 112
          Top = 120
          Width = 89
          Height = 22
          TabOrder = 1
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object CSpinEdit10: TCSpinEdit
          Left = 208
          Top = 120
          Width = 89
          Height = 22
          TabOrder = 2
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object CSpinEdit11: TCSpinEdit
          Left = 16
          Top = 176
          Width = 89
          Height = 22
          TabOrder = 3
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object CSpinEdit12: TCSpinEdit
          Left = 112
          Top = 176
          Width = 89
          Height = 22
          TabOrder = 4
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object CSpinEdit13: TCSpinEdit
          Left = 208
          Top = 176
          Width = 89
          Height = 22
          TabOrder = 5
          Value = 900
          OnChange = CSpinEdit8Change
        end
        object LabeledEdit10: TLabeledEdit
          Left = 16
          Top = 48
          Width = 121
          Height = 21
          EditLabel.Width = 96
          EditLabel.Height = 12
          EditLabel.Caption = #36830#26438#26368#30701#38271#24230'(mm)'
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
        object LabeledEdit11: TLabeledEdit
          Left = 152
          Top = 48
          Width = 121
          Height = 21
          EditLabel.Width = 96
          EditLabel.Height = 12
          EditLabel.Caption = #36830#26438#26368#22823#38271#24230'(mm)'
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
      object Memo2: TMemo
        Left = 0
        Top = 217
        Width = 368
        Height = 407
        Align = alClient
        Lines.Strings = (
          #26438#38271)
        TabOrder = 1
      end
      object Panel3: TPanel
        Left = 0
        Top = 624
        Width = 368
        Height = 150
        Align = alBottom
        TabOrder = 2
        object Button7: TButton
          Left = 128
          Top = 8
          Width = 75
          Height = 25
          Caption = #20282#26381#36816#21160
          TabOrder = 0
        end
        object Button8: TButton
          Left = 8
          Top = 8
          Width = 113
          Height = 25
          Caption = #35745#31639#20301#23039
          TabOrder = 1
        end
        object Button5: TButton
          Left = 8
          Top = 40
          Width = 75
          Height = 25
          Caption = #24402#38646
          TabOrder = 2
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #36816#21160#27169#25311
      ImageIndex = 3
      object Shape2: TShape
        Left = 32
        Top = 728
        Width = 65
        Height = 65
      end
      object GroupBox6: TGroupBox
        Left = 0
        Top = 233
        Width = 368
        Height = 233
        Align = alTop
        Caption = #19978#24179#21488#20301#32622
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        object Panel9: TPanel
          Left = 16
          Top = 32
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'X(mm) '
          TabOrder = 0
        end
        object Panel11: TPanel
          Left = 136
          Top = 32
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 1
        end
        object Panel13: TPanel
          Left = 16
          Top = 64
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Y(mm) '
          TabOrder = 2
        end
        object Panel15: TPanel
          Left = 136
          Top = 64
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 3
        end
        object Panel17: TPanel
          Left = 16
          Top = 96
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Z(mm) '
          TabOrder = 4
        end
        object Panel18: TPanel
          Left = 136
          Top = 96
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 5
        end
        object Panel19: TPanel
          Left = 16
          Top = 128
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Yaw('#176') '
          TabOrder = 6
        end
        object Panel20: TPanel
          Left = 136
          Top = 128
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 7
        end
        object Panel21: TPanel
          Left = 16
          Top = 160
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Pitch('#176') '
          TabOrder = 8
        end
        object Panel22: TPanel
          Left = 136
          Top = 160
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 9
        end
        object Panel23: TPanel
          Left = 16
          Top = 192
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Pitch('#176')'
          TabOrder = 10
        end
        object Panel24: TPanel
          Left = 136
          Top = 192
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 11
        end
      end
      object GroupBox7: TGroupBox
        Left = 0
        Top = 0
        Width = 368
        Height = 233
        Align = alTop
        Caption = #39134#26426#21152#36895#24230
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        object Panel25: TPanel
          Left = 16
          Top = 32
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'X(mm) '
          TabOrder = 0
        end
        object Panel26: TPanel
          Left = 136
          Top = 32
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 1
        end
        object Panel27: TPanel
          Left = 16
          Top = 64
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Y(mm) '
          TabOrder = 2
        end
        object Panel28: TPanel
          Left = 136
          Top = 64
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 3
        end
        object Panel29: TPanel
          Left = 16
          Top = 96
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Z(mm) '
          TabOrder = 4
        end
        object Panel30: TPanel
          Left = 136
          Top = 96
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 5
        end
        object Panel31: TPanel
          Left = 16
          Top = 128
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Yaw('#176') '
          TabOrder = 6
        end
        object Panel32: TPanel
          Left = 136
          Top = 128
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 7
        end
        object Panel33: TPanel
          Left = 16
          Top = 160
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Pitch('#176') '
          TabOrder = 8
        end
        object Panel34: TPanel
          Left = 136
          Top = 160
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 9
        end
        object Panel35: TPanel
          Left = 16
          Top = 192
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Pitch('#176')'
          TabOrder = 10
        end
        object Panel36: TPanel
          Left = 136
          Top = 192
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 11
        end
      end
      object CSpinEdit1: TCSpinEdit
        Left = 32
        Top = 528
        Width = 121
        Height = 22
        TabOrder = 2
      end
      object CheckBox1: TCheckBox
        Left = 32
        Top = 488
        Width = 97
        Height = 17
        Caption = 'Trans FSX'
        TabOrder = 3
      end
      object CSpinEdit2: TCSpinEdit
        Left = 32
        Top = 560
        Width = 121
        Height = 22
        TabOrder = 4
      end
      object CSpinEdit3: TCSpinEdit
        Left = 32
        Top = 592
        Width = 121
        Height = 22
        TabOrder = 5
      end
      object Button1: TButton
        Left = 208
        Top = 504
        Width = 75
        Height = 25
        Caption = 'Button1'
        TabOrder = 6
        OnClick = Button1Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'TabSheet3'
      ImageIndex = 4
      object GroupBox8: TGroupBox
        Left = 0
        Top = 0
        Width = 368
        Height = 254
        Align = alTop
        Caption = #36816#21160#22686#37327
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Visible = False
        object Panel37: TPanel
          Left = 16
          Top = 32
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack1'
          TabOrder = 0
        end
        object Panel38: TPanel
          Left = 136
          Top = 32
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 1
        end
        object Panel39: TPanel
          Left = 16
          Top = 64
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack2'
          TabOrder = 2
        end
        object Panel40: TPanel
          Left = 136
          Top = 64
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 3
        end
        object Panel41: TPanel
          Left = 16
          Top = 96
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack3'
          TabOrder = 4
        end
        object Panel42: TPanel
          Left = 136
          Top = 96
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 5
        end
        object Panel43: TPanel
          Left = 16
          Top = 128
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack4'
          TabOrder = 6
        end
        object Panel44: TPanel
          Left = 136
          Top = 128
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 7
        end
        object Panel45: TPanel
          Left = 16
          Top = 160
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack5'
          TabOrder = 8
        end
        object Panel46: TPanel
          Left = 136
          Top = 160
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 9
        end
        object Panel47: TPanel
          Left = 16
          Top = 192
          Width = 113
          Height = 25
          Alignment = taRightJustify
          BevelOuter = bvLowered
          Caption = 'Jack6'
          TabOrder = 10
        end
        object Panel48: TPanel
          Left = 136
          Top = 192
          Width = 169
          Height = 25
          Alignment = taLeftJustify
          BevelOuter = bvLowered
          TabOrder = 11
        end
      end
    end
  end
  object ImageList1: TImageList
    Left = 536
    Top = 224
    Bitmap = {
      494C010109000E00040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
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
      0000000000000000000000000000000000000000000000800000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000008000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000008000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000080
      0000008000000080000000800000008000000080000000800000008000000080
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000008000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000800000000000000000
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
      0000000000000000000000000000000000000000000000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000800000008000000080000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000008000000000000000000000000000000000
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
      000000 000000000000000000000000000000000000000000000000000000000
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
      00000000000000000000000000000000FFFF000000000000FFFF000000000000
      FFFF000000000000FF7F000000000000FF3F000000000000FF1F000000000000
      C00F000000000000C007000000000000C003000000000000C007000000000000
      C00F000000000000FF1F000000000000FF3F000000000000FF7F000000000000
      FFFF000000000000FFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
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
    Interval = 20
    OnTimer = Timer1Timer
    Left = 400
    Top = 48
  end
  object Timer2: TTimer
    Interval = 20
    OnTimer = Timer2Timer
    Left = 432
    Top = 48
  end
  object Timer3: TTimer
    Interval = 100
    OnTimer = Timer3Timer
    Left = 464
    Top = 48
  end
end
