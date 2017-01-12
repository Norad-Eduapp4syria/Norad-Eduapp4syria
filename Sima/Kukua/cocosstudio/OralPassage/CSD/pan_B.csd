<GameFile>
  <PropertyGroup Name="pan_B" Type="Skeleton" ID="c5b5595d-1449-41b6-aab7-f39f4f7f87e5" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000" ActivedAnimationName="panel_press">
        <Timeline ActionTag="-31593741" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="5" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-31593741" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="1.0500" Y="1.0500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-31593741" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="5" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="panel_press" StartIndex="0" EndIndex="5">
          <RenderColor A="255" R="128" G="0" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="panel_release" StartIndex="5" EndIndex="20">
          <RenderColor A="255" R="240" G="255" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="168" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_pan_A" ActionTag="-31593741" ZOrder="1" Tag="170" Length="116.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="pan_A" ActionTag="-1239462465" Tag="169" IconVisible="False" LeftMargin="-314.5000" RightMargin="-314.5000" TopMargin="-71.5000" BottomMargin="-71.5000" ctype="SpriteObjectData">
                <Size X="629.0000" Y="143.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="OralPassage/PNG/QuestionMenu/pan_B.png" Plist="" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="text" ActionTag="587478521" Tag="739" IconVisible="False" LeftMargin="-275.0001" RightMargin="-274.9999" TopMargin="-50.0000" BottomMargin="-50.0000" IsCustomSize="True" FontSize="40" LabelText="" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                <Size X="550.0000" Y="100.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="26" G="26" B="26" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FontResource Type="Normal" Path="OralPassage/Arabic-Regular.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
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