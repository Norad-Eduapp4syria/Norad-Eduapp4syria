<GameFile>
  <PropertyGroup Name="Libro_Vita" Type="Skeleton" ID="772a507e-3790-4c5e-aa1d-8672c63ab525" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="80" Speed="1.0000" ActivedAnimationName="apparizione">
        <Timeline ActionTag="-151224475" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="33" X="9.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="36" X="-4.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="39" X="4.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="43" X="-3.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="49" X="3.0000" Y="0.0000">
            <EasingData Type="7" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="3.0000" Y="396.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-151224475" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0900">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.1000" Y="1.1800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="33" X="1.0000" Y="1.0800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="36" X="1.0000" Y="1.0800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="39" X="1.0000" Y="1.0800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="43" X="1.0000" Y="1.0800">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="49" X="1.0000" Y="1.0800">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="80" X="0.7855" Y="1.3611">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-151224475" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="33" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="36" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="39" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="43" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="49" X="0.0000" Y="0.0000">
            <EasingData Type="7" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="80" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="apparizione" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="255" G="239" B="213" />
        </AnimationInfo>
        <AnimationInfo Name="Perdita_vita" StartIndex="30" EndIndex="80">
          <RenderColor A="255" R="255" G="105" B="180" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="369" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_libro" ActionTag="-151224475" ZOrder="1" Tag="371" Length="97.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Libro" ActionTag="-1552039184" Tag="370" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
                <Size X="119.0000" Y="138.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="OralPassage/PNG/Libro.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position />
            <Scale ScaleX="0.0100" ScaleY="0.0900" />
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