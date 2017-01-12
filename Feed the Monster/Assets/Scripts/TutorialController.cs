using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class TutorialController : MonoBehaviour {
	public static TutorialController Instance;
	public Image tutorialHandImage;
	public GameObject PanelTutorial;
	// Use this for initialization
	void Awake(){
		Instance = this;
	}
	void Start () {
		//PanelTutorial.SetActive (false);
	}

	public enum TutorialState{
		Inactive,
		InGame,
		Pointing
	}

//	public TutorialState State { get; private set; }

//	Vector3 pointLocation;
//	Vector3 pointAnimationStart;
//	Vector3 pointAnimationEnd;
//	Vector3 initialLocation = new Vector3(0,0,0);

//	float counter = .99f;
//	float PointingSpeedMultiplier = 1.5f;
//	float MovingSpeedMultiplier = 2f;

	//private IEnumerator runningTutorial;


	public GameObject startButton;

//	Animator animController;

	public Image MapBlocker;
	bool IsInMinigameTutorial = false;
	public bool GetIsInMinigameTutorial() { return IsInMinigameTutorial; }
	public void SetIsInMinigameTutorial(bool newValue) { IsInMinigameTutorial = newValue; MapBlocker.gameObject.SetActive(TutorialController.Instance.GetIsInMinigameTutorial()); }

//	private bool draggingStone = false;

//	LetterController[] letters;
	Transform clone;
//	public Transform getClone() { return clone; }

	Tutorial currentTutorial = null;

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


//	private bool running = false;

	// Update is called once per frame
	void Update () {

/*
		if (firstLetter) {
			firstLetter.OnDrag (null);
		}


		try {
			switch (State) {
			case TutorialState.Pointing:
				if (counter >= 1) { // finished animation
					if (Vector3.Distance (pointAnimationEnd, pointLocation) < 1) { // finished going to point
						foreach (Transform child in tutorialHandImage.transform) {
							child.gameObject.SetActive (true);
						}
						if (Random.value > 0.95f) {
							pointAnimationEnd = pointLocation + new Vector3 (0, 10 + Random.value * 20, 0);
							//print (pointAnimationEnd);
							counter = 0;
						}
					} else {
						pointAnimationEnd = pointLocation;
						counter = 0;
					}
					pointAnimationStart = tutorialHandImage.transform.localPosition;

				} else {
					tutorialHandImage.transform.localPosition = Vector3.Lerp (pointAnimationStart, pointAnimationEnd, counter);
					counter += Time.deltaTime*PointingSpeedMultiplier;
				}
				break;

			//case TutorialState.InGame:
			//	if (GameplayController.Instance.IsPause)
			//		break;
			//	print ("should work I think maybe not?");
			//	runningTutorial.MoveNext ();
			//		//	State = TutorialState.Inactive;
			//	break;
			}
		} catch {
			State = TutorialState.Inactive;
		}
*/
	}
		




	public void StartTutorial() {
		//initialLocation = new Vector3(findCorrectLetters()[0].transform.position.x, findCorrectLetters()[0].transform.position.y, findCorrectLetters()[0].transform.position.z);
//		State = TutorialState.InGame;
		PanelTutorial.SetActive (true);
		//tutorialHandImage.transform.SetParent(GameplayController.Instance.MonsterHoleButton.transform.parent);
		tutorialHandImage.transform.position = GameplayController.Instance.MonsterHoleButton.transform.position;
		tutorialHandImage.gameObject.SetActive (true);

		//runningTutorial = FeedLetters (2.5f);
		//StartCoroutine (runningTutorial);


		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}
		currentTutorial = gameObject.AddComponent<Tutorial> ();
		currentTutorial.tutorialHandImage = tutorialHandImage;
		currentTutorial.InitGame ();
	}

	public void StartTutorial(MiniGameController.GameType gameType){
		//initialLocation = new Vector3(findCorrectLetters()[0].transform.position.x, findCorrectLetters()[0].transform.position.y, findCorrectLetters()[0].transform.position.z);
//		State = TutorialState.InGame;
		PanelTutorial.SetActive (true);
		//tutorialHandImage.transform.SetParent(GameplayController.Instance.MonsterHoleButton.transform.parent);
		tutorialHandImage.transform.position = GameplayController.Instance.MonsterHoleButton.transform.position;
		tutorialHandImage.gameObject.SetActive (true);
			

		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}

		currentTutorial = gameObject.AddComponent<Tutorial> ();
		currentTutorial.tutorialHandImage = tutorialHandImage;


		if (gameType == MiniGameController.GameType.CountTo10) {
//			runningTutorial = FeedMinigameLetters (2f);
//			StartCoroutine (runningTutorial);

			currentTutorial.InitCountToTenGame();

		} else if (gameType == MiniGameController.GameType.MonsterPetting) {
//			runningTutorial = PetMinigameMonster (2f);
//			StartCoroutine (runningTutorial);
			currentTutorial.InitPettingMonster();
		}

		//GameplayController.Instance.IsInteractable = false; /*Jonathan*/
	}

	public void EndTutorial(){
/*
		if (State != TutorialState.Inactive) {
		
			GameplayController.Instance.IsInteractable = true;

			LetterTouchController[] ltrs = PanelTutorial.transform.GetComponentsInChildren<LetterTouchController>();
			foreach (LetterTouchController l in ltrs) {
				Destroy (l.gameObject);
			}

			firstLetter = null;

			if (runningTutorial != null) {
				if (GetIsInMinigameTutorial () && clone != null)
					Destroy (clone.gameObject);
				StopCoroutine (runningTutorial);
			}
			runningTutorial = null;
			PanelTutorial.SetActive (false);
		}
		State = TutorialState.Inactive;
*/


		tutorialHandImage.transform.SetParent (null);
		tutorialHandImage.gameObject.SetActive (false);



		if (currentTutorial != null) {
			Destroy (currentTutorial);
			currentTutorial = null;
		}


	}

	public void PointAt(Vector3 point, Transform parent = null){
//		State = TutorialState.Pointing;
		tutorialHandImage.gameObject.SetActive (true);
		if (parent == null) {
			tutorialHandImage.transform.SetParent (GameObject.Find ("Canvas").transform);
		} else {
			tutorialHandImage.transform.SetParent (parent);
		}
		tutorialHandImage.transform.localPosition = point;
//		pointAnimationEnd = pointAnimationStart = point;
//		pointLocation = point;
	}

/*
	private LetterController[] findCorrectLetters(){
		LetterController[] _letters = GameplayController.Instance.AllLetters;
		List<LetterController> correctLetters = new List<LetterController> ();
		foreach (string requiredLetter in GameplayController.Instance.CurrentSegment.MonsterRequiredLetters) {
			foreach (LetterController letter in _letters) {
				//if (letter.value == requiredLetter) {
				if (letter.stone != null) {
					if (letter.stone.value == requiredLetter) {
						correctLetters.Add (letter);
					}
				}
			}
		}

		return correctLetters.ToArray ();
	}
*/
//	LetterController firstLetter;

	/*
	private IEnumerator FeedLetters(float delay = 0)
	{
		if (State == TutorialState.Inactive) {
			yield return true;
		}


		//yield return new WaitForSeconds (delay);
		//Jonathan
		startButton = GameObject.Find("monster");
		//PointAt(startButton.transform.position + new Vector3 (0, -40, 0), startButton.transform.parent);
		PointAt(new Vector2(0, -140), startButton.transform.parent);
		//
		while (GameplayController.Instance.State != GameplayController.GameState.SegmentIdle)
			yield return null;
		//tutorialHandImage.enabled = false;
		//tutorialHandImage.gameObject.SetActive(false);
		tutorialHandImage.gameObject.GetComponent<UIPopInOut>().PopOut();
		State = TutorialState.InGame;
		AudioController.Instance.PlaySound ( Resources.Load("Sounds/Voice/Instructions/feed the monster") as AudioClip ); 
		var lettersOriginal = findCorrectLetters();
		letters = new LetterController[lettersOriginal.Length];
		Transform curContainer;
		GameObject tempContainer;
		yield return new WaitForSeconds (0.75f);
		if (lettersOriginal.Length == 0)
			EndTutorial ();
		initialLocation = new Vector3 (lettersOriginal [0].transform.position.x, lettersOriginal [0].transform.position.y, lettersOriginal [0].transform.position.z);
		for (int l = 0; l < lettersOriginal.Length; l++) {

			if (isEnd()) { yield return true; }

			//yield return new WaitForSeconds (1f);

			curContainer = lettersOriginal [l].transform.parent;
			//if (initialLocation.Equals(new Vector3(0,0,0)))
			//initialLocation = new Vector3(curContainer.position.x, curContainer.position.y, curContainer.position.z);
			tempContainer = (GameObject)Instantiate(curContainer.gameObject, curContainer.position, curContainer.rotation, PanelTutorial.transform);

			foreach (Transform child in tempContainer.transform) {
				if (isEnd()) { yield return true; }

				letters[l] = child.GetComponent<LetterController> ();
				child.transform.localScale = new Vector3 (1, 1, 1);
				Image[] images = child.GetComponentsInChildren<Image> ();
				foreach (Image image in images) {
					image.enabled = true;
				}
			}
			letters [l].isTutorial = true;
			letters [l].gameObject.GetComponent<CanvasGroup> ().alpha = 0.5f;
			letters [l].gameObject.GetComponent<CanvasGroup> ().blocksRaycasts = false;
			letters [l].gameObject.GetComponent<CanvasGroup> ().interactable = false;
			//Destroy (letters [l].gameObject.GetComponent<LetterController> ());
			letters[l].transform.position = lettersOriginal[l].mTargetPosition;
			letters [l].enabled = false;
		}
		Vector3 startPos, handDest;
		if (letters.Length != 0) {

			firstLetter = letters [0];
			clone = firstLetter.transform;
			firstLetter.isTutorial = true;
			tutorialHandImage.transform.position = firstLetter.transform.position;
			tutorialHandImage.gameObject.SetActive(true);
			foreach (Transform child in tutorialHandImage.transform) {
				child.gameObject.SetActive (true);
			}

			for (int letterIndex = 0; letterIndex < letters.Length; letterIndex++) {
				if (isEnd()) { yield return true; }
			//foreach (LetterController letter in letters) {
				LetterController letter = letters[letterIndex];
				tutorialHandImage.enabled = true;
				startPos = tutorialHandImage.transform.position;

				if (letter == null) {
					EndTutorial ();
				}

				handDest = letter.transform.position;// + new Vector3(0,50,0);
				for (float t = 0; t <= 1; t += GameplayController.Instance.IsPause ? 0 : Time.deltaTime / 1.5f) {
					if (isEnd()) { yield return true; }
					tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * 1.5f*MovingSpeedMultiplier);
					if (letter != firstLetter) {
						letters[letterIndex-1].transform.position = tutorialHandImage.transform.position;
					}	
					yield return null;
				}
				if (letterIndex > 0) {
					letters [letterIndex - 1].gameObject.GetComponent<CanvasGroup> ().alpha = 0;


					Vector3 newScale = letter.transform.localScale * GameplaySettings.LetterComboScale [letterIndex-1];
					if (newScale.x <= GameplaySettings.LetterComboMaxScale || newScale.y <= GameplaySettings.LetterComboMaxScale) {
						letter.transform.localScale = newScale;
					}


				}
				tutorialHandImage.transform.position = handDest;
				startPos = tutorialHandImage.transform.position;
				yield return new WaitForSeconds (0.1f);

				//GameObject copiedLetterObj = (GameObject)Instantiate (letter.gameObject, letter.transform.position, letter.transform.rotation, letter.transform.parent);
				//LetterTouchController copiedLetter = copiedLetterObj.GetComponent<LetterTouchController> ();
				// added by Tzahi
				if (letter == firstLetter) {
					//letter.Select ();	
					//firstLetter.OnBeginDrag (null);
					//letter.SetState(LetterController.LetterState.Tutorial);
//					draggingStone = true;
				}
				//yield return new WaitForSeconds (0.1f);
				if (isEnd()) { yield return true; }
			}

			//Jonathan
			if (letters.Length > 1) {
				Vector3 newScale2 = letters [letters.Length - 2].transform.localScale * GameplaySettings.LetterComboScale [letters.Length];
				if (newScale2.x <= GameplaySettings.LetterComboMaxScale || newScale2.y <= GameplaySettings.LetterComboMaxScale) {
					letters [letters.Length - 1].transform.localScale = newScale2;
				}
			}
			//End Jonathan(?)

			startPos = tutorialHandImage.transform.position;
			handDest = firstLetter.getMonsterMouth ();// + new Vector2(0,40);

			//animController.SetInteger("EatState", 1);
			for (float t = 0; t <= 1; t += GameplayController.Instance.IsPause ? 0 : Time.deltaTime / 1.5f) {
				if (isEnd()) { yield return true; }
				tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
				letters[letters.Length-1].transform.position = tutorialHandImage.transform.position;
				yield return null;
			}
			tutorialHandImage.transform.position = handDest;

			yield return new WaitForSeconds (0.125f);
			if (isEnd()) { yield return true; }

			while (GameplayController.Instance.IsPause) {
				yield return null;
			}

			//Jonathan

			//firstLetter.OnEndDrag (null);

			foreach (Transform child in PanelTutorial.transform) {
				if (isEnd()) { yield return true; }
				foreach (Transform grandchild in child) {
					if (isEnd()) { yield return true; }
					if (grandchild.GetComponent<CanvasGroup> () != null) {
						if(!grandchild.GetComponent<CanvasGroup>().interactable)
							Destroy (child.gameObject);
					}
				}
			}

			//animController.SetInteger("EatState", 0);
			yield return FeedLetters (delay);
			tutorialHandImage.transform.position = handDest;
			//GameplayController.Instance.CollectLettersToMonster ();
		}
		//tutorialHandImage.gameObject.SetActive (false);
		//EndTutorial ();
	}
*/

	/*
	private IEnumerator moveHandTo(Vector3 handDest){
		Vector3 startPos = tutorialHandImage.transform.position;
		for (float t = 0; t <= 1; t += GameplayController.Instance.IsPause ? 0 : Time.deltaTime / 1.5f) {
			tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t);
			yield return Vector3.Lerp (startPos, handDest, t);
		}
		tutorialHandImage.transform.position = handDest;
	}*/
/*
	private IEnumerator WaitWithPause(float time){
		float t = 0;
		while (t < time && State == TutorialState.InGame) {
			t += Time.deltaTime;
			yield return null;
		}
			
	}
*/
/*
	bool isEnd()
	{
		if (
			State == TutorialState.Inactive
			||
			firstLetter == null
			|| 
			tutorialHandImage == null
		) {
			return true;
		}
		return false;
	}
*/

/*
	private IEnumerator FeedMinigameLetters (float delay = 0)
	{
		//tutorialHandImage.gameObject.GetComponent<UIPopInOut> ().PopOut ();
		State = TutorialState.InGame;
		yield return new WaitForSeconds (0.1f);

		if (GameObject.Find ("LetterPrefab 1") == null)
			yield break;

		Transform letterOriginal = GameObject.Find ("LetterPrefab 1").transform;
		Transform letter = ((GameObject)Instantiate(letterOriginal.gameObject, letterOriginal.position, letterOriginal.rotation, letterOriginal.parent.transform)).transform;
		if(letter != null)
			clone = letter;
		initialLocation = new Vector3 (letterOriginal.transform.position.x, letterOriginal.transform.position.y, letterOriginal.transform.position.z);
		tutorialHandImage.transform.position = initialLocation;
		tutorialHandImage.gameObject.SetActive (true);

		letter.gameObject.GetComponent<CanvasGroup> ().alpha = 0.5f;
		letter.gameObject.GetComponent<CanvasGroup> ().blocksRaycasts = false;
		letter.gameObject.GetComponent<CanvasGroup> ().interactable = false;
		letter.GetComponent<CountTo10Letter> ().enabled = false;
		//letter.transform.position = letterOriginal.transform.position;
		Vector3 startPos, handDest;
		startPos = tutorialHandImage.transform.position;
		handDest = getMonsterMouth ();// + new Vector2(0,40);
		for (float t = 0; t <= 1; t += Time.deltaTime / 1.5f) {
			if (isEnd ()) {
				yield return true;
			}
			tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
			if(letter != null)
				letter.transform.position = tutorialHandImage.transform.position;
			if (Vector3.Distance (tutorialHandImage.transform.position, handDest) < 1f)
				break;
			yield return null;
		}
		tutorialHandImage.transform.position = handDest;
		//yield return new WaitForSeconds (0.125f);
		if(letter != null)
			Destroy (letter.gameObject);
		if (isEnd ()) {
			yield return true;
		}
		tutorialHandImage.transform.position = initialLocation;
		yield return FeedMinigameLetters (delay);
		tutorialHandImage.transform.position = handDest;
	}
*/
/*
	public Vector2 getMonsterMouth()
	{
		Transform to = GameObject.Find ("monster").transform.Find ("Mouth");
		Vector2 toPos = new Vector2();
		if (to == null) {
			//to = EatingMonster.transform;
			//toPos = EatingMonster.transform.position;
		} else {
			toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

			Canvas c = GameObject.Find("LetterPrefab 1").GetComponentInParent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

			toPos = new Vector2 (
				((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
				((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
			);

		}
		return toPos;
	}
*/
/*
	private IEnumerator PetMinigameMonster(float delay = 0) {
		//tutorialHandImage.gameObject.SetActive (false);
		//tutorialHandImage.gameObject.GetComponent<UIPopInOut> ().PopOut ();
		State = TutorialState.InGame;
		yield return new WaitForSeconds (0.1f);
		GameObject zone = null;
		while (zone == null) {
			zone = GameObject.Find ("Petting Zone");
			yield return new WaitForSeconds (0.1f); //Jonathan - DANGEROUS
		}
		Rect zoneBounds = zone.GetComponent<RectTransform> ().rect;
		float setY = getMonsterBody ().y ; //getMonsterMouth().y;
		initialLocation = new Vector3(zoneBounds.xMin*0.75f, setY + 0.75f*(Random.value-0.5f)*setY, 0);
		//initialLocation = new Vector3 (letterOriginal.transform.position.x, letterOriginal.transform.position.y, letterOriginal.transform.position.z);
		tutorialHandImage.transform.position = initialLocation;
		tutorialHandImage.gameObject.SetActive (true);
		tutorialHandImage.transform.SetParent (zone.transform.parent.parent);
		tutorialHandImage.transform.localScale = new Vector3 (1, 1, 1);

		Vector3 startPos, handDest;
		startPos = tutorialHandImage.transform.position;
		handDest = new Vector3(zoneBounds.xMax*0.75f, setY + 0.75f*(Random.value-0.5f)*setY, 0);
		for (float t = 0; t <= 1; t += Time.deltaTime / 1.5f) {
			if (isEnd ()) {
				yield return true;
			}
			tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
			if (Vector3.Distance (tutorialHandImage.transform.position, handDest) < 1f)
				break;
			yield return null;
		}
		tutorialHandImage.transform.position = handDest;
		//yield return new WaitForSeconds (0.125f);
		if (isEnd ()) {
			yield return true;
		}
		yield return PetMinigameMonster (delay);
		tutorialHandImage.transform.position = handDest;
	}
*/
/*
	public Vector2 getMonsterBody()
	{
		Transform to = GameObject.Find ("monster").transform.Find ("Monster");
		Vector2 toPos = new Vector2();
		if (to == null) {
			//to = EatingMonster.transform;
			//toPos = EatingMonster.transform.position;
		} else {
			toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

			Canvas c = GameObject.Find("Panel - Mini Games").GetComponentInParent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

			toPos = new Vector2 (
				((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
				((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
			);

		}
		return toPos;
	}
*/
}
