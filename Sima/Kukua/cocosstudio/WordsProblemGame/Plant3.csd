<GameFile>
  <PropertyGroup Name="Plant3" Type="Skeleton" ID="0cdafb66-4b09-4f00-bdaf-ea4beb9d4566" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="100" Speed="1.0000" ActivedAnimationName="move">
        <Timeline ActionTag="1601732288" Property="Position">
          <PointFrame FrameIndex="0" X="5.6443" Y="-66.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="5.6443" Y="-66.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="100" X="5.6443" Y="-66.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1601732288" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0506">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1601732288" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-0.5457" Y="-0.5457">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="-0.5457" Y="-0.5457">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="-0.5457" Y="-0.5457">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="move" StartIndex="0" EndIndex="100">
          <RenderColor A="150" R="0" G="250" B="154" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="253" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="plant_3" ActionTag="1601732288" ZOrder="1" Tag="255" Length="148.0000" RotationSkewX="-0.5457" RotationSkewY="-0.5457" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="plant_3" ActionTag="1988053095" Tag="254" RotationSkewX="0.5477" RotationSkewY="0.5453" IconVisible="False" LeftMargin="-118.0155" RightMargin="-107.9845" TopMargin="-161.0508" BottomMargin="-28.9492" ctype="SpriteObjectData">
                <Size X="226.0000" Y="190.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-5.0155" Y="66.0508" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="WordsProblemGame/png/plant_3.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position X="5.6443" Y="-66.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0160" />
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