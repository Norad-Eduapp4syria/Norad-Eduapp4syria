<GameFile>
  <PropertyGroup Name="letter_box" Type="Skeleton" ID="fd2fb737-d83b-45b3-97bb-0551083c9963" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="75" Speed="1.0000" ActivedAnimationName="press_letter">
        <Timeline ActionTag="658166739" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="516.4926">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="-38.3333">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="35" X="0.0000" Y="10.0878">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="55" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="65" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="75" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="658166739" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="0.8000" Y="0.8000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="1.1000" Y="1.1000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="658166739" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="0.3951" Y="0.3951">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="enter" StartIndex="0" EndIndex="50">
          <RenderColor A="255" R="0" G="255" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="press_letter" StartIndex="50" EndIndex="75">
          <RenderColor A="255" R="147" G="112" B="219" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="99" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="letter_master" ActionTag="658166739" ZOrder="2" Tag="102" Length="472.0000" RotationSkewX="0.3951" RotationSkewY="0.3951" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="letter_box" ActionTag="-1118757101" ZOrder="1" Tag="101" Length="292.0000" RotationSkewX="0.0008" RotationSkewY="-0.0002" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="letter_box" ActionTag="1891146813" Tag="100" RotationSkewX="-0.3951" RotationSkewY="-0.3951" IconVisible="False" LeftMargin="-88.9999" RightMargin="-89.0001" TopMargin="-129.5001" BottomMargin="-129.4999" ctype="SpriteObjectData">
                    <Size X="178.0000" Y="259.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="0.0001" Y="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="WordReading/Png/letter_box.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Text" ActionTag="-1446282807" Tag="101" RotationSkewY="0.0015" IconVisible="False" LeftMargin="-34.5767" RightMargin="-27.4233" TopMargin="-87.0318" BottomMargin="-35.9682" FontSize="100" LabelText="" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-3.5767" Y="25.5318" />
                    <Scale ScaleX="1.8000" ScaleY="1.8000" />
                    <CColor A="255" R="249" G="142" B="28" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="WordReading/Century Gothic Grassetto.ttf" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="hit" ActionTag="1919423999" Alpha="0" Tag="61" RotationSkewX="-0.3946" RotationSkewY="-0.3946" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                    <Size X="46.0000" Y="46.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="4.0000" ScaleY="5.5000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position Y="516.4926" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <BlendFunc Src="770" Dst="771" />
            <BoneColor A="255" R="25" G="25" B="25" />
          </AbstractNodeData>
        </Children>
        <Position />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <CColor A="255" R="255" G="255" B="255" />
        <BlendFunc Src="770" Dst="771" />
        <BoneColor A="255" R="25" G="25" B="25" />
      </ObjectData>
    </Content>
  </Content>
</GameFile>