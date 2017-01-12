<GameFile>
  <PropertyGroup Name="board" Type="Skeleton" ID="2c126aa2-cb6b-4e03-b4f2-f7db627027a8" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="85" Speed="1.0000">
        <Timeline ActionTag="36500093" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="1321.5966">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="388.2778">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="452.1667">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="0.0000" Y="433.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="85" X="0.0000" Y="1321.5966">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="36500093" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="36500093" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-1.1458" Y="-1.1458">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="-1.1458" Y="-1.1458">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="-1.1458" Y="-1.1458">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="-1.1458" Y="-1.1458">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="85" X="-1.1458" Y="-1.1458">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="enter" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="255" G="239" B="213" />
        </AnimationInfo>
        <AnimationInfo Name="exit" StartIndex="60" EndIndex="85">
          <RenderColor A="255" R="153" G="50" B="204" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="150" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="master_board" ActionTag="36500093" ZOrder="3" Tag="9" Length="150.0000" RotationSkewX="-1.1458" RotationSkewY="-1.1458" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="board" ActionTag="-1329991608" ZOrder="1" Tag="6" Length="278.0000" RotationSkewX="1.1441" RotationSkewY="1.1466" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="board" ActionTag="746618440" Tag="5" IconVisible="False" LeftMargin="-244.5000" RightMargin="-244.5000" TopMargin="-439.5000" BottomMargin="-439.5000" ctype="SpriteObjectData">
                    <Size X="489.0000" Y="879.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="Bodyparts/png/board.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-8.6582" Y="-432.9134" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="text" ActionTag="879234484" ZOrder="2" Tag="8" Length="124.0000" RotationSkewX="1.1441" RotationSkewY="1.1466" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="text" ActionTag="-651365181" Tag="7" IconVisible="False" LeftMargin="-11.0000" RightMargin="-11.0000" TopMargin="-110.0000" BottomMargin="-110.0000" FontSize="90" LabelText=".&#xA;" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="22.0000" Y="220.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="51" G="51" B="51" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="Bodyparts/Century Gothic Grassetto.ttf" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <Position X="-9.6580" Y="-482.9034" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position Y="1321.5966" />
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