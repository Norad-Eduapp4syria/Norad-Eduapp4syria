using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using System.Linq;
using UnityEngine.SceneManagement;
using UnityEngine.EventSystems;
using System.Text;

public class GameplayController : MonoBehaviour {

	public static GameplayController Instance;
	//	[System.Serializable]
//	public struct LetterRecognitionStrcut{
//		public string Letter;
//		public string Variants; // seperated with commas
//	}

	public struct GameplayPositionStruct {
		public int LevelIndex;
		public int SegmentIndex;
		public int LevelScore;
		public Booster SelectedBooster;


		public bool[] SucsessSegments;

		public bool AllowMaxStars;

		public int SucsessSegment
		{
			get
			{
				int count = 0;
				if (SucsessSegments != null) {
					foreach (bool sucsess in SucsessSegments) {
						if (sucsess) {
							count++;
						}
					}
				}
				return count;
			}
		}


		public int LevelStars
		{
			get
			{
				int count = SucsessSegment;

				if 		  (count >= 5 && AllowMaxStars == true) {
					return 3;
				} else if (count >= 3) {
					return 2;
				} else if (count >= 2) {
					return 1;
				}
				return 0;
			}
		}
	}


	public enum GameState {
		None,
		LoadLevel,
		LoadSegment, 
		ThoughtBubbleAnimation,
		SegmentIdle, //Playing the game!!
		CollectLetters,
		LetterComingToMonster,
		EatingLetter,
		SegmentWinAnimation,
		SegmentLoseAnimation,
		LevelWinAnimation,
//		LevelLoseAnimation,
		EndSegment

		//		MemorizingSegment, // Traffic light
		//		ShowNeededInputAnimation,
		//		LettersPopupAnimation,
		//		ReactingToLetter,
		//		DisplayBadLetter,
		//		LettersDestroyAnimation,

	}

//	public TextAsset RecognitionVariantsText;

	[HideInInspector]
	public MonsterCalloutController CurrentActive;

	public int NumOfLevels;
	public Level DefaultLevelTempletes;

	public GameObject[] LetterPrefab_1;
	public GameObject[] LetterPrefab_2;

	public GameObject[] LettersLocations;
	public GameObject LettersPanel;
	public GameObject MonsterPanel;

	public GameObject BoosterPrefab;
	public Material MouseTrailMaterial;
	public Text LevelScoreText;
	public UISegmentsDisplay SegmentsDisplay;

	public UIScoreAnimationController ScoreAnimation;

	public float CountdownCounter { get; set; }
	public float ShowupBetweenLetterDelay;

	[HideInInspector]
	public bool IsPause;

	[HideInInspector]
	public bool IsPausePopup { get; set; }

	public bool IsInteractable = true;

	public Button MonsterHoleButton;

	public GameState State { get; private set; }
	public GameState PreviousState { get; private set; }




	public GameObject FeedbackGO;

	public GameObject LevelBackground;

	public StartButton startButton;

	[HideInInspector]
	public Vector2 LauncherPoint;


	public GameObject BonusGameHolder;
//	public GameObject treasureChestPrefabs;
//	public GameObject bonusPuzzlePrefabs;



	[HideInInspector]
	public bool ReaplaceBackground;

	bool _reaplaceBackground_SelectMonster = true;
	public bool ReaplaceBackground_SelectMonster { 
		set {
			_reaplaceBackground_SelectMonster = value;
		}
		get { 
			return _reaplaceBackground_SelectMonster;
		}
	}


	public AudioClip SoundTimeup;
	public AudioClip SoundMargeLetters;
	public AudioClip SoundCancelDrag;
	public AudioClip SoundSpitsMeal;
	public AudioClip SoundScoreCount;



	public string[] backgrounds;


	[HideInInspector]
	public float segmentTime;

	bool isTimeup;

	GameplayPositionStruct mGameplayPosition;

	GameObject ltrPrefab = null;


//	bool impatient = false;
	int ShowTreasureChestInSegment = -1;
	float _currentLevelScoreToFlush;

	int mTargetScore;

	TreasureChest treasureChestPopup;
	BonusPuzzle bonusPuzzlePopup;


	public float calcSpeed(float mainSpeed)
	{
		if (slowBoosterDuration > 0) {
			return mainSpeed * 0.5f;
		}
		return mainSpeed;
	}

	public int AddLevelScoreToFlush
	{
		get { return (int)_currentLevelScoreToFlush; }
		set {
			float toadd = value;
			toadd += (((float)value) * (GameplaySettings.LevelScoreFactor * (this.CurrentLevelIndex + 1)));
			_currentLevelScoreToFlush += toadd;
		}
	}
	public int IncreaseLevelScore(int value, bool addFactor = true)
	{
		float toadd = value;

		if (addFactor == true) {
			toadd += (((float)value) * (GameplaySettings.LevelScoreFactor * (this.CurrentLevelIndex + 1)));
		}
		mGameplayPosition.LevelScore += (int)toadd;

		//LevelScoreText.text = mGameplayPosition.LevelScore.ToString ();

		return (int)toadd;
	}


	public Level CurrentLevel;
	/*
	public Level CurrentLevel
	{
		get {
			return XMLController.Instance.getLevel(mGameplayPosition.LevelIndex);
			//return Levels [mGameplayPosition.LevelIndex];
		}
	}
*/
	public Segment CurrentSegment
	{
		get {
			return CurrentLevel.Segments [mGameplayPosition.SegmentIndex];
//			return XMLController.Instance.getLevel(mGameplayPosition.LevelIndex).Segments [mGameplayPosition.SegmentIndex];
		}
	}

	public int SucsessSegment
	{
		get {
			return mGameplayPosition.SucsessSegment;
		}
	}

	void updateSegmentTime()
	{
		if (CurrentSegment.SegmentTime > 0) {
			segmentTime = CurrentSegment.SegmentTime;
		} else if (CurrentLevel.SegmentTime > 0) {
			segmentTime = CurrentLevel.SegmentTime;
		} else {
			segmentTime = GameplaySettings.CountdownDefault;
		}
	}

	void Countdown(float t)
	{
		if (GameplayController.Instance.IsPause || GameplayController.Instance.IsPausePopup)
			return;


		LetterController[] letters = AllLetters;
//		MonsterCalloutController monster = Component.FindObjectOfType<MonsterCalloutController> ();

//		if (CountdownCounter >= GameplaySettings.Countdown * GameplaySettings.CountdownWarningLetterRatio) {
		if (CountdownCounter >= segmentTime * GameplaySettings.CountdownWarningLetterRatio) {
			if (NeedShowLetterWarning()) {
				foreach (LetterController letter in letters) {
					if (CurrentLevel.monsterInputType == MonsterInputType.Letter || CurrentLevel.monsterInputType == MonsterInputType.LetterName || CurrentLevel.monsterInputType == MonsterInputType.LetterInWord || CurrentLevel.monsterInputType == MonsterInputType.SoundLetter || CurrentLevel.monsterInputType == MonsterInputType.SoundLetterName) {
						if (letter.text.text == CurrentSegment.MonsterRequiredLetters [0]) {
							if (letter.State == LetterController.LetterState.Idle && NeedShowLetterWarning ())
								letter.SetState (LetterController.LetterState.Warning);
						} else {
							if (letter.State == LetterController.LetterState.Warning)
								letter.SetState (LetterController.LetterState.Idle);
						}
					} else if (CurrentLevel.monsterInputType == MonsterInputType.Word || CurrentLevel.monsterInputType == MonsterInputType.SoundWord /*Jonathan*/){
						for (int i=0; i<CurrentSegment.MonsterRequiredLetters.Length; i++) {
							if (letter.text.text == CurrentSegment.MonsterRequiredLetters[i]) {
								if (i > 0) {
									for (int k=i; k>=0; k--) {
										if (k != i && FindLetterInGame(CurrentSegment.MonsterRequiredLetters[k]) == null) {
											if (letter.State == LetterController.LetterState.Idle && NeedShowLetterWarning ())
												letter.SetState (LetterController.LetterState.Warning);
										}
									}
								} else {
									if (letter.State == LetterController.LetterState.Idle && NeedShowLetterWarning ())
										letter.SetState (LetterController.LetterState.Warning);
								}
							}
						}
					}
				}
			}	
		} else {
			foreach (LetterController letter in letters) {
				if (letter.State == LetterController.LetterState.Warning)
					letter.SetState (LetterController.LetterState.Idle);
			}
		}

//		if (CountdownCounter >= GameplaySettings.Countdown) {
		if (CountdownCounter >= segmentTime) {
//			Debug.Log ("Countdown");
			Timer.Instance.Remove (Countdown );
//			AudioController.Instance.PlaySound (SoundTimeup, .5f);

			this.mGameplayPosition.AllowMaxStars = false;

			if(isSegmentComplete == true) {
				GameplayController.Instance.SegmentWin();
				Invoke ("OnEatAnimationEnd", 1.0f);
			} else {
				GameplayController.Instance.SegmentLose ();
				Invoke ("OnEatAnimationEnd", 0.6f);
			}
		} else {
			// use for freeze timer booster
			if (segmentTime - CountdownCounter <= GameplaySettings.ShowTimeupSeconds && !isTimeup) {
				isTimeup = true;
				AudioController.Instance.PlaySound (SoundTimeup, true);
			}
			if (isFreezeTimer == false) {
				CountdownCounter += t;//Time.deltaTime;
				// start added by Tzahi
				updateTimerSlider ();
			}

			if(slowBoosterDuration > 0) {
				slowBoosterDuration -= t;//Time.deltaTime;
			}

			if(shildBoosterDuration > 0) {
				shildBoosterDuration -= t;//Time.deltaTime;
			}


		}
		// end added by Tzahi
	}

	void updateTimerSlider()
	{
		float timePrecent = CountdownCounter / (segmentTime / 100);
		timerSlider.value = 100 - ((timePrecent > 100) ? 100 : timePrecent);

		Vector3 v;
		{
			v = timerTicks1.transform.rotation.eulerAngles;
			v.z -= 1;
			timerTicks1.transform.rotation = Quaternion.Euler (v);
		}
		{
			v = timerTicks2.transform.rotation.eulerAngles;
			v.z -= 2;
			timerTicks2.transform.rotation = Quaternion.Euler (v);
		}
	}

	bool NeedShowLetterWarning()
	{
		LetterController[] letters = AllLetters;
		foreach (LetterController letter in letters) {
			if (letter.State == LetterController.LetterState.Warning)
				return false;
		}
		return true;
	}

	void Awake()
	{
		Instance = this;
	}

	public void SetState(GameState state)
	{
		PreviousState = State;
		if ((state == GameState.CollectLetters || state == GameState.SegmentIdle) && IsPause || IsPausePopup)
			return;
		
		State = state;
	}

	void OnDisable() {
		DestroyBonusPuzzlePopup ();
	}

	// Use this for initialization
	void Start () {
//		Init ();
	}

	void Init()
	{
//		GameplayController.Instance.CurrentLevelIndex = Mathf.Min(GameAssets.CurrentLevelIndex, GameAssets.Instance.NumOfLevels - 1);
	}

	public void SetCurrentBooster(Booster booster)
	{
		mGameplayPosition.SelectedBooster = booster;
	}

	public void FlushLevelScore()
	{
		mGameplayPosition.LevelScore += (int)_currentLevelScoreToFlush;

//		LevelScoreText.text = mGameplayPosition.LevelScore.ToString ();
		_currentLevelScoreToFlush = 0;
	}

	void SetSegmentToShowTreasureChest()
	{
		ShowTreasureChestInSegment = -1;
		if (mGameplayPosition.LevelIndex != 0) {
			if (mGameplayPosition.LevelIndex == 1 || UnityEngine.Random.value <= GameplaySettings.TreasureChest_ChanceToShow) {
				ShowTreasureChestInSegment = Random.Range (1, CurrentLevel.Segments.Length);
			}
		}
//		ShowTreasureChestInSegment = 0;
	}

	public void LoadLevel()
	{
		int levelId = GameAssets.CurrentLevelIndex;

		ClearGameplay ();
		CurrentLevel = XMLController.Instance.getLevel(levelId);
		if (CurrentLevel.shuffleSegment) {
			CurrentLevel.ShuffleSegments ();
		}

//		Debug.Log ("Load Level " + levelIndex);
		SetState(GameState.LoadLevel);
		mGameplayPosition.LevelScore = 0;
		mGameplayPosition.LevelIndex = levelId;
		mGameplayPosition.SegmentIndex = -1;
//		mGameplayPosition.SucsessSegment = 0;
		mGameplayPosition.SucsessSegments = new bool[5];

		mGameplayPosition.AllowMaxStars = true;



		LevelScoreText.text = "0";

		SetSegmentToShowTreasureChest ();

		if(ReaplaceBackground_SelectMonster) {
			LoadBackground ();
			ReaplaceBackground_SelectMonster = false;
		}
		UpdateLauncherPoint ();
		UpdateCurrentMonster ();
		MouseTrailMaterial.color = CurrentLevel.ActiveTintColor;
		Common.Instance.AddNonPauseAction(LoadFirstSegment);

//		LevelScoreText.text = mGameplayPosition.LevelScore.ToString();

		mGameplayPosition.SelectedBooster = null;

		SegmentsDisplay.Init (CurrentLevel.Segments.Length);
		/*if (UserInfo.Instance.CollectedFriends.Length > 0) {
			UIController.Instance. ShowPopup(UIController.Instance.SelectFriendPopup);
		} */

		if (CurrentLevel.StoneType == 2) {
			ltrPrefab = LetterPrefab_2 [Random.Range (0, LetterPrefab_2.Length)];
		} else {
			ltrPrefab = LetterPrefab_1 [Random.Range (0, LetterPrefab_1.Length)];
		}

		Analitics.TreckScreen ("Level " + (levelId + 1) + " - Profile: " + UsersController.Instance.CurrentProfileId);
	}


	void UpdateLauncherPoint()
	{
		Transform to = LevelBackground.transform.Find ("Launcher");

		Canvas c = LettersPanel.GetComponentInParent<Canvas> ();
		RectTransform CanvasRect = c.GetComponent<RectTransform> ();
		Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

		LauncherPoint = new Vector2 (
			((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
			((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
		);
	}

	public void DestroyBackground()
	{
		if (LevelBackground != null) {
			Destroy (LevelBackground);
		}
	}

	public void LoadBackground(GameObject background)
	{
		DestroyBackground ();
		LevelBackground = Instantiate (background);
		LevelBackground.name = "LevelBackground";
	}

	public void LoadBackground(string background = "")
	{
		GameObject go;
		if (background != "") {
//			go = background;
			go = Resources.Load ("Gameplay/Background/" + background) as GameObject;
		} else {
			string fileName = backgrounds [Random.Range (0, backgrounds.Length)];
			go = Resources.Load ("Gameplay/Background/" + fileName ) as GameObject;
		}
		LoadBackground (go);
	}


	int SegmentToLoad = -1;

	void LoadFirstSegment()
	{
		LoadSegment (0);
//		SegmentToLoad = 0;
	}


	public void LoadSegment (int segmentIndex)
	{
		if (mGameplayPosition.SegmentIndex == segmentIndex) {
			return;
		}

		mGameplayPosition.SegmentIndex = segmentIndex;
		CountdownCounter = 0;
		slowBoosterDuration = 0;
		shildBoosterDuration = 0;

		timerSlider.value = 100;

		toDoMagnet = false;
		isFreezeTimer = false;
//		mIsLetterDrag = false;
		isSegmentComplete = false;
		isTimeup = false;

		updateSegmentTime ();

		EndTutorial ();

		Feedback fb = UIController.Instance.GamePanel.transform.GetComponentInChildren<Feedback> ();
		if (fb != null) {
			Destroy (fb.gameObject);
		}

//		if (addTreasureChest ()) {
		if (AddBonusPuzzle ()) {
			IsPause = true;
		} else {
			LoadSegment();
		}
	}


	public Transform TutorialHolder;

	[HideInInspector]
	public Tutorial gameTutorial;
	[HideInInspector]
	public Tutorial pointTutorial;

	

	void StartTutorial()
	{
		gameTutorial = TutorialController.Instance.StartTutorial (TutorialHolder);
	}

	void StartHandTutorial()
	{
		Vector2 toPos = GameplayController.Instance.getMonsterHandPosition();
		pointTutorial = TutorialController.Instance.PointAt (toPos, TutorialHolder, true);
	}

	
	public void LoadSegment ()
	{
		DestroyBonusPuzzlePopup ();

		if (
			(CurrentLevelIndex == TutorialSettings.TutorialLetterLevel && mGameplayPosition.SegmentIndex < 1)
			||
			(CurrentLevelIndex == TutorialSettings.TutorialWordLevel && mGameplayPosition.SegmentIndex < 1) 
			||
			(CurrentLevelIndex == TutorialSettings.TutorialLetterInWordLevel && mGameplayPosition.SegmentIndex < 1)
			||
			!string.IsNullOrEmpty(CurrentSegment.VoiceTutorial)
			||
			CurrentSegment.IsTutorial
//			||
//			(CurrentLevelIndex == TutorialSettings.TutorialSwipeLevel && mGameplayPosition.SegmentIndex < 1)
		) {
			Invoke ("StartTutorial", 0.5f);
		} else {
			if (UsersController.Instance.userData ().getLastLetterGroup() <= 1) {
				Invoke ("StartHandTutorial", 2f);
			}
		}

		SetState(GameState.LoadSegment);

		CreateLetters ();
		CreateMonsters ();

//		UIController.Instance.PuzzleCountdown.text = (CurrentLevel.Segments.Length - mGameplayPosition.SegmentIndex).ToString();

		Timer.Instance.Create (new Timer.TimerCommand (0.01f, Countdown, GameState.SegmentIdle));

		StartSegment ();
	}


	public void EndTutorial()
	{
		TutorialController.Instance.EndTutorial ();
	}

	public void EndHandTutorial()
	{
		CancelInvoke ("StartHandTutorial"); 
		if (pointTutorial != null) {
			TutorialController.Instance.EndTutorial (pointTutorial);
			pointTutorial = null;
		}
	}

	void DestroyBonusPuzzlePopup()
	{
		if (bonusPuzzlePopup != null) {
			Destroy (bonusPuzzlePopup.gameObject);
		}
		bonusPuzzlePopup = null;
	}


	void loadBonusPazzleIfNeeded()
	{
		if(GameAssets.Instance.BonusPazzleGO == null) {
			GameAssets.Instance.BonusPazzleGO = Resources.Load ("Gameplay/BonusPuzzle") as GameObject;
		}
	}

	bool AddBonusPuzzle()
	{
		DestroyBonusPuzzlePopup ();
		loadBonusPazzleIfNeeded ();

		if (GameAssets.Instance.BonusPazzleGO!= null && ShowTreasureChestInSegment > -1 && ShowTreasureChestInSegment == mGameplayPosition.SegmentIndex) {
			GameObject go = Instantiate (GameAssets.Instance.BonusPazzleGO, BonusGameHolder.transform) as GameObject;
			bonusPuzzlePopup = go.GetComponent<BonusPuzzle> ();
			bonusPuzzlePopup.onDone = LoadSegment;
			return true;
		}
		return false;
	}



/*
	void DestroyTreasureChestPopup()
	{
		if (treasureChestPopup != null) {
			Destroy (treasureChestPopup.gameObject);
		}
		treasureChestPopup = null;
	}

	bool addTreasureChest()
	{
		DestroyTreasureChestPopup ();

		if (ShowTreasureChestInSegment > -1 && ShowTreasureChestInSegment == mGameplayPosition.SegmentIndex) {
			GameObject go = Instantiate (treasureChestPrefabs, BonusGameHolder.transform) as GameObject;
			treasureChestPopup = go.GetComponent<TreasureChest> ();
			treasureChestPopup.onDone = LoadSegment;

			if(CurrentLevelIndex == 1) {
				treasureChestPopup.addTutorial ();
			}
			return true;
		}
		return false;
	}
*/


	void StartSegment()
	{
		// added by Tzahi
		IsPause = false;

/*
 		letterReplacedQueue.Clear ();
 		Level lvl = CurrentLevel;
		if (lvl.ReplaceLerrtrTimes > 0 && lvl.ReplaceLerrtrStartTime > 0 && lvl.ReplaceLerrtrDelay > 0 && Tutorial.getState == TutorialController.TutorialState.Inactive) {
			for (int i = 1; i <= lvl.ReplaceLerrtrTimes; i++) {
				letterReplacedQueue.Enqueue (lvl.ReplaceLerrtrStartTime + ((i - 1) * lvl.ReplaceLerrtrDelay));
			}
		}
*/
		startButton.StartLevel ();
		Analitics.Instance.treckEvent (AnaliticsCategory.GamePlay, AnaliticsAction.SegmentStart + "_Level_" + (CurrentLevelIndex + 1), "Puzzle " + GameplayController.Instance.CurrentSegment.valueForAnalitics );
	}

	void DestroyLetters()
	{
		for (int i = 0; i < LettersPanel.transform.childCount; i++) {
			Destroy (LettersPanel.transform.GetChild (i).gameObject);
		}
	}

	void CreateLetters()
	{
		GameObject location = null;
		List<GameObject> locations = new List<GameObject>( LettersLocations);
		List<int> SpawnIds = new List<int>();
		if(CurrentSegment.SpawnIds != null && CurrentSegment.SpawnIds.Length > 0) {
			SpawnIds = new List<int> (System.Array.ConvertAll<string, int> (CurrentSegment.SpawnIds.Trim ().Split(','), int.Parse));
		}

		for ( int i=CurrentSegment.Stones.Length-1; i>=0; i--) {
			Stone stone = CurrentSegment.Stones[i];
			if (stone.chanceToShow != 0f && stone.chanceToShow < 100f) {
				if (stone.chanceToShow > (UnityEngine.Random.value * 100f)) {
					continue;				
				}
			}

			int rndLocationIndex;
			location = null;

			if (stone.spawnIds.Length > 0) {
				location = getLocationBySpawnId (locations, stone.spawnIds[0]);
			} else if (int.TryParse (stone.spawnId, out rndLocationIndex)) {
				location = getLocationBySpawnId (locations, rndLocationIndex);
			} else {
				stone.spawnId = "";

				if (SpawnIds.Count > 0) {
					rndLocationIndex = Random.Range (0, SpawnIds.Count);
					location = getLocationBySpawnId (locations, SpawnIds [rndLocationIndex]);

					SpawnIds.RemoveAt (rndLocationIndex);
				}
			}

			if (location != null) {
				try {
					if (stone.value.Trim ().ToLower ().Equals ("monsterbooster")) {
						if(CurrentMonster != null && CurrentMonster.IsReady)
                        {
							createBooster (CurrentMonster.booster, stone, location);
						}
					} else {
						Booster.BoosterType boosterType = Booster.toEnum (stone.value);
						if (boosterType == Booster.BoosterType.NONE) {
							createLetter (stone, location);			
						} else {
							createBooster (boosterType, stone, location);
						}					
					}
				} catch {
				}
			}
		}
	}

	void createLetter(Stone stone, GameObject location)
	{
		GameObject holder = new GameObject("Letter Stone");
		holder.AddComponent<LetterTouchController> ();
		holder.transform.SetParent(LettersPanel.transform);
		holder.transform.position = location.transform.position;

//		GameObject newLetter = GameObject.Instantiate (ltrPrefab, location.transform.position, Quaternion.identity) as GameObject;
		GameObject newLetter = GameObject.Instantiate (ltrPrefab, LauncherPoint, Quaternion.identity) as GameObject;

		newLetter.transform.SetParent (holder.transform);
		newLetter.transform.position = Vector3.zero;
		newLetter.GetComponent<LetterController> ().Init (stone, location.transform.position, location.GetComponent<LetterSpawn>().id);
	}

	void createBooster(Booster.BoosterType boosterType, Stone stone, GameObject location)
	{
		if (boosterType != Booster.BoosterType.NONE) {

			GameObject holder = new GameObject("Booster Stone");
			holder.AddComponent<LetterTouchController> ();
			holder.transform.SetParent(LettersPanel.transform);
			holder.transform.position = Vector3.zero;

//			GameObject newBooster = GameObject.Instantiate (BoosterPrefab, location.transform.position, Quaternion.identity) as GameObject;
			GameObject newBooster = GameObject.Instantiate (BoosterPrefab, LauncherPoint, Quaternion.identity) as GameObject;
			newBooster.transform.SetParent (holder.transform);
			newBooster.transform.position = location.transform.position;
/*
			GameObject newBooster = GameObject.Instantiate (BoosterPrefab, location.transform.position, Quaternion.identity) as GameObject;
			newBooster.transform.SetParent (LettersPanel.transform);
			newBooster.transform.position = location.transform.position;
*/
			// Added by Tzahi
			string type = Booster.BoosterNames [(int)boosterType];
			var booster = Resources.Load ("Gameplay/Boosters/" + type) as Booster;

			newBooster.GetComponent<BoosterController> ().Init (stone, booster, location.transform.position, location.GetComponent<LetterSpawn> ().id);
		}
	}


	public GameObject getLocationBySpawnId(int spawnId)
	{
		List<GameObject> locations = new List<GameObject>( LettersLocations);

		return getLocationBySpawnId (locations, spawnId);
	}


	public GameObject getLocationBySpawnId(List<GameObject> locations, int spawnId)
	{
		foreach (GameObject location in locations) {
			if (location.GetComponent<LetterSpawn> ().id == spawnId) {
				return location;
			}
		}
		return null;
	}

	void DestroyMonsters()
	{
		for (int i = 0; i < MonsterPanel.transform.childCount; i++) {
			Destroy (MonsterPanel.transform.GetChild (i).gameObject);
		}

		SetMonsterHole (false);
	}
	Monster _currentMonster; 

	public Monster CurrentMonster
	{
		get
		{
			if (_currentMonster == null) {
				UpdateCurrentMonster ();
			}
			return _currentMonster;
		}
	}

	void UpdateCurrentMonster()
	{
		GameObject go = GameObject.Find ("monster");
		if (go != null) {
			MonsterSpritesController msc = go.GetComponent<MonsterSpritesController> ();
			_currentMonster = msc.monster;
		}
	}

	void CreateMonsters()
	{
		GameObject prefab = null;

		if (CurrentMonster != null) {
			prefab = CurrentMonster.MonsterPrefab;
		}

		GameObject newMonster = GameObject.Instantiate (prefab) as GameObject;
		newMonster.SetActive (true);
		newMonster.GetComponent<MonsterCalloutController> ().Init ();

		SetMonsterHole (true);

		CurrentActive = newMonster.GetComponent<MonsterCalloutController> ();
	}

	void SetMonsterHole(bool enabled)
	{
		MonsterHoleButton.enabled = enabled;
		MonsterHoleButton.image.enabled = enabled;
	}

	bool HasNextSegment()
	{
//		return mGameplayPosition.SegmentIndex + 1 <  XMLController.Instance.getLevel(mGameplayPosition.LevelIndex).Segments.Length;
		return mGameplayPosition.SegmentIndex + 1 <  CurrentLevel.Segments.Length;
	}
	
	// Update is called once per frame

	AudioSource SoundScoreCountSRC;


/*
	IEnumerator updateScore(int fromS)
	{
		if (SoundScoreCountSRC == null) {
			SoundScoreCountSRC = AudioController.Instance.PlaySound (SoundScoreCount, 0.15f, 1f, false);
			SoundScoreCountSRC.loop = true;
		}
		while (fromS < mGameplayPosition.LevelScore)
		{
			yield return new WaitForSeconds (0.01f);
			fromS += 10;
			LevelScoreText.text = (fromS).ToString ();
		}
		LevelScoreText.text = mGameplayPosition.LevelScore.ToString();

		SoundScoreCountSRC.loop = false;
		while (SoundScoreCountSRC.isPlaying) {
			yield return new WaitForSeconds (0.01f);
		}

//		SoundScoreCountSRC.Stop ();
		Destroy (SoundScoreCountSRC.gameObject);
		SoundScoreCountSRC = null;

		yield return true;
	}
*/
	void Update () {

		if (!IsPause && !IsPausePopup) {
			if (SegmentToLoad > -1) {
				LoadSegment (SegmentToLoad);
				SegmentToLoad = -1;
			}
		}

		int fromS = int.Parse (LevelScoreText.text);
/*
		if (fromS < mGameplayPosition.LevelScore) {
			StartCoroutine (updateScore (fromS));
		}
*/

		if (fromS < mGameplayPosition.LevelScore) {
			fromS += 10;

			if (SoundScoreCountSRC == null) {
				SoundScoreCountSRC = AudioController.Instance.PlaySound (SoundScoreCount, 0.15f, 1f, false);
				if (SoundScoreCountSRC) {
					SoundScoreCountSRC.loop = true;
				}
			}
		} else {
			
			if(SoundScoreCountSRC != null) {
				SoundScoreCountSRC.loop = false;

				if (!SoundScoreCountSRC.isPlaying) {
					SoundScoreCountSRC.Stop ();
					Destroy (SoundScoreCountSRC.gameObject);
					SoundScoreCountSRC = null;
				}
			}
			fromS = mGameplayPosition.LevelScore;

		}
		LevelScoreText.text = (fromS).ToString ();



		if (IsPause || IsPausePopup || !IsInteractable)
			return;

		if (Input.GetMouseButtonUp (0)) {
			MonsterCalloutController monster = Component.FindObjectOfType<MonsterCalloutController> ();

			if (monster != null && State == GameState.SegmentIdle) {
				// start added by tzahi
				bool isMouseOver = false;
				RaycastHit2D hit = Physics2D.GetRayIntersection (Camera.main.ScreenPointToRay (Input.mousePosition));

//				if (RectTransformUtility.RectangleContainsScreenPoint ((RectTransform)MonsterHoleButton.transform, Input.mousePosition, canvasCamera))
				if (hit.transform != null &&  hit.transform.tag == "Monster")
				{
					isMouseOver = true;
				}
				// end added by tzahi

				if ((monster.IsMouseOver || isMouseOver)) {
					CollectLettersToMonster (monster);
//					UnSelectAllLetters ();
					UnOverAllMonsters ();
					return;
				}
			}
/*
			LoadLevel,
			LoadSegment, 
			ThoughtBubbleAnimation,
			SegmentIdle, //Playing the game!!
			SegmentWinAnimation,
			SegmentLoseAnimation,
			LevelWinAnimation,
			//		LevelLoseAnimation,
			EndSegment
*/
			if (State != GameState.CollectLetters && State != GameState.LetterComingToMonster && State != GameState.EatingLetter) {
				UnSelectAllLetters ();
				UnOverAllMonsters ();
			}
		}
	}

	public void CollectLettersToMonster(MonsterCalloutController monster = null)
	{
		if (monster == null)
			monster = CurrentActive;
		if (SomeLettersSelected ()) {
			SetState (GameState.CollectLetters);
			CurrentActive = monster;
			monster.CollectSelectedLetters ();
		}
	}

	bool SomeLettersSelected()
	{
		LetterController[] letters = AllLetters;
		foreach (LetterController letter in letters) {
			if (letter.State == LetterController.LetterState.Selected)
				return true;
		}
		return false;
	}

	bool IsInsideTransform(Vector3 pos, RectTransform rectTransform)
	{
		return pos.x > rectTransform.position.x && pos.x < rectTransform.position.x + rectTransform.rect.width && pos.y > rectTransform.position.y && pos.y < rectTransform.position.y + rectTransform.rect.height;
	}

	void UnSelectAllLetters()
	{
		LetterController[] letters = AllLetters;
		foreach (LetterController letter in letters) {
			letter.UnSelect ();
		}
	}

	void UnOverAllMonsters()
	{
		MonsterCalloutController monster = Component.FindObjectOfType<MonsterCalloutController> ();
		if (monster != null)
			monster.IsMouseOver = false;
	}

	public bool CheckIfSegmentWin(LetterController eatenLetter)
	{
		EndTutorial (); //Jonathan

		LetterController[] letters = AllLetters;


		mGameplayPosition.SucsessSegments[mGameplayPosition.SegmentIndex] = true;

		foreach (string requiredLetter in CurrentSegment.MonsterRequiredLetters) {
			foreach (LetterController letter in letters) {
				if (letter.stone == null)
					continue;
				if ( 
					eatenLetter != letter 
					&&
//					eatenLetter.stone.value != letter.stone.value// added by Tzahi
//					&&
					letter.stone.value == requiredLetter
				) {
					return false; // do nothing cuz needed letter is still waiting in screen.
				}
			}
		}

//		mGameplayPosition.SucsessSegment++;
		SegmentWin (); // win cuz needed letter cannot be found anymore.
		return true;
	}

	public LetterController FindLetterInGame(string letterText)
	{
		LetterController[] letters = AllLetters;
		foreach (LetterController letter in letters) {
			if (letter.text.text == letterText) {
				return letter; 
			}
		}
		return null;
	}

	void SegmentWin()
	{
//		Debug.Log ("SegmentWin");
		Invoke ("PlayPositive", .5f);


		//AudioController.Instance.PlaySound (Resources.Load ("Sounds/Success") as AudioClip);
		// AddLevelScoreToFlush = 50 * AllLetters.Length; // delete by Tzahi


		int bonusScore = 0;
		GameplaySettings.PuzzleSuccessScore.TryGetValue(CurrentLevel.monsterInputType, out bonusScore);

		bonusScore += ((int)(segmentTime - CountdownCounter)) * GameplaySettings.PuzzleLeftTimeScore;

		AddLevelScoreToFlush = bonusScore;

		ShowSegmentWinAnimation ();
	}

	void PlayPositive()
	{
		string fileName = AudioController.Instance.PlayFeedback ();
		ShowPositive (fileName);
	}

	void ShowPositive(string fileName)
	{
		if (FeedbackGO != null) {
			GameObject go = Instantiate(FeedbackGO, UIController.Instance.GamePanel.transform) as GameObject;
			go.transform.localScale = new Vector3 (1f, 1f, 1f);
			Feedback fb = go.GetComponent<Feedback> ();
			fb.init (fileName);
		}
	}

	public void BadBooster()
	{
		SetState(GameState.SegmentIdle);
		cancelDrag ();
//		Invoke ("EndSegmentLoseAnimation", 1.5f);
	}

	public void SegmentLose()
	{
//		Debug.Log ("SegmentLose");
		//AudioController.Instance.PlaySound (Resources.Load ("Sounds/GameOver") as AudioClip);
		ShowSegmentLoseAnimation ();
	}

	void ShowSegmentLoseAnimation()
	{
		LetterController[] letters = AllLetters;
		foreach (LetterController letter in letters) {
			letter.DisapearLost ();
		}

		SetState(GameState.SegmentLoseAnimation);
		//CurrentActive.PlayMouthAnimation (CurrentActive.MouthAngrySprites);
		//CurrentActive.PlayEyeAnimation (CurrentActive.EyeAngrySprites);

		//Invoke ("EndSegmentLoseAnimation", 1.5f);
//		Invoke ("OnEatAnimationEnd", 1.5f);


		mGameplayPosition.AllowMaxStars = false;
	}

	void ShowSegmentWinAnimation()
	{
		LetterController[] letters = AllLetters;
		int[] letterDisappearDelays = new int[letters.Length];
		for (int i = 0; i < letterDisappearDelays.Length; i++)
			letterDisappearDelays [i] = i;
		letterDisappearDelays = letterDisappearDelays.OrderBy (x => Random.value).ToArray ();

		for (int i = 0; i < letters.Length; i++) {
			letters [i].DisapearWon (letterDisappearDelays [i] * 0.07f);
		}

//		CurrentActive.SetMonsterState (MonsterCalloutController.MonsterState.Happy);

		SetState(GameState.SegmentWinAnimation);

		if(_currentLevelScoreToFlush > 0) {

			if (ScoreAnimation != null) {
			ScoreAnimation.Play();
			} else {
				Component.FindObjectOfType<UIScoreAnimationController> ().Play ();
			}
		} else {
//			Debug.Log("Score is ziro");
			GameplayController.Instance.EndSegmentWinAnimation ();
//			OnEatAnimationEnd ();
		}

	}

	public void EndSegmentWinAnimation()
	{
//		Debug.Log ("end segment animation " + State);
		if (State == GameState.SegmentWinAnimation) {
			Invoke ("EndSegment", 1.6f);
			//EndSegment ();
		}
	}

	public void EndSegmentLoseAnimation()
	{
		if (State == GameState.SegmentLoseAnimation) {
//			EndSegment ();
		}
	}

	void EndSegment()
	{
		CancelInvoke("EndSegment");

		Analitics.Instance.treckEvent (
			AnaliticsCategory.GamePlay,
			((State == GameState.SegmentWinAnimation) ? AnaliticsAction.SegmentSuccess : AnaliticsAction.SegmentFail) + "_Level_" + (CurrentLevelIndex + 1),
			"Puzzle " + GameplayController.Instance.CurrentSegment.valueForAnalitics
		);

//		Debug.Log ("end segment");
		SetState (GameState.EndSegment);

		SegmentsDisplay.Fill (CurrentSegmentIndex);

		DestroyLetters ();
		DestroyMonsters ();
		Timer.Instance.Remove (Countdown);

		startButton.StopLevel ();

		if (HasNextSegment ()) {
			SegmentToLoad = mGameplayPosition.SegmentIndex + 1;
			//LoadSegment (mGameplayPosition.SegmentIndex + 1);
		} else {
			LevelEnd ();
		}
	}

	void LevelEnd()
	{
//		Debug.Log ("new score for level " + CurrentLevelIndex + " : " + CurrentLevelScore);

		int stars = mGameplayPosition.LevelStars;
		UsersController.Instance.userData().setLevelStars (CurrentLevelIndex, stars);

		CurrentMonster.setLevelComplite (stars);
//		MiniGameController.Instance.LevelComplite ();

		if (stars > 0)
		{
			UsersController.Instance.userData().setLastLetterGroup(CurrentLevel.lettersGroup);
			PlayWinImageAnimation ();
			if (CurrentLevelIndex == 0) {
				Invoke ("PointAtNextButton", 2f);
			}
		}
		else
		{
			UIController.Instance.ShowPopup (UIController.Instance.LevelEndPopup);
		}
	}

	void PointAtNextButton(){
		var curPin = GameObject.Find ("Button - Next").transform;
		TutorialController.Instance.PointAt (curPin.localPosition /*- new Vector3 (0, 25, 0)*/, curPin.parent);
	}

	void PlayWinImageAnimation()
	{
		SetState (GameState.LevelWinAnimation);

		Invoke ("EndLevelWinAnimation", 1f);
	}

	void EndLevelWinAnimation()
	{
		//Invoke (() => LevelWinImage.gameObject.SetActive (false), 0.5f);
		UIController.Instance.ShowPopup (UIController.Instance.LevelEndPopup);
	}

	public void Debug_Restart_Game()
	{
		SceneManager.LoadScene (0);
	}

	public int CurrentLevelIndex
	{
		get {
			return mGameplayPosition.LevelIndex;
		} 
		set {
			mGameplayPosition.LevelIndex = value;

		}
	}

	public int CurrentSegmentIndex
	{
		get{
			return mGameplayPosition.SegmentIndex;
		}
	}

	public int CurrentLevelScore
	{
		get {
			return mGameplayPosition.LevelScore;
		}
	}

	public int CurrentLevelStars
	{
		get {
			return mGameplayPosition.LevelStars;
		}
	}

/*
	public float CurrentLevelXP
	{
		get {
			return mGameplayPosition.LevelScore / 10;
		}
	}
*/

	public void ClearGameplay()
	{
//		DestroyTreasureChestPopup ();
		DestroyBonusPuzzlePopup ();

		EndTutorial ();

		if (CurrentActive != null) {
			CurrentActive.SetMonsterState (MonsterCalloutController.MonsterState.Idle);
		}
		_currentLevelScoreToFlush = 0;
		CancelInvoke ();
		DestroyLetters ();
		DestroyMonsters ();

		FreezeGauge.stopFrezz ();
//		FreezeGauge.gameObject.SetActive (false);
		Timer.Instance.Remove (Countdown);
	}

	public LetterController[] AllLetters {
		get {
			return Component.FindObjectsOfType<LetterController> ();
		}
	}

	private bool IsDistractor(LetterController checkLetter){
//		if (!CurrentSegment.MonsterRequiredLetters.Contains (checkLetter.value)) {
		if (!CurrentSegment.MonsterRequiredLetters.Contains (checkLetter.stone.value)) {
			return true;
		}

		return false;
	}

	public void OnPlayerInteraction(object sender)
	{
		// we dont need to reset the timer - Tzahi
		// CountdownCounter = 0;	

		if (sender is LetterController) {
			LetterController stone = (sender as LetterController);
			if (stone.State == LetterController.LetterState.Selected) {
				CurrentActive.SetMonsterState (MonsterCalloutController.MonsterState.Eating);
			} else {
				CurrentActive.SetMonsterState (MonsterCalloutController.MonsterState.Idle);
			}
		}
	}

/*
* Tzahi - start
*/
	public Camera canvasCamera;

	public IceBoosterGaugeController FreezeGauge;
	public Slider timerSlider;
	public GameObject timerTicks1;
	public GameObject timerTicks2;
//	Queue<int> letterReplacedQueue = new Queue<int>();
//	bool mIsLetterDrag = false;
	public bool isSegmentComplete = false;



	public void OnEatAnimationEnd()
	{
		if (
			State == GameState.SegmentWinAnimation
			||
			State == GameState.SegmentLoseAnimation
		) {

			CurrentActive.OnEatDone ();

			Invoke ("EndSegment", 1.6f);
//			EndSegment ();
		}
	}


	public void OnMealStartAnimationEnd()
	{
		GameplayController.Instance.CurrentActive.StartPlay (0f);
//		GameplayController.Instance.CurrentActive.hideBubble ();
	}

	public void SpitsMeal()
	{
		AudioController.Instance.PlaySound (SoundSpitsMeal);
	}


	public void onBeginDragLetter(LetterController dragedLetter)
	{
//		mIsLetterDrag = true;
	}

	public void onEndDragLetter(LetterController dragedLetter)
	{
//		mIsLetterDrag = false;
	}

	public void onDragLetter(LetterController dragedLetter)
	{
		if (dragedLetter.stone == null)
			return;
		
		doDragMagnet (dragedLetter);

		foreach (LetterController letter in AllLetters) 
		{
			//Jonathan
//			var isEnabled = !letter.gameObject.GetComponent<CanvasGroup> ().interactable;
//			if (!isEnabled || letter.stone == null) {
			if (letter.stone == null) {
				continue;
			}
			//End Jonathan

			if (dragedLetter != letter && letter.State != LetterController.LetterState.Selected) {
				if (
					(
						dragedLetter.isTutorial == false
						&&
						RectTransformUtility.RectangleContainsScreenPoint ((RectTransform)letter.transform, Input.mousePosition, canvasCamera)
					)
					||
					(
						dragedLetter.isTutorial == true
						&&
						(
							(int)letter.transform.position.x == (int)dragedLetter.transform.position.x
							&&
							(int)letter.transform.position.y == (int)dragedLetter.transform.position.y
						)
					)
				)
				{
					if (dragedLetter.stone.value == BoosterController.letterName) {

						GameObject holder = dragedLetter.GetComponentInParent<LetterTouchController> ().gameObject;
						letter.transform.SetParent(holder.transform);
						letter.Select ();
						letter.OnBeginDrag (null);

						MonsterCalloutController monster = Component.FindObjectOfType<MonsterCalloutController> ();
						if (monster != null) {
							monster.EatBooster ((BoosterController)dragedLetter, null);
						}

						Destroy (dragedLetter.gameObject);
					} else if (letter.stone.value == BoosterController.letterName) {
						MonsterCalloutController monster = Component.FindObjectOfType<MonsterCalloutController> ();
						if (monster != null) {
							monster.EatBooster ((BoosterController)letter, dragedLetter);
						}
					
					} else if (CurrentLevel.monsterInputType == MonsterInputType.Letter || CurrentLevel.monsterInputType == MonsterInputType.LetterName || CurrentLevel.monsterInputType == MonsterInputType.LetterInWord || CurrentLevel.monsterInputType == MonsterInputType.SoundLetter || CurrentLevel.monsterInputType == MonsterInputType.SoundLetterName) {
						if (letter.stone.value == dragedLetter.stone.value) {
							TutorialController.Instance.EndTutorial ();

							margeLetters (letter, dragedLetter);
							AudioController.Instance.PlaySound (SoundMargeLetters);
						} else if (shildBoosterDuration <= 0 && letter.stone.value != dragedLetter.stone.value) {
							cancelDrag (dragedLetter);
							letter.addMergeParticlesReject ();
							AudioController.Instance.PlaySound (SoundCancelDrag);
							return;
						}
					} else if(CurrentLevel.monsterInputType == MonsterInputType.Word || CurrentLevel.monsterInputType == MonsterInputType.SoundWord /*Jonathan*/) {
						if (CurrentSegment.MonsterRequiredLetters.Contains (dragedLetter.stone.value) && CurrentSegment.MonsterRequiredLetters.Contains (letter.stone.value)) {
							TutorialController.Instance.EndTutorial ();

							dragedLetter.addCollectLetter (letter);
								
							letter.numSubLetters = 1;
							letter.Select ();
							letter.SetVisible (false);

							if (dragedLetter.numSubLetters > 0) {
								int s = IncreaseLevelScore (GameplaySettings.LetterComboScore/* [dragedLetter.numSubLetters - 1]*/);
								dragedLetter.addScorebubble (s);
							}
						} else if (shildBoosterDuration <= 0) {
							cancelDrag (dragedLetter);
							return;
						}
					}
				}
			}
		}
	}	

	void doDragMagnet(LetterController dragedLetter)
	{
		if (toDoMagnet == true) {
			toDoMagnet = false;

			if (CurrentLevel.monsterInputType == MonsterInputType.Letter || CurrentLevel.monsterInputType == MonsterInputType.LetterName || CurrentLevel.monsterInputType == MonsterInputType.LetterInWord || CurrentLevel.monsterInputType == MonsterInputType.SoundLetter || CurrentLevel.monsterInputType == MonsterInputType.SoundLetterName) {
				foreach (LetterController letter in AllLetters) {
					if (letter != dragedLetter && letter.stone.value == dragedLetter.stone.value) {
						letter.magnetToLetter (dragedLetter);

						break;
					}
				}
			} else if (CurrentLevel.monsterInputType == MonsterInputType.Word || CurrentLevel.monsterInputType == MonsterInputType.SoundWord /*Jonathan*/) {
				if (CurrentActive.IsGoodLetter (dragedLetter)) {
					foreach (LetterController letter in AllLetters) {
						if (letter != dragedLetter && CurrentActive.IsGoodNextLetter (letter, dragedLetter.numSubLetters + 1)) {
							letter.numSubLetters = 1;
							letter.magnetToLetter (dragedLetter);
//							letter.Select ();
//							letter.SetVisible (false);

							dragedLetter.addCollectLetter (letter);

							if (dragedLetter.numSubLetters > 0) {
								int s = IncreaseLevelScore (GameplaySettings.LetterComboScore/* [dragedLetter.numSubLetters - 1]*/);
								dragedLetter.addScorebubble (s);
							}
							return;
						}
					}
				} else {
					cancelDrag (dragedLetter);
					return;
				}
			}
		}
	}

	public void margeLetters(LetterController fromLetter, LetterController toLetter)
	{
		toLetter.addSubLetter ();
		if (toLetter.numSubLetters > 0) {
			int s = IncreaseLevelScore (GameplaySettings.LetterComboScore/* [toLetter.numSubLetters - 1] */);

			toLetter.addMergeParticlesAccept ();

			Booster.BoosterType boosterType = Booster.toEnum (toLetter.stone.value);
			if (boosterType == Booster.BoosterType.BonusLetter) {
				//toLetter.addScorebubble (toLetter.transform, 2844);
			} else {
				toLetter.addScorebubble (s);
			}
		}
		Destroy (fromLetter.gameObject);
	}

	public void cancelDrag ()
	{
		foreach (LetterController letter in AllLetters)
		{
			letter.cancelDrag ();
		}
	}

	void cancelDrag (LetterController dragedLetter)
	{
		cancelDrag ();
	}

	#region Boosters
	bool toDoMagnet = false;
	float slowBoosterDuration = 0;
	float shildBoosterDuration = 0;
	public bool isFreezeTimer = false;

	public void DoFireBooster(BoosterController booster, LetterController dragedLetter)
	{
		foreach (LetterController letter in AllLetters) {
			if (letter != booster && letter != dragedLetter && IsDistractor (letter) && letter.State == LetterController.LetterState.Idle) {
				GameObject fire = GameObject.Instantiate (booster.Model.EffectOnLetterPrefab, letter.transform.position, Quaternion.identity) as GameObject;
				fire.transform.SetParent (letter.transform.parent);
				fire.transform.localPosition = new Vector3(letter.transform.localPosition.x, letter.transform.localPosition.y, letter.transform.localPosition.z - 1);
				fire.transform.localScale = fire.transform.localScale * letter.transform.localScale.x;
				letter.DisapearLost (0f);
				Destroy(letter.gameObject);
				break;
			}
		}
	}

	public void ShieldBooster(BoosterController booster, LetterController dragedLetter)
	{
		shildBoosterDuration = GameplaySettings.BoosterShowCalloutTimes;
		addBoosterEfect (booster, shildBoosterDuration, dragedLetter);
	}

	public void SlowMovmentBooster(BoosterController booster, LetterController dragedLetter)
	{
		slowBoosterDuration = GameplaySettings.BoosterSlowMovementDuration;
		addBoosterEfect (booster, slowBoosterDuration, dragedLetter);
	}

	public void DoMagnetBooster(BoosterController booster, LetterController dragedLetter)
	{
		toDoMagnet = true;
		addBoosterEfect (booster, 0, dragedLetter);
	}

	public void ShowCalloutBooster(BoosterController booster, LetterController dragedLetter)
	{
		CurrentActive.reshowCallout ();
		addBoosterEfect (booster, 0,  dragedLetter);
	}


	void addBoosterEfect(BoosterController booster, float destroyAfter, LetterController dragedLetter)
	{
		if (booster != null && booster.Model != null && booster.Model.EffectOnLetterPrefab != null) {

			LetterController ltr = null;
			if (dragedLetter != null) {
				ltr = dragedLetter;
			} else {
				foreach (LetterController letter in AllLetters) {
					if (letter != booster && letter.isDragable) {
						ltr = letter;
						break;
					}
				}
			}

			if (ltr != null) {
				GameObject shild = GameObject.Instantiate (booster.Model.EffectOnLetterPrefab, ltr.transform.position, Quaternion.identity) as GameObject;
				shild.transform.SetParent (ltr.transform);
				shild.transform.localPosition = new Vector3 (0, 0, 0);
				shild.transform.localScale = shild.transform.localScale * ltr.transform.localScale.x;

				if (destroyAfter > 0) {
					DestroyAfter ds = shild.AddComponent<DestroyAfter> ();
					ds.After = destroyAfter;
				}
			}
		}

	}



	public void DoFreezeBooster() {
		FreezeGauge.startFrezz ();

//		FreezeGauge.gameObject.SetActive (true);
//		CountdownCounter -= GameplaySettings.FreezeDuration;

//		isFreezeTimer = true;
	}



	public void DoBounsLetterBooster(BoosterController booster)
	{
		int bonus;
		int.TryParse (booster.stone.bonusScore, out bonus);
		if (bonus == 0) {
			bonus = GameplaySettings.BonusLetterBoosterScore;
		}
		bonus = IncreaseLevelScore (bonus);
		booster.addScorebubble (booster.transform.parent, bonus);
	}
	#endregion

	public Vector2 getMonsterHandPosition() { 
		Transform to = GameObject.Find ("monster").transform.Find ("Hand");
		Vector2 toPos = GameplayController.Instance.MonsterHoleButton.transform.position;
		if (to != null) {
			toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);
			Canvas c = UIController.Instance.GamePanel.GetComponentInParent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint (to.position));
			toPos = new Vector2 (
				((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
				((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
			);
		}
		return toPos;
	}

/*
* Tzahi - End
*/


}
