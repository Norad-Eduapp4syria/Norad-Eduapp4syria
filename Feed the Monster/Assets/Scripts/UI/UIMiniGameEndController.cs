using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class UIMiniGameEndController : MonoBehaviour {
//	public Text ScoreText;
//	public GameObject ScorePanel;

	public Button MapButton;
	public UICircularParticleSystem particles;

//	public Image Icon_gage_1;
//	public Image Icon_gage_2;
//	public Image Icon_gage_3;

//	public Sprite Icon_gage_on_1;
//	public Sprite Icon_gage_off_1;

//	public Sprite Icon_gage_on_2;
//	public Sprite Icon_gage_off_2;

//	public Sprite Icon_gage_on_3;
//	public Sprite Icon_gage_off_3;

	public AudioClip GameWinMusic;
	public AudioClip GameWonFanfare;
//	public AudioClip SoundEvolve;


//	public AudioClip SoundScoreCount;
//	public AudioClip SoundBarFull;

//	public Slider MonsterGageSliderA;
	public MonsterBar monsterBar;


//	AudioSource SoundScoreCountSRC;

//	bool isGageChanged = false;
//	Sprite NextGageSprite;
//	bool isStatusPopupShow = false;
	Monster monster;
	Queue statusQueue = new Queue();
	UIFlashAnimation flashAnimation;



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
//		isStatusPopupShow = false;
//		hideGageIcons ();
//		MonsterGageSliderA.gameObject.SetActive (false);

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

//		ScoreText.text = GameplaySettings.MiniGame_SuccessScore.ToString();

		transform.localScale = new Vector3 (3.1f, 3.1f, 3.1f);
		Camera.main.orthographicSize = 5f;
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
/*
		if(SoundScoreCountSRC != null) {
			SoundScoreCountSRC.Stop ();
			Destroy (SoundScoreCountSRC.gameObject);
			SoundScoreCountSRC = null;
		}
*/
		gameObject.SetActive (false);
	}

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



	void doStatusQueue(status s)
	{
		switch (s) {
		case status.FirstZoomIn:
			firstZoomIn ();
			break;
/*
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
			MapButton.interactable = true;

			gageZoomIn ();
			break;
*/
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
//		showSlider (true);
	}



/*
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
		if (showHideSliders ()) {
			UpdateGageSprite ();

			MonsterGageSliderA.value = monster.GageValue;
			if (toAddGage) {
				isGageChanged = monster.AddGageValue (GameplaySettings.MiniGame_SuccessScore);
			}

			statusQueue.Enqueue (status.UpdateSlider);	
		} else {
			Invoke ("ShowStatusPopup", 0.5f);
		}
	}

	bool showHideSliders()
	{
		if (monster.IsReady) {
			if (MonsterGageSliderA) {
				MonsterGageSliderA.gameObject.SetActive (false);
			}
			if (ScorePanel) {
				ScorePanel.gameObject.SetActive (false);
			}

		} else if (MonsterGageSliderA != null) {
			MonsterGageSliderA.gameObject.SetActive (true);
			if (ScorePanel) {
				ScorePanel.gameObject.SetActive (true);
			}
			return true;
		} else {
			if (MonsterGageSliderA != null) {
				MonsterGageSliderA.gameObject.SetActive (false);
			}
			if (ScorePanel) {
				ScorePanel.gameObject.SetActive (false);
			}
		}
		return false;
	}

	void UpdateNewSliderValue ()
	{
		float to;

		if (isGageChanged) {
			to = 100f;

			MapButton.interactable = false;
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
					SoundScoreCountSRC = AudioController.Instance.PlaySound (SoundScoreCount, 0.15f, 1f, false);
					if (SoundScoreCountSRC) {
						SoundScoreCountSRC.loop = true;
					}
				}
			}
			if (f <= 0)
			{
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
	}


	Dictionary<MonsterType, bool> showenStatusPopup = new Dictionary<MonsterType, bool>();

	void ShowStatusPopup()
	{
		if (!isStatusPopupShow) {

			//			Monster monster = MiniGameController.Instance.getEmotionMonster ();
			if (monster != null && monster.IsReady) {
				bool needToShow = false;
				if (
					(monster.EmotionType != MonsterEmotionTypes.Happy && monster.EmotionType != MonsterEmotionTypes.NONE)
					&&
					(
						!showenStatusPopup.ContainsKey (monster.MonsterType)
						||
						showenStatusPopup [monster.MonsterType] == false
					)) {
					needToShow = true;
				} else if(monster.EmotionType != MonsterEmotionTypes.Happy && monster.EmotionType != MonsterEmotionTypes.NONE) {
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

*/
	// End Tzahi

}
