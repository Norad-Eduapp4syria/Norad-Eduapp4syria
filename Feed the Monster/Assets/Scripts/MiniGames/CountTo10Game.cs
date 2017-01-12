using UnityEngine;

using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;

public class CountTo10Game : BaseMiniGame {
	public static CountTo10Game Instance;

	public CountTo10Letter[] letters;

	public GameObject[] LettersLocations;

	public GameObject MonsterMouthHit;


	public AudioClip[] SoundCorrectAnswers;
	public AudioClip SoundEat;
	public AudioClip SoundCorrentLetter;
	public AudioClip SoundCorrentLetterFinish;

	int CurrentDigit = 1;
	int currentLocation;


	public void onStartDragLetter() {
		animController.SetInteger("EatState", 1);
	}

	public void onEndDragLetter(CountTo10Letter letter)
	{
		animController.SetInteger("EatState", 0);
		if (RectTransformUtility.RectangleContainsScreenPoint ((RectTransform)MonsterMouthHit.transform, Input.mousePosition, GameplayController.Instance.canvasCamera)) {
//			ApproveDigit (letter);
			letter.gotoMouth();
		} else {
			letter.Rollback ();
		}
	}

	public void ApproveDigit(CountTo10Letter letter)
	{
		if (letter.value == "" + CurrentDigit) {
			if (UserInfo.Instance.GetHadMinigameTutorial () == 0) {
				TutorialController.Instance.SetIsInMinigameTutorial (false);
//				if (TutorialController.Instance.getClone () != null) {
//					Destroy (TutorialController.Instance.getClone ().gameObject);
//				}
				UserInfo.Instance.SetHadMinigameTutorial (1);
			}
			TutorialController.Instance.EndTutorial ();	
			//Jonathan
			AudioController.Instance.PlaySound ( SoundCorrectAnswers[UnityEngine.Random.Range(0, SoundCorrectAnswers.Length)] );		
			AudioController.Instance.PlaySound ( SoundEat );

			if (CurrentDigit+1 >= 11) {
				AudioController.Instance.PlaySound (SoundCorrentLetterFinish, .35f);
			} else {
				AudioController.Instance.PlaySound (SoundCorrentLetter, .35f);
			}
			//Jonathan

			animController.SetInteger("EatState", 2);
			letters [CurrentDigit - 1].gameObject.SetActive (false);


			AudioClip voice = Resources.Load ("Sounds/Voice/Numbers/" + letters [CurrentDigit - 1].value) as AudioClip;
			if (voice != null) {
				AudioController.Instance.PlaySound (voice, 1);
			}


			CurrentDigit++;



			if (CurrentDigit >= 11) {
				TutorialController.Instance.SetIsInMinigameTutorial (false);
				Complete ();
			} else {
				EnableCurrentDigit ();
			}




		}
	}

	void Complete() {
		//this.gameObject.GetComponent<UIPopupPanel> ().PopOut ();
		//MiniGameController.Instance.onMiniGameDone ();
		//UIController.Instance.ShowPanel (UIController.Instance.MonsterCollectionPanel);

		startHappyEvolution ();
	}

	void EnableCurrentDigit() {
		if(CurrentDigit - 2 >= 0) {
		}
		letters [CurrentDigit - 1].gameObject.SetActive (true);
	}

	void Awake()
	{
		Instance = this;
	}


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (endingMonster != null) {
			endingMonster.transform.localScale = Vector3.Lerp (endingMonster.transform.localScale, new Vector3(0.8f, 0.8f, 0.8f), Time.deltaTime * 5);
			endingMonster.transform.position = Vector3.Lerp (endingMonster.transform.position, endingMonster.GetComponent<MonsterPosition> ().GameScreen, Time.deltaTime * 5);

			float dis1 = Vector2.Distance (endingMonster.transform.localScale, new Vector3(0.8f, 0.8f, 0.8f));
			float dis2 = Vector2.Distance (endingMonster.transform.position, endingMonster.GetComponent<MonsterPosition> ().GameScreen);

			if (dis1 < 0.001f && dis2 < 0.001f) {
				endingMonster = null;
				startHappyEvolution ();
			}
		}

	}

	void OnEnable()
	{
		StartMiniGame ();

		var obj = GameObject.Find ("monster");
		if (obj != null) {
			animController = obj.GetComponentInChildren<Animator> ();
		}

		CurrentDigit = 1;
		foreach (CountTo10Letter letter in letters) {
			letter.gameObject.SetActive (false);
		}
//		letters[CurrentDigit - 1].NewPos = letters[CurrentDigit - 1].transform.position;

		EnableCurrentDigit ();
//		letters [CurrentDigit - 1].gameObject.SetActive(true);
	}

	public override void init (Monster monster)
	{
		base.init (monster);
		currentHappyEvolution = HappyEvolution.Sad;
		Debug.Log ("CountTo10Game init");
	}


	// start added by Tzahi - 9-11-2016


	enum HappyEvolution
	{
		Sad,
		IdleSad,
		Idle,
		Happy,
		Done
	}

	HappyEvolution currentHappyEvolution = HappyEvolution.Sad;
	GameObject endingMonster;


	void startHappyEvolution ()
	{
		switch (currentHappyEvolution)
		{
		case HappyEvolution.Sad:
//			animController.SetInteger ("EatState", 0);
//			animController.SetInteger ("IdleState", 1);
//			currentHappyEvolution = HappyEvolution.IdleSad;
//			Invoke ("startHappyEvolution", 0.1f);
//			break;
		case HappyEvolution.IdleSad:
			animController.SetInteger ("EatState", 0);
			animController.SetInteger ("IdleState", 0);
			animController.SetInteger ("EmotionState", 0);
			animController.SetBool ("IsSad", false);
			currentHappyEvolution = HappyEvolution.Idle;
			Invoke ("startHappyEvolution", 1.0f);
			break;
		case HappyEvolution.Idle:
			animController.SetInteger ("IdleState", 0);
			animController.SetInteger ("EmotionState", 2);

			EndMiniGame();

//			currentHappyEvolution = HappyEvolution.Happy;
//			Invoke ("startHappyEvolution", 1.0f);
			break;
		case HappyEvolution.Happy:
			endingMonster = GameObject.Find ("monster");
			MonsterBar.Instance.addBackMonster (endingMonster);
			currentHappyEvolution = HappyEvolution.Done;
//			Invoke ("startHappyEvolution", 1.0f);
			break;
		case HappyEvolution.Done:
			animController.SetInteger ("EmotionState", 0);
			EndMiniGame();
			break;
		}
	}



	// end added by Tzahi

}
