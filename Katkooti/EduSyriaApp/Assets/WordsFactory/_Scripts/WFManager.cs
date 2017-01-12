using UnityEngine;
using System.Collections;

public class WFManager : MonoBehaviour {

	public GameObject LetterSpawnPOint,StarSpawnPoint,Star;
//	private int TimeVal =5;
//	private int TotalLives=5;
	public GameObject [] WordPoints;
	public string[] words;
	public string CurrentWord;
	public int counter = 0;
	public int StringLength;
	private bool LetterToBucket;
	GameObject MovableLetter;
	public GameObject[] LettersPool;
	public int destroycounter;
	private bool once;

	public GameObject CompletionEffectPoint,CompletionEffect;
	public GameObject PinpointHand;
	public GameObject SFX;
	private UIManager UM;

	public int wordCompleted;
	public string[] Sound ;
	// Use this for initialization

	void Awake(){
		wordCompleted = 0;
		words = new string[GameManager.Instance.CurrentQuest.LearningItemsInQuest.Length];
		Sound = new string[GameManager.Instance.CurrentQuest.LearningItemsInQuest.Length];

		for (int i=0; i<GameManager.Instance.CurrentQuest.LearningItemsInQuest.Length;i++) {
			words [i] = GameManager.Instance.CurrentQuest.LearningItemsInQuest[i].letter;
			Sound [i] = GameManager.Instance.CurrentQuest.LearningItemsInQuest [i].soundName;
		}
	}
	void Start () 
	{
		
		UM = GameObject.FindObjectOfType<UIManager> ().GetComponent<UIManager> ();
		once = true;
		destroycounter = 0;
		LetterToBucket = false;


		CurrentWord = words [wordCompleted];
	//s	StartCoroutine ("LetterSpawner");
		EnableHandpointer ();

	}


	public string Word
	{
		get 
		{
			return CurrentWord;
		}
		set 
		{
			CurrentWord = value;
		}
	}
//
//	public int _Time
//	{
//		get 
//		{
//			return TimeVal;
//		}
//		set 
//		{
//			TimeVal = value;
//		}
//	}

//	public int Lives
//	{
//		get 
//		{
//			return TotalLives;
//		}
//		set 
//		{
//			TotalLives = value;
//		}
//	}

	public void StartLetterSpawner()
	{
		StartCoroutine ("LetterSpawner");
	}

	IEnumerator LetterSpawner()
	{
		while(true)
		{
			InitLetter ();
			yield return new WaitForSeconds (9f);
		}
	}
	public void InitLetter()
	{
		
			GameObject temp = Instantiate(Resources.Load("Letter") as GameObject);
			Vector3 Letterposition = new Vector3 (LetterSpawnPOint.transform.position.x,LetterSpawnPOint.transform.position.y,LetterSpawnPOint.transform.position.z);
			temp.transform.position = Letterposition;

			Invoke ("AssignRightLetter",0.5f);

	}


	public void AssignRightLetter()
	{
		GameObject[] SpawnedLetters = GameObject.FindGameObjectsWithTag ("Letter");
		int TempRandomizer = Random.Range (0,SpawnedLetters.Length-1);
		Debug.Log (TempRandomizer);
		for (int i = 0; i < SpawnedLetters.Length; i++) 
		{
			if (i == TempRandomizer) {
				SpawnedLetters [i].gameObject.transform.GetChild(0).gameObject.GetComponent<TextMesh> ().text = CurrentWord [counter].ToString();
			}
		}
	}

	void Update()
	{

		if (UM.Word == Word && once ) {
			StopAllCoroutines();
			SFX.GetComponent<Animator>().SetTrigger("glow");
			Invoke("LevelCleared",2f);
			once = false;
		}
	}


//	void OnEnable()
//	{
//		GameManager.PopulateQuest += OnGamePopulate;
//	}
//
//	void OnDisable()
//	{
//		GameManager.PopulateQuest -= OnGamePopulate;
//	}


	void OnGamePopulate(Quest quest)
	{
		words = new string[GameManager.Instance.CurrentQuest.LearningItemsInQuest.Length];
		for (int i=0; i<GameManager.Instance.CurrentQuest.LearningItemsInQuest.Length;i++) {
			words [i] = GameManager.Instance.CurrentQuest.LearningItemsInQuest[i].letter;
		}
	}

//	public IEnumerator StartTimer()
//	{
//		while (TimeVal > 0) {
//			yield return new WaitForSeconds (1);
//			TimeVal--;
//		}
//
//
//		CheckLives ();
//	}


//	public void LifeLost()
//	{
//
//		int templife = Lives;
//		templife--;
//		if (templife <= 0) {
//			Lives = 0;
//		} else {
//			Lives = templife;
//
//		}
//
//	}

	public void DestroyLetter()
	{
		GameObject[] LetterTemp = GameObject.FindGameObjectsWithTag ("Letter");
		foreach (GameObject Let in LetterTemp) 
		{
			Destroy (Let.gameObject);
		}
	}

	public void Reset()
	{

//		_Time = 5;


	}

	public void ResetLevel()
	{
//		Lives = 5;
		counter = 0;
		UM.ClearMainWord ();
//		Reset();
	}

	public bool MatchLetter(GameObject letter)
	{
		string TempString = CurrentWord;
		StringLength = CurrentWord.Length;
		if (CurrentWord [counter].ToString() == letter.transform.GetChild(0).GetComponent<TextMesh>().text)
			return true;
		else
			return false;

	}



	public void SetLettertoBucketFalse()
	{
		LetterToBucket = false;
	}

	public void LevelCleared()
	{
		Debug.Log ("Boo Ya ! Level Cleared");
		SoundManager.Instance.PlaySoundOneShot ("WinningSound");
		SoundManager.Instance.PlaySoundOneShot (Sound [wordCompleted]);
		wordCompleted++;
		SpawnStar ();
		if (wordCompleted == words.Length) {
			GameManager.Instance.ChickSongPowerValue = 1;
			StartCoroutine ("Success");

		} else {
			
			ResetLevel ();
			Invoke ("GameRestart", 2.5f);
		}
	}

	IEnumerator Success()
	{
		UM.gameObject.SetActive (false);
		MainUIManager.Instance.decisionUiController.PopDicisionBox ("CompletionStars");
		yield return new WaitUntil(() => (MainUIManager.Instance.decisionUiController.proceedStatus==true));
		MainUIManager.Instance.decisionUiController.UnPopDecisionBox (); 
		GameManager.Instance.QuestInitialized = false;
	}

	public void GameRestart()
	{
		UM.PauseGame ();
		Start ();

	}

//	public void CheckLives()
//	{
//		if (Lives > 0) {
//			Reset ();
//
//		} else {
//			ResetLevel ();
//		}
//	}

	public void EnableHandpointer()
	{
		PinpointHand.SetActive (true);
		Invoke ("DisableHandpointer", 5f);
	}

	public void DisableHandpointer()
	{
		PinpointHand.SetActive (false);
	}
		
	public void SpawnStar()
	{
		StartCoroutine ("SpawnStarNow");
	}

	IEnumerator SpawnStarNow()
	{
		for (int i = 0; i < 4; i++) {
			yield return new WaitForSeconds (0.15f);
			Instantiate (Star, StarSpawnPoint.transform.position, Quaternion.identity);
		}
	}

	public void CompletionEffectSpawn()
	{
		Instantiate (CompletionEffect, CompletionEffectPoint.transform.position, Quaternion.identity);
	}


}
