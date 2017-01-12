<GameFile>
  <PropertyGroup Name="Life" Type="Skeleton" ID="77195fc3-7d71-4efd-8685-8686c0a1e4ef" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="85" Speed="1.0000" ActivedAnimationName="life_B">
        <Timeline ActionTag="1932648696" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="11" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </PointFrame>
          <PointFrame FrameIndex="55" X="-0.0007" Y="30.2712">
            <EasingData Type="6" />
          </PointFrame>
          <PointFrame FrameIndex="85" X="-0.0026" Y="-153.7325">
            <EasingData Type="6" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1932648696" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="11" X="1.1000" Y="1.1000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="0.0100" Y="0.0100">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1932648696" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="11" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="55" X="28.5326" Y="28.5326">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="105.7224" Y="105.7224">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="life_A" StartIndex="0" EndIndex="40">
          <RenderColor A="255" R="100" G="149" B="237" />
        </AnimationInfo>
        <AnimationInfo Name="life_B" StartIndex="40" EndIndex="85">
          <RenderColor A="255" R="199" G="21" B="133" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="1171" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="RootBone" ActionTag="1932648696" ZOrder="1" Tag="1173" Length="39.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Sprite" ActionTag="656626480" Tag="1172" IconVisible="False" LeftMargin="-24.5000" RightMargin="-24.5000" TopMargin="-27.0000" BottomMargin="-27.0000" ctype="SpriteObjectData">
                <Size X="49.0000" Y="54.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="FallingLetters/png/life/life_1.png" Plist="" />
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