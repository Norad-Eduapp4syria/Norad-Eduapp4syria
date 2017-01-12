using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class StartButton : MonoBehaviour
{
	enum StepColors
	{
		t1,
		t2,
		t3,
		t4
	}

/*
	public Sprite IconGreen;
	public Sprite IconOrange;
	public Sprite IconRed;

	public AudioClip SoundGreen;
	public AudioClip SoundOrange;
	public AudioClip SoundRed;

	public Vector2 PositionIn;
	public Vector2 PositionOut;
*/
	StepColors currentColor;
//	Vector2 currentPosition;

//	bool slidingIn = true;

	bool isActive = false;

	// Use this for initialization
	void Start () {

//		transform.position = PositionOut;
//		currentPosition = PositionOut;
	}
	
	// Update is called once per frame
	void Update ()
	{
//		transform.position = Vector2.MoveTowards (transform.position, currentPosition, 1000 * Time.deltaTime);	
		//Jonathan

		if (GameplayController.Instance.CurrentLevelIndex == 0 && (GameplayController.Instance.CurrentSegmentIndex == 0 || GameplayController.Instance.CurrentSegmentIndex == 1)) {
//			if (currentPosition.x == PositionIn.x && transform.position.x == PositionIn.x && slidingIn) {
//				if (TutorialController.Instance != null) {
					//TutorialController.Instance.PointAt (transform.localPosition);
//					slidingIn = false;
//				}
//			}
		}
		//End Jonathan
	}

	public void StartLevel()
	{
//		slidingIn = true;
		addButton ();
		Invoke ("startFirstStep", 0.1f);
	}

	public void StopLevel()
	{
		Timer.Instance.Remove (OnStepDone);
	}


	void startFirstStep()
	{
		isActive = true;
		startStep (StepColors.t1);
	}

	float stepTime
	{
		get
		{
			Segment segment = GameplayController.Instance.CurrentSegment;
			switch(currentColor)
			{
			case StepColors.t1:
				return GameplaySettings.ShuterButtonShowTime_1;
			case StepColors.t2:
				return GameplaySettings.ShuterButtonShowTime_2;
			case StepColors.t3:
				return GameplaySettings.ShuterButtonShowTime_3;
			case StepColors.t4:
				return GameplaySettings.ShuterButtonShowTime_4;
			}
			return GameplaySettings.ShuterButtonShowTime_1;
		}
	}

	void startStep(StepColors color)
	{
		currentColor = color;

		Timer.Instance.Remove (OnStepDone);
		Timer.Instance.Create (new Timer.TimerCommand (Time.time, stepTime, OnStepDone));
//		updateColor ();
	}

	void OnStepDone()
	{
		if (GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup) {
			return;		
		}

		if (currentColor == StepColors.t1)
		{
			startStep (StepColors.t2);
		}
		else if (currentColor == StepColors.t2)
		{
			startStep (StepColors.t3);
		}
		else if (currentColor == StepColors.t3)
		{
			startStep (StepColors.t4);
		}
		else if (currentColor == StepColors.t4)
		{
			playAnimation ();
//			Debug.Log ("Start Game");
		}
	}

/*
	void updateColor()
	{
		Image image = gameObject.GetComponent<Image> ();

		switch (currentColor) 
		{
		case StepColors.Green:
			if (IconGreen != null) {
				image.sprite = IconGreen;
			}
			if (SoundGreen != null) {
				AudioController.Instance.PlaySound (SoundGreen, .35f);
			}
			break;
		case StepColors.Orange:
			if (IconOrange != null) {
				image.sprite = IconOrange;
			}
			if (SoundOrange != null) {
				AudioController.Instance.PlaySound (SoundOrange, .35f);
			}
			break;
		case StepColors.Red:
			if (IconRed != null) {
				image.sprite = IconRed;
			}
			if (SoundRed != null) {
				AudioController.Instance.PlaySound (SoundRed, .35f);
			}
			break;
		}
	}
*/

	public void onClick()
	{
		if (isActive) {
			playAnimation ();
		}
	}


	void OnDisable()
	{
		Timer.Instance.Remove (OnStepDone);
	}

	void playAnimation()
	{
		Timer.Instance.Remove (OnStepDone);


		removeButton ();
		isActive = false;

		Animator animController = GameObject.Find ("monster").GetComponentInChildren<Animator> ();

		animController.SetInteger ("EatState", 0);
		animController.SetInteger ("IdleState", 0);
		animController.SetInteger ("EmotionState", 5);

		if (GameplayController.Instance.CurrentLevel.hideCallout > -1) {
			addRevinu ();
			GameplayController.Instance.CurrentActive.hideCallout ();
		}
		//Invoke ("startPlay", 1.0f);
	}

	void startPlay()
	{
		GameplayController.Instance.CurrentActive.StartPlay ();
		if (GameplayController.Instance.CurrentLevel.hideCallout > -1) {
			GameplayController.Instance.CurrentActive.hideCallout ();
		}
	}

	void addRevinu()
	{
		int score = 0;
		switch (currentColor) 
		{
		case StepColors.t1:
			score = GameplayController.Instance.IncreaseLevelScore (GameplaySettings.ShuterButtonAddScore_1);
//			GameplayController.Instance.segmentTime = GameplayController.Instance.segmentTime - (GameplayController.Instance.segmentTime / 100 * GameplaySettings.ShuterButtonDecreaseTime_1);
			break;
		case StepColors.t2:
			score = GameplayController.Instance.IncreaseLevelScore (GameplaySettings.ShuterButtonAddScore_2);
//			GameplayController.Instance.segmentTime = GameplayController.Instance.segmentTime - (GameplayController.Instance.segmentTime / 100 * GameplaySettings.ShuterButtonDecreaseTime_2);
			break;
		case StepColors.t3:
			score = GameplayController.Instance.IncreaseLevelScore (GameplaySettings.ShuterButtonAddScore_3);
//			GameplayController.Instance.segmentTime = GameplayController.Instance.segmentTime - (GameplayController.Instance.segmentTime / 100 * GameplaySettings.ShuterButtonDecreaseTime_3);
			break;
		case StepColors.t4:
			score = GameplayController.Instance.IncreaseLevelScore (GameplaySettings.ShuterButtonAddScore_4);
//			GameplayController.Instance.segmentTime = GameplayController.Instance.segmentTime - (GameplayController.Instance.segmentTime / 100 * GameplaySettings.ShuterButtonDecreaseTime_4);
			break;
		}

		if(score > 0) {
			addScorebubble (score);
		}
	}


	void addButton()
	{
//		currentPosition = PositionIn;
		gameObject.GetComponent<Button>().interactable = true;
		gameObject.GetComponent<Image> ().raycastTarget = true;
	}

	void removeButton()
	{
//		currentPosition = PositionOut;
		gameObject.GetComponent<Button>().interactable = false;
		gameObject.GetComponent<Image> ().raycastTarget = false;

	}

	void addScorebubble (int score)
	{
		if(score > 0)
		{
			GameObject GOScore = Instantiate(Resources.Load ("Gameplay/ScoreAnimation") as GameObject);
			GOScore.transform.SetParent (transform.parent, false);
			GOScore.transform.localPosition = GOScore.transform.localPosition + transform.localPosition;

			UIScoreAnimationController c = GOScore.GetComponent<UIScoreAnimationController>();
			c.Play (score);
		}
	}



}
