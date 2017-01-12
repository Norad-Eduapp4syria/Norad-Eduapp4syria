<GameFile>
  <PropertyGroup Name="Ball" Type="Skeleton" ID="96d3c6d3-0ac9-45b1-a022-b38ef105fa30" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="85" Speed="1.0000" ActivedAnimationName="enter">
        <Timeline ActionTag="136163297" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="7" />
          </PointFrame>
          <PointFrame FrameIndex="70" X="-0.0018" Y="-755.1339">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="71" X="0.0000" Y="0.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="77" X="0.0000" Y="0.0000">
            <EasingData Type="7" />
          </PointFrame>
          <PointFrame FrameIndex="85" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="136163297" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.1000" Y="1.1000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="70" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="71" X="1.0000" Y="1.0000">
            <EasingData Type="8" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="77" X="1.5086" Y="1.2000">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="0.0100" Y="0.0100">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="136163297" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="70" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="71" X="0.0000" Y="0.0000">
            <EasingData Type="8" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="77" X="0.0000" Y="0.0000">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="enter" StartIndex="0" EndIndex="50">
          <RenderColor A="255" R="219" G="112" B="147" />
        </AnimationInfo>
        <AnimationInfo Name="out" StartIndex="50" EndIndex="70">
          <RenderColor A="255" R="127" G="255" B="212" />
        </AnimationInfo>
        <AnimationInfo Name="tap" StartIndex="71" EndIndex="85">
          <RenderColor A="255" R="230" G="230" B="250" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="390" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Master_ball" ActionTag="136163297" ZOrder="3" Tag="410" Length="198.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="ball" ActionTag="-1695334927" ZOrder="1" Tag="392" Length="152.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="ball" ActionTag="-1947183428" Tag="391" IconVisible="False" LeftMargin="-150.0000" RightMargin="-150.0000" TopMargin="-150.5000" BottomMargin="-150.5000" ctype="SpriteObjectData">
                    <Size X="300.0000" Y="301.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="NightrunnerGame_1_4/png/ball.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="labelRef" ActionTag="-1210821580" Tag="241" IconVisible="True" TopMargin="-7.8000" BottomMargin="7.8000" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="0.0000" Y="20.1766" />
                <Scale ScaleX="2.5867" ScaleY="2.5867" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <Position />
            <Scale ScaleX="0.0100" ScaleY="0.0100" />
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