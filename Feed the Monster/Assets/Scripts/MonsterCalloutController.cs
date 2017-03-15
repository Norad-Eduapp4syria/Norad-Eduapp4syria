using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;
using UnityEngine.UI;
using System;
using System.Collections.Generic;

public class MonsterCalloutController : MonoBehaviour {
	public const int ANIMATION_IDLE = 0, ANIMATION_EATING = 1, ANIMATION_ANGRY = 2, ANIMATION_HAPPY = 3;

	public enum MonsterState
	{
		Idle,
		Happy,
		Sad,
		Eating,
		EatGood,
		EatBad,
		Finished
	}

	public bool IsMouseOver { get;  set; }
	public Text text;

	public HoleButtonController holeButtonController;


	public AudioClip[] SoundCorrectAnswers;
	public AudioClip SoundWrongAnswer;
	public AudioClip SoundCorrentLetter;
	public AudioClip SoundEat;
	public AudioClip SoundAngry;
	public AudioClip SoundCorrentLetterFinish;

/*
	public Color BubbleFontColorDefault;
	public Color BubbleFontColorBold;
*/

	public Color FontColorLetter;

	public Color FontColorWordDefault;
	public Color FontColorWordBold;

	public int FontSizeLetter = 120;
	public int FontSizeWord = 110;

	public GameObject ShowPartical;
	public GameObject HidePartical;

	// Delete by Tzahi
	//	public Monster Model{ get; private set; }

	MonsterState monsterState;
	public Image bubbleImage;
	public Image playImage;

	MonsterInputType mMonsterInputType;

	Queue<LetterController> mSelectedLettersToCollectQueue = new Queue<LetterController>();
	LetterController mCurrentLetterInMouth;
	NeededLettersAnimation mNeededLettersAnimation;

	Animator animController;

	float mTimeAlive;
	float idleStateTimer = 0;


	private int requiredLetterIndex = 0;


	Monster _monster = null;

	Monster monster
	{
		get
		{ 
			if (_monster == null && GameplayController.Instance != null) {

				_monster = GameplayController.Instance.CurrentMonster;
			}
			return _monster;
		}
	}

	// Use this for initialization
	void Start () {
		GameObject go = GameObject.Find ("monster");
		if (go != null) {
			animController = go.GetComponentInChildren<Animator> ();

			animController.SetInteger ("EatState", 0);
			animController.SetInteger ("IdleState", 0);
			animController.SetInteger ("EmotionState", 0);
		}
		bubbleImage = GetComponentInChildren<Image> ();
		getCanvasGroup.interactable = false;

//		if (ShowPartical != null) {
//			ShowPartical.SetActive (false);
//		}
		if(HidePartical != null) {
			HidePartical.SetActive (false);
		}
	}

	public void OnEatDone()
	{
		if (animController) {
			animController.SetInteger ("EatState", 0);
		}
	
	}




	// Update is called once per frame
	void Update ()
	{
		if (GameplayController.Instance && GameplayController.Instance.CurrentActive == this && !GameplayController.Instance.IsPause &&  !GameplayController.Instance.IsPausePopup) {
			switch (GameplayController.Instance.State) {
			case GameplayController.GameState.CollectLetters:
				if (mSelectedLettersToCollectQueue.Count > 0) {
					mSelectedLettersToCollectQueue.Dequeue ().GoToMonster (this);
					GameplayController.Instance.SetState (GameplayController.GameState.LetterComingToMonster);
				}
				break;
			}
		}
		if (monsterState == MonsterState.Finished) {
			getCanvasGroup.interactable = false;

			if (bubbleImage) {
				bubbleImage.color = Color.Lerp (bubbleImage.color, new Color (1, 1, 1, 0), Time.deltaTime * 5);
			}
			if (playImage) {
				playImage.color = Color.Lerp (playImage.color, new Color (1, 1, 1, 0), Time.deltaTime * 5);
			}

			text.gameObject.SetActive(false);//color  = Color.Lerp( text.color , GameplayController.Instance.CurrentLevel.BubbleLetterFontColorDefault * new Color (1, 1, 1, 0), Time.deltaTime*10);
		}
	}

	void FixedUpdate() {
		if (monsterState != MonsterState.Eating && monsterState != MonsterState.Finished ) {
			idleStateTimer += Time.deltaTime; // count back to idle mode
		}
		
		if (idleStateTimer >= .8f) {
			idleStateTimer = 0;

			monsterState = MonsterState.Idle;
			if (animController != null) {
				animController.SetInteger ("EatState", 0);
			}
			if (UnityEngine.Random.value < 0.3f) {
				// Added by Tzahi
				if (monster != null && animController != null) {
					animController.SetInteger ("IdleState", monster.IdleStates [UnityEngine.Random.Range (0, monster.IdleStates.Count)]);
					return;
				}
				// Delete by Tzahi
				//				animController.SetInteger ("IdleState", UnityEngine.Random.Range (1, 4));
			} else {
				// Delete by Tzahi
				//animController.SetInteger ("IdleState", 0);
			}
			// Added by Tzahi
			if (animController != null) {
				animController.SetInteger ("IdleState", 0);
			}
		}
	}

	public void Init()
	{
		requiredLetterIndex = 0;
//		text.color = GameplayController.Instance.CurrentLevel.BubbleLetterFontColorBold;
//		text.GetComponent<Outline>().effectColor = GameplayController.Instance.CurrentLevel.BubbleLetterFontOutlineColorDefault;


		mMonsterInputType = GameplayController.Instance.CurrentLevel .monsterInputType;

		if (mMonsterInputType == MonsterInputType.LetterInWord || mMonsterInputType == MonsterInputType.Word) {
			text.fontSize = FontSizeWord;
		} else {
			text.fontSize = FontSizeLetter;
		}

		transform.SetParent (GameObject.Find ("Panel - Monsters").transform);

		GameObject location = GameplayController.Instance.MonsterHoleButton.gameObject;//GameObject.Find("MonsterHoleButton");

		// Delete by Tzahi
		//		transform.position = location.transform.position;
		// Added by Tzahi
		transform.localPosition = new Vector2();

		holeButtonController = location.GetComponent<HoleButtonController>();
		holeButtonController.onPointerEnter += OnPointerEnter;
		holeButtonController.onPointerDown += OnPointerDown;
		holeButtonController.onPointerExit += OnPointerExit;
		holeButtonController.onPointerUp += OnPointerUp;
		holeButtonController.onPointerClick += HoleButtonController_onPointerClick;

		// Delete by Tzahi
//		Model = GameplayController.Instance.CurrentLevel.HoleMonster;

		ThoughtBubbleAnimation ();

		SetMonsterState (MonsterState.Idle);

		//SetAnimation (ANIMATION_IDLE);
		//PlayMouthAnimation (MouthIdleSprites);
		//PlayEyeAnimation (EyeIdleSprites);
	}

	public void onCalloutClicked()
	{
		if(bubbleImage.gameObject.activeSelf != true)
		{
			return;
		}
		PlayCalloutSound ();
	}

	public void PlayCalloutSound(){
		string fileName;
		string url;
		AudioClip voice;
		string word = "";

		getCanvasGroup.interactable = true;

		switch (GameplayController.Instance.CurrentLevel.monsterInputType) {
		case MonsterInputType.Letter:
		case MonsterInputType.SoundLetter:
			url = "Sounds/Voice/Letters/" + RTL.Clean(GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [0]);
			voice = Resources.Load (url) as AudioClip;
//			var ss = Resources.Load (url);

			if (voice != null) {
				AudioController.Instance.PlaySound (voice, 1, monster.Pitch);
			} else {
				Debug.Log ("Sound is missing - '" + url + "'");
			}
			break;

		case MonsterInputType.LetterInWord:
			//			voice = Resources.Load ("Sounds/Voice/Letters/" + Common.Instance.GetIsolatedForm(GameplayController.Instance.CurrentSegment.MonsterRequiredLetters[0])) as AudioClip;
			fileName = ArabicBaseForm.Extract (RTL.Clean(GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [0]));
			url = "Sounds/Voice/Letters/" + fileName;
			voice = Resources.Load (url) as AudioClip;
			if (voice != null) {
				AudioController.Instance.PlaySound (voice, 1, monster.Pitch);
			} else {
				Debug.Log ("Sound is missing - '" + url + "'");
			}
			break;
		case MonsterInputType.Word:
		case MonsterInputType.SoundWord:
			word = "";
			foreach (string letter in GameplayController.Instance.CurrentSegment.MonsterRequiredLetters) {
				word += letter;
			}
			url = "Sounds/Voice/Words/" + ArabicBaseForm.Extract (RTL.Clean(word));

			voice = Resources.Load (url) as AudioClip;
			if (voice != null) {
				AudioController.Instance.PlaySound (voice, 1, monster.Pitch);
			} else {
				Debug.Log ("Sound is missing - '" + url + "'");
			}	
			break;
		}

	}
	/*Jonathan - thought bubble*/
	void ThoughtBubbleAnimation()
	{
		GameplayController.Instance.SetState (GameplayController.GameState.ThoughtBubbleAnimation);
		GetComponentInChildren<Animation> ().Play ("ThoughtBubbleAnimation");


		if (ShowPartical != null) {
			ShowPartical.SetActive (true);
		}

		GetComponentInChildren<Image> ().enabled = true;
		Invoke("EndThoughtBubbleAnimation", 1.0f);
//		EndThoughtBubbleAnimation ();
	}

	public void EndThoughtBubbleAnimation()
	{
		ShowNeededLetters ();
	}

	public void ShowNeededLetters()
	{
//		GameplayController.Instance.SetState (GameplayController.GameState.ShowNeededInputAnimation);
		float timeToEndShow = 1.5f;

		/*foreach (Transform children in transform) {
			foreach (Transform grandchild in children) {
				if (grandchild.name == "Picture") {
					grandchild.gameObject.activeSelf = (GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.SoundWord); //Jonathan
				}
			}
		}*/

		switch (GameplayController.Instance.CurrentLevel.monsterInputType) {
		case MonsterInputType.Letter:
			Invoke ("PlayCalloutSound", 0.5f);

			mNeededLettersAnimation = new NeededLettersAnimation (text, this);
			timeToEndShow = 1f;
			mNeededLettersAnimation.Show (timeToEndShow);
			break;
		case MonsterInputType.SoundLetter: //Jonathan
			Invoke ("PlayCalloutSound", 0.5f);
			timeToEndShow = 1f;
			foreach (Transform children in transform) {
				foreach (Transform grandchild in children) {
					if (grandchild.name == "Picture") {
						grandchild.gameObject.SetActive(true);
					}
					if (grandchild.name == "Text") {
						grandchild.gameObject.SetActive(false);
					}
				}
			}
			break;
		case MonsterInputType.LetterInWord:
			Invoke ("PlayCalloutSound", 0.5f);
			mNeededLettersAnimation = new NeededLettersAnimation (text, this);
			timeToEndShow = 1.2f;
			mNeededLettersAnimation.Show (timeToEndShow);
			break;

		case MonsterInputType.Word:
			Invoke ("PlayCalloutSound", 0.5f);
			
			mNeededLettersAnimation = new NeededLettersAnimation (text, this);
//			timeToEndShow = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length;
			timeToEndShow = 1.5f;
			mNeededLettersAnimation.Show (timeToEndShow);
			break;

		case MonsterInputType.SoundWord: //Jonathan
			Invoke ("PlayCalloutSound", 0.5f);
			string word = "";
			foreach (string letter in GameplayController.Instance.CurrentSegment.MonsterRequiredLetters) {
				word += letter;
			}
			foreach (Transform children in transform) {
				foreach (Transform grandchild in children) {
					if (grandchild.name == "Picture") {
						//grandchild.gameObject.activeSelf = true;
						grandchild.gameObject.SetActive(true);
						//grandchild.GetComponent<Image>().sprite = Resources.Load<Sprite> ("Images/" + ArabicBaseForm.Extract(word)) as Sprite;
						//Debug.Log ("1: " + word);
						//Debug.Log ("2: " + ArabicBaseForm.Extract(word));
					}
					if (grandchild.name == "Text") {
						//grandchild.Translate (new Vector3 (0, -7.5f, 0));
						grandchild.gameObject.SetActive(false);
					}
				}
			}
			mNeededLettersAnimation = new NeededLettersAnimation (text, this);
//			timeToEndShow = GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length;
			timeToEndShow = 1.5f;
			mNeededLettersAnimation.Show (timeToEndShow);
			break;
		}

//		Timer.Instance.Create (new Timer.TimerCommand (Time.time, timeToEndShow, StartPlay));
	}



	public void StartPlay()
	{
		SetMonsterState (MonsterState.Idle);

		GameplayController.Instance.SetState(GameplayController.GameState.SegmentIdle);
		Timer.Instance.Remove (StartPlay);
//		GetComponent<Animation> ().CrossFade ("Monster Idle");

		Timer.Instance.Create (new Timer.TimerCommand (Time.time, GameplayController.Instance.ShowupBetweenLetterDelay, ShowupLetter));
	}

	void ShowupLetter()
	{
		LetterController[] letters =GameplayController.Instance.AllLetters;
		foreach (LetterController letter in letters) {
			if (!letter.IsShownup()) {
				letter.Showup ();
				return;
			}
		}
		Timer.Instance.Remove (ShowupLetter);
	}

	public void OnPointerEnter (PointerEventData eventData)
	{
		IsMouseOver = true;
	}

	public void OnPointerDown (PointerEventData eventData)
	{
		IsMouseOver = true;
	}

	public void OnPointerExit (PointerEventData eventData)
	{
		IsMouseOver = false;
	}

	public void OnPointerUp (PointerEventData eventData)
	{
		IsMouseOver = false;
	}


	void HoleButtonController_onPointerClick (PointerEventData eventData)
	{
		idleStateTimer = 0;
		if(animController == null) animController = GameObject.Find ("monster").GetComponentInChildren<Animator> ();		

/*
 * what is it IdleState 7
*/
//		animController.SetInteger ("IdleState", 7);
	}

	public void CollectSelectedLetters()
	{
		LetterController[] letters = GameplayController.Instance.AllLetters;
		List<LetterController> selectedLettersToCollectList = new List<LetterController> ();
		foreach (LetterController letter in letters) {
			
			if (letter.State == LetterController.LetterState.Selected) {
				selectedLettersToCollectList.Add (letter);
				letter.SetState (LetterController.LetterState.WaitingForMonster);
			}
		}
		SortByTimeAndEnqueue (selectedLettersToCollectList);
	}

	void SortByTimeAndEnqueue(List<LetterController> selectedLettersToCollectList)
	{
		mSelectedLettersToCollectQueue = new Queue<LetterController> ();
		selectedLettersToCollectList.Sort(delegate(LetterController letter1, LetterController letter2) { return letter1.TimeSelected.CompareTo(letter2.TimeSelected); });
		foreach (LetterController letter in selectedLettersToCollectList) {
			mSelectedLettersToCollectQueue.Enqueue (letter);
		}
	}

	public void EatBooster(BoosterController booster, LetterController dragedLetter)
	{
//		Debug.Log ("EatBooster " + booster.Model.Type);
		switch (booster.Model.Type) {
			case Booster.BoosterType.FireWrongLetter:
				GameplayController.Instance.DoFireBooster (booster, dragedLetter);
				break;
			case Booster.BoosterType.FreezeTime:
				GameplayController.Instance.DoFreezeBooster ();
				break;
			case Booster.BoosterType.LoseSegment:
				GameplayController.Instance.SegmentLose ();
				break;
			case Booster.BoosterType.MagnetLetter:
				GameplayController.Instance.DoMagnetBooster(booster, dragedLetter);
				break;
			case Booster.BoosterType.SlowMovment:
				GameplayController.Instance.SlowMovmentBooster(booster, dragedLetter);
				break;
			case Booster.BoosterType.ShowCallout:
				GameplayController.Instance.ShowCalloutBooster(booster, dragedLetter);
				break;
			case Booster.BoosterType.Shield:
				GameplayController.Instance.ShieldBooster(booster, dragedLetter);
				break;


			case Booster.BoosterType.BonusLetter:
				//booster.addScorebubble (600);
				GameplayController.Instance.DoBounsLetterBooster (booster);
				break;
		}
		booster.Eaten ();
		booster.PlaySound ();
	}

	public void EatBadBooster(BoosterController booster)
	{
		SetMonsterState (MonsterState.EatBad);
		Common.Instance.AddNonPauseAction (BadBooster);
	}

	void BadBooster()
	{

		GameplayController.Instance.SetState(GameplayController.GameState.SegmentIdle);

		GameplayController.Instance.BadBooster();
	}

	void EatBadLetter()
	{
		SetMonsterState (MonsterState.EatBad);

//		Debug.Log ("EatBadLetter " + mCurrentLetterInMouth.text.text);
		mCurrentLetterInMouth.Spilt();
		Common.Instance.AddNonPauseAction (SegmentLose);
	}

	void SegmentLose()
	{
		GameplayController.Instance. SegmentLose ();
	}




	public void Eat (LetterController letter)
	{
		if (animController.GetInteger ("EatState") != 1) {
			return;
		}
		GameplayController.Instance.SetState(GameplayController.GameState.EatingLetter);
		mCurrentLetterInMouth = letter;


		if (letter.GetType() == typeof(BoosterController)) {
/*			
			// added by Tzahi
			EatBadBooster (letter as BoosterController);
			AudioController.Instance.PlaySound ( SoundWrongAnswer );
			SetMonsterState (MonsterState.Sad);
			return; 
*/
			EatBooster (letter as BoosterController, null);
		}
		else if (IsGoodLetter (letter)) {
			EatGoodLetter (letter);

			if (mNeededLettersAnimation != null) {
				mNeededLettersAnimation.UnMarkFirstLetter ();
			}
		} 
		else {
			EatBadLetter ();
			AudioController.Instance.PlaySound ( SoundWrongAnswer );	
			AudioController.Instance.PlaySound ( SoundEat );
			SetMonsterState (MonsterState.Finished);

			return; // don't continue eating. We lose everything.
		}

		if (mSelectedLettersToCollectQueue.Count > 0) {
			GameplayController.Instance.SetState(GameplayController.GameState.CollectLetters);
			SetMonsterState (MonsterState.Eating);

			//PlayMouthAnimation (MouthOpenSprites);
			//PlayEyeAnimation (EyeOpenSprites);
		} 
		else {	
			AudioController.Instance.PlaySound ( SoundCorrectAnswers[UnityEngine.Random.Range(0, SoundCorrectAnswers.Length)] );		
			AudioController.Instance.PlaySound ( SoundEat );

			SetMonsterState (MonsterState.EatGood);
			GameplayController.Instance.SetState(GameplayController.GameState.SegmentIdle);

			if (GameplayController.Instance.CheckIfSegmentWin (mCurrentLetterInMouth)) {
				AudioController.Instance.PlaySound (SoundCorrentLetterFinish, .35f);
				SetMonsterState (MonsterState.Finished);
			} else {
				AudioController.Instance.PlaySound (SoundCorrentLetter, .35f);
			}


			//PlayMouthAnimation (MouthIdleSprites);
			//PlayEyeAnimation (EyeIdleSprites);
		}
	}

	public bool IsGoodLetter(LetterController letter)
	{
		return IsGoodLetter (letter, requiredLetterIndex);
	}
	public bool IsGoodNextLetter(LetterController letter, int indexToAdd)
	{
		return IsGoodLetter (letter, requiredLetterIndex + indexToAdd);
	}

	bool IsGoodLetter(LetterController letter, int letterIndex)
	{
		if (GameplayController.Instance.CurrentSegment.MonsterRequiredLetters.Length <= letterIndex) {
			return false;
		}

		switch (GameplayController.Instance.CurrentLevel.monsterInputType) {
		case MonsterInputType.Letter:
		case MonsterInputType.LetterInWord:
		case MonsterInputType.SoundLetter:
			//			if (letter.value == GameplayController.Instance.CurrentSegment.MonsterRequiredLetters[0]) { // correct letter
			if (letter.stone.value == GameplayController.Instance.CurrentSegment.MonsterRequiredLetters[0]) { // correct letter
				return true;
			} else { // bad letter
				return false;
			}
		case MonsterInputType.Word:
		case MonsterInputType.SoundWord:
			//return (letter.value == GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [requiredLetterIndex]);

			return (letter.stone.value == GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [letterIndex]);
/*		case MonsterInputType.SoundWord:
			return (letter.stone.value == GameplayController.Instance.CurrentSegment.MonsterRequiredLetters [letterIndex]);
*/
		}
		return false;
	}


	void EatGoodLetter(LetterController letter)
	{
		int scoreToadd = 0;

		if (GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.Word || GameplayController.Instance.CurrentLevel.monsterInputType == MonsterInputType.SoundWord) {
			requiredLetterIndex++;

			if (letter.numSubLetters > 0) {
				scoreToadd = GameplaySettings.LetterInWordComboScore;
			} else {
				scoreToadd = GameplaySettings.LetterScore;
			}
		}
		else
		{
			if (GameplayController.Instance.PreviousState == GameplayController.GameState.CollectLetters) {
				scoreToadd = GameplaySettings.LetterComboScore;
			} else {
				// changed by Tzahi

				if (letter.numSubLetters > 0) {
						scoreToadd = GameplaySettings.LetterInComboScore * (letter.numSubLetters + 1);
				} else {
					scoreToadd = GameplaySettings.LetterScore;
				}

				//GameplayController.Instance.CurrentLevelScoreToFlush = 100;
			}
			GameplayController.Instance.isSegmentComplete = true;

		}

		GameplayController.Instance.AddLevelScoreToFlush = scoreToadd;
//		GameplayController.Instance.IncreaseLevelScore(scoreToadd);


		// delete from Tzahi
//		GameplayController.Instance.CountdownCounter = 0;

		mCurrentLetterInMouth.Eaten();
	}


	void OnEnable(){
//		getCanvasGroup.interactable = false;
	}

	void OnDisable()
	{
		CancelInvoke ();
		Timer.Instance.Remove (ShowupLetter);
		Timer.Instance.Remove (StartPlay);
		holeButtonController.onPointerEnter -= OnPointerEnter;
		holeButtonController.onPointerDown -= OnPointerDown;
		holeButtonController.onPointerExit -= OnPointerExit;
		holeButtonController.onPointerUp -= OnPointerUp;
		holeButtonController.onPointerClick -= HoleButtonController_onPointerClick;
	}

	public void SetMonsterState(MonsterState monsterState)
	{
		if (animController == null) {
			var obj = GameObject.Find ("monster");
			if (obj != null) {
				animController = obj.GetComponentInChildren<Animator> ();
			}
			//animController = GameObject.Find ("monster").GetComponentInChildren<Animator> ();
		}
		if (this.monsterState == monsterState && monsterState != MonsterState.Idle)
			return;


		this.monsterState = monsterState;

		idleStateTimer = 0;


		switch (monsterState) {
		case MonsterState.Idle:
			animController.SetInteger ("IdleState", 0);
			animController.SetInteger ("EmotionState", 0);
			animController.SetInteger ("EatState", 0);
			break;

		case MonsterState.Happy:
			animController.SetInteger ("IdleState", 0);
//			animController.SetInteger ("EmotionState", 2);
			if (monster != null) {
				int state = monster.HappyStates [UnityEngine.Random.Range (0, monster.HappyStates.Count)];
				animController.SetInteger ("EmotionState", state);
			}
			break;
		case MonsterState.Sad:
			animController.SetInteger ("IdleState", 0);
//			animController.SetInteger ("EmotionState", 3);
			if (monster != null) {
				int state = monster.SadStates [UnityEngine.Random.Range (0, monster.SadStates.Count)];
				animController.SetInteger ("EmotionState", state);
			}
			break;
		case MonsterState.Eating:
			animController.SetInteger ("EatState", 1);
			animController.SetInteger ("IdleState", 0);
			break;
		case MonsterState.EatGood:
//			animController.SetInteger ("EatState", 2);
			if (monster != null) {
				int state = monster.EatStates [UnityEngine.Random.Range (0, monster.EatStates.Count)];

				animController.SetInteger ("EatState", state);
			}
			break;
		case MonsterState.EatBad:
			//int state = UnityEngine.Random.Range (3, 5);
			if (monster != null) {
				int state = monster.NoEatStates [UnityEngine.Random.Range (0, monster.NoEatStates.Count)];

				animController.SetInteger ("EatState", state);
			}
			break;
		case MonsterState.Finished:
//			animController.SetInteger ("EatState", 0);
//			animController.SetInteger ("IdleState", 0);
			break;

		}
	}


	public void hideCallout()
	{
		if (ShowPartical != null) {
			ShowPartical.SetActive (false);
		}

		if (HidePartical != null) {
			HidePartical.SetActive (true);
		}
		Invoke ("hide2", 0.5f);
	}


	CanvasGroup cg;
	CanvasGroup getCanvasGroup
	{
		get
		{ 
			if (cg == null) {
				cg = bubbleImage.gameObject.AddComponent<CanvasGroup> ();
			}
			return cg;
		}
	}




	void hide2()
	{
		if (bubbleImage != null && bubbleImage.gameObject != null) {
			if (GameplayController.Instance.CurrentLevel.hideCallout == 0) {
				bubbleImage.gameObject.SetActive (false);
				getCanvasGroup.interactable = false;

			} else if (GameplayController.Instance.CurrentLevel.hideCallout > 0) {
				StartCoroutine (Blink (GameplayController.Instance.CurrentLevel.hideCallout));
			}
		}
	}


	public void reshowCallout()
	{
		if (GameplayController.Instance.CurrentLevel.hideCallout > 0 && bubbleImage.gameObject.activeSelf == false) {
			bubbleImage.gameObject.SetActive (true);
			getCanvasGroup.interactable = true;
			StartCoroutine (
				Blink (
					GameplaySettings.BoosterShowCalloutTimes
				)
			);
		}
	}


	IEnumerator Blink(int times)
	{
		int count = 0;

		float minAlpha = 0.2f;
		float i = 0.025f;

		while(count < times) {
			count++;
			while (getCanvasGroup.alpha > minAlpha) {
				yield return new WaitForSeconds(0.01f);
				getCanvasGroup.alpha = getCanvasGroup.alpha - i;
			}
			yield return new WaitForSeconds(UnityEngine.Random.Range(0f, 0.2f));
			while (getCanvasGroup.alpha < 1) {
				yield return new WaitForSeconds(0.01f);
				getCanvasGroup.alpha = getCanvasGroup.alpha + i;
			}
			yield return new WaitForSeconds(UnityEngine.Random.Range(0f, 0.2f));
		}
		while (getCanvasGroup.alpha > 0) {
			yield return new WaitForSeconds(0.01f);
			getCanvasGroup.alpha = getCanvasGroup.alpha - i;
		}

		bubbleImage.gameObject.SetActive (false);
		getCanvasGroup.interactable = false;
		getCanvasGroup.alpha = 1;
	}

}
