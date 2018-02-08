using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;



public class Analitics : MonoBehaviour
{
	public static Analitics Instance = null;
	public static Queue<string> screensQueue = new Queue<string> ();

	IAnalitics connector;

	void Awake()
	{
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}

	void OnDisable() {
		connector.StopSession ();
	}


	public void init() {
		#if UNITY_WEBGL && !UNITY_EDITOR
		connector = gameObject.AddComponent<WebGLAnalitics> ();
		#else
		connector = gameObject.AddComponent<DefaultAnalitics> ();
		#endif

		connector.init ();
		connector.StartSession ();
	}

	public static void TreckScreen (string screenName)
	{
		if (Analitics.Instance == null) {
			screensQueue.Enqueue (screenName);
		} else {
			Analitics.Instance.treckScreen (screenName);
		}
	}

	void treckScreen (string screenName)
	{
		connector.TreckScreen (screenName);
	}

	public void treckEvent (AnaliticsCategory category, AnaliticsAction action, string label, long value = 0)
	{
		treckEvent (category, action.ToString (), label, value);
	}

	public void treckEvent (AnaliticsCategory category, string action, string label, long value = 0)
	{
		connector.TreckEvent (category.ToString (), action, label, value);
	}



}
