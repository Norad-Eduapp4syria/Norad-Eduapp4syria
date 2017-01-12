<GameFile>
  <PropertyGroup Name="userBtn_new" Type="Skeleton" ID="fe016132-751b-48ab-8a43-cf18a89ebd85" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="38" Speed="1.0000" ActivedAnimationName="user_active">
        <Timeline ActionTag="1204564507" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="3" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="13" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="23" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="38" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1204564507" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="3" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="13" X="1.0500" Y="1.0500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="23" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="38" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1204564507" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="3" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="13" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="23" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="38" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="user_active" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="119" G="136" B="153" />
        </AnimationInfo>
        <AnimationInfo Name="user_tap" StartIndex="0" EndIndex="38">
          <RenderColor A="255" R="210" G="180" B="140" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="158" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="user_master" ActionTag="1204564507" ZOrder="4" Tag="166" Length="300.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="user_new" ActionTag="-301005750" ZOrder="1" Tag="160" Length="200.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="user_new" ActionTag="-1708396223" Tag="161" IconVisible="False" LeftMargin="-149.5000" RightMargin="-149.5000" TopMargin="-111.0000" BottomMargin="-111.0000" ctype="SpriteObjectData">
                    <Size X="299.0000" Y="222.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="UserScene/png/user_new.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="1.0000" />
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
          </AbstractNodeData>
          <AbstractNodeData Name="button" ActionTag="-1618276412" Alpha="0" Tag="405" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-18.0000" BottomMargin="-18.0000" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="46.0000" Y="36.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="4.2000" ScaleY="5.2000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
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