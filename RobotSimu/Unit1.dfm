object Form1: TForm1
  Left = 54
  Top = 107
  Width = 1600
  Height = 900
  Caption = #24182#32852#26426#22120#20154#27979#35797
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
  object PaintBox1: TPaintBox
    Left = 400
    Top = 53
    Width = 1184
    Height = 790
    Cursor = crHandPoint
    Align = alClient
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
  end
  object CoolBar1: TCoolBar
    Left = 0
    Top = 0
    Width = 1584
    Height = 53
    AutoSize = True
    Bands = <
      item
        Control = ToolBar2
        ImageIndex = -1
        MinHeight = 22
        Width = 1580
      end
      item
        Control = ToolBar1
        ImageIndex = -1
        Width = 1580
      end>
    object ToolBar2: TToolBar
      Left = 9
      Top = 0
      Width = 1567
      Height = 22
      AutoSize = True
      ButtonWidth = 75
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
        AutoSize = True
        Caption = #26242#20572
        ImageIndex = 3
        OnClick = ToolButton11Click
      end
      object ToolButton12: TToolButton
        Left = 748
        Top = 0
        Caption = #20302#36895#27979#35797
        ImageIndex = 2
        OnClick = ToolButton12Click
      end
    end
    object ToolBar1: TToolBar
      Left = 9
      Top = 24
      Width = 1567
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
      object RadioButton4: TRadioButton
        Left = 523
        Top = 0
        Width = 94
        Height = 22
        Caption = #20943#25670#25511#21046
        TabOrder = 4
      end
      object RadioButton5: TRadioButton
        Left = 617
        Top = 0
        Width = 94
        Height = 22
        Caption = #20845#36275#26426#22120#20154
        TabOrder = 5
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 53
    Width = 400
    Height = 790
    Align = alLeft
    BevelOuter = bvNone
    Caption = 'Panel1'
    TabOrder = 1
    object Bevel1: TBevel
      Left = 0
      Top = 0
      Width = 400
      Height = 9
      Align = alTop
      Shape = bsSpacer
    end
    object PageControl1: TPageControl
      Left = 0
      Top = 504
      Width = 400
      Height = 433
      ActivePage = TabSheet10
      Align = alTop
      MultiLine = True
      TabIndex = 4
      TabOrder = 0
      object TabSheetRobot: TTabSheet
        Caption = #20301#23039#25511#21046
        ImageIndex = 1
        object GroupBox2: TGroupBox
          Left = 0
          Top = 0
          Width = 392
          Height = 145
          Align = alTop
          Caption = #19978#24179#21488#20301#23039
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object Label1: TLabel
            Left = 16
            Top = 32
            Width = 42
            Height = 14
            Caption = 'X (mm)'
          end
          object Label2: TLabel
            Left = 112
            Top = 32
            Width = 42
            Height = 14
            Caption = 'Y (mm)'
          end
          object Label3: TLabel
            Left = 208
            Top = 32
            Width = 42
            Height = 14
            Caption = 'Z (mm)'
          end
          object Label4: TLabel
            Left = 16
            Top = 88
            Width = 21
            Height = 14
            Caption = 'Yaw'
          end
          object Label5: TLabel
            Left = 112
            Top = 88
            Width = 35
            Height = 14
            Caption = 'Pitch'
          end
          object Label6: TLabel
            Left = 208
            Top = 88
            Width = 28
            Height = 14
            Caption = 'Roll'
          end
          object CSpinEditX: TCSpinEdit
            Left = 16
            Top = 48
            Width = 89
            Height = 23
            TabOrder = 0
          end
          object CSpinEditY: TCSpinEdit
            Left = 112
            Top = 48
            Width = 89
            Height = 23
            TabOrder = 1
          end
          object CSpinEditZ: TCSpinEdit
            Left = 208
            Top = 48
            Width = 89
            Height = 23
            TabOrder = 2
          end
          object CSpinEditYaw: TCSpinEdit
            Left = 16
            Top = 104
            Width = 89
            Height = 23
            TabOrder = 3
          end
          object CSpinEditPitch: TCSpinEdit
            Left = 112
            Top = 104
            Width = 89
            Height = 23
            TabOrder = 4
          end
          object CSpinEditRoll: TCSpinEdit
            Left = 208
            Top = 104
            Width = 89
            Height = 23
            TabOrder = 5
          end
        end
        object Memo1: TMemo
          Left = 0
          Top = 496
          Width = 368
          Height = 282
          Align = alCustom
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          Lines.Strings = (
            #26438#38271)
          TabOrder = 1
        end
        object Button2: TButton
          Left = 16
          Top = 160
          Width = 75
          Height = 25
          Caption = 'Button2'
          TabOrder = 2
          OnClick = Button2Click
        end
        object Button3: TButton
          Left = 128
          Top = 160
          Width = 75
          Height = 25
          Caption = 'Button3'
          TabOrder = 3
        end
        object Button4: TButton
          Left = 264
          Top = 168
          Width = 75
          Height = 25
          Caption = 'Button4'
          TabOrder = 4
        end
        object Edit1: TEdit
          Left = 24
          Top = 208
          Width = 233
          Height = 21
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          TabOrder = 5
          Text = 'Edit1'
        end
      end
      object TabSheetServo: TTabSheet
        Caption = #30452#25509#30005#32568#25511#21046
        ImageIndex = 2
        object GroupBox4: TGroupBox
          Left = 0
          Top = 0
          Width = 392
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
          object CSpinEditL1: TCSpinEdit
            Left = 16
            Top = 48
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 0
            Value = 200
          end
          object CSpinEditL2: TCSpinEdit
            Left = 112
            Top = 48
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 1
            Value = 200
          end
          object CSpinEditL3: TCSpinEdit
            Left = 208
            Top = 48
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 2
            Value = 200
          end
          object CSpinEditL4: TCSpinEdit
            Left = 16
            Top = 104
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 3
            Value = 200
          end
          object CSpinEditL5: TCSpinEdit
            Left = 112
            Top = 104
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 4
            Value = 200
          end
          object CSpinEditL6: TCSpinEdit
            Left = 208
            Top = 104
            Width = 89
            Height = 22
            MaxValue = 500
            TabOrder = 5
            Value = 200
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = #36816#21160#27169#25311
        ImageIndex = 3
        object PageControl3: TPageControl
          Left = 0
          Top = 0
          Width = 392
          Height = 405
          ActivePage = TabSheet5
          Align = alClient
          TabIndex = 0
          TabOrder = 0
          object TabSheet5: TTabSheet
            Caption = #32473#23450#25511#21046
            object Panel49: TPanel
              Left = 0
              Top = 0
              Width = 384
              Height = 33
              Align = alTop
              BevelOuter = bvNone
              TabOrder = 0
              object CheckBoxFSXCtrl: TCheckBox
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
            object GroupBox7: TGroupBox
              Left = 0
              Top = 33
              Width = 384
              Height = 144
              Align = alTop
              Caption = #39134#26426#21152#36895#24230
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = #23435#20307
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              object ListView1: TListView
                Left = 2
                Top = 16
                Width = 380
                Height = 126
                Align = alClient
                Columns = <
                  item
                    Caption = #36890#36947
                    Width = 100
                  end
                  item
                    Caption = #32473#23450
                    Width = 100
                  end
                  item
                    Caption = #36755#20986
                    Width = 100
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
            object GroupBox9: TGroupBox
              Left = 0
              Top = 177
              Width = 384
              Height = 112
              Align = alTop
              Caption = #32473#23450#21152#36895#24230
              Font.Charset = ANSI_CHARSET
              Font.Color = clWindowText
              Font.Height = -14
              Font.Name = #23435#20307
              Font.Style = []
              ParentFont = False
              TabOrder = 2
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
          end
          object TabSheet6: TTabSheet
            Caption = #21152#36895#24230#21442#25968
            ImageIndex = 1
            object LabeledEdit5: TLabeledEdit
              Left = 8
              Top = 32
              Width = 110
              Height = 21
              EditLabel.Width = 90
              EditLabel.Height = 12
              EditLabel.Caption = 'X'#36724#26368#22823#34892#31243'(mm)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit6: TLabeledEdit
              Left = 128
              Top = 32
              Width = 110
              Height = 21
              EditLabel.Width = 102
              EditLabel.Height = 12
              EditLabel.Caption = 'X'#36724#26368#22823#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit7: TLabeledEdit
              Left = 8
              Top = 80
              Width = 110
              Height = 21
              EditLabel.Width = 90
              EditLabel.Height = 12
              EditLabel.Caption = 'Y'#36724#26368#22823#34892#31243'(mm)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
            object LabeledEdit8: TLabeledEdit
              Left = 128
              Top = 80
              Width = 110
              Height = 21
              EditLabel.Width = 102
              EditLabel.Height = 12
              EditLabel.Caption = 'Y'#36724#26368#22823#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
            end
            object LabeledEdit9: TLabeledEdit
              Left = 8
              Top = 128
              Width = 110
              Height = 21
              EditLabel.Width = 90
              EditLabel.Height = 12
              EditLabel.Caption = 'Z'#36724#26368#22823#34892#31243'(mm)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
            object LabeledEdit10: TLabeledEdit
              Left = 128
              Top = 128
              Width = 110
              Height = 21
              EditLabel.Width = 102
              EditLabel.Height = 12
              EditLabel.Caption = 'Z'#36724#26368#22823#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 5
            end
            object LabeledEdit11: TLabeledEdit
              Left = 8
              Top = 184
              Width = 110
              Height = 21
              EditLabel.Width = 96
              EditLabel.Height = 12
              EditLabel.Caption = #20463#20208#26368#22823#35282#24230'('#176')'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 6
            end
            object LabeledEdit12: TLabeledEdit
              Left = 128
              Top = 184
              Width = 110
              Height = 21
              EditLabel.Width = 120
              EditLabel.Height = 12
              EditLabel.Caption = #20463#20208#26368#22823#35282#36895#24230'('#176'/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 7
            end
            object LabeledEdit13: TLabeledEdit
              Left = 8
              Top = 232
              Width = 110
              Height = 21
              EditLabel.Width = 96
              EditLabel.Height = 12
              EditLabel.Caption = #28378#36716#26368#22823#35282#24230'('#176')'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 8
            end
            object LabeledEdit14: TLabeledEdit
              Left = 128
              Top = 232
              Width = 110
              Height = 21
              EditLabel.Width = 120
              EditLabel.Height = 12
              EditLabel.Caption = #28378#36716#26368#22823#35282#36895#24230'('#176'/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 9
            end
            object LabeledEdit27: TLabeledEdit
              Left = 248
              Top = 32
              Width = 110
              Height = 21
              EditLabel.Width = 114
              EditLabel.Height = 12
              EditLabel.Caption = 'X'#36724#26368#22823#21152#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 10
            end
            object LabeledEdit28: TLabeledEdit
              Left = 248
              Top = 80
              Width = 110
              Height = 21
              EditLabel.Width = 114
              EditLabel.Height = 12
              EditLabel.Caption = 'Y'#36724#26368#22823#21152#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 11
            end
            object LabeledEdit29: TLabeledEdit
              Left = 248
              Top = 128
              Width = 110
              Height = 21
              EditLabel.Width = 114
              EditLabel.Height = 12
              EditLabel.Caption = 'Z'#36724#26368#22823#21152#36895#24230'(mm/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 12
            end
            object Button1: TButton
              Left = 8
              Top = 272
              Width = 113
              Height = 25
              Caption = #20445#23384#24182#24212#29992
              TabOrder = 13
              OnClick = Button1Click
            end
          end
          object TabSheet7: TTabSheet
            Caption = #35282#36895#24230#21442#25968
            ImageIndex = 2
            object LabeledEdit15: TLabeledEdit
              Left = 16
              Top = 88
              Width = 121
              Height = 21
              EditLabel.Width = 96
              EditLabel.Height = 12
              EditLabel.Caption = #20463#20208#26368#22823#35282#24230'('#176')'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 0
            end
            object LabeledEdit16: TLabeledEdit
              Left = 152
              Top = 88
              Width = 121
              Height = 21
              EditLabel.Width = 120
              EditLabel.Height = 12
              EditLabel.Caption = #20463#20208#26368#22823#35282#36895#24230'('#176'/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 1
            end
            object LabeledEdit17: TLabeledEdit
              Left = 16
              Top = 136
              Width = 121
              Height = 21
              EditLabel.Width = 96
              EditLabel.Height = 12
              EditLabel.Caption = #28378#36716#26368#22823#35282#24230'('#176')'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 2
            end
            object LabeledEdit18: TLabeledEdit
              Left = 152
              Top = 136
              Width = 121
              Height = 21
              EditLabel.Width = 120
              EditLabel.Height = 12
              EditLabel.Caption = #28378#36716#26368#22823#35282#36895#24230'('#176'/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 3
            end
            object LabeledEdit19: TLabeledEdit
              Left = 16
              Top = 40
              Width = 121
              Height = 21
              EditLabel.Width = 96
              EditLabel.Height = 12
              EditLabel.Caption = #20559#33322#26368#22823#35282#24230'('#176')'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 4
            end
            object LabeledEdit20: TLabeledEdit
              Left = 152
              Top = 40
              Width = 121
              Height = 21
              EditLabel.Width = 120
              EditLabel.Height = 12
              EditLabel.Caption = #20559#33322#26368#22823#35282#36895#24230'('#176'/s)'
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpAbove
              LabelSpacing = 3
              TabOrder = 5
            end
          end
          object TabSheet8: TTabSheet
            Caption = #39640#36890#28388#27874
            ImageIndex = 3
            object CheckBox3: TCheckBox
              Left = 16
              Top = 16
              Width = 73
              Height = 17
              Caption = 'X'
              TabOrder = 0
            end
            object CheckBox4: TCheckBox
              Left = 16
              Top = 48
              Width = 73
              Height = 17
              Caption = 'Y'
              TabOrder = 1
            end
            object CheckBox5: TCheckBox
              Left = 16
              Top = 80
              Width = 73
              Height = 17
              Caption = 'Z'
              TabOrder = 2
            end
            object CheckBox6: TCheckBox
              Left = 16
              Top = 112
              Width = 65
              Height = 17
              Caption = 'Yaw'
              TabOrder = 3
            end
            object CheckBox7: TCheckBox
              Left = 16
              Top = 144
              Width = 65
              Height = 17
              Caption = 'Pitch'
              TabOrder = 4
            end
            object CheckBox8: TCheckBox
              Left = 16
              Top = 176
              Width = 65
              Height = 17
              Caption = 'Roll'
              TabOrder = 5
            end
            object LabeledEdit21: TLabeledEdit
              Left = 160
              Top = 16
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 6
            end
            object LabeledEdit22: TLabeledEdit
              Left = 160
              Top = 48
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 7
            end
            object LabeledEdit23: TLabeledEdit
              Left = 160
              Top = 80
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 8
            end
            object LabeledEdit24: TLabeledEdit
              Left = 160
              Top = 112
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 9
            end
            object LabeledEdit25: TLabeledEdit
              Left = 160
              Top = 144
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 10
            end
            object LabeledEdit26: TLabeledEdit
              Left = 160
              Top = 176
              Width = 121
              Height = 21
              EditLabel.Width = 48
              EditLabel.Height = 12
              EditLabel.Caption = #28388#27874#31995#25968
              EditLabel.Font.Charset = ANSI_CHARSET
              EditLabel.Font.Color = clWindowText
              EditLabel.Font.Height = -12
              EditLabel.Font.Name = #23435#20307
              EditLabel.Font.Style = []
              EditLabel.ParentFont = False
              ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
              LabelPosition = lpLeft
              LabelSpacing = 3
              TabOrder = 11
            end
          end
          object TabSheet9: TTabSheet
            Caption = #36755#20837#26354#32447
            ImageIndex = 4
          end
        end
      end
      object TabSheet4: TTabSheet
        Caption = #20943#25670#25511#21046#27169#25311
        ImageIndex = 3
        object CheckBox2: TCheckBox
          Left = 16
          Top = 8
          Width = 113
          Height = 17
          Caption = #35835#21462#21152#35745#25968#25454
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = CheckBox2Click
        end
        object LabeledEdit1: TLabeledEdit
          Left = 80
          Top = 48
          Width = 161
          Height = 21
          EditLabel.Width = 38
          EditLabel.Height = 13
          EditLabel.Caption = 'AccX'#65306
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 1
        end
        object LabeledEdit2: TLabeledEdit
          Left = 80
          Top = 72
          Width = 161
          Height = 21
          EditLabel.Width = 38
          EditLabel.Height = 13
          EditLabel.Caption = 'AccY'#65306
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 2
        end
        object LabeledEdit3: TLabeledEdit
          Left = 80
          Top = 96
          Width = 161
          Height = 21
          EditLabel.Width = 38
          EditLabel.Height = 13
          EditLabel.Caption = 'AccZ'#65306
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 3
        end
        object LabeledEdit4: TLabeledEdit
          Left = 80
          Top = 120
          Width = 161
          Height = 21
          EditLabel.Width = 64
          EditLabel.Height = 13
          EditLabel.Caption = 'CommRate'#65306
          ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
          LabelPosition = lpLeft
          LabelSpacing = 3
          TabOrder = 4
        end
        object CSpinEdit7: TCSpinEdit
          Left = 48
          Top = 184
          Width = 121
          Height = 22
          TabOrder = 5
        end
      end
      object TabSheet10: TTabSheet
        Caption = #20845#36275#26426#22120#20154
        ImageIndex = 4
        object GroupBox11: TGroupBox
          Left = 136
          Top = 16
          Width = 241
          Height = 161
          Caption = #38190#30424#25511#21046
          TabOrder = 0
          object Label7: TLabel
            Left = 32
            Top = 32
            Width = 72
            Height = 12
            Caption = 'X'#26041#21521#20998#37327'(%)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label20: TLabel
            Left = 32
            Top = 56
            Width = 72
            Height = 12
            Caption = 'Y'#26041#21521#20998#37327'(%)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label21: TLabel
            Left = 48
            Top = 80
            Width = 42
            Height = 12
            Caption = 'Yaw'#35282#24230
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label22: TLabel
            Left = 56
            Top = 104
            Width = 42
            Height = 12
            Caption = #36895#24230'(%)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label23: TLabel
            Left = 16
            Top = 128
            Width = 84
            Height = 12
            Caption = 'XY'#24179#38754#39640#24230'(mm)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object CSpinEdit8: TCSpinEdit
            Left = 104
            Top = 25
            Width = 120
            Height = 22
            MaxValue = 100
            MinValue = -100
            TabOrder = 0
          end
          object CSpinEdit9: TCSpinEdit
            Left = 104
            Top = 49
            Width = 120
            Height = 22
            MaxValue = 100
            MinValue = -100
            TabOrder = 1
          end
          object CSpinEdit10: TCSpinEdit
            Left = 104
            Top = 73
            Width = 120
            Height = 22
            MaxValue = 30
            MinValue = -30
            TabOrder = 2
          end
          object CSpinEdit11: TCSpinEdit
            Left = 104
            Top = 97
            Width = 120
            Height = 22
            MaxValue = 100
            TabOrder = 3
          end
          object CSpinEdit12: TCSpinEdit
            Left = 104
            Top = 121
            Width = 120
            Height = 22
            MaxValue = 100
            MinValue = 20
            TabOrder = 4
            Value = 50
          end
        end
        object GroupBox12: TGroupBox
          Left = 16
          Top = 128
          Width = 113
          Height = 49
          Caption = #25671#26438#25511#21046
          TabOrder = 1
          Visible = False
          object CheckBox9: TCheckBox
            Left = 16
            Top = 24
            Width = 137
            Height = 17
            Caption = #20351#33021#25671#26438#25511#21046
            TabOrder = 0
            OnClick = CheckBox9Click
          end
        end
        object Panel7: TPanel
          Left = 24
          Top = 24
          Width = 100
          Height = 100
          BevelOuter = bvLowered
          TabOrder = 2
          object PaintBox2: TPaintBox
            Left = 1
            Top = 1
            Width = 98
            Height = 98
            Align = alClient
          end
        end
        object GroupBox13: TGroupBox
          Left = 136
          Top = 184
          Width = 241
          Height = 57
          Caption = #32593#32476#21457#36865
          TabOrder = 3
          object LabeledEdit30: TLabeledEdit
            Left = 32
            Top = 24
            Width = 105
            Height = 21
            EditLabel.Width = 13
            EditLabel.Height = 13
            EditLabel.Caption = 'IP '
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 0
          end
          object LabeledEdit31: TLabeledEdit
            Left = 168
            Top = 24
            Width = 57
            Height = 21
            EditLabel.Width = 22
            EditLabel.Height = 13
            EditLabel.Caption = 'Port '
            ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
            LabelPosition = lpLeft
            LabelSpacing = 3
            TabOrder = 1
          end
          object CheckBox10: TCheckBox
            Left = 64
            Top = 0
            Width = 17
            Height = 17
            TabOrder = 2
          end
        end
      end
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 9
      Width = 400
      Height = 89
      Align = alTop
      Caption = #19978#24179#21488#36816#21160#33539#22260
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Visible = False
      object EditMinZ: TLabeledEdit
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
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object EditMaxZ: TLabeledEdit
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
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
    end
    object PageControl2: TPageControl
      Left = 0
      Top = 153
      Width = 400
      Height = 351
      ActivePage = TabSheet1
      Align = alTop
      TabIndex = 0
      TabOrder = 2
      object TabSheet1: TTabSheet
        Caption = #27169#25311#35745#31639#26174#31034
        object GroupBox6: TGroupBox
          Left = 0
          Top = 0
          Width = 392
          Height = 183
          Align = alTop
          Caption = #19978#24179#21488#20301#23039
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          object ListViewPostures: TListView
            Left = 2
            Top = 56
            Width = 388
            Height = 125
            Align = alBottom
            Columns = <
              item
                Caption = #36890#36947
                Width = 100
              end
              item
                Caption = #26426#22120#20154#20301#23039
                Width = 120
              end
              item
                Caption = #27491#21521#35299#31639#20301#23039
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
          object Panel3: TPanel
            Left = 8
            Top = 24
            Width = 217
            Height = 25
            Alignment = taLeftJustify
            BevelOuter = bvLowered
            Caption = 'Panel3'
            TabOrder = 1
          end
        end
        object GroupBox10: TGroupBox
          Left = 0
          Top = 183
          Width = 392
          Height = 140
          Align = alClient
          Caption = #36830#26438#38271#24230
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -14
          Font.Name = #23435#20307
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          object ListViewJacks: TListView
            Left = 2
            Top = 16
            Width = 388
            Height = 122
            Align = alClient
            Columns = <
              item
                Caption = #36890#36947
                Width = 65
              end
              item
                Caption = 'Length(mm)'
                Width = 90
              end
              item
                Caption = 'Pulse'
                Width = 70
              end
              item
                Caption = 'Spd(rpm)'
                Width = 80
              end>
            GridLines = True
            Items.Data = {
              C80000000600000000000000FFFFFFFFFFFFFFFF0300000000000000024C3100
              000000000000FFFFFFFFFFFFFFFF0300000000000000024C3200000000000000
              FFFFFFFFFFFFFFFF0300000000000000024C3300000000000000FFFFFFFFFFFF
              FFFF0300000000000000024C3400000000000000FFFFFFFFFFFFFFFF03000000
              00000000024C3500000000000000FFFFFFFFFFFFFFFF0300000000000000024C
              36000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
              FFFFFFFFFFFFFFFF}
            ReadOnly = True
            TabOrder = 0
            ViewStyle = vsReport
          end
        end
      end
      object TabSheet3: TTabSheet
        Caption = #25511#21046#22120#21453#39304#26174#31034
        ImageIndex = 1
        object GroupBox3: TGroupBox
          Left = 0
          Top = 0
          Width = 392
          Height = 129
          Align = alTop
          Caption = #38480#20301#29366#24577
          TabOrder = 0
          object Shape1: TShape
            Left = 16
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape2: TShape
            Left = 40
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape3: TShape
            Left = 64
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape4: TShape
            Left = 88
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape5: TShape
            Left = 112
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape6: TShape
            Left = 136
            Top = 24
            Width = 17
            Height = 17
          end
          object Shape7: TShape
            Left = 16
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape8: TShape
            Left = 40
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape9: TShape
            Left = 64
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape10: TShape
            Left = 88
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape11: TShape
            Left = 112
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape12: TShape
            Left = 136
            Top = 48
            Width = 17
            Height = 17
          end
          object Shape13: TShape
            Left = 16
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape14: TShape
            Left = 40
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape15: TShape
            Left = 64
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape16: TShape
            Left = 88
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape17: TShape
            Left = 112
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape18: TShape
            Left = 136
            Top = 80
            Width = 17
            Height = 17
          end
          object Shape19: TShape
            Left = 16
            Top = 104
            Width = 17
            Height = 17
          end
          object Shape20: TShape
            Left = 40
            Top = 104
            Width = 17
            Height = 17
          end
          object Shape21: TShape
            Left = 64
            Top = 104
            Width = 17
            Height = 17
          end
          object Shape22: TShape
            Left = 88
            Top = 104
            Width = 17
            Height = 17
          end
          object Shape23: TShape
            Left = 112
            Top = 104
            Width = 17
            Height = 17
          end
          object Shape24: TShape
            Left = 136
            Top = 104
            Width = 17
            Height = 17
          end
        end
        object GroupBox5: TGroupBox
          Left = 0
          Top = 129
          Width = 392
          Height = 194
          Align = alClient
          Caption = #36830#26438#38271#24230
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
            Width = 388
            Height = 176
            Align = alClient
            Columns = <
              item
                Caption = #36890#36947
                Width = 65
              end
              item
                Caption = 'Length(mm)'
                Width = 90
              end
              item
                Caption = 'Pulse'
                Width = 70
              end
              item
                Caption = 'Spd(rpm)'
                Width = 80
              end>
            GridLines = True
            Items.Data = {
              C80000000600000000000000FFFFFFFFFFFFFFFF0300000000000000024C3100
              000000000000FFFFFFFFFFFFFFFF0300000000000000024C3200000000000000
              FFFFFFFFFFFFFFFF0300000000000000024C3300000000000000FFFFFFFFFFFF
              FFFF0300000000000000024C3400000000000000FFFFFFFFFFFFFFFF03000000
              00000000024C3500000000000000FFFFFFFFFFFFFFFF0300000000000000024C
              36000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
              FFFFFFFFFFFFFFFF}
            ReadOnly = True
            TabOrder = 0
            ViewStyle = vsReport
          end
        end
      end
    end
    object GroupBox8: TGroupBox
      Left = 0
      Top = 98
      Width = 400
      Height = 55
      Align = alTop
      Caption = #36890#20449#20018#21475
      TabOrder = 3
      object ComboBox1: TComboBox
        Left = 16
        Top = 24
        Width = 145
        Height = 21
        Style = csDropDownList
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 0
        Items.Strings = (
          'COM1'
          'COM2'
          'COM3'
          'COM4'
          'COM5'
          'COM6'
          'COM7'
          'COM8'
          'COM9'
          'COM10')
      end
      object CheckBox1: TCheckBox
        Left = 176
        Top = 24
        Width = 113
        Height = 17
        Caption = #19982#25511#21046#22120#36890#20449
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = #23435#20307
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = CheckBox1Click
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 843
    Width = 1584
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
    Left = 424
    Top = 80
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
  object TimerCtrlSimu: TTimer
    Enabled = False
    Interval = 20
    OnTimer = TimerCtrlSimuTimer
    Left = 456
    Top = 80
  end
  object TimerComm: TTimer
    Interval = 100
    OnTimer = TimerCommTimer
    Left = 488
    Top = 80
  end
  object AccSensorTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = AccSensorTimerTimer
    Left = 520
    Top = 80
  end
  object TimerJoyStick: TTimer
    Enabled = False
    Interval = 50
    OnTimer = TimerJoyStickTimer
    Left = 552
    Top = 80
  end
  object IdUDPClient1: TIdUDPClient
    Active = True
    Port = 0
    Left = 584
    Top = 80
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 616
    Top = 80
  end
end
