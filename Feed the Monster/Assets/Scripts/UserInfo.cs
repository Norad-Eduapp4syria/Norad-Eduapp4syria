using UnityEngine;
using System;
using System.Collections;
using System.Linq;
using System.Collections.Generic;

public class UserInfo : MonoBehaviour {
	public static UserInfo Instance;
	public Monster[] StartMonsters;

	enum Keys
	{
		LetterGroup,
	}


	string getPrefsKey(Keys key)
	{
		string str = "U" + UsersController.Instance.CurrentUserId + "_";

		switch (key) {
		case Keys.LetterGroup:
			return str + "LastLetterGroup";
		}
		return null;
	}



	// Use this for initialization
	void Awake () {
		Instance = this;
		AddFirstFriendsToCollection(StartMonsters);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void SetLevelScoreIfNewRecord (int levelIndex, int score) {
		int currentLevelScore = GetLevelScore (levelIndex);
		PlayerPrefs.SetInt ("LevelScore" + levelIndex, Mathf.Max(currentLevelScore, score));
	}
	public int GetLevelScore(int levelIndex)
	{
		return PlayerPrefs.GetInt ("LevelScore" + levelIndex, 0);
	}

	public void SetLevelStarsIfNewRecord (int levelIndex, int stars) {
		int currentLevelScore = GetLevelStars (levelIndex);
		PlayerPrefs.SetInt ("LevelStars" + levelIndex, Mathf.Max(currentLevelScore, stars));
	}
	public int GetLevelStars(int levelIndex)
	{
		return PlayerPrefs.GetInt ("LevelStars" + levelIndex, 0);
	}


	public int SetMonsterLevelFaled(Monster monster)
	{
		int num = GetMonsterLevelFaled (monster) + 1;
		SetMonsterLevelFaled (monster, num);
		return num;
	}

	public void SetMonsterLevelFaled(Monster monster, int num)
	{
		PlayerPrefs.SetInt ("MonsterLevelFaled_" + ((int)monster.MonsterType).ToString (), num);
	}

	public int GetMonsterLevelFaled(Monster monster)
	{
		return PlayerPrefs.GetInt ("MonsterLevelFaled_" + ((int)monster.MonsterType).ToString (), 0);
	}
		
	public int SetMonsterLastUsed(Monster monster)
	{
		PlayerPrefs.SetString ("MonsterLastUsed_" + ((int)monster.MonsterType).ToString (), System.DateTime.Now.Date.Ticks.ToString());
		return GetMonsterLastUsed (monster);
	}


	public int GetToLevelCount()
	{
		return PlayerPrefs.GetInt ("LevelCount", 0);
	}

	public void SetToLevelCount(int count)
	{
		PlayerPrefs.SetInt("LevelCount", count);
	}


	/*
	 * return diff days
	 * 
	 */
	public int GetMonsterLastUsed(Monster monster)
	{
		long l = long.Parse(PlayerPrefs.GetString ("MonsterLastUsed_" + ((int)monster.MonsterType).ToString (), System.DateTime.Now.Date.Ticks.ToString()));

//		Debug.Log ("*** l: " + l.ToString ());

		DateTime now = DateTime.Now.Date;
		DateTime lastused = new DateTime(l);

		return (int)((now - lastused).TotalDays);
	}





	public MonsterEmotionTypes getEmotionType (Monster monster)
	{
		return (MonsterEmotionTypes)Enum.Parse(typeof(MonsterEmotionTypes), PlayerPrefs.GetInt ("MonsterEmotionType_" + ((int)monster.MonsterType).ToString (), 0).ToString());
	}



	public void SetEmotionType (Monster monster, MonsterEmotionTypes EmotionType)
	{
		PlayerPrefs.SetInt ("MonsterEmotionType_" + ((int)monster.MonsterType), (int)EmotionType);
	}





	public void SetMusic(bool enable)
	{
		PlayerPrefs.SetInt ("MusicEnable", enable ? 1 : 0);
	}

	public bool IsMusicEnable()
	{
		return PlayerPrefs.GetInt ("MusicEnable", 1) == 1;
	}

	public void SetSound(bool enable)
	{
		PlayerPrefs.SetInt ("SoundEnable", enable ? 1 : 0);
	}

	public bool IsSoundEnable()
	{
		return PlayerPrefs.GetInt ("SoundEnable", 1) == 1;
	}

	public int CollectionLength{
		get {
			return CollectedFriends.Length;

//			return CountCollectedFriends ();
		}
	}





	public void SetHighestOpenLevel(int levelIndex)
	{
		if(levelIndex > PlayerPrefs.GetInt("LevelOpenIndex", 0))
			PlayerPrefs.SetInt ("LevelOpenIndex", levelIndex);
	}

	public int GetHighestOpenLevel()
	{
		return PlayerPrefs.GetInt ("LevelOpenIndex", 0);
	}



	public void AddFirstFriendsToCollection(Monster[] monsters)
	{
		foreach(Monster monstser in monsters) {
			// no one shuld start ready
			monstser.IsReady = false;
			AddFriendToCollection (monstser);
			SetMonsterStatus (monstser);
		}
	}

	public void AddFriendToCollection(Monster monster)
	{
		if (HasCollectedFriend (monster)) {
			return;
		}
		PlayerPrefs.SetString ("Monster" + ((int)monster.MonsterType).ToString (), monster.name);
	}


	public bool HasCollectedFriend(Monster monster)
	{
		string collectedMonsterType = PlayerPrefs.GetString ("Monster" + ((int)monster.MonsterType).ToString (), "");
		if(collectedMonsterType == monster.name) {
			return true;
		}
		return false;
	}





	public Monster[] CollectedFriends { 
		get {
			List<Monster> monsters = new List<Monster>();

			foreach (MonsterType monsterType in Enum.GetValues(typeof(MonsterType))) {

				if (PlayerPrefs.HasKey ("Monster" + ((int)monsterType).ToString ())) {
					string collectedMonsterType = monsterType.ToString ();
					if (collectedMonsterType.Length > 0) {
						Monster monster = Resources.Load ("Gameplay/Monsters/" + collectedMonsterType) as Monster;
						monster.Gage = UserInfo.Instance.GetMonsterGage (monster);
						monster.GageValue = UserInfo.Instance.GetMonsterGageValue (monster);
						monster.IsReady = UserInfo.Instance.GetMonsterStatus (monster);

						monster.LastUse = UserInfo.Instance.GetMonsterLastUsed (monster);
						monster.LevelFaled = UserInfo.Instance.GetMonsterLevelFaled (monster);
						monster.EmotionType = UserInfo.Instance.getEmotionType (monster);

						monsters.Add (monster);
					}
				}
			}
			return monsters.ToArray();
		}
	}


	// Start Tzahi

	public bool GetMonsterStatus(Monster monster)
	{
		int status = PlayerPrefs.GetInt ("MonsterReady_" + ((int)monster.MonsterType).ToString (), 0);

		return (status == 1) ? true : false;
	}

	public void SetMonsterStatus(Monster monster)
	{
		PlayerPrefs.SetInt("MonsterReady_" + ((int)monster.MonsterType).ToString(), (monster.IsReady == true) ? 1 : 0);
	}

	public int GetMonsterGage(Monster monster)
	{
		return PlayerPrefs.GetInt("MonsterGage_" + ((int)monster.MonsterType).ToString(), 0);
	}

	public void SetMonsterGage(Monster monster)
	{
		PlayerPrefs.SetInt("MonsterGage_" + ((int)monster.MonsterType).ToString(), monster.Gage);
	}

	public float GetMonsterGageValue(Monster monster)
	{
		return PlayerPrefs.GetFloat("MonsterGageValue_" + ((int)monster.MonsterType).ToString(), 0f);
	}

	public void SetMonsterGageValue(Monster monster)
	{
		PlayerPrefs.SetFloat("MonsterGageValue_" + ((int)monster.MonsterType).ToString(), monster.GageValue);
	}

	public int GetLastPlayingLevel()
	{
		return PlayerPrefs.GetInt("LastPlayingLevel", 0);
	}

	public void SetLastPlayingLevel(int levelId)
	{
		PlayerPrefs.SetInt("LastPlayingLevel", levelId);
	}

	public void SetHadMinigameTutorial(int hadMinigameTutorial)
	{
		PlayerPrefs.SetInt ("HadMinigameTutorial", hadMinigameTutorial);
	}
	public int GetHadMinigameTutorial()
	{
		return PlayerPrefs.GetInt ("HadMinigameTutorial");
	}


	public void SetLastLetterGroup (int letterGroup) {
		int currentGroup = GetLastLetterGroup ();
		PlayerPrefs.SetInt (getPrefsKey(Keys.LetterGroup), Mathf.Max(currentGroup, letterGroup));
	}
	public int GetLastLetterGroup ()
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.LetterGroup), 1);
	}



	// End Tzahi

}
