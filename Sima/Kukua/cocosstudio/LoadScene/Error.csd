<GameFile>
  <PropertyGroup Name="Error" Type="Skeleton" ID="ec6590a7-e597-49e7-82cf-96e303403077" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="45" Speed="1.0000" ActivedAnimationName="pop_alert">
        <Timeline ActionTag="-1488372777" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="-0.0001">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="-0.0001">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="-0.0001">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="45" X="0.0000" Y="-0.0001">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1488372777" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.1000" Y="1.1000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="45" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1488372777" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="45" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="pop_alert" StartIndex="0" EndIndex="45">
          <RenderColor A="255" R="0" G="139" B="139" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="668" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="solid_white" ActionTag="-1480240241" Tag="669" IconVisible="False" LeftMargin="-404.0000" RightMargin="-404.0000" TopMargin="-252.0000" BottomMargin="-252.0000" ctype="SpriteObjectData">
            <Size X="808.0000" Y="504.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="LoadScene/PNG/solid_white.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="alert" ActionTag="-1488372777" ZOrder="1" Tag="671" Length="259.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="alert" ActionTag="-1102982863" Tag="670" IconVisible="False" LeftMargin="-221.5000" RightMargin="-221.5000" TopMargin="-175.0001" BottomMargin="-174.9999" ctype="SpriteObjectData">
                <Size X="443.0000" Y="350.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="LoadScene/PNG/alert.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position Y="-0.0001" />
            <Scale ScaleX="0.0100" ScaleY="0.0100" />
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