object Form1: TForm1
  Left = -35
  Top = 25
  Width = 1696
  Height = 1000
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 201
    Height = 943
    Align = alLeft
    BorderWidth = 5
    TabOrder = 0
    object Bevel1: TBevel
      Left = 6
      Top = 486
      Width = 189
      Height = 5
      Align = alTop
      Shape = bsSpacer
    end
    object GroupBox1: TGroupBox
      Left = 6
      Top = 6
      Width = 189
      Height = 480
      Align = alTop
      Caption = #26426#22120#20154#26426#26800#32467#26500#21442#25968
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
        Width = 126
        Height = 14
        Caption = #19978#24179#21488#38271#36724#38271#24230'(mm)'
      end
      object Label2: TLabel
        Left = 16
        Top = 88
        Width = 126
        Height = 14
        Caption = #19978#24179#21488#30701#36724#38271#24230'(mm)'
      end
      object Label3: TLabel
        Left = 16
        Top = 200
        Width = 126
        Height = 14
        Caption = #19979#24179#21488#38271#36724#38271#24230'(mm)'
      end
      object Label4: TLabel
        Left = 16
        Top = 256
        Width = 126
        Height = 14
        Caption = #19979#24179#21488#30701#36724#38271#24230'(mm)'
      end
      object Label5: TLabel
        Left = 16
        Top = 368
        Width = 112
        Height = 14
        Caption = #30005#32568#22266#23450#38271#24230'(mm)'
      end
      object Label6: TLabel
        Left = 16
        Top = 424
        Width = 112
        Height = 14
        Caption = #30005#32568#26368#22823#34892#31243'(mm)'
      end
      object Label7: TLabel
        Left = 16
        Top = 144
        Width = 140
        Height = 14
        Caption = #19978#24179#21488#38128#25509#28857#39640#24230'(mm)'
      end
      object Label8: TLabel
        Left = 16
        Top = 312
        Width = 140
        Height = 14
        Caption = #19979#24179#21488#20132#25509#28857#39640#24230'(mm)'
      end
      object CSpinEdit1: TCSpinEdit
        Left = 16
        Top = 56
        Width = 169
        Height = 23
        TabOrder = 0
      end
      object CSpinEdit2: TCSpinEdit
        Left = 16
        Top = 112
        Width = 169
        Height = 23
        TabOrder = 1
      end
      object CSpinEdit3: TCSpinEdit
        Left = 16
        Top = 224
        Width = 169
        Height = 23
        TabOrder = 2
      end
      object CSpinEdit4: TCSpinEdit
        Left = 16
        Top = 280
        Width = 169
        Height = 23
        TabOrder = 3
      end
      object CSpinEdit5: TCSpinEdit
        Left = 16
        Top = 392
        Width = 169
        Height = 23
        TabOrder = 4
      end
      object CSpinEdit6: TCSpinEdit
        Left = 16
        Top = 448
        Width = 169
        Height = 23
        TabOrder = 5
      end
      object CSpinEdit7: TCSpinEdit
        Left = 16
        Top = 168
        Width = 169
        Height = 23
        TabOrder = 6
      end
      object CSpinEdit8: TCSpinEdit
        Left = 16
        Top = 336
        Width = 169
        Height = 23
        TabOrder = 7
      end
    end
    object GroupBox2: TGroupBox
      Left = 6
      Top = 491
      Width = 189
      Height = 368
      Align = alTop
      Caption = #20202#22120#20301#23039#21442#25968
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object Label9: TLabel
        Left = 16
        Top = 32
        Width = 35
        Height = 14
        Caption = 'X(mm)'
      end
      object Label10: TLabel
        Left = 16
        Top = 88
        Width = 35
        Height = 14
        Caption = 'Y(mm)'
      end
      object Label11: TLabel
        Left = 16
        Top = 200
        Width = 49
        Height = 14
        Caption = 'Yaw('#176')'
      end
      object Label12: TLabel
        Left = 16
        Top = 256
        Width = 63
        Height = 14
        Caption = 'Pitch('#176')'
      end
      object Label15: TLabel
        Left = 16
        Top = 144
        Width = 35
        Height = 14
        Caption = 'Z(mm)'
      end
      object Label16: TLabel
        Left = 16
        Top = 312
        Width = 56
        Height = 14
        Caption = 'Roll('#176')'
      end
      object CSpinEdit9: TCSpinEdit
        Left = 16
        Top = 56
        Width = 169
        Height = 23
        TabOrder = 0
      end
      object CSpinEdit10: TCSpinEdit
        Left = 16
        Top = 112
        Width = 169
        Height = 23
        TabOrder = 1
      end
      object CSpinEdit11: TCSpinEdit
        Left = 16
        Top = 224
        Width = 169
        Height = 23
        TabOrder = 2
      end
      object CSpinEdit12: TCSpinEdit
        Left = 16
        Top = 280
        Width = 169
        Height = 23
        TabOrder = 3
      end
      object CSpinEdit15: TCSpinEdit
        Left = 16
        Top = 168
        Width = 169
        Height = 23
        TabOrder = 4
      end
      object CSpinEdit16: TCSpinEdit
        Left = 16
        Top = 336
        Width = 169
        Height = 23
        TabOrder = 5
        Value = -180
      end
    end
    object Button7: TButton
      Left = 16
      Top = 872
      Width = 121
      Height = 25
      Caption = #35774#32622#21442#25968
      TabOrder = 2
      OnClick = Button7Click
    end
  end
  object Panel3: TPanel
    Left = 201
    Top = 0
    Width = 201
    Height = 943
    Align = alLeft
    BorderWidth = 5
    TabOrder = 1
    object Bevel2: TBevel
      Left = 6
      Top = 446
      Width = 189
      Height = 5
      Align = alTop
      Shape = bsSpacer
    end
    object Bevel3: TBevel
      Left = 6
      Top = 441
      Width = 189
      Height = 5
      Align = alTop
      Shape = bsSpacer
    end
    object GroupBox3: TGroupBox
      Left = 6
      Top = 6
      Width = 189
      Height = 251
      Align = alTop
      Caption = #26426#22120#20154#25511#21046
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label20: TLabel
        Left = 16
        Top = 32
        Width = 98
        Height = 14
        Caption = #26426#22120#20154#36890#20449#31471#21475
      end
      object Label13: TLabel
        Left = 24
        Top = 96
        Width = 56
        Height = 14
        Caption = #30005#32568#32534#21495
      end
      object Label14: TLabel
        Left = 24
        Top = 152
        Width = 84
        Height = 14
        Caption = #30005#32568#38271#24230'(mm)'
      end
      object ComboBox1: TComboBox
        Left = 16
        Top = 56
        Width = 145
        Height = 22
        Style = csDropDownList
        ItemHeight = 14
        ItemIndex = 0
        TabOrder = 0
        Text = 'COM1'
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
      object CSpinEdit13: TCSpinEdit
        Left = 20
        Top = 112
        Width = 149
        Height = 23
        MaxValue = 6
        MinValue = 1
        TabOrder = 1
        Value = 1
      end
      object CSpinEdit14: TCSpinEdit
        Left = 20
        Top = 168
        Width = 149
        Height = 23
        TabOrder = 2
      end
      object Button2: TButton
        Left = 16
        Top = 200
        Width = 121
        Height = 25
        Caption = #25163#21160#25511#21046#30005#32568
        TabOrder = 3
        OnClick = Button2Click
      end
    end
    object GroupBox4: TGroupBox
      Left = 6
      Top = 451
      Width = 189
      Height = 262
      Align = alTop
      Caption = #37319#26679#26631#23450'('#26679#26412#25968#65306'0)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = #23435#20307
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      object Label21: TLabel
        Left = 24
        Top = 32
        Width = 56
        Height = 14
        Caption = #37319#26679#25968#37327
      end
      object Button3: TButton
        Left = 16
        Top = 80
        Width = 121
        Height = 25
        Caption = #22686#21152#37319#26679
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 16
        Top = 168
        Width = 121
        Height = 25
        Caption = #26631#23450#35745#31639
        TabOrder = 1
      end
      object Button5: TButton
        Left = 16
        Top = 208
        Width = 121
        Height = 25
        Caption = #28165#38500#37319#26679
        TabOrder = 2
      end
      object CSpinEdit21: TCSpinEdit
        Left = 20
        Top = 48
        Width = 149
        Height = 23
        MaxValue = 10000
        MinValue = 1
        TabOrder = 3
        Value = 1
      end
      object Button1: TButton
        Left = 16
        Top = 112
        Width = 121
        Height = 25
        Caption = #20572#27490#37319#26679
        TabOrder = 4
        OnClick = Button1Click
      end
    end
    object GroupBox5: TGroupBox
      Left = 6
      Top = 257
      Width = 189
      Height = 184
      Align = alTop
      Caption = #30005#32568#21453#39304#38271#24230
      TabOrder = 2
      object ValueList: TValueListEditor
        Left = 2
        Top = 15
        Width = 185
        Height = 167
        Align = alClient
        TabOrder = 0
        ColWidths = (
          79
          100)
      end
    end
  end
  object PageControl1: TPageControl
    Left = 402
    Top = 0
    Width = 1278
    Height = 943
    ActivePage = TabSheet2
    Align = alClient
    TabIndex = 1
    TabOrder = 2
    object TabSheet1: TTabSheet
      Caption = #22522#20110#28145#24230#30456#26426#26631#23450
      object PaintBox1: TPaintBox
        Left = 0
        Top = 0
        Width = 1270
        Height = 772
        Align = alClient
      end
      object Memo1: TMemo
        Left = 0
        Top = 772
        Width = 1270
        Height = 143
        Align = alBottom
        Lines.Strings = (
          'Memo1')
        TabOrder = 0
      end
    end
    object TabSheet2: TTabSheet
      Caption = #27169#25311#27979#35797
      ImageIndex = 1
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 1270
        Height = 217
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object GroupBox6: TGroupBox
          Left = 0
          Top = 0
          Width = 185
          Height = 217
          Align = alLeft
          Caption = #27979#35797#26465#20214
          TabOrder = 0
          object CheckBox1: TCheckBox
            Left = 16
            Top = 40
            Width = 153
            Height = 17
            Caption = #24573#30053#19979#24179#21488#38128#25509#28857#35823#24046
            TabOrder = 0
          end
          object CheckBox2: TCheckBox
            Left = 16
            Top = 72
            Width = 153
            Height = 17
            Caption = #24573#30053#30005#32568#35823#24046
            TabOrder = 1
          end
          object CheckBox3: TCheckBox
            Left = 16
            Top = 104
            Width = 153
            Height = 17
            Caption = #24573#30053#35266#27979#35823#24046
            TabOrder = 2
          end
          object CheckBox4: TCheckBox
            Left = 16
            Top = 136
            Width = 153
            Height = 17
            Caption = #38543#26426#29983#25104#26679#26412
            TabOrder = 3
          end
        end
        object GroupBox7: TGroupBox
          Left = 185
          Top = 0
          Width = 200
          Height = 217
          Align = alLeft
          Caption = #35823#24046#33539#22260
          TabOrder = 1
          object Label29: TLabel
            Left = 22
            Top = 24
            Width = 154
            Height = 14
            Caption = #26426#22120#20154#26412#20307#35823#24046#33539#22260'(mm)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label18: TLabel
            Left = 22
            Top = 72
            Width = 154
            Height = 14
            Caption = #35266#27979#22120#32447#24615#35823#24046#33539#22260'(mm)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label30: TLabel
            Left = 22
            Top = 120
            Width = 154
            Height = 14
            Caption = #35266#27979#22120#35282#24230#35823#24046#33539#22260'('#176')'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label17: TLabel
            Left = 22
            Top = 168
            Width = 112
            Height = 14
            Caption = #27979#37327#35823#24046#33539#22260'(mm)'
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object CSpinEdit29: TCSpinEdit
            Left = 23
            Top = 42
            Width = 153
            Height = 22
            TabOrder = 0
            Value = 5
          end
          object CSpinEdit20: TCSpinEdit
            Left = 23
            Top = 90
            Width = 153
            Height = 22
            TabOrder = 1
            Value = 10
          end
          object CSpinEdit30: TCSpinEdit
            Left = 23
            Top = 138
            Width = 153
            Height = 22
            TabOrder = 2
            Value = 10
          end
          object CSpinEdit17: TCSpinEdit
            Left = 23
            Top = 186
            Width = 157
            Height = 22
            TabOrder = 3
            Value = 1
          end
        end
        object GroupBox8: TGroupBox
          Left = 385
          Top = 0
          Width = 208
          Height = 217
          Align = alLeft
          Caption = #35745#31639#21442#25968
          TabOrder = 2
          object Label19: TLabel
            Left = 16
            Top = 72
            Width = 112
            Height = 14
            Caption = #26631#23450#36845#20195#35745#31639#27425#25968
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label23: TLabel
            Left = 16
            Top = 120
            Width = 112
            Height = 14
            Caption = #35823#24046#20998#26512#26679#26412#25968#37327
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object Label22: TLabel
            Left = 16
            Top = 24
            Width = 84
            Height = 14
            Caption = #38543#26426#26679#26412#25968#37327
            Font.Charset = ANSI_CHARSET
            Font.Color = clWindowText
            Font.Height = -14
            Font.Name = #23435#20307
            Font.Style = []
            ParentFont = False
          end
          object CSpinEdit18: TCSpinEdit
            Left = 19
            Top = 90
            Width = 157
            Height = 22
            TabOrder = 0
            Value = 5000
          end
          object CSpinEdit19: TCSpinEdit
            Left = 19
            Top = 138
            Width = 157
            Height = 22
            TabOrder = 1
            Value = 5000
          end
          object CSpinEdit22: TCSpinEdit
            Left = 19
            Top = 42
            Width = 157
            Height = 22
            TabOrder = 2
            Value = 500
          end
        end
        object GroupBox9: TGroupBox
          Left = 593
          Top = 0
          Width = 185
          Height = 217
          Align = alLeft
          Caption = #35745#31639#27979#35797
          TabOrder = 3
          object Button8: TButton
            Left = 24
            Top = 40
            Width = 129
            Height = 25
            Caption = #20135#29983#27979#35797#35823#24046
            TabOrder = 0
            OnClick = Button8Click
          end
          object Button6: TButton
            Left = 24
            Top = 72
            Width = 129
            Height = 25
            Caption = #22686#21152#26679#26412
            TabOrder = 1
            OnClick = Button6Click
          end
          object Button9: TButton
            Left = 24
            Top = 104
            Width = 129
            Height = 25
            Caption = #26631#23450#35745#31639
            TabOrder = 2
            OnClick = Button9Click
          end
          object Button10: TButton
            Left = 24
            Top = 136
            Width = 129
            Height = 25
            Caption = #20998#26512#35823#24046#24433#21709
            TabOrder = 3
            OnClick = Button10Click
          end
          object Button11: TButton
            Left = 24
            Top = 176
            Width = 129
            Height = 25
            Caption = 'Button11'
            TabOrder = 4
            Visible = False
            OnClick = Button11Click
          end
        end
        object GroupBox10: TGroupBox
          Left = 778
          Top = 0
          Width = 167
          Height = 217
          Align = alLeft
          Caption = #25968#25454#22788#29702
          TabOrder = 4
          object Button12: TButton
            Left = 16
            Top = 40
            Width = 129
            Height = 25
            Caption = #20445#23384#35823#24046#20998#24067#22270
            TabOrder = 0
            OnClick = Button12Click
          end
        end
      end
      object PageControl2: TPageControl
        Left = 0
        Top = 217
        Width = 1270
        Height = 698
        ActivePage = TabSheet5
        Align = alClient
        TabIndex = 1
        TabOrder = 1
        object TabSheet3: TTabSheet
          Caption = #26631#23450#25968#25454
          object ListView1: TListView
            Left = 0
            Top = 0
            Width = 624
            Height = 670
            Align = alClient
            Columns = <>
            GridLines = True
            RowSelect = True
            TabOrder = 0
            ViewStyle = vsReport
          end
          object Memo2: TMemo
            Left = 624
            Top = 0
            Width = 638
            Height = 670
            Align = alRight
            ScrollBars = ssBoth
            TabOrder = 1
          end
        end
        object TabSheet4: TTabSheet
          Caption = 'TabSheet4'
          ImageIndex = 1
          TabVisible = False
          object Chart1: TChart
            Left = 0
            Top = 0
            Width = 1262
            Height = 670
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Title.Text.Strings = (
              'TChart')
            Legend.Visible = False
            View3D = False
            Align = alClient
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
          end
        end
        object TabSheet5: TTabSheet
          Caption = #35823#24046#20998#24067
          ImageIndex = 2
          object Chart2: TChart
            Left = 0
            Top = 41
            Width = 1262
            Height = 629
            BackWall.Brush.Color = clWhite
            BackWall.Brush.Style = bsClear
            Title.Text.Strings = (
              'TChart')
            Title.Visible = False
            BottomAxis.LabelsFont.Charset = DEFAULT_CHARSET
            BottomAxis.LabelsFont.Color = clBlack
            BottomAxis.LabelsFont.Height = -13
            BottomAxis.LabelsFont.Name = 'Arial'
            BottomAxis.LabelsFont.Style = []
            BottomAxis.Title.Caption = #20301#32622#30456#23545#26368#22823#35823#24046#30334#20998#27604'(%)'
            LeftAxis.LabelsFont.Charset = DEFAULT_CHARSET
            LeftAxis.LabelsFont.Color = clBlack
            LeftAxis.LabelsFont.Height = -13
            LeftAxis.LabelsFont.Name = 'Arial'
            LeftAxis.LabelsFont.Style = []
            LeftAxis.Title.Caption = #20998#24067#30334#20998#27604'(%)'
            Legend.Visible = False
            TopAxis.LabelsFont.Charset = DEFAULT_CHARSET
            TopAxis.LabelsFont.Color = clBlack
            TopAxis.LabelsFont.Height = -13
            TopAxis.LabelsFont.Name = 'Arial'
            TopAxis.LabelsFont.Style = []
            TopAxis.Title.Caption = #23039#24577#30456#23545#26368#22823#35823#24046#30334#20998#27604'(%)'
            View3D = False
            Align = alClient
            TabOrder = 0
            object Series2: TBarSeries
              Marks.ArrowLength = 20
              Marks.Visible = False
              SeriesColor = clRed
              ShowInLegend = False
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Bar'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
            object Series3: TBarSeries
              HorizAxis = aTopAxis
              Marks.ArrowLength = 20
              Marks.Visible = False
              SeriesColor = clGreen
              XValues.DateTime = False
              XValues.Name = 'X'
              XValues.Multiplier = 1
              XValues.Order = loAscending
              YValues.DateTime = False
              YValues.Name = 'Bar'
              YValues.Multiplier = 1
              YValues.Order = loNone
            end
          end
          object Panel4: TPanel
            Left = 0
            Top = 0
            Width = 1262
            Height = 41
            Align = alTop
            BevelOuter = bvNone
            TabOrder = 1
            object Edit1: TEdit
              Left = 8
              Top = 8
              Width = 761
              Height = 21
              TabOrder = 0
              Text = 'Edit1'
            end
          end
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 943
    Width = 1680
    Height = 19
    Panels = <
      item
        Width = 150
      end
      item
        Width = 50
      end
      item
        Width = 50
      end>
    SimplePanel = False
  end
  object Timer1: TTimer
    Interval = 200
    OnTimer = Timer1Timer
    Left = 1368
    Top = 40
  end
  object SavePictureDialog1: TSavePictureDialog
    Left = 1408
    Top = 40
  end
end
