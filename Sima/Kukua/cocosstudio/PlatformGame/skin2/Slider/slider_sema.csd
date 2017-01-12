<GameFile>
  <PropertyGroup Name="slider_sema" Type="Skeleton" ID="876488c1-cceb-4c4d-9583-0631dabb878b" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="120" Speed="1.0000" ActivedAnimationName="slider_appare">
        <Timeline ActionTag="-395953150" Property="Position">
          <PointFrame FrameIndex="60" X="18.7637" Y="-25.6760">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="120" X="18.7637" Y="-25.6760">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-395953150" Property="Scale">
          <ScaleFrame FrameIndex="60" X="0.0132" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="120" X="1.0032" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="-395953150" Property="RotationSkew">
          <ScaleFrame FrameIndex="60" X="90.6856" Y="90.6850">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="120" X="90.6856" Y="90.6850">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="200716940" Property="Position">
          <PointFrame FrameIndex="0" X="-218.9558" Y="142.6007">
            <EasingData Type="23" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="-218.9559" Y="-23.5448">
            <EasingData Type="23" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="200716940" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="23" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="23" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="200716940" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-90.5817" Y="-90.5817">
            <EasingData Type="23" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="-90.5817" Y="-90.5817">
            <EasingData Type="23" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="slider_load" StartIndex="60" EndIndex="120">
          <RenderColor A="150" R="173" G="216" B="230" />
        </AnimationInfo>
        <AnimationInfo Name="slider_appare" StartIndex="0" EndIndex="60">
          <RenderColor A="150" R="186" G="85" B="211" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="390" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="Bone_4slider_master" ActionTag="200716940" ZOrder="4" Tag="399" Length="97.0000" RotationSkewX="-90.5817" RotationSkewY="-90.5817" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="base" ActionTag="-194962400" ZOrder="-1" Tag="397" Length="313.0000" RotationSkewX="90.5213" RotationSkewY="90.5213" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="caricamento_2" ActionTag="-2001597411" Alpha="97" Tag="398" RotationSkewX="0.0603" RotationSkewY="0.0606" IconVisible="False" LeftMargin="-0.5063" RightMargin="-314.4937" TopMargin="-19.4453" BottomMargin="-18.5547" ctype="SpriteObjectData">
                    <Size X="315.0000" Y="38.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="156.9937" Y="0.4453" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="0" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="PlatformGame/skin1/Slider/caricamento.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="17.9824" Y="-24.2527" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="load" ActionTag="-395953150" ZOrder="1" Tag="396" Length="313.0000" RotationSkewX="90.6856" RotationSkewY="90.6850" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="caricamento_2" ActionTag="-829268571" Tag="392" RotationSkewX="0.0603" RotationSkewY="0.0606" IconVisible="False" LeftMargin="-0.5063" RightMargin="-314.4937" TopMargin="-19.4453" BottomMargin="-18.5547" ctype="SpriteObjectData">
                    <Size X="315.0000" Y="38.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="156.9937" Y="0.4453" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="PlatformGame/skin1/Slider/caricamento.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="18.7637" Y="-25.6760" />
                <Scale ScaleX="0.0132" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="slider" ActionTag="636012293" ZOrder="2" Tag="394" Length="54.0000" RotationSkewX="-358.6335" RotationSkewY="1.3670" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Slider_base_Sema_3" ActionTag="-503194026" Tag="393" RotationSkewX="89.2152" RotationSkewY="89.2169" IconVisible="False" LeftMargin="-198.6815" RightMargin="-208.3185" TopMargin="-188.3657" BottomMargin="93.3657" ctype="SpriteObjectData">
                    <Size X="407.0000" Y="95.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="4.8185" Y="140.8657" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Normal" Path="PlatformGame/skin1/Slider/Slider_base_Sema.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="13.1444" Y="-359.8943" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position X="-218.9558" Y="142.6007" />
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