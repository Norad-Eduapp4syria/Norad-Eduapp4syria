<GameFile>
  <PropertyGroup Name="portal_lock" Type="Skeleton" ID="3ed3d0fc-d110-4a56-9e10-e73c04de62f8" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000" ActivedAnimationName="portal_lock_pop">
        <Timeline ActionTag="-664116643" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-664116643" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.1500" Y="1.1500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-664116643" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="portal_lock_pop" StartIndex="0" EndIndex="30">
          <RenderColor A="150" R="245" G="245" B="245" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="34" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="portal_lock" ActionTag="-664116643" ZOrder="1" Tag="36" Length="49.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="portal_lock" ActionTag="-720375321" Tag="35" IconVisible="False" LeftMargin="-24.5000" RightMargin="-24.5000" TopMargin="-27.0000" BottomMargin="-27.0000" ctype="SpriteObjectData">
                <Size X="49.0000" Y="54.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="MapScene/png/Portal/Portal_episodes/portal_lock.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position />
            <Scale ScaleX="0.4039" ScaleY="0.4039" />
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