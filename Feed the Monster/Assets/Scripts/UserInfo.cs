using UnityEngine;
using System;
using System.Collections;
using System.Linq;
using System.Collections.Generic;

public class UserInfo : MonoBehaviour {
	public static UserInfo Instance;
	public Monster[] StartMonsters;


	bool isInited = false;
	bool isMusic;
	bool isSound;
	int lastProfileId = -1;


	enum Keys
	{
		LevelScore,
		LevelStars,
		LevelCount,

		LetterGroup,
		MonsterLevelFaled,
		MonsterLastUsed,

		MonsterEmotionType,
		LevelOpenIndex,
		Monster,
		MonsterReady,
		MonsterGage,
		MonsterGageValue,
		LastPlayingLevel,
		LastMonsterIndex,
		LastPettingZoneTutorial,

	}

	string getPrefsKey(Keys key, string val)
	{
		string str = getPrefsKey(key, -1);
		if (!string.IsNullOrEmpty (val)) {
			str += "_" + val; 
		}
		return str;
	}

	string getPrefsKey(Keys key)
	{
		return getPrefsKey (key, -1);
	}

	string getPrefsKey(Keys key, int profileId)
	{
		string str = "U_";
		if (profileId > -1) {
			str += profileId;
		} else {
			str += UsersController.Instance.CurrentProfileId;
		}
		str += "_";

		switch (key) {

		case Keys.LevelScore:
			return str + "LevelScore";
		case Keys.LevelStars:
			return str + "LevelStars";
		case Keys.LevelCount:
			return str + "LevelCount";
		case Keys.MonsterLevelFaled:
			return str + "MonsterLevelFaled";
		case Keys.MonsterLastUsed:
			return str + "MonsterLastUsed";
		case Keys.LetterGroup:
			return str + "LastLetterGroup";
		case Keys.MonsterEmotionType:
			return str + "MonsterEmotionType";
		case Keys.LevelOpenIndex:
			return str + "LevelOpenIndex";
		case Keys.Monster:
			return str + "Monster";
		case Keys.MonsterReady:
			return str + "MonsterReady";
		case Keys.MonsterGage:
			return str + "MonsterGage";
		case Keys.MonsterGageValue:
			return str + "MonsterGageValue";
		case Keys.LastPlayingLevel:
			return str + "LastPlayingLevel";
		case Keys.LastPettingZoneTutorial:
			return str + "LastPettingZoneTutorial";
		}
		return str;
	}

	// Use this for initialization
	void Awake () {
		Instance = this;
		IsMusicEnable ();
		IsSoundEnable ();
		isInited = true;
	}

	void Start () {
		AddFirstFriendsToCollection();
	}

	// Update is called once per frame
	void Update () {
	
	}

	public void Save()
	{
		PlayerPrefs.Save ();
	}

	public void SetMusic(bool enable)
	{
		isMusic = enable;
		PlayerPrefs.SetInt ("MusicEnable", enable ? 1 : 0);
	}

	public bool IsMusicEnable()
	{
		if (!isInited) {
			isMusic = (PlayerPrefs.GetInt ("MusicEnable", 1) == 1);
		}
		return isMusic;
	}

	public void SetSound(bool enable)
	{
		isSound = enable;
		PlayerPrefs.SetInt ("SoundEnable", enable ? 1 : 0);
	}
	public bool IsSoundEnable()
	{
		if (!isInited) {
			isSound = (PlayerPrefs.GetInt ("SoundEnable", 1) == 1);
		}
		return isSound;
	}

	public void SetLastProfileId(int profileId)
	{
		lastProfileId = profileId;
		PlayerPrefs.SetInt ("LastProfileId", lastProfileId);
	}
	public int GetLastProfileId()
	{
		if (lastProfileId == -1) {
			lastProfileId = PlayerPrefs.GetInt ("LastProfileId", -1);
		}
		return lastProfileId;
	}

	public void SetLevelStarsIfNewRecord (int levelIndex, int stars) {
		int currentLevelScore = GetLevelStars (levelIndex);
		PlayerPrefs.SetInt (getPrefsKey(Keys.LevelStars, levelIndex.ToString()), Mathf.Max(currentLevelScore, stars));
	}
	public int GetLevelStars(int levelIndex)
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.LevelStars, levelIndex.ToString()), 0);
	}

	public int SetMonsterLevelFaled(Monster monster)
	{
		int num = GetMonsterLevelFaled (monster) + 1;
		SetMonsterLevelFaled (monster, num);
		return num;
	}

	public void SetMonsterLevelFaled(Monster monster, int num)
	{
		if (monster.MiniGame == MiniGameController.GameType.None) {
			return;
		}
		PlayerPrefs.SetInt (getPrefsKey(Keys.MonsterLevelFaled, ((int)monster.MonsterType).ToString ()), num);
	}

	public int GetMonsterLevelFaled(Monster monster)
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.MonsterLevelFaled, ((int)monster.MonsterType).ToString ()), 0);
	}
		
	public int SetMonsterLastUsed(Monster monster)
	{
		PlayerPrefs.SetString (getPrefsKey(Keys.MonsterLastUsed, ((int)monster.MonsterType).ToString ()), System.DateTime.Now.Date.Ticks.ToString());
		return GetMonsterLastUsed (monster);
	}

//	public int GetToLevelCount()
//	{
//		return PlayerPrefs.GetInt (getPrefsKey(Keys.LevelCount), 0);
//	}

//	public void SetToLevelCount(int count)
//	{
//		PlayerPrefs.SetInt(getPrefsKey(Keys.LevelCount), count);
//	}

	/*
	 * return diff days
	 * 
	 */
	public int GetMonsterLastUsed(Monster monster)
	{
		long l = long.Parse(PlayerPrefs.GetString (getPrefsKey(Keys.MonsterLastUsed, ((int)monster.MonsterType).ToString ()), System.DateTime.Now.Date.Ticks.ToString()));

		DateTime now = DateTime.Now.Date;
		DateTime lastused = new DateTime(l);

		return (int)((now - lastused).TotalDays);
	}

	public MonsterEmotionTypes getEmotionType (Monster monster)
	{
		int type = PlayerPrefs.GetInt (getPrefsKey(Keys.MonsterEmotionType, ((int)monster.MonsterType).ToString ()), 0);

		return (MonsterEmotionTypes)Enum.Parse(typeof(MonsterEmotionTypes), type.ToString());
	}

	public void SetEmotionType (Monster monster, MonsterEmotionTypes EmotionType)
	{

		if (EmotionType == MonsterEmotionTypes.NONE) {
			return;
		}

		PlayerPrefs.SetInt (
			getPrefsKey(
				Keys.MonsterEmotionType,
				((int)monster.MonsterType).ToString()
			)
		, (int)EmotionType
		);
	}

	public int CollectionLength {
		get {
			return CollectedFriends.Length;
		}
	}

	public void SetHighestOpenLevel(int levelIndex)
	{
		if (levelIndex > PlayerPrefs.GetInt (getPrefsKey (Keys.LevelOpenIndex), 0)) {
			PlayerPrefs.SetInt (getPrefsKey (Keys.LevelOpenIndex), levelIndex);
		}
	}

	public int GetHighestOpenLevel()
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.LevelOpenIndex), 0);
	}

	public int GetHighestOpenLevel(int profileId)
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.LevelOpenIndex, profileId), 0);
	}

	public void AddFirstFriendsToCollection()
	{
		if (UIController.Instance.DEBUG_ADD_ALL_MONSTERS == true) {
			foreach (MonsterType type in Enum.GetValues(typeof(MonsterType)))
			{
				PlayerPrefs.SetString (getPrefsKey(Keys.Monster, ((int)type).ToString ()), type.ToString());
			}
		}

		foreach(Monster monster in StartMonsters) {
			// no one shuld start ready
			Monster mo = Instantiate (monster);

			mo.IsReady = false;
			AddFriendToCollection (mo);
			SetMonsterStatus (mo);
		}
	}

	public void AddFriendToCollection(Monster monster)
	{
		if (HasCollectedFriend (monster)) {
			return;
		}
		PlayerPrefs.SetString (getPrefsKey(Keys.Monster, ((int)monster.MonsterType).ToString ()), monster.name);
	}

	public bool HasCollectedFriend(Monster monster)
	{
		string collectedMonsterType = PlayerPrefs.GetString (getPrefsKey(Keys.Monster, ((int)monster.MonsterType).ToString ()), "");
		if(collectedMonsterType == monster.name) {
			return true;
		}
		return false;
	}

	public Monster[] CollectedFriends { 
		get {
			List<Monster> monsters = new List<Monster>();

			foreach (MonsterType monsterType in Enum.GetValues(typeof(MonsterType))) {

				if (monsterType!= MonsterType.NONE && PlayerPrefs.HasKey (getPrefsKey(Keys.Monster, ((int)monsterType).ToString ()))) {
					string collectedMonsterType = monsterType.ToString ();
					if (collectedMonsterType.Length > 0) {
						Monster monster = Resources.Load ("Gameplay/Monsters/" + collectedMonsterType) as Monster;
						if (monster != null) {
							monster.reset ();
							monster.IsReady = UserInfo.Instance.GetMonsterStatus (monster);
//							monster.Gage = UserInfo.Instance.GetMonsterGage (monster);
//							monster.GageValue = UserInfo.Instance.GetMonsterGageValue (monster);
							monster.LastUse = UserInfo.Instance.GetMonsterLastUsed (monster);
							monster.LevelFaled = UserInfo.Instance.GetMonsterLevelFaled (monster);
//							monster.EmotionType = UserInfo.Instance.getEmotionType (monster);
							monster.updateEmotionType();
							monsters.Add (monster);
						}
					}
				}
			}
			return monsters.ToArray();
		}
	}

	// Start Tzahi

	public bool GetMonsterStatus(Monster monster)
	{
		string key = getPrefsKey (Keys.MonsterReady, ((int)monster.MonsterType).ToString ());

		int status = 0;

		if (PlayerPrefs.HasKey (key)) {
			status = PlayerPrefs.GetInt (key, 0);
		}

		return (status == 1) ? true : false;
	}

	public void SetMonsterStatus(Monster monster)
	{
		string key = getPrefsKey (Keys.MonsterReady, ((int)monster.MonsterType).ToString ());
		PlayerPrefs.SetInt(key, (monster.IsReady == true) ? 1 : 0);
	}

	public int GetMonsterGage(Monster monster)
	{
		return PlayerPrefs.GetInt(getPrefsKey(Keys.MonsterGage, ((int)monster.MonsterType).ToString()), 0);
	}

	public void SetMonsterGage(Monster monster)
	{
		PlayerPrefs.SetInt(getPrefsKey(Keys.MonsterGage, ((int)monster.MonsterType).ToString()), monster.Gage);
	}

	public float GetMonsterGageValue(Monster monster)
	{
		return PlayerPrefs.GetFloat(getPrefsKey(Keys.MonsterGageValue, ((int)monster.MonsterType).ToString()), 0f);
	}

	public void SetMonsterGageValue(Monster monster)
	{
		PlayerPrefs.SetFloat(getPrefsKey(Keys.MonsterGageValue, ((int)monster.MonsterType).ToString()), monster.GageValue);
	}

	public int GetLastPlayingLevel()
	{
		return PlayerPrefs.GetInt(getPrefsKey(Keys.LastPlayingLevel), 0);
	}
	public void SetLastPlayingLevel(int levelId)
	{
		PlayerPrefs.SetInt(getPrefsKey(Keys.LastPlayingLevel), levelId);
	}

	public void SetLastLetterGroup (int letterGroup) {
		int currentGroup = GetLastLetterGroup ();
		PlayerPrefs.SetInt (getPrefsKey(Keys.LetterGroup), Mathf.Max(currentGroup, letterGroup));
	}
	public int GetLastLetterGroup ()
	{
		return PlayerPrefs.GetInt (getPrefsKey(Keys.LetterGroup), 1);
	}

	public int GetLastMonsterIndex ()
	{
		return PlayerPrefs.GetInt(getPrefsKey(Keys.LastMonsterIndex), 0);
	}
	public void SetLastMonsterIndex (int monsterIndex)
	{
		PlayerPrefs.SetInt(getPrefsKey(Keys.LastMonsterIndex), monsterIndex);
	}


	public int GetLastPettingZoneTutorial ()
	{
		return PlayerPrefs.GetInt(getPrefsKey(Keys.LastPettingZoneTutorial), -1);
	}
	public void SetLastPettingZoneTutorial (int monsterIndex)
	{
		PlayerPrefs.SetInt(getPrefsKey(Keys.LastPettingZoneTutorial), monsterIndex);
	}

	// End Tzahi

}
