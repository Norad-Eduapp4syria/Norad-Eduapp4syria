<GameFile>
  <PropertyGroup Name="spiral" Type="Skeleton" ID="5647e188-0258-42fe-be9e-b4e85e247c7d" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="80" Speed="1.0000" ActivedAnimationName="Spiral_ruota">
        <Timeline ActionTag="-2108534578" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="4" />
          </PointFrame>
          <PointFrame FrameIndex="80" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-2108534578" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="4" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="80" X="0.0100" Y="0.0100">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-2108534578" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-40.0000" Y="-40.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="45.0000" Y="45.0000">
            <EasingData Type="4" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="80" X="80.0000" Y="80.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Spiral_appare" StartIndex="1" EndIndex="20">
          <RenderColor A="255" R="245" G="245" B="220" />
        </AnimationInfo>
        <AnimationInfo Name="Spiral_ruota" StartIndex="20" EndIndex="59">
          <RenderColor A="255" R="250" G="250" B="210" />
        </AnimationInfo>
        <AnimationInfo Name="Spiral_sparisce" StartIndex="60" EndIndex="80">
          <RenderColor A="255" R="0" G="255" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="2839" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_spirale" ActionTag="-2108534578" ZOrder="1" Tag="2841" Length="280.0000" RotationSkewX="-40.0000" RotationSkewY="-40.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Spirale_motore3_1" CanEdit="False" ActionTag="-1562833882" Tag="2840" IconVisible="False" LeftMargin="-403.0000" RightMargin="-403.0000" TopMargin="-403.0000" BottomMargin="-403.0000" ctype="SpriteObjectData">
                <Size X="806.0000" Y="806.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="ShapesGame2/PNG/Interfaccia/Spirale_motore3.png" Plist="" />
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