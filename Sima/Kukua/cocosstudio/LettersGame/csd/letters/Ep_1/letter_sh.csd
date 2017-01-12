<GameFile>
  <PropertyGroup Name="letter_sh" Type="Skeleton" ID="e187ea93-c489-4a60-8620-b7491ecadbd7" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="60" Speed="1.0000" ActivedAnimationName="letter_pop">
        <Timeline ActionTag="477345414" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="477345414" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.0100" Y="0.0100">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.2000" Y="1.2000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.9000" Y="0.9000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="477345414" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="40" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="60" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="letter_pop" StartIndex="0" EndIndex="60">
          <RenderColor A="255" R="85" G="107" B="47" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="2060" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="letter" ActionTag="477345414" ZOrder="-20" Tag="2062" Length="225.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="letter" CanEdit="False" ActionTag="-1105402595" Tag="2061" RotationSkewX="-0.0293" RotationSkewY="-0.0293" IconVisible="False" LeftMargin="-252.0000" RightMargin="-252.0000" TopMargin="-279.5000" BottomMargin="-279.5000" ctype="SpriteObjectData">
                <Size X="504.0000" Y="559.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="LettersGame/png/letters/Ep_1/sh.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_1" ActionTag="201237428" ZOrder="2" Tag="2332" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_1" CanEdit="False" ActionTag="-330886755" Tag="2331" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_1" ActionTag="-198432053" VisibleForFrame="False" Tag="17905" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="216.9999" Y="55.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_2" ActionTag="-546297326" ZOrder="2" Tag="2337" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_2" CanEdit="False" ActionTag="-1657488968" Tag="2338" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_2" ActionTag="242962869" VisibleForFrame="False" Tag="17906" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-214.0001" Y="-39.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_1" ActionTag="898086522" ZOrder="4" Tag="2347" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-912929844" Tag="2348" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1496071181" VisibleForFrame="False" Tag="17907" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="227.9134" Y="16.2611" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_2" ActionTag="-1517987815" ZOrder="4" Tag="18008" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1618383107" Tag="18009" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-300903849" VisibleForFrame="False" Tag="18010" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="228.4020" Y="-21.3373" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_3" ActionTag="-1618035777" ZOrder="4" Tag="18011" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="430945881" Tag="18012" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="1721047751" VisibleForFrame="False" Tag="18013" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="215.5575" Y="-60.7984" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_4" ActionTag="-907551285" ZOrder="4" Tag="18014" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="2145217385" Tag="18015" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-55420072" VisibleForFrame="False" Tag="18016" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="190.0637" Y="-92.1717" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_5" ActionTag="-528579084" ZOrder="4" Tag="18017" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-489587944" Tag="18018" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1500267077" VisibleForFrame="False" Tag="18019" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="148.3914" Y="-91.3389" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_6" ActionTag="-556380363" ZOrder="4" Tag="18020" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1294432972" Tag="18021" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-115724697" VisibleForFrame="False" Tag="18022" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="135.0613" Y="-56.3386" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_7" ActionTag="177334392" ZOrder="4" Tag="18023" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1919339383" Tag="18024" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-448203644" VisibleForFrame="False" Tag="18025" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="125.0600" Y="-17.1721" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_8" ActionTag="-538766314" ZOrder="4" Tag="18026" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1032711812" Tag="18027" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-453260651" VisibleForFrame="False" Tag="18028" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="127.5585" Y="21.9945" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_9" ActionTag="525231572" ZOrder="4" Tag="18029" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1871295544" Tag="18030" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1174769348" VisibleForFrame="False" Tag="18031" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="107.2631" Y="-50.5040" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_10" ActionTag="-897650299" ZOrder="4" Tag="18032" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1272148289" Tag="18033" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1953244585" VisibleForFrame="False" Tag="18034" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="84.7601" Y="-83.8379" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_11" ActionTag="1332292626" ZOrder="4" Tag="18035" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-464302861" Tag="18036" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="118597508" VisibleForFrame="False" Tag="18037" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="50.5902" Y="-107.1712" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_12" ActionTag="424145784" ZOrder="4" Tag="18041" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-417628267" Tag="18042" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="356362949" VisibleForFrame="False" Tag="18043" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="13.9195" Y="-82.1721" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_13" ActionTag="-1023316550" ZOrder="4" Tag="18044" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1861818581" Tag="18045" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1073892123" VisibleForFrame="False" Tag="18046" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-4.4156" Y="-37.1721" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_14" ActionTag="-1480513131" ZOrder="4" Tag="18047" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1566399449" Tag="18048" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1806686415" VisibleForFrame="False" Tag="18049" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-17.7534" Y="6.1613" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_15" ActionTag="826230564" ZOrder="4" Tag="18051" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-333997599" Tag="18052" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="1170673921" VisibleForFrame="False" Tag="18053" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-4.4200" Y="-37.1733" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_16" ActionTag="482057816" ZOrder="4" Tag="18057" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1843771448" Tag="18058" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="849441360" VisibleForFrame="False" Tag="18059" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="13.9199" Y="-81.8797" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_17" ActionTag="-1095791970" ZOrder="4" Tag="18060" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1904617834" Tag="18061" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1922966834" VisibleForFrame="False" Tag="18062" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="15.6843" Y="-135.4110" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_18" ActionTag="-1332440301" ZOrder="4" Tag="18063" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="2097563109" Tag="18064" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1228089133" VisibleForFrame="False" Tag="18065" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-1.3749" Y="-176.5892" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_19" ActionTag="690258744" ZOrder="4" Tag="18066" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1878759709" Tag="18067" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="1882912518" VisibleForFrame="False" Tag="18068" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-31.3736" Y="-207.1776" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_20" ActionTag="-1806876158" ZOrder="4" Tag="18069" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1143495422" Tag="18070" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="1831880153" VisibleForFrame="False" Tag="18071" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-65.4897" Y="-231.8838" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_21" ActionTag="1722636691" ZOrder="4" Tag="18072" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-921623310" Tag="18073" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1156112874" VisibleForFrame="False" Tag="18074" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-107.2545" Y="-243.0607" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_22" ActionTag="-92768512" ZOrder="4" Tag="18075" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-845518028" Tag="18076" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="2035822162" VisibleForFrame="False" Tag="18077" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-150.7851" Y="-246.5907" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_23" ActionTag="-2026058504" ZOrder="4" Tag="18078" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="957876809" Tag="18079" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1872584506" VisibleForFrame="False" Tag="18080" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-190.1962" Y="-226.5910" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_24" ActionTag="-2072567457" ZOrder="4" Tag="18081" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1231265750" Tag="18082" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="1671594608" VisibleForFrame="False" Tag="18083" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-214.3148" Y="-191.2972" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_25" ActionTag="1385402741" ZOrder="4" Tag="18084" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1376280273" Tag="18085" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1717564530" VisibleForFrame="False" Tag="18086" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-229.0182" Y="-153.0621" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_26" ActionTag="-230271798" ZOrder="4" Tag="18087" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-1118670651" Tag="18088" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="44818888" VisibleForFrame="False" Tag="18089" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-231.9625" Y="-113.6506" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_27" ActionTag="1845810954" ZOrder="4" Tag="18090" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-669548978" Tag="18091" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-152630731" VisibleForFrame="False" Tag="18092" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="-227.8414" Y="-77.1802" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_3" ActionTag="-1101753045" ZOrder="2" Tag="18093" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_1" CanEdit="False" ActionTag="571141813" Tag="18094" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_1" ActionTag="-684710319" VisibleForFrame="False" Tag="18095" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="131.1172" Y="169.1177" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_4" ActionTag="-467672213" ZOrder="2" Tag="18096" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_2" CanEdit="False" ActionTag="-189868252" Tag="18097" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_2" ActionTag="454251943" VisibleForFrame="False" Tag="18098" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="184.2357" Y="117.4711" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_5" ActionTag="-1404203064" ZOrder="2" Tag="18099" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_1" CanEdit="False" ActionTag="-2841253" Tag="18100" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_1" ActionTag="2069720178" VisibleForFrame="False" Tag="18101" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="39.9412" Y="164.4120" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_6" ActionTag="-1459181390" ZOrder="2" Tag="18102" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_2" CanEdit="False" ActionTag="-1300328301" Tag="18103" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_2" ActionTag="-173083999" VisibleForFrame="False" Tag="18104" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="90.1184" Y="115.1183" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_7" ActionTag="-668730979" ZOrder="2" Tag="18105" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_1" CanEdit="False" ActionTag="2026384287" Tag="18106" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_1" ActionTag="1149510507" VisibleForFrame="False" Tag="18107" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="75.2354" Y="256.1776" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="1" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="marker_8" ActionTag="303751269" ZOrder="2" Tag="18108" Length="62.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="marker_2" CanEdit="False" ActionTag="1340739514" Tag="18109" IconVisible="True" LeftMargin="0.0001" RightMargin="-0.0001" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="0.0001" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="0" G="0" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="marker_2" ActionTag="-1776861565" VisibleForFrame="False" Tag="18110" IconVisible="False" LeftMargin="-20.0000" RightMargin="-22.0000" TopMargin="-22.0000" BottomMargin="-20.0000" ctype="SpriteObjectData">
                    <Size X="42.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="126.5894" Y="206.8833" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_28" ActionTag="-1994182380" ZOrder="4" Tag="18111" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="-108366768" Tag="18112" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="834654528" VisibleForFrame="False" Tag="18113" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="157.4531" Y="142.8204" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_29" ActionTag="-483036408" ZOrder="4" Tag="18114" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1118312990" Tag="18115" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-409766782" VisibleForFrame="False" Tag="18116" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="64.5125" Y="138.7031" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
              <AbstractNodeData Name="shape_30" ActionTag="150245736" ZOrder="4" Tag="18117" Length="74.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="shape_1" CanEdit="False" ActionTag="1396108023" Tag="18118" IconVisible="True" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="shape_1" ActionTag="-1190759803" VisibleForFrame="False" Tag="18119" IconVisible="False" LeftMargin="-13.5000" RightMargin="-15.5000" TopMargin="-15.5000" BottomMargin="-13.5000" ctype="SpriteObjectData">
                    <Size X="29.0000" Y="29.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="1.0000" Y="1.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FileData Type="Default" Path="Default/Sprite.png" Plist="" />
                    <BlendFunc Src="770" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <Position X="100.3955" Y="233.4099" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position />
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