using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class UIMiniGameEndController : MonoBehaviour {
//	public Text ScoreText;
//	public GameObject ScorePanel;


	public UICircularParticleSystem particles;

	public AudioClip GameWinMusic;
	public AudioClip GameWonFanfare;

	public MonsterBar monsterBar;


//	Monster monster;
	Queue statusQueue = new Queue();
	UIFlashAnimation flashAnimation;


	public Button MapButton;

	public Button Button_MapLevel;
	public Button Button_NextLevel;
	public Button Button_GameComplete;

	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {
		if (statusQueue.Count > 0) {
			doStatusQueue ((status)statusQueue.Dequeue ());
		}
	}

	void OnEnable()
	{
		updateButtons ();

		GameObject go = GameObject.Find ("monster");
		if(go != null) {

			Animator animController;
			animController = go.GetComponentInChildren<Animator> ();
			if (animController != null) {
				animController.SetBool ("IsMiniGame", false);
				animController.SetInteger ("IdleState", 0);
				animController.SetInteger ("EmotionState", 2);
				animController.SetInteger ("EatState", 0);
			}
		}

		particles.enabled = true;

		statusQueue.Enqueue (status.FirstZoomIn);

		AudioController.Instance.PlaySound (GameWonFanfare);
		Invoke ("UnPauseMusic", 1.4f);

		transform.localScale = new Vector3 (3.1f, 3.1f, 3.1f);
		Camera.main.orthographicSize = 5f;
	}


	void updateButtons() {

		bool hasNextLevel = (GameAssets.CurrentLevelIndex != GameAssets.Instance.NumOfLevels - 1);


		if (GameAssets.Instance.MiniGameAsLevel == true) {
			GameAssets.Instance.MiniGameAsLevel = false;
			if (hasNextLevel) {
				Button_MapLevel.gameObject.SetActive (true);
				Button_NextLevel.gameObject.SetActive (true);


				Button_GameComplete.gameObject.SetActive (false);
				MapButton.gameObject.SetActive (false);
			} else {
				Button_GameComplete.gameObject.SetActive (true);

				Button_MapLevel.gameObject.SetActive (false);
				Button_NextLevel.gameObject.SetActive (false);

				MapButton.gameObject.SetActive (false);
			}
		} else {
			MapButton.gameObject.SetActive (true);

			Button_MapLevel.gameObject.SetActive (false);
			Button_NextLevel.gameObject.SetActive (false);
			Button_GameComplete.gameObject.SetActive (false);
		}
	}



	void UnPauseMusic(){
		AudioController.Instance.ChangeMusic (GameWinMusic, true);
	}

	void OnDisable(){
		if (Camera.main != null) {
			Camera.main.orthographicSize = 5;
			Camera.main.transform.position = new Vector3 (0, 0, -10);
			particles.enabled = false;
		}
		gameObject.SetActive (false);
	}

	enum status
	{
		FirstZoomIn,
	}



	void doStatusQueue(status s)
	{
		switch (s) {
		case status.FirstZoomIn:
			firstZoomIn ();
			break;
		}
	}


	void firstZoomIn() {
		GameObject.Find ("monster").GetComponent<MonsterPosition> ().setEndPosition ();

		UIZoomIn uIZoomIn = gameObject.AddComponent<UIZoomIn> ();
		uIZoomIn.onDone = onFirstZoomInDone;
		uIZoomIn.init ();
	}

	void onFirstZoomInDone()
	{

	}


}
