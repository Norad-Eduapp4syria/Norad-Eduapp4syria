<GameFile>
  <PropertyGroup Name="oscuramento" Type="Skeleton" ID="7dee2f6f-6a8b-4c43-b25d-4c2935f8dd90" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="100" Speed="1.0000" ActivedAnimationName="Shadow_Up">
        <Timeline ActionTag="-383585236" Property="Position">
          <PointFrame FrameIndex="0" X="-0.0011" Y="-921.3955">
            <EasingData Type="2" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="1" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="-0.0011" Y="-921.3955">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="75" X="-0.0011" Y="443.1432">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="100" X="-0.0011" Y="-921.3955">
            <EasingData Type="2" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-383585236" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.0000" Y="1.0000">
            <EasingData Type="1" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="1.0000" Y="1.0000">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-383585236" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="0.0000" Y="0.0000">
            <EasingData Type="1" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="100" X="0.0000" Y="0.0000">
            <EasingData Type="2" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="Shadow_Up" StartIndex="0" EndIndex="25">
          <RenderColor A="255" R="255" G="69" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="Shadow_down" StartIndex="25" EndIndex="50">
          <RenderColor A="255" R="0" G="0" B="0" />
        </AnimationInfo>
        <AnimationInfo Name="Shadow_full" StartIndex="50" EndIndex="75">
          <RenderColor A="255" R="65" G="105" B="225" />
        </AnimationInfo>
        <AnimationInfo Name="shadow_full_down" StartIndex="75" EndIndex="100">
          <RenderColor A="255" R="255" G="235" B="205" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="1242" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_ombra" ActionTag="-383585236" ZOrder="1" Tag="1244" Length="310.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="ombra" CanEdit="False" Visible="False" ActionTag="853081834" Tag="1243" IconVisible="False" LeftMargin="-640.0001" RightMargin="-639.9999" TopMargin="-478.4999" BottomMargin="-478.5001" ctype="SpriteObjectData">
                <Size X="1280.0000" Y="957.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-0.0001" Y="-0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="WordDictation/PNG/Interfaccia/ombra.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="ombra_lunga_1" ActionTag="1347130937" Tag="1037" IconVisible="False" LeftMargin="-640.0002" RightMargin="-639.9998" TopMargin="-444.9825" BottomMargin="-919.0175" ctype="SpriteObjectData">
                <Size X="1280.0000" Y="1364.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="-0.0002" Y="-237.0175" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="WordDictation/PNG/ombra_lunga.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <Position X="-0.0011" Y="-921.3955" />
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