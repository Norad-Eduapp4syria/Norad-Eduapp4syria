using System.Collections.Generic;
using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UILevelEndController : MonoBehaviour {
	public Text TitleText;
	public Text ScoreText;

	public GameObject Stars;

	public Sprite LoseScreen;
	public Sprite WinScreen;
	public Button NextButton;
	public Button RetryButton;
	public Button RetryFailButton;
	public Button MapButton;
	public UICircularParticleSystem particles;


	public Image Icon_gage_1;
	public Image Icon_gage_2;
	public Image Icon_gage_3;

	public Sprite Icon_gage_on_1;
	public Sprite Icon_gage_off_1;

	public Sprite Icon_gage_on_2;
	public Sprite Icon_gage_off_2;

	public Sprite Icon_gage_on_3;
	public Sprite Icon_gage_off_3;


	public AudioClip GameWinMusic;
	public AudioClip GameFailMusic;

	public AudioClip GameLostFanfare;

	public AudioClip GameWonFanfare;

	public AudioClip SoundEvolve;
	public AudioClip SoundScoreCount;

	public AudioClip SoundBarFull;


	AudioSource SoundScoreCountSRC;

	bool isWin;
	bool isGageChanged = false;

	bool isStatusPopupShow = false;


	Monster monster;

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
		isStatusPopupShow = false;

		hideGageIcons ();

		isWin = GameplayController.Instance.CurrentLevelStars > 0;

		GameObject go = GameObject.Find ("monster");
		if(go != null) {
			MonsterSpritesController msc = go.GetComponent<MonsterSpritesController> ();

			if (msc != null && msc.monster != null)
			{
				monster = msc.monster;
			}

			Animator animController;
			animController = go.GetComponentInChildren<Animator> ();
			if (animController != null) {
				animController.SetInteger ("IdleState", 0);
				animController.SetInteger ("EmotionState", 0);
				animController.SetInteger ("EatState", 0);
			}

		}

		particles.enabled = isWin;
		transform.GetChild (0).gameObject.GetComponent<Image> ().sprite = isWin ? WinScreen : LoseScreen;

		statusQueue.Enqueue (status.FirstZoomIn);

		if (isWin) {
			AudioController.Instance.PlaySound (GameWonFanfare);
			Invoke ("UnPauseMusic", 1.4f);

			Analitics.Instance.treckScreen ("Level " + (GameplayController.Instance.CurrentLevelIndex + 1) + " Success");

			Analitics.Instance.treckEvent (AnaliticsCategory.GamePlay, AnaliticsAction.LevelSuccess	+ "_" + (GameplayController.Instance.CurrentLevelIndex + 1).ToString(), GameplayController.Instance.SucsessSegment.ToString() + " puzzles");
		} else {
			AudioController.Instance.PlaySound (GameLostFanfare);

			Analitics.Instance.treckScreen ("Level " + (GameplayController.Instance.CurrentLevelIndex + 1) + " Fail");
			Analitics.Instance.treckEvent (AnaliticsCategory.GamePlay, AnaliticsAction.LevelFail	+ "_" + (GameplayController.Instance.CurrentLevelIndex + 1).ToString(), GameplayController.Instance.SucsessSegment.ToString() + " puzzles");
		}

		UIController.Instance.ClosePopup (UIController.Instance.GamePanel);

		if (GameplayController.Instance != null && GameplayController.Instance.CurrentActive != null) {
			GameplayController.Instance.CurrentActive.SetMonsterState (isWin ? MonsterCalloutController.MonsterState.Happy : MonsterCalloutController.MonsterState.Sad);
		}

//		if (isWin && GameplayController.Instance.Levels.Length > GameplayController.Instance.CurrentLevelIndex + 1) {
		if (isWin && GameplayController.Instance.NumOfLevels > GameplayController.Instance.CurrentLevelIndex + 1) {
			UserInfo.Instance.SetHighestOpenLevel (GameplayController.Instance.CurrentLevelIndex + 1);
		}

		//NextButton.gameObject.SetActive (UserInfo.Instance.GetHighestOpenLevel() >= GameplayController.Instance.CurrentLevelIndex + 1 );

		TitleText.text = isWin ? "LEVEL\nWON!" : "LEVEL\nFAILED";

		bool hasNextLevel = GameplayController.Instance.CurrentLevelIndex != GameplayController.Instance.NumOfLevels - 1;
		// button for win
		NextButton.gameObject.SetActive (isWin && hasNextLevel);
		RetryButton.gameObject.SetActive (isWin);
		// buttons for lose
		RetryFailButton.gameObject.SetActive (!isWin);
		Stars.SetActive (isWin);

		ScoreText.text = GameplayController.Instance.CurrentLevelScore.ToString();

		// this is to stop loop of happy / sad animations
//		if (GameplayController.Instance != null && GameplayController.Instance.CurrentActive != null) {
//			GameplayController.Instance.CurrentActive.SetMonsterState (MonsterCalloutController.MonsterState.Idle);
//		}

		transform.localScale = new Vector3 (3.1f, 3.1f, 3.1f);
		Camera.main.orthographicSize = 5f;
	}

	void UnPauseMusic(){
		AudioController.Instance.ChangeMusic (GameWinMusic, true);
	}

	void OnDisable(){
//		GameplayController.Instance.GameBackgroundSpriteRenderer.color = new Color (1, 1, 1, 1);
		Camera.main.orthographicSize = 5;
		Camera.main.transform.position = new Vector3 (0, 0, -10);
		particles.enabled = false;


		if(SoundScoreCountSRC != null) {
			SoundScoreCountSRC.Stop ();
			Destroy (SoundScoreCountSRC.gameObject);
			SoundScoreCountSRC = null;
		}
	}
/*
	IEnumerator FadeBgToWhite(){
		Color c = GameplayController.Instance.GameBackgroundSpriteRenderer.color;
		Color end = new Color (0,0,0,0);
		for (float t = 0; t <= 1; t += Time.deltaTime) {
			GameplayController.Instance.GameBackgroundSpriteRenderer.color = Color.Lerp(c, end, t);
			yield return null;
		}
	}
*/
	// Start Tzahi

	enum status
	{
		FirstZoomIn,
		UpdateSlider,
		WaitGageAnimation,
		ZoomOutForGage,

		GageAnimationIn,
		ReaplaceMonster,
		WaitGageZoomIn,

		GageZoomIn
	}

	Queue statusQueue = new Queue();

	public Slider MonsterGageSliderA;
	public Slider MonsterGageSliderB;
	public MonsterBar monsterBar;
	UIFlashAnimation flashAnimation;


	void doStatusQueue(status s)
	{
		switch (s) {
		case status.FirstZoomIn:
			firstZoomIn ();
			break;
		case status.UpdateSlider:
			UpdateNewSliderValue ();
			break;
		case status.WaitGageAnimation:
			StartCoroutine (waitBefom(0.3f, status.ZoomOutForGage));
			break;
		case status.ZoomOutForGage:
			ZoomOutForGage();
			break;
		case status.GageAnimationIn:
			AddGageAnimation ();
			AudioController.Instance.PlaySound (SoundEvolve);
			break;
		case status.ReaplaceMonster:
			ReaplaceMonster ();
			hideGageIcons ();
			UpdateGageSprite ();
			break;
		case status.WaitGageZoomIn:
			StartCoroutine (waitBefom(0.2f, status.GageZoomIn));
			break;
		case status.GageZoomIn:
			NextButton.interactable = true;
			RetryButton.interactable = true;
			MapButton.interactable = true;

			gageZoomIn ();
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
		showSlider (true);
	}

	Sprite NextGageSprite;


	void hideGageIcons ()
	{
		Icon_gage_1.gameObject.SetActive (false);
		Icon_gage_2.gameObject.SetActive (false);
		Icon_gage_3.gameObject.SetActive (false);
	}

	void UpdateGageSprite()
	{
		if (monster.Gage == 0) {
			Icon_gage_1.sprite = Icon_gage_off_1;
			Icon_gage_1.gameObject.SetActive (true);
			NextGageSprite = Icon_gage_on_1;
		} else if (monster.Gage == 1) {
			Icon_gage_2.sprite = Icon_gage_off_2;
			Icon_gage_2.gameObject.SetActive (true);
			NextGageSprite = Icon_gage_on_2;
		} else if (monster.Gage == 2) {
			Icon_gage_3.sprite = Icon_gage_off_3;
			Icon_gage_3.gameObject.SetActive (true);
			NextGageSprite = Icon_gage_on_3;
		}
	}

	void showSlider(bool toAddGage)
	{
		if (showHideSliders () && isWin) {
			UpdateGageSprite ();

			MonsterGageSliderA.value = monster.GageValue;
			MonsterGageSliderB.value = monster.GageValue;

			if (toAddGage) {
//				isGageChanged = monster.AddGageValue (GameplayController.Instance.CurrentLevelXP);
				isGageChanged = monster.AddGageValue (GameplayController.Instance.CurrentLevelScore);
				if (isGageChanged) {
					NextButton.interactable = false;
					RetryButton.interactable = false;
					MapButton.interactable = false;
				} else {
					NextButton.interactable = true;
					RetryButton.interactable = true;
					MapButton.interactable = true;
				}
			}
			statusQueue.Enqueue (status.UpdateSlider);	
		} else {
			Invoke ("ShowStatusPopup", 0.5f);
		}
	}

	bool showHideSliders()
	{
		if (monster.IsReady) {
			MonsterGageSliderA.gameObject.SetActive (false);
			MonsterGageSliderB.gameObject.SetActive (false);
		} else if (MonsterGageSliderA != null && MonsterGageSliderB != null) {
			if (isWin) {

				MonsterGageSliderA.gameObject.SetActive (true);
				MonsterGageSliderB.gameObject.SetActive (true);
				return true;
			} else {
				MonsterGageSliderA.gameObject.SetActive (false);
				MonsterGageSliderB.gameObject.SetActive (false);
			}
		} else {
			if (MonsterGageSliderA != null) {
				MonsterGageSliderA.gameObject.SetActive (false);
			}
			if (MonsterGageSliderB != null) {
				MonsterGageSliderB.gameObject.SetActive (false);
			} 
		}
		return false;
	}

	void UpdateNewSliderValue ()
	{
		float to;

		if (isGageChanged) {
			to = 100f;
		} else {
			to = monster.GageValue;
		}

		float diff = Mathf.Abs (MonsterGageSliderA.value - to);

		if (diff > 0.1f) {
			float newValue = Mathf.Lerp (MonsterGageSliderA.value, to, 2 * Time.deltaTime);
			float d = (newValue - MonsterGageSliderA.value);
			MonsterGageSliderA.value = newValue;

			int f = (int)(float.Parse (ScoreText.text) - ((monster.currentGageCost / 100f ) * d));
			if (f < 0) {
				f = 0;
			} else {
				if (SoundScoreCountSRC == null) {
					SoundScoreCountSRC = AudioController.Instance.PlaySound (SoundScoreCount, 0.15f, 1, false);
					if (SoundScoreCountSRC) {
						SoundScoreCountSRC.loop = true;
					}
				}
			}



			if (f <= 0) {
				if(SoundScoreCountSRC != null) {
					SoundScoreCountSRC.Stop ();
					Destroy (SoundScoreCountSRC.gameObject);
					SoundScoreCountSRC = null;
				}
			}

//			ScoreText.text = ((int)Mathf.Lerp (int.Parse (ScoreText.text), 0, 5 * Time.deltaTime)).ToString ();
			ScoreText.text = f.ToString ();

			statusQueue.Enqueue (status.UpdateSlider);
		} else if (isGageChanged == true) {
			ScoreText.text = "0";
			statusQueue.Enqueue (status.WaitGageAnimation);

			Icon_gage_1.sprite = NextGageSprite;
			Icon_gage_2.sprite = NextGageSprite;
			Icon_gage_3.sprite = NextGageSprite;

			isGageChanged = false;
			AudioController.Instance.PlaySound (SoundBarFull);

			if(SoundScoreCountSRC != null) {
				SoundScoreCountSRC.Stop ();
				Destroy (SoundScoreCountSRC.gameObject);
				SoundScoreCountSRC = null;
			}
		} else {
			ScoreText.text = "0";
			Invoke ("ShowStatusPopup", 0.5f);

			if(SoundScoreCountSRC != null) {
				SoundScoreCountSRC.Stop ();
				Destroy (SoundScoreCountSRC.gameObject);
				SoundScoreCountSRC = null;
			}
		}
	}

	IEnumerator waitBefom(float time, status sts)
	{
		yield return new WaitForSeconds (time);
		statusQueue.Enqueue (sts);
	}

	void ZoomOutForGage()
	{
		UIZoomOut uIZoomOut = gameObject.AddComponent<UIZoomOut> ();
		uIZoomOut.onDone = onZoomOutDone;
		uIZoomOut.init ();
	}

	void onZoomOutDone()
	{
		statusQueue.Enqueue (status.GageAnimationIn);
	}

	void AddGageAnimation()
	{
		//FlashAnimation;

		GameObject go = Instantiate(Resources.Load ("Gameplay/FlashAnimation") as GameObject);
		flashAnimation = go.GetComponent<UIFlashAnimation> ();

		flashAnimation.onPeak	= onGageAnimationInDone;
		flashAnimation.onEnd	= onGageAnimationOutDone;

		go.transform.SetParent(transform, true);

		go.transform.localScale = transform.localScale;
	}

	void onGageAnimationInDone()
	{
		ScoreText.text = "0";
		statusQueue.Enqueue (status.ReaplaceMonster);
	}

	void ReaplaceMonster()
	{
		GameObject newMonster = Instantiate (monster.currentPlayGO, new Vector3 (), Quaternion.identity) as GameObject;

		newMonster.transform.parent = monsterBar.transform.GetChild (0);
		newMonster.transform.localPosition = new Vector3 (0, 0, 0);
		newMonster.transform.localScale = new Vector3 (1f, 1f, 1f);
		newMonster.AddComponent<MonsterSpritesController> ().monster = monster;
		newMonster.transform.parent = null;

		newMonster.GetComponent<MonsterPosition> ().setEndPosition (false);

		Destroy (GameObject.Find ("monster"));
		newMonster.name = "monster";

		showSlider (false);
	}

	void onGageAnimationOutDone()
	{
		Destroy (flashAnimation.gameObject);
		statusQueue.Enqueue (status.WaitGageZoomIn);
	}

	void gageZoomIn() {
		UIZoomIn uIZoomIn = gameObject.AddComponent<UIZoomIn> ();

		uIZoomIn.onDone = onGageZoomInDone;
		uIZoomIn.init ();
	}

	void onGageZoomInDone()
	{
//		Invoke ("ShowStatusPopup", 0.5f);

		if (monster.MonsterType == MonsterType.Magnet && monster.Gage == 1) {
			RetryButton.interactable = false;
			NextButton.interactable = false;

			TutorialController.Instance.SetIsInMinigameTutorial (true);
			TutorialController.Instance.PointAt (MapButton.transform.position, transform);
		}
	}


	Dictionary<MonsterType, bool> showenStatusPopup = new Dictionary<MonsterType, bool>();

	void ShowStatusPopup()
	{
		if (!isStatusPopupShow) {

//			Monster monster = MiniGameController.Instance.getEmotionMonster ();
			if (monster != null && monster.Gage > 0) {
				bool needToShow = false;
				if (
					monster.EmotionType != MonsterEmotionTypes.Happy
					&&
					(
					    !showenStatusPopup.ContainsKey (monster.MonsterType)
					    ||
					    showenStatusPopup [monster.MonsterType] == false
					)) {
					needToShow = true;
				} else if(monster.EmotionType != MonsterEmotionTypes.Happy) {
					float r = Random.value;
					Debug.Log ("Random.value: " + r.ToString ());
					if (r <= 0.2f) {
						needToShow = true;
					}
				}
				if(needToShow == true)
				{
					UIController.Instance.MonsterStatusPopup.SetActive (true);
					UIStatusController StatusController = UIController.Instance.MonsterStatusPopup.GetComponent<UIStatusController> ();
					StatusController.init (monster);

					if (showenStatusPopup.ContainsKey (monster.MonsterType)) {
						showenStatusPopup [monster.MonsterType] = true;
					} else {
						showenStatusPopup.Add(monster.MonsterType, true);
					}
				}
			}
		}
		isStatusPopupShow = true;
	}

	// End Tzahi

}
