<GameFile>
  <PropertyGroup Name="userBtn" Type="Skeleton" ID="36da2c09-91ed-458e-9e21-d07145983a03" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="33" Speed="1.0000" ActivedAnimationName="user_deselect">
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
          <PointFrame FrameIndex="33" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1204564507" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="3" X="0.9500" Y="0.9500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="13" X="1.2000" Y="1.2000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="23" X="1.1500" Y="1.1500">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="33" X="1.0000" Y="1.0000">
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
          <ScaleFrame FrameIndex="33" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="user_select" StartIndex="0" EndIndex="23">
          <RenderColor A="255" R="210" G="180" B="140" />
        </AnimationInfo>
        <AnimationInfo Name="user_deselect" StartIndex="23" EndIndex="33">
          <RenderColor A="255" R="139" G="0" B="139" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="158" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="user_master" ActionTag="1204564507" ZOrder="4" Tag="166" Length="300.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="user_profile" ActionTag="-301005750" ZOrder="1" Tag="160" Length="200.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="user_profile" ActionTag="-1708396223" Tag="161" IconVisible="False" LeftMargin="-111.0000" RightMargin="-111.0000" TopMargin="-110.5000" BottomMargin="-110.5000" ctype="SpriteObjectData">
                    <Size X="222.0000" Y="221.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="UserScene/png/user_profile.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="1.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="user_shape" ActionTag="-1820497754" ZOrder="-10" Tag="163" Length="200.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="user_shape" ActionTag="-1482355451" Tag="162" IconVisible="False" LeftMargin="-149.5000" RightMargin="-149.5000" TopMargin="-110.5000" BottomMargin="-110.5000" ctype="SpriteObjectData">
                    <Size X="299.0000" Y="221.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="UserScene/png/user_shape.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="1.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="play_select" ActionTag="-594289449" ZOrder="5" Tag="37" Length="132.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="playBtn" ActionTag="1817878305" VisibleForFrame="False" Tag="38" IconVisible="False" LeftMargin="-60.0000" RightMargin="-60.0000" TopMargin="-58.0000" BottomMargin="-58.0000" ctype="SpriteObjectData">
                    <Size X="121.0000" Y="116.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="UserScene/png/playBtn.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="Node" ActionTag="1343489026" Tag="36" IconVisible="True" LeftMargin="-0.0001" RightMargin="0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="-0.0001" />
                    <Scale ScaleX="0.9524" ScaleY="0.9524" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <Position X="0.0001" Y="-95.2400" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="photoBone" ActionTag="-2102383115" ZOrder="-20" Tag="315" Length="71.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="photoHere" ActionTag="1860463709" Tag="314" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="0.2400" ScaleY="0.2400" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
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
          </AbstractNodeData>
          <AbstractNodeData Name="hitArea" ActionTag="216433532" Alpha="0" Tag="122" IconVisible="False" LeftMargin="-23.0000" RightMargin="-23.0000" TopMargin="-23.0000" BottomMargin="-23.0000" ctype="SpriteObjectData">
            <Size X="46.0000" Y="46.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="4.2000" ScaleY="4.2000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
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