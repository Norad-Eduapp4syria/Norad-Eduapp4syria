using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class Tutorial : MonoBehaviour
{
	public GameObject startButton;

	public Image tutorialHandImage;

	public TutorialController.TutorialState State { get; private set; }

	public float PointingSpeedMultiplier = 1.5f;
	public float MovingSpeedMultiplier = 2f;


	float counter = 0.99f;

	LetterController[] letters;
	LetterController firstLetter;
	Vector3 initialLocation = new Vector3(0,0,0);





	Vector3 pointLocation;
	Vector3 pointAnimationStart;
	Vector3 pointAnimationEnd;


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
		if (firstLetter) {
			firstLetter.OnDrag (null);
		}


		try {
			switch (State) {
			case TutorialController.TutorialState.Pointing:
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
					counter += Time.deltaTime * PointingSpeedMultiplier;
				}
				break;

				/*case TutorialState.InGame:
				if (GameplayController.Instance.IsPause)
					break;
				print ("should work I think maybe not?");
				runningTutorial.MoveNext ();
				//State = TutorialState.Inactive;
				break;*/
			}
		} catch {
			State = TutorialController.TutorialState.Inactive;
		}
	}



	void OnDestroy()
	{
		if (letters != null) {
			foreach (LetterController letter in letters) {
				if (letter != null && letter.gameObject != null) {
					Destroy (letter.gameObject);
				}
			}
		}
		if (countToTenLetter != null && countToTenLetter.gameObject != null) {
			Destroy (countToTenLetter.gameObject);
		}
	}




	public void InitGame()
	{
		State = TutorialController.TutorialState.InGame;

		StartCoroutine (FeedGameLetter (2.5f));
	}

	public void InitCountToTenGame()
	{
		State = TutorialController.TutorialState.InGame;
		StartCoroutine (FeedCountToTenGameLetters (2f));
	}

	public void InitPettingMonster()
	{
		State = TutorialController.TutorialState.InGame;
		StartCoroutine (FeedPettingMonster (2f));
	}

	private IEnumerator FeedGameLetter(float delay = 0)
	{
		if (State == TutorialController.TutorialState.Inactive) {
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
		State = TutorialController.TutorialState.InGame;
		AudioController.Instance.PlaySound ( Resources.Load("Sounds/Voice/Instructions/feed the monster") as AudioClip ); 
		var lettersOriginal = findCorrectLetters();
		letters = new LetterController[lettersOriginal.Length];
		Transform curContainer;
		GameObject tempContainer;
		yield return new WaitForSeconds (0.75f);
		if (lettersOriginal.Length == 0) {
			TutorialController.Instance.EndTutorial ();
		}
		initialLocation = new Vector3 (lettersOriginal [0].transform.position.x, lettersOriginal [0].transform.position.y, lettersOriginal [0].transform.position.z);
		for (int l = 0; l < lettersOriginal.Length; l++)
		{
			curContainer = lettersOriginal [l].transform.parent;
			tempContainer = (GameObject)Instantiate(curContainer.gameObject, curContainer.position, curContainer.rotation, TutorialController.Instance.PanelTutorial.transform);

			foreach (Transform child in tempContainer.transform)
			{
				letters[l] = child.GetComponent<LetterController> ();
				child.transform.localScale = new Vector3 (1, 1, 1);
				Image[] images = child.GetComponentsInChildren<Image> ();
				foreach (Image image in images) {
					image.enabled = true;
				}
			}
//			letters [l].isTutorial = true;
			letters [l].gameObject.GetComponent<CanvasGroup> ().alpha = 0.5f;
			letters [l].gameObject.GetComponent<CanvasGroup> ().blocksRaycasts = false;
			letters [l].gameObject.GetComponent<CanvasGroup> ().interactable = false;

			letters[l].transform.position = lettersOriginal[l].mTargetPosition;
			letters [l].enabled = false;
		}
		Vector3 startPos, handDest;
		if (letters.Length != 0) {

			firstLetter = letters [0];

			firstLetter.isTutorial = true;
			tutorialHandImage.transform.position = firstLetter.transform.position;
			tutorialHandImage.gameObject.SetActive(true);
			foreach (Transform child in tutorialHandImage.transform) {
				child.gameObject.SetActive (true);
			}

			for (int letterIndex = 0; letterIndex < letters.Length; letterIndex++) {

				LetterController letter = letters[letterIndex];
				tutorialHandImage.enabled = true;
				startPos = tutorialHandImage.transform.position;

				handDest = letter.transform.position;// + new Vector3(0,50,0);
				for (float t = 0; t <= 1; t += GameplayController.Instance.IsPause ? 0 : Time.deltaTime / 1.5f) {
					tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * 1.5f * MovingSpeedMultiplier);
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
				yield return new WaitForSeconds (0.0f);
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


			for (float t = 0; t <= 1; t += GameplayController.Instance.IsPause ? 0 : Time.deltaTime / 1.5f) {
				tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
				letters[letters.Length-1].transform.position = tutorialHandImage.transform.position;
				yield return null;
			}
			tutorialHandImage.transform.position = handDest;

			yield return new WaitForSeconds (0.05f);

			while (GameplayController.Instance.IsPause) {
				yield return null;
			}

			//Jonathan

			//firstLetter.OnEndDrag (null);

			foreach (Transform child in TutorialController.Instance.PanelTutorial.transform) {
				foreach (Transform grandchild in child) {
					if (grandchild.GetComponent<CanvasGroup> () != null) {
						if(!grandchild.GetComponent<CanvasGroup>().interactable)
							Destroy (child.gameObject);
					}
				}
			}

			yield return FeedGameLetter (delay);
			tutorialHandImage.transform.position = handDest;
			//GameplayController.Instance.CollectLettersToMonster ();
		}
		//tutorialHandImage.gameObject.SetActive (false);
		//EndTutorial ();
	}











	Transform countToTenLetter;


	private IEnumerator FeedCountToTenGameLetters (float delay = 0)
	{
		//tutorialHandImage.gameObject.GetComponent<UIPopInOut> ().PopOut ();
		State = TutorialController.TutorialState.InGame;
		yield return new WaitForSeconds (0.05f);

		if (GameObject.Find ("LetterPrefab 1") == null)
			yield break;

		Transform letterOriginal = GameObject.Find ("LetterPrefab 1").transform;
		countToTenLetter = ((GameObject)Instantiate(letterOriginal.gameObject, letterOriginal.position, letterOriginal.rotation, letterOriginal.parent.transform)).transform;
		if (countToTenLetter != null) {
//			clone = letter;
		}
		initialLocation = new Vector3 (letterOriginal.transform.position.x, letterOriginal.transform.position.y, letterOriginal.transform.position.z);
		tutorialHandImage.transform.position = initialLocation;
		tutorialHandImage.gameObject.SetActive (true);

		countToTenLetter.gameObject.GetComponent<CanvasGroup> ().alpha = 0.5f;
		countToTenLetter.gameObject.GetComponent<CanvasGroup> ().blocksRaycasts = false;
		countToTenLetter.gameObject.GetComponent<CanvasGroup> ().interactable = false;
		countToTenLetter.GetComponent<CountTo10Letter> ().enabled = false;
		//letter.transform.position = letterOriginal.transform.position;
		Vector3 startPos, handDest;
		startPos = tutorialHandImage.transform.position;
		handDest = getMonsterMouth ();// + new Vector2(0,40);
		for (float t = 0; t <= 1; t += Time.deltaTime / 1.5f) {
			tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
			if (countToTenLetter != null) {
				countToTenLetter.transform.position = tutorialHandImage.transform.position;
			}
			if (Vector3.Distance (tutorialHandImage.transform.position, handDest) < 1f) {
				break;
			}
			yield return null;
		}
		tutorialHandImage.transform.position = handDest;
		//yield return new WaitForSeconds (0.125f);
		if (countToTenLetter != null) {
			Destroy (countToTenLetter.gameObject);
			countToTenLetter = null;
		}
		tutorialHandImage.transform.position = initialLocation;
		yield return FeedCountToTenGameLetters (delay);
		tutorialHandImage.transform.position = handDest;
	}



	private IEnumerator FeedPettingMonster(float delay = 0) {
		//tutorialHandImage.gameObject.SetActive (false);
		//tutorialHandImage.gameObject.GetComponent<UIPopInOut> ().PopOut ();
		State = TutorialController.TutorialState.InGame;
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
			tutorialHandImage.transform.position = Vector3.Lerp (startPos, handDest, t * MovingSpeedMultiplier);
			if (Vector3.Distance (tutorialHandImage.transform.position, handDest) < 1f) {
				break;
			}
			yield return null;
		}
		tutorialHandImage.transform.position = handDest;
		//yield return new WaitForSeconds (0.125f);

		yield return FeedPettingMonster (delay);
		tutorialHandImage.transform.position = handDest;
	}









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


	public void PointAt(Vector3 point, Transform parent = null){
		State =  TutorialController.TutorialState.Pointing;
		tutorialHandImage.gameObject.SetActive (true);
		if (parent == null) {
			tutorialHandImage.transform.SetParent (GameObject.Find ("Canvas").transform);
		} else {
			tutorialHandImage.transform.SetParent (parent);
		}
		tutorialHandImage.transform.localPosition = point;
		pointAnimationEnd = pointAnimationStart = point;
		pointLocation = point;
	}


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



}
