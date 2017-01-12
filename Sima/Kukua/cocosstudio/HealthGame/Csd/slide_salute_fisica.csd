<GameFile>
  <PropertyGroup Name="slide_salute_fisica" Type="Skeleton" ID="1f20ebee-57b0-4385-9463-e315ce364a98" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000" ActivedAnimationName="stop">
        <Timeline ActionTag="-371175396" Property="Position">
          <PointFrame FrameIndex="0" X="1634.0724" Y="0.0001">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0001" Y="0.0001">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="-1810.5798" Y="0.0001">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-371175396" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-371175396" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="enter" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="0" G="0" B="205" />
        </AnimationInfo>
        <AnimationInfo Name="exit" StartIndex="30" EndIndex="60">
          <RenderColor A="255" R="127" G="255" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="stop" StartIndex="30" EndIndex="30">
          <RenderColor A="255" R="240" G="255" B="240" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="166" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Master_slide" ActionTag="-371175396" ZOrder="3" Tag="177" Length="973.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Slide_1" ActionTag="-1935821040" ZOrder="1" Tag="168" Length="800.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Slide" ActionTag="-659678994" Tag="167" IconVisible="False" LeftMargin="-640.0000" RightMargin="-640.0000" TopMargin="-500.0000" BottomMargin="-500.0000" ctype="SpriteObjectData">
                    <Size X="1280.0000" Y="1000.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="HealthGame/Png/Slide_1.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position Y="-0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="backGuardian_btn" ActionTag="427499384" ZOrder="2" VisibleForFrame="False" Tag="170" Length="100.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="backGuardian_btn" ActionTag="-889132820" Tag="169" IconVisible="False" LeftMargin="-60.0000" RightMargin="-60.0000" TopMargin="-57.5000" BottomMargin="-57.5000" ctype="SpriteObjectData">
                    <Size X="120.0000" Y="115.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="HealthGame/Png/backGuardian_btn.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node_1" ActionTag="1418307651" Tag="171" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <Position X="-559.4495" Y="273.4185" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position X="1634.0724" Y="0.0001" />
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