using UnityEngine;
using UnityEngine.UI;
using System;
using System.Collections;
using System.Collections.Generic;

public class TutorialController : MonoBehaviour {
	public static TutorialController Instance = null;


	public enum TutorialState{
		Inactive,
		InGame,
		Pointing
	}


	Transform clone;
	Tutorial currentTutorial = null;
	Image mTutorialHandImage = null;

	public Image tutorialHandImage {
		get { 
			if (mTutorialHandImage == null) {
				GameObject go = Instantiate (GameAssets.Instance.tutorialHend);
				mTutorialHandImage = go.GetComponent<Image> ();
			}
			return mTutorialHandImage;
		}
	}


	// Use this for initialization
	void Awake(){
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}
	}
/*
	void Start () {
		//PanelTutorial.SetActive (false);
	}

	void Update () {
	}
*/
	public void init()
	{

	}


	public TutorialState getState
	{
		get
		{
			if (currentTutorial == null) {
				return TutorialState.Inactive;
			} else {
				return currentTutorial.State;
			}
		}
	}


		


	public Tutorial StartTutorial(Transform holder) {
//		PanelTutorial.SetActive (true);
		tutorialHandImage.gameObject.SetActive (true);

		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}
		currentTutorial = gameObject.AddComponent<Tutorial> ();
		currentTutorial.tutorialHandImage = tutorialHandImage;
		currentTutorial.InitGame (holder);
		return currentTutorial;
	}

	public void StartTutorial(MiniGameController.GameType gameType){
//		PanelTutorial.SetActive (true);
//		tutorialHandImage.transform.position = GameplayController.Instance.MonsterHoleButton.transform.position;
		tutorialHandImage.gameObject.SetActive (true);
			
		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}

		currentTutorial = gameObject.AddComponent<Tutorial> ();
		currentTutorial.tutorialHandImage = tutorialHandImage;

	}

	public void StartTutorial(GameObject go) {
//		PanelTutorial.SetActive (true);
//		tutorialHandImage.transform.position = GameplayController.Instance.MonsterHoleButton.transform.position;
		tutorialHandImage.gameObject.SetActive (true);

		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}

		currentTutorial = gameObject.AddComponent<Tutorial> ();
		currentTutorial.tutorialHandImage = tutorialHandImage;

		currentTutorial.InitPettingMonster(go);
	}

	public void EndTutorial() {
		EndTutorial (currentTutorial);
	}

	public void EndTutorial(Tutorial tutorial) {
		if (tutorialHandImage != null && tutorialHandImage.transform != null ) {
			tutorialHandImage.transform.SetParent (null);
			tutorialHandImage.gameObject.SetActive (false);
		}
		if (tutorial != null) {
			Destroy (tutorial);
			tutorial = null;
		}
	}


	public Tutorial PointAt(Vector3 point, Transform parent = null, bool startPointing = false){
		tutorialHandImage.gameObject.SetActive (true);
		if (parent == null) {
			tutorialHandImage.transform.SetParent (GameObject.Find ("Canvas").transform);
		} else {
			tutorialHandImage.transform.SetParent (parent);
		}
		tutorialHandImage.transform.localPosition = point;

		if (startPointing) {
			if (currentTutorial != null) {
				Destroy (currentTutorial);
				currentTutorial = null;
			}
			currentTutorial = gameObject.AddComponent<Tutorial> ();
			currentTutorial.tutorialHandImage = tutorialHandImage;
			currentTutorial.PointAt (point, parent);
			return currentTutorial;
		}
		return null;
	}

	public void AddVoiceTutorial(string dataToLoad, Action onDoneDelegate = null)
	{
		GameObject go = Resources.Load ("Gameplay/Popups/Popup Panel - VoiceTutorial") as GameObject;
		if (go != null) {
			GameObject popup = Instantiate (go, GameObject.Find ("Canvas").transform);
			UIVoiceTutorial voiceTutorial = popup.GetComponent<UIVoiceTutorial> ();
			voiceTutorial.dataToLoad = dataToLoad;
			voiceTutorial.onDone = onDoneDelegate;
		}

	}

}
