using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LetterTracingGame : BaseMiniGame
{
	public static LetterTracingGame Instance;


	public TR_GameManager GameManager;

	public Image Title;
	public AudioClip StartTraceingSound;

	public Queue<GameObject> LettersForTesting2;

	public List<GameObject> LettersForTesting;

	public List<GameObject> LettersGroup_1;
	public List<GameObject> LettersGroup_2;
	public List<GameObject> LettersGroup_3;
	public List<GameObject> LettersGroup_4;
	public List<GameObject> LettersGroup_5;
	public List<GameObject> LettersGroup_6;

	public LetterTracingStone[] Stones;



	RectTransform _rectTransform;
	Queue<GameObject> shapesQueue = new Queue<GameObject> ();
	int currentStone;
	GameObject FeedbackGO;


	RectTransform rectTransform {
		get
		{ 
			if (_rectTransform == null) {
				_rectTransform = (RectTransform)transform;
			}
			return _rectTransform;
		}
	}

	void Awake()
	{
		Instance = this;
	}

	// Use this for initialization
	void Start () {
		GameManager.onComplete = complete;
	}

	void OnEnable()
	{
		StartMiniGame ();
		if (Title != null) {
			Title.gameObject.SetActive (true);
			//Title.gameObject.GetComponent<UIPopInOut> ().PopIn ();
		}
		GameManager.DestroyOldShape ();

		UpdateLettersForGroup ();
		FillStones ();

		Invoke("initStones", 1.5f);
		Analitics.Instance.treckScreen ("Letter Tracing - Profile: " + UsersController.Instance.CurrentProfileId);
	}

	void initStones ()
	{
		if (Title != null) {
			Title.gameObject.GetComponent<UIPopInOut> ().PopOut ();
		}
		Invoke("LoadNextStone", 1.5f);
	}

	void OnDisable() {
		CancelInvoke ();
		if (Title != null) {
			Title.gameObject.SetActive (false);
		}
		if (FeedbackGO != null) {
			Destroy (FeedbackGO);
		}
	}


	// Update is called once per frame
	void Update () {
		
	}

	public override void init (Monster monster)
	{
		base.init (monster);
	}

	public void complete() 
	{
		LetterTracingStone lts = Stones [currentStone];
		lts.CloseGame ();

	}

	void UpdateLettersForGroup()
	{
		int currentGroup = 6;


		if (UIController.Instance != null && UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS && shapesQueue.Count > 2) {
			return;
		}

		if(UserInfo.Instance != null) {
			currentGroup = UserInfo.Instance.GetLastLetterGroup();
		}

		List<GameObject> newList = new List<GameObject>();


		if(UIController.Instance != null && UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS && LettersForTesting.Count > 0){
			newList.AddRange (LettersForTesting);
		} else {
			if(currentGroup >= 1) {
				newList.AddRange (LettersGroup_1);
			}
			if(currentGroup >= 2) {
				newList.AddRange (LettersGroup_2);
			}
			if(currentGroup >= 3) {
				newList.AddRange (LettersGroup_3);
			}
			if(currentGroup >= 4) {
				newList.AddRange (LettersGroup_4);
			}
			if(currentGroup >= 5) {
				newList.AddRange (LettersGroup_5);
			}
			if(currentGroup >= 6) {
				newList.AddRange (LettersGroup_6);
			}
		}

		GameObject[] shapes = newList.ToArray ();

		shapesQueue.Clear (); 
		System.Random rng = new System.Random ();
		int n = shapes.Length;
		while (n > 1) 
		{
			int k = rng.Next(n--);
			GameObject temp = shapes[n];
			shapes[n] = shapes[k];
			shapes[k] = temp;
		}
		foreach(GameObject go in shapes )
		{
			if (go != null) {
				shapesQueue.Enqueue (go);
			}
		}
	}

	void FillStones ()
	{
		currentStone = 0;

		int stoneCount = 0;

		foreach (LetterTracingStone stone in Stones) {
			foreach(Transform t in stone.transform) {
				Destroy (t.gameObject);
			}
			GameObject origShape = shapesQueue.Dequeue ();
			GameObject shapeGameObject = Instantiate (origShape, stone.transform, false) as GameObject;
			shapeGameObject.transform.localPosition = origShape.transform.localPosition;
			shapeGameObject.name = origShape.name;
			shapeGameObject.transform.localScale = origShape.transform.localScale;

//			stone.Reset (stoneCount);
			stoneCount++;
		}
	}

	void LoadNextStone()
	{
		if (currentStone < Stones.Length) {
			
			LetterTracingStone lts = Stones [currentStone];
			lts.onCompleteGame = onStoneLocated;
			lts.onCompleteIdle = onStoneHided;

			lts.OpenGame ();
		} else {

//			if (MiniGameController.Instance != null) {
//				MiniGameController.Instance.ResetEmotion ();
//			}
			if (animController != null) {
				animController.SetBool ("IsSad", false);
				animController.SetInteger ("EmotionState", 1);
			}

			Analitics.Instance.treckScreen ("Letter Tracing Done - Profile: " + UsersController.Instance.CurrentProfileId);
			EndMiniGame ();
		}
	}

	void onStoneLocated() {
		LetterTracingStone lts = Stones [currentStone];
		lts.onCompleteGame = null;

		GameManager.loadShape (lts.shape);
		lts.shape.init ();
		if (AudioController.Instance) {
			AudioController.Instance.PlaySound (StartTraceingSound);
		}
	}

	void onStoneHided()
	{
		LetterTracingStone lts = Stones [currentStone];
		lts.onCompleteIdle = null;
		lts.shape.DisableTracingHand ();

		currentStone++;

		ShowPositiveFeedback ();

		if (animController != null) {
			animController.SetInteger ("EmotionState", 1);
		}
		Invoke("sd", 0.5f);
	}

	void sd() {
		if (animController != null) {
			animController.SetInteger ("EmotionState", 0);
		}
		Invoke("LoadNextStone", 1.0f);
	}





	void ShowPositiveFeedback()
	{
		string fileName = AudioController.Instance.PlayFeedback ("positive");

		Debug.Log ("Feedback added" + currentStone.ToString());


		if (FeedbackGO != null) {
			Destroy (FeedbackGO);
		}
		if (GameplayController.Instance.FeedbackGO  != null) {
			FeedbackGO = Instantiate(GameplayController.Instance.FeedbackGO, transform) as GameObject;
			FeedbackGO.transform.localScale = new Vector3 (1f, 1f, 1f);
			Feedback fb = FeedbackGO.GetComponent<Feedback> ();
			fb.init (fileName);
		}
	}

}
