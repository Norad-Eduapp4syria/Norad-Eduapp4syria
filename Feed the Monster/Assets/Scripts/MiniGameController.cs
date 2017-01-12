using UnityEngine;
using System;
using System.Collections;
using Random = UnityEngine.Random;

public class MiniGameController : MonoBehaviour
{
	public static MiniGameController Instance;

	public BaseMiniGame CountTo10;
	public BaseMiniGame MonsterPetting;
	public BaseMiniGame LetterTracing;

	public GameType TutorialMinigame = GameType.CountTo10;


	BaseMiniGame currentGame;

	public BaseMiniGame CurrentGame
	{
		get { return currentGame; }
	}

	public enum GameType {
//		Nil,
		CountTo10,
		MonsterPetting,
		LetterTracing
	}


	void Awake()
	{
		Instance = this;
	}

	// Use this for initialization
	void Start () {
		hideAllGames ();
	}

	// Update is called once per frame
	void Update () {
	
	}

	public void hideAllGames()
	{
		if(CountTo10 != null) { CountTo10.gameObject.SetActive (false); }
		if(MonsterPetting != null) {MonsterPetting.gameObject.SetActive (false); }
		if(LetterTracing != null) {LetterTracing.gameObject.SetActive (false); }
	}

	public void StartRandomGame(Monster monster)
	{
		_currentMonster = monster;

		GameType game;
		if (TutorialController.Instance.GetIsInMinigameTutorial()) { //JONATHAN!!!!//UserInfo.Instance.GetHadMinigameTutorial() == 0) {
			game = TutorialMinigame; 
		} else {
			Array values = Enum.GetValues(typeof(GameType));
			int rnd = Random.Range (0, values.Length);
			game = (GameType)values.GetValue(rnd);
		}
		 

//		StartGame (game);
		StartGame (GameType.LetterTracing);
//		StartGame (GameType.CountTo10);
//		StartGame (GameType.MonsterPetting);
	}

	void StartGame(GameType game)
	{
		DestroyGame ();

		switch (game)
		{
		case GameType.CountTo10:
			currentGame = CountTo10;
				break;
		case GameType.MonsterPetting:
			currentGame = MonsterPetting;
			break;

		case GameType.LetterTracing:
			currentGame = LetterTracing;
			break;
		}

		if (currentGame != null) {
			currentGame.gameObject.SetActive (true);
			currentGame.init (CurrentMonster);
			if (game == GameType.MonsterPetting || TutorialController.Instance.GetIsInMinigameTutorial()) {
				TutorialController.Instance.StartTutorial (game);
			}
		} else {
			onMiniGameDone ();
		}
	}

	void DestroyGame()
	{
		if (currentGame != null) {
			currentGame.gameObject.SetActive(false);
		}
		currentGame = null;
	}

	public void onMiniGameDone()
	{
		DestroyGame ();

		ResetEmotion ();

		UIMiniGame.Instance.ShowEndGamePanel();
	}

	Monster _currentMonster; 

	public void ResetEmotion()
	{
		if (CurrentMonster != null) {
			CurrentMonster.ResetEmotion ();
		}
	}


	public Monster CurrentMonster
	{
		get
		{
			return _currentMonster;
		}
	}

	public void LevelComplite()
	{
		int count = UserInfo.Instance.GetToLevelCount() + 1;
		if (count >= GameplaySettings.HungryAfraidCompliteLevels) {

			Monster monster = getNotEmotionMonster ();
			if (monster != null) {
				if (UnityEngine.Random.value < 0.5f) {
					monster.EmotionType = MonsterEmotionTypes.Hungry;	
				} else {
					monster.EmotionType = MonsterEmotionTypes.Afraid;
				}
			}
			UserInfo.Instance.SetToLevelCount (0);
		} else {
			UserInfo.Instance.SetToLevelCount (count);
		}
	}


	public Monster getNotEmotionMonster()
	{
		Monster[] monsters = UserInfo.Instance.CollectedFriends;

		foreach (Monster m in monsters) {
			if (m.EmotionType == MonsterEmotionTypes.Happy && m.Gage > 0) {
				return m;
			}
		}
		return null;
	}

	public Monster getEmotionMonster()
	{
		Monster[] monsters = UserInfo.Instance.CollectedFriends;

		foreach (Monster m in monsters) {
			if (m.EmotionType != MonsterEmotionTypes.Happy && m.Gage > 0) {
				return m;
			}
		}
		return null;
	}

}
