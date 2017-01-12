<GameFile>
  <PropertyGroup Name="HelpHand_old" Type="Skeleton" ID="1a8ea14f-240f-46ed-b98f-3a53aef5b2ae" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="90" Speed="1.0000" ActivedAnimationName="hand_help_2">
        <Timeline ActionTag="209010551" Property="Position">
          <PointFrame FrameIndex="30" X="-292.0000" Y="-0.0002">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="0.0000" Y="-0.0002">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="90" X="-292.0000" Y="-0.0002">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="209010551" Property="Scale">
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="90" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="209010551" Property="RotationSkew">
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="90" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="hand_help_2" StartIndex="30" EndIndex="90">
          <RenderColor A="255" R="0" G="100" B="0" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="456" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Manina" ActionTag="209010551" ZOrder="1" Tag="458" Length="129.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Manina" ActionTag="445163633" Tag="457" IconVisible="False" LeftMargin="-78.0000" RightMargin="-78.0000" TopMargin="-92.5001" BottomMargin="-92.4999" ctype="SpriteObjectData">
                <Size X="156.0000" Y="185.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="FallingLetters/png/main_prop/Manina.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position X="-73.0000" Y="-0.0002" />
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