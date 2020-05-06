Shader "Hidden/DarkFade" {
	Properties {
		_MainTex ("Base (RGB)", 2D) = "white" {}
		_T("t", float) = 1
	}
	
	CGINCLUDE

		#include "UnityCG.cginc"

		sampler2D _MainTex;

		half _T;
				
		uniform half4 _MainTex_TexelSize;
		
		struct v2f
		{
			float4 pos : SV_POSITION;
			half2 uv : TEXCOORD0;
		};

		v2f vert (appdata_img v)
		{
			v2f o;
			o.pos = mul (UNITY_MATRIX_MVP, v.vertex);
			o.uv = half4(v.texcoord.xy,1,1);

			return o; 
		}

		half4 frag ( v2f i ) : SV_Target
		{
			half4 color = tex2D(_MainTex, i.uv);

			return lerp(fixed4(0,0,0,1),color, _T);
		}	
					
	ENDCG
	
	SubShader {
	  ZTest Off Cull Off ZWrite Off Blend Off

	Pass {		
		ZTest Always
		Cull Off
				
		CGPROGRAM
		
		#pragma vertex vert
		#pragma fragment frag
		
		ENDCG
		}	
	}	

	FallBack Off
}
