<GameFile>
  <PropertyGroup Name="ProblemSignboard" Type="Skeleton" ID="8b2a57cc-74ce-43f4-b4d7-6c3c7014e73b" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="110" Speed="1.0000">
        <Timeline ActionTag="1658780551" Property="Position">
          <PointFrame FrameIndex="0" X="0.0002" Y="579.2614">
            <EasingData Type="6" />
          </PointFrame>
          <PointFrame FrameIndex="25" X="0.0000" Y="-20.4443">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="50" X="0.0000" Y="15.3334">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="75" X="0.0000" Y="0.0000">
            <EasingData Type="3" />
          </PointFrame>
          <PointFrame FrameIndex="110" X="0.0002" Y="579.2614">
            <EasingData Type="6" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1658780551" Property="Scale">
          <ScaleFrame FrameIndex="0" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="1.0000" Y="1.0000">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="110" X="1.0000" Y="1.0000">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="1658780551" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="-0.8952" Y="-0.8952">
            <EasingData Type="6" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="25" X="-0.8952" Y="-0.8952">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="50" X="-0.8952" Y="-0.8952">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="75" X="-0.8952" Y="-0.8952">
            <EasingData Type="3" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="110" X="-0.8952" Y="-0.8952">
            <EasingData Type="6" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="show" StartIndex="0" EndIndex="75">
          <RenderColor A="255" R="248" G="248" B="255" />
        </AnimationInfo>
        <AnimationInfo Name="hide" StartIndex="75" EndIndex="110">
          <RenderColor A="255" R="0" G="255" B="127" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Skeleton" Tag="270" Length="20.0000" RotationSkewX="0.0000" RotationSkewY="0.0000" ctype="SkeletonNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="cartel" ActionTag="1658780551" ZOrder="1" Tag="272" Length="327.0000" RotationSkewX="-0.8952" RotationSkewY="-0.8952" ctype="BoneNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="cartel" ActionTag="-2028916784" Tag="271" RotationSkewX="0.8937" RotationSkewY="0.8952" IconVisible="False" LeftMargin="-274.4999" RightMargin="-274.5001" TopMargin="-341.5000" BottomMargin="-341.5000" ctype="SpriteObjectData">
                <Size X="549.0000" Y="683.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="0.0001" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="WordsProblemGame/png/cartel.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="Text" ActionTag="117850667" ZOrder="2" Tag="274" Length="228.0000" RotationSkewX="0.8937" RotationSkewY="0.8952" ctype="BoneNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="Text" ActionTag="-1639628406" Tag="273" IconVisible="False" LeftMargin="-210.1110" RightMargin="-199.8890" TopMargin="-136.5926" BottomMargin="-143.4074" FontSize="46" LabelText="Sema sees 6 bugs. &#xA;Tatu sees 2 bugs. &#xA;How many bugs &#xA;did they see?&#xA;" HorizontalAlignmentType="HT_Center" VerticalAlignmentType="VT_Center" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="410.0000" Y="280.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="-5.1110" Y="-3.4074" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <FontResource Type="Normal" Path="WordsProblemGame/Century Gothic Grassetto.ttf" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <Position X="1.6503" Y="-221.5334" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <BlendFunc Src="770" Dst="771" />
                <BoneColor A="255" R="25" G="25" B="25" />
              </AbstractNodeData>
            </Children>
            <Position X="0.0001" Y="200.1299" />
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