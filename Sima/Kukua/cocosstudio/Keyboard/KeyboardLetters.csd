<GameFile>
  <PropertyGroup Name="KeyboardLetters" Type="Node" ID="d096ee9e-fd4a-4c10-8e6c-a91e8863ed86" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="40" Speed="1.0000" ActivedAnimationName="intro">
        <Timeline ActionTag="-785769778" Property="ActionValue">
          <InnerActionFrame FrameIndex="0" Tween="False" InnerActionType="SingleFrame" CurrentAniamtionName="-- ALL --" SingleFrameIndex="0" />
          <InnerActionFrame FrameIndex="20" Tween="False" InnerActionType="SingleFrame" CurrentAniamtionName="-- ALL --" SingleFrameIndex="0" />
          <InnerActionFrame FrameIndex="40" Tween="False" InnerActionType="SingleFrame" CurrentAniamtionName="-- ALL --" SingleFrameIndex="0" />
        </Timeline>
        <Timeline ActionTag="-785769778" Property="Position">
          <PointFrame FrameIndex="0" X="640.0000" Y="261.0250">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="639.9998" Y="1003.0001">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="640.0000" Y="261.0250">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-785769778" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-785769778" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1942639051" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="-1.1682">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="373.0313">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1942639051" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1942639051" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="intro" StartIndex="0" EndIndex="20">
          <RenderColor A="255" R="72" G="61" B="139" />
        </AnimationInfo>
        <AnimationInfo Name="exit" StartIndex="20" EndIndex="40">
          <RenderColor A="255" R="255" G="160" B="122" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" Tag="122" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="ombra" ActionTag="-785769778" Tag="746" IconVisible="True" LeftMargin="640.0000" RightMargin="-640.0000" TopMargin="-261.0250" BottomMargin="261.0250" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="0.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="640.0000" Y="261.0250" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="WordDictation/CSD/oscuramento.csd" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Keyboard" ActionTag="1942639051" Tag="132" IconVisible="True" TopMargin="1.1682" BottomMargin="-1.1682" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Button_enter" ActionTag="-201034298" Tag="367" IconVisible="True" LeftMargin="-217.3972" RightMargin="217.3972" TopMargin="1438.7937" BottomMargin="-1438.7937" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-217.3972" Y="-1438.7937" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button_enter.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_space" ActionTag="104007689" Tag="588" IconVisible="True" LeftMargin="-455.3406" RightMargin="455.3406" TopMargin="1349.6158" BottomMargin="-1349.6158" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-455.3406" Y="-1349.6158" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button_space.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_canc" ActionTag="-1242512314" Tag="821" IconVisible="True" LeftMargin="-426.4716" RightMargin="426.4716" TopMargin="1239.4761" BottomMargin="-1239.4761" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-426.4716" Y="-1239.4761" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button_canc.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_DAAD" ActionTag="135666947" Tag="133" IconVisible="True" LeftMargin="77.2595" RightMargin="-77.2595" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="77.2595" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_SAD" ActionTag="1972136232" Tag="137" RotationSkewX="0.2317" RotationSkewY="0.2326" IconVisible="True" LeftMargin="157.2602" RightMargin="-157.2602" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="157.2602" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_SH" ActionTag="1421537667" Tag="141" IconVisible="True" LeftMargin="237.2606" RightMargin="-237.2606" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="237.2606" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_S" ActionTag="-1159957736" Tag="283" IconVisible="True" LeftMargin="317.2604" RightMargin="-317.2604" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="317.2604" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Z" ActionTag="-1674493762" Tag="287" IconVisible="True" LeftMargin="397.2599" RightMargin="-397.2599" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="397.2599" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_R" ActionTag="527817643" Tag="291" IconVisible="True" LeftMargin="477.2596" RightMargin="-477.2596" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="477.2596" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_DH" ActionTag="1795703" Tag="55" IconVisible="True" LeftMargin="557.2596" RightMargin="-557.2596" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="557.2596" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_D" ActionTag="992868162" Tag="60" IconVisible="True" LeftMargin="637.2597" RightMargin="-637.2597" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="637.2597" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_JA" ActionTag="-826177686" Tag="65" IconVisible="True" LeftMargin="717.2597" RightMargin="-717.2597" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="717.2597" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_HA" ActionTag="-678388094" Tag="70" IconVisible="True" LeftMargin="797.2593" RightMargin="-797.2593" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="797.2593" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_G" ActionTag="-1486727243" Tag="717" IconVisible="True" LeftMargin="877.2593" RightMargin="-877.2593" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="877.2593" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_TH" ActionTag="-9136559" Tag="722" IconVisible="True" LeftMargin="957.2600" RightMargin="-957.2600" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="957.2600" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_T" ActionTag="-1358980426" Tag="727" IconVisible="True" LeftMargin="1037.2595" RightMargin="-1037.2595" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1037.2595" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_B" ActionTag="1427942083" Tag="732" IconVisible="True" LeftMargin="1117.2593" RightMargin="-1117.2593" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1117.2593" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_A" ActionTag="506222346" Tag="737" IconVisible="True" LeftMargin="1197.2598" RightMargin="-1197.2598" TopMargin="65.0000" BottomMargin="-65.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1197.2598" Y="-65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_hamza" ActionTag="-1476199758" Tag="75" IconVisible="True" LeftMargin="124.3707" RightMargin="-124.3707" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="124.3707" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Y" ActionTag="2075841848" Tag="80" IconVisible="True" LeftMargin="204.3711" RightMargin="-204.3711" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="204.3711" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_W" ActionTag="864894663" Tag="85" IconVisible="True" LeftMargin="284.3709" RightMargin="-284.3709" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="284.3709" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_H" ActionTag="1327190057" Tag="90" IconVisible="True" LeftMargin="364.3713" RightMargin="-364.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="364.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_N" ActionTag="1115117983" Tag="95" IconVisible="True" LeftMargin="444.3717" RightMargin="-444.3717" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="444.3717" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_M" ActionTag="-1223285936" Tag="100" IconVisible="True" LeftMargin="524.3713" RightMargin="-524.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="524.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_L" ActionTag="-1189210997" Tag="105" IconVisible="True" LeftMargin="604.3713" RightMargin="-604.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="604.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_K" ActionTag="-1686768173" Tag="110" IconVisible="True" LeftMargin="684.3721" RightMargin="-684.3721" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="684.3721" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Q" ActionTag="34725191" Tag="115" IconVisible="True" LeftMargin="764.3711" RightMargin="-764.3711" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="764.3711" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_F" ActionTag="181842385" Tag="1188" IconVisible="True" LeftMargin="844.3713" RightMargin="-844.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="844.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_GH" ActionTag="-120340486" Tag="1193" IconVisible="True" LeftMargin="924.3712" RightMargin="-924.3712" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="924.3712" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_AA" ActionTag="-1758977766" Tag="1198" IconVisible="True" LeftMargin="1004.3712" RightMargin="-1004.3712" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1004.3712" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_ZAA" ActionTag="1696878839" Tag="1203" IconVisible="True" LeftMargin="1084.3713" RightMargin="-1084.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1084.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_TAA" ActionTag="221790888" Tag="1208" IconVisible="True" LeftMargin="1164.3713" RightMargin="-1164.3713" TopMargin="160.0000" BottomMargin="-160.0000" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="1164.3713" Y="-160.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD1" ActionTag="987380044" Tag="120" IconVisible="True" LeftMargin="265.6699" RightMargin="-265.6699" TopMargin="268.9461" BottomMargin="-268.9461" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="265.6699" Y="-268.9461" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD2" ActionTag="1818070366" Tag="125" IconVisible="True" LeftMargin="372.1994" RightMargin="-372.1994" TopMargin="268.9814" BottomMargin="-268.9814" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="372.1994" Y="-268.9814" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD3" ActionTag="379242471" Tag="130" IconVisible="True" LeftMargin="476.9590" RightMargin="-476.9590" TopMargin="269.2516" BottomMargin="-269.2516" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="476.9590" Y="-269.2516" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD4" ActionTag="2101522102" Tag="135" IconVisible="True" LeftMargin="583.3705" RightMargin="-583.3705" TopMargin="269.5220" BottomMargin="-269.5220" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="583.3705" Y="-269.5220" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD5" ActionTag="-439380965" Tag="140" IconVisible="True" LeftMargin="688.7831" RightMargin="-688.7831" TopMargin="269.7908" BottomMargin="-269.7908" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="688.7831" Y="-269.7908" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD6" ActionTag="-601693751" Tag="145" IconVisible="True" LeftMargin="794.4270" RightMargin="-794.4270" TopMargin="269.1753" BottomMargin="-269.1753" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="794.4270" Y="-269.1753" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_FORKEYBOARD7" ActionTag="1289236397" Tag="150" IconVisible="True" LeftMargin="900.8390" RightMargin="-900.8390" TopMargin="269.5595" BottomMargin="-269.5595" StretchWidthEnable="False" StretchHeightEnable="False" InnerActionSpeed="1.0000" CustomSizeEnabled="False" ctype="ProjectNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="900.8390" Y="-269.5595" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Keyboard/csd/Button.csd" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position Y="-1.1682" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>