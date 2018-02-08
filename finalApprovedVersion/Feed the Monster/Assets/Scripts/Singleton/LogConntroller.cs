using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LogConntroller : MonoBehaviour {

	public static LogConntroller Instance;

	GUIStyle style;
	int logMaxLines = 10;
	string logText = string.Empty;
	List<string> logLines;


	void Awake () {
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}

	public void init()
	{
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			logText = string.Empty;
			style = new GUIStyle();
			style.fontSize = Mathf.Min(Screen.width, Screen.height) / 30;
			logLines = new List<string>();
		}
	}



	public void Clear() {
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			logLines.Clear ();
			logText = string.Empty;
		}
	}

	public void Log(string text) {
		if (GameAssets.Instance.DEBUG_ACTIVE) {

			Debug.Log (text);

			logLines.Add (text);
			if (logLines.Count > logMaxLines) {
				logLines.RemoveAt (0);
			}

			logText = string.Empty;
			for (int i = logLines.Count - 1; i > -1 ; i--) {
				logText += i.ToString() + " - " + logLines[i] + "\n";
			}
		}
	}


	void OnGUI()
	{
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			if (logText.Length > 0) {
				GUI.Box (new Rect (0, 0, Screen.width, Screen.height), logText, style);
			}
		}
	}

}
