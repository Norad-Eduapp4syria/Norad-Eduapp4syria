<GameFile>
  <PropertyGroup Name="listen_button" Type="Skeleton" ID="4c709558-ca2d-4845-8ba8-244a75c670a4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="100" Speed="1.0000" ActivedAnimationName="button_pulse">
        <Timeline ActionTag="-1015890754" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="43" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </PointFrame>
          <PointFrame FrameIndex="75" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </PointFrame>
          <PointFrame FrameIndex="100" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1015890754" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.0500" Y="1.0500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="43" X="0.8500" Y="0.8500">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="0.9000" Y="0.9000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1015890754" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="43" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="button_popin" StartIndex="0" EndIndex="40">
          <RenderColor A="255" R="255" G="255" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="button_press" StartIndex="40" EndIndex="50">
          <RenderColor A="255" R="250" G="235" B="215" />
        </AnimationInfo>
        <AnimationInfo Name="button_pulse" StartIndex="50" EndIndex="100">
          <RenderColor A="255" R="219" G="112" B="147" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="107" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_listen" ActionTag="-1015890754" ZOrder="1" Tag="109" Length="119.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="listen_button" CanEdit="False" ActionTag="-258583881" Tag="108" IconVisible="False" LeftMargin="-63.5001" RightMargin="-63.4999" TopMargin="-66.5000" BottomMargin="-66.5000" ctype="SpriteObjectData">
                <Size X="127.0000" Y="133.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ListComprehens/PNG/listen_button.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position />
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