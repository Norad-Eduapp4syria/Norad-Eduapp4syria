<GameFile>
  <PropertyGroup Name="Time" Type="Skeleton" ID="1c6951f7-7bfd-4d41-bc51-f0c123d18a4a" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="35" Speed="1.0000" ActivedAnimationName="loop">
        <Timeline ActionTag="-1488372777" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="-0.0001">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="35" X="0.0000" Y="-0.0001">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1488372777" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1488372777" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="35" X="359.0000" Y="359.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="loop" StartIndex="0" EndIndex="35">
          <RenderColor A="150" R="0" G="139" B="139" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="668" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="solid_white" ActionTag="-1480240241" Tag="669" IconVisible="False" LeftMargin="-404.0000" RightMargin="-404.0000" TopMargin="-252.0001" BottomMargin="-251.9999" ctype="SpriteObjectData">
            <Size X="808.0000" Y="504.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position Y="0.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="LoadScene/PNG/solid_white.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="time" ActionTag="-1488372777" ZOrder="1" Tag="671" Length="259.0000" RotationSkewX="246.1714" RotationSkewY="246.1714" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="time" ActionTag="-1102982863" Tag="670" IconVisible="False" LeftMargin="-66.0000" RightMargin="-66.0000" TopMargin="-76.0000" BottomMargin="-76.0000" ctype="SpriteObjectData">
                <Size X="132.0000" Y="152.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="LoadScene/PNG/time.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position Y="-0.0001" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
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