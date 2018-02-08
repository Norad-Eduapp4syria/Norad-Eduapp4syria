using System.Runtime.InteropServices;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WebGLAnalitics : MonoBehaviour, IAnalitics {


	#if UNITY_WEBGL
	[DllImport("__Internal")]
	public static extern void GAWebGL_TreckScreen(string screenName);

	[DllImport("__Internal")]
	public static extern string GAWebGL_TreckEvent(string category, string action, string label, long value);
	#endif

	public void init() {
	}

	public void StopSession() {
	}

	public void StartSession() {
	}

	public void TreckScreen(string screenName) {
		#if UNITY_WEBGL
		WebGLAnalitics.GAWebGL_TreckScreen (screenName);
		#endif
	}

	public void TreckEvent(string category, string action, string label, long value) {
		#if UNITY_WEBGL
		WebGLAnalitics.GAWebGL_TreckEvent (category, action, label, value);
		#endif
	}


}
