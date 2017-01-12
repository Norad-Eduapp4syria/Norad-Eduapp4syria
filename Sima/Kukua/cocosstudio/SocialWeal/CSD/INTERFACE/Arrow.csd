<GameFile>
  <PropertyGroup Name="Arrow" Type="Skeleton" ID="96cca85e-2f6f-4a94-9f67-5d63cac1a4d9" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="65" Speed="1.0000" ActivedAnimationName="popin">
        <Timeline ActionTag="1577586862" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="53.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1577586862" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.7000" Y="0.7000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.7000" Y="0.7000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="65" X="0.0100" Y="0.0100">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1577586862" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="popin" StartIndex="0" EndIndex="15">
          <RenderColor A="255" R="0" G="100" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="standing" StartIndex="15" EndIndex="50">
          <RenderColor A="255" R="255" G="228" B="181" />
        </AnimationInfo>
        <AnimationInfo Name="popout" StartIndex="50" EndIndex="65">
          <RenderColor A="255" R="255" G="99" B="71" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="357" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="arrow" ActionTag="1577586862" ZOrder="1" Tag="359" Length="120.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="next_1" CanEdit="False" ActionTag="-519336615" Tag="358" IconVisible="False" LeftMargin="-151.0000" RightMargin="-151.0000" TopMargin="-126.5000" BottomMargin="-126.5000" ctype="SpriteObjectData">
                <Size X="302.0000" Y="253.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="SocialWeal/PNG/next.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position X="18.3110" />
            <Scale ScaleX="0.7000" ScaleY="0.7000" />
            <CColor A="255" R="255" G="255" B="255" />
            <BlendFunc Src="1" Dst="771" />
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