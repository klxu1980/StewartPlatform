object Form1: TForm1
  Left = 460
  Top = 0
  Width = 1142
  Height = 779
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 741
    Align = alLeft
    TabOrder = 0
    object GroupBox1: TGroupBox
      Left = 8
      Top = 16
      Width = 161
      Height = 257
      Caption = 'P0'
      TabOrder = 0
      object LabeledEdit1: TLabeledEdit
        Left = 16
        Top = 48
        Width = 121
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'X'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object LabeledEdit2: TLabeledEdit
        Left = 16
        Top = 96
        Width = 121
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'Y'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object LabeledEdit3: TLabeledEdit
        Left = 16
        Top = 152
        Width = 121
        Height = 21
        EditLabel.Width = 12
        EditLabel.Height = 13
        EditLabel.Caption = 'Vx'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
      object LabeledEdit4: TLabeledEdit
        Left = 16
        Top = 208
        Width = 121
        Height = 21
        EditLabel.Width = 12
        EditLabel.Height = 13
        EditLabel.Caption = 'Vy'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 296
      Width = 161
      Height = 257
      Caption = 'P1'
      TabOrder = 1
      object LabeledEdit5: TLabeledEdit
        Left = 16
        Top = 48
        Width = 121
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'X'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 0
      end
      object LabeledEdit6: TLabeledEdit
        Left = 16
        Top = 96
        Width = 121
        Height = 21
        EditLabel.Width = 7
        EditLabel.Height = 13
        EditLabel.Caption = 'Y'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 1
      end
      object LabeledEdit7: TLabeledEdit
        Left = 16
        Top = 152
        Width = 121
        Height = 21
        EditLabel.Width = 12
        EditLabel.Height = 13
        EditLabel.Caption = 'Vx'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 2
      end
      object LabeledEdit8: TLabeledEdit
        Left = 16
        Top = 208
        Width = 121
        Height = 21
        EditLabel.Width = 12
        EditLabel.Height = 13
        EditLabel.Caption = 'Vy'
        ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 3
      end
    end
    object Button1: TButton
      Left = 24
      Top = 640
      Width = 75
      Height = 25
      Caption = 'Button1'
      TabOrder = 2
      OnClick = Button1Click
    end
    object LabeledEdit9: TLabeledEdit
      Left = 24
      Top = 592
      Width = 121
      Height = 21
      EditLabel.Width = 7
      EditLabel.Height = 13
      EditLabel.Caption = 'T'
      ImeName = #20013#25991'('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
    end
  end
  object Chart1: TChart
    Left = 185
    Top = 0
    Width = 941
    Height = 741
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'TChart')
    Legend.Visible = False
    View3D = False
    OnAfterDraw = Chart1AfterDraw
    Align = alClient
    TabOrder = 1
    object Series1: TLineSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
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
