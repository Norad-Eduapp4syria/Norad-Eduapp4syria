Shader "Masked/Mask" {
 
         // by moffatjason.
     Properties 
     {
         _MainTex ("Base (RGB) Alpha (A)", 2D) = "white" {}
         _Cutoff ("Base Alpha cutoff", Range (0,.9)) = .5
     }
     SubShader {
         // Render the mask after regular geometry, but before masked geometry and
         // transparent things. 
         //Tags {"Queue" = "Geometry+10"}
         //Tags {"Queue" = "Transparent"}
         // Don't draw in the RGBA channels; just the depth buffer
         ColorMask 0
         ZWrite On
         Pass 
         {
             AlphaTest GEqual [_Cutoff]       
             SetTexture [_MainTex]
         }
     }
     FallBack "Transparent/Diffuse"
}
