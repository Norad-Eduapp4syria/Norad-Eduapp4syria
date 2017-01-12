<GameFile>
  <PropertyGroup Name="Emotions_1" Type="Skeleton" ID="13c55cf0-1991-4c9c-8770-f76fa1011cf2" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="30" Speed="1.0000" ActivedAnimationName="fall">
        <Timeline ActionTag="-1370650187" Property="Position">
          <PointFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="5" X="0.0000" Y="0.0000">
            <EasingData Type="4" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-1370650187" Property="Scale">
          <ScaleFrame FrameIndex="1" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="1.1000" Y="1.1000">
            <EasingData Type="4" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0100" Y="0.0100">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-1370650187" Property="RotationSkew">
          <ScaleFrame FrameIndex="1" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="0.0000" Y="0.0000">
            <EasingData Type="4" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="176.6050" Y="176.6050">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="stop" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="107" G="142" B="35" />
        </AnimationInfo>
        <AnimationInfo Name="take" StartIndex="1" EndIndex="5">
          <RenderColor A="255" R="244" G="164" B="96" />
        </AnimationInfo>
        <AnimationInfo Name="fall" StartIndex="5" EndIndex="30">
          <RenderColor A="255" R="205" G="133" B="63" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="163" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="emo_1" ActionTag="-1370650187" ZOrder="1" Tag="165" Length="180.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="emo_1" ActionTag="-1712844272" Tag="164" IconVisible="False" LeftMargin="-118.5000" RightMargin="-118.5000" TopMargin="-81.5000" BottomMargin="-81.5000" ctype="SpriteObjectData">
                <Size X="237.0000" Y="163.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="Salute_Emotiva/png/Expressions/gioia.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position />
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