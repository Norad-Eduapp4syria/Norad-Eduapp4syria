using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using UnityEngine.UI;

public class SingletonLoader : MonoBehaviour {

	#if UNITY_WEBGL && !UNITY_EDITOR
	[DllImport("__Internal")]
	public static extern bool WebGL_isSiteAllow();
	#endif

	void Awake ()
	{
		#if UNITY_WEBGL && !UNITY_EDITOR
		if(!WebGL_isSiteAllow()) {
		UnityEngine.SceneManagement.SceneManager.LoadScene("SiteError");
		return;
		}
		#endif

//		PlayerPrefs.DeleteAll ();

		Application.runInBackground = false;
		Input.multiTouchEnabled = false;


		if (LogConntroller.Instance == null) {
			gameObject.AddComponent<LogConntroller>();
		}
		if (SaveStatConnector.Instance == null) {
			gameObject.AddComponent<SaveStatConnector>();
		}
		if (Timer.Instance == null) {
			gameObject.AddComponent<Timer>();
		}
		if (Analitics.Instance == null) {
			gameObject.AddComponent<Analitics>();
		}
		if (AudioController.Instance == null) {
			gameObject.AddComponent<AudioController>();
		}
		if (UsersController.Instance == null) {
			gameObject.AddComponent<UsersController>();
		}
		if (DressingController.Instance == null) {
			gameObject.AddComponent<DressingController>();
		}
		if (XMLController.Instance == null) {
			gameObject.AddComponent<XMLController>();
		}
		if (TutorialController.Instance == null) {
			gameObject.AddComponent<TutorialController>();
		}

		if (SceneController.Instance == null) {
			loadSceneController ();
		}

		if (SceneController.Instance == null) {
			loadSceneController ();
		}

		Destroy (this);
	}

	public static void CheckSingleton()
	{

		if (
			LogConntroller.Instance != null
			&&
			SaveStatConnector.Instance != null
			&&
			GameAssets.Instance != null 
			&&
			Timer.Instance != null
			&&
			Analitics.Instance != null
			&&
			AudioController.Instance != null
			&&
			UsersController.Instance != null
			&&
			DressingController.Instance != null
			&&
			XMLController.Instance != null
			&&
			TutorialController.Instance != null
			&& 
			SceneController.Instance != null
		) {
			LogConntroller.Instance.init ();
			SaveStatConnector.Instance.init ();
			GameAssets.Instance.init();
			Timer.Instance.init();
			Analitics.Instance.init();
			AudioController.Instance.init();
			UsersController.Instance.init();
			DressingController.Instance.init();
			XMLController.Instance.init();
			TutorialController.Instance.init();
			SceneController.Instance.init();

			SaveStatConnector.Instance.gameObject.AddComponent<StateConverter_2> ();
//			StateConverter_2 sc2 = SaveStatConnector.Instance.gameObject.AddComponent<StateConverter_2> ();
//			sc2.onDone = onReadyToInit;
		}
	}

	static void onReadyToInit() {
	}


	void loadSceneController() {
		if (SceneController.Instance == null) {
			//GameObject goLoader = Instantiate (Resources.Load ("Gameplay/SceneController") as GameObject);
			Instantiate (Resources.Load ("Gameplay/SceneController") as GameObject);
		}
	}


}
