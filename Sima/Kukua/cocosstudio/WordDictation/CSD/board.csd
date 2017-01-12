<GameFile>
  <PropertyGroup Name="board" Type="Skeleton" ID="5e5062a6-adee-4dc7-8ef6-d96571eed807" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000" ActivedAnimationName="out">
        <Timeline ActionTag="548322720" Property="Position">
          <PointFrame FrameIndex="0" X="0.0032" Y="1046.7366">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="0.0032" Y="1046.7366">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="548322720" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="548322720" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="30" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="in" StartIndex="0" EndIndex="30">
          <RenderColor A="255" R="72" G="61" B="139" />
        </AnimationInfo>
        <AnimationInfo Name="out" StartIndex="30" EndIndex="60">
          <RenderColor A="255" R="255" G="250" B="250" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="113" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="board" ActionTag="548322720" ZOrder="1" Tag="115" Length="800.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="board" ActionTag="974357071" Tag="114" IconVisible="False" LeftMargin="-579.5001" RightMargin="-579.4999" TopMargin="-368.5000" BottomMargin="-368.5000" ctype="SpriteObjectData">
                <Size X="1159.0000" Y="737.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="WordDictation/PNG/Interfaccia/board.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="letterNode" ActionTag="-385297647" Tag="110" IconVisible="True" LeftMargin="-0.0032" RightMargin="0.0032" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <AnchorPoint />
                <Position X="-0.0032" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <Position X="0.0032" Y="1046.7366" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <BlendFunc Src="1" Dst="771" />
            <BoneColor A="255" R="25" G="25" B="25" />
          </AbstractNodeData>
          <AbstractNodeData Name="bg" ActionTag="1009130079" Alpha="0" Tag="87" IconVisible="False" LeftMargin="-640.0000" RightMargin="-640.0000" TopMargin="-500.0000" BottomMargin="-500.0000" ctype="SpriteObjectData">
            <Size X="1280.0000" Y="1000.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="WordDictation/PNG/Skin1/bk_alpha.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
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