using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StateConverter_2 : MonoBehaviour {
	public Action onDone;

	// Use this for initialization
	void Start () {
		int DataVersion = SaveStatConnector.Instance.DataVersion;

		if (DataVersion < 2) {
			convertToVer_2 ();
		}
		if (onDone != null) {
			onDone ();
		}
		Destroy (this);
	}

	#region ver 2
	void convertToVer_2()
	{
		for (int profileId = 0; profileId <= 4; profileId++) {
			UserDataTO userData = convertProfile_2 (profileId);
			if (userData != null) {
				userData.Organize ();
				UsersController.Instance.save (userData, false);
			}
		}
		SaveStatConnector.Instance.DataVersion = 2;
	}

	UserDataTO convertProfile_2(int profileId) {
		UserDataTO userData = UsersController.Instance.userData(profileId);
		//		UserDataTO userData = new UserDataTO ();
		userData.UserId = UsersController.LocalUserPrefix + profileId.ToString ();

		userData.HighestOpenLevel = PlayerPrefs.GetInt (getPrefsKey_2(Keys_2.LevelOpenIndex, profileId), -1);
		userData.LastPlayingLevel = PlayerPrefs.GetInt(getPrefsKey_2(Keys_2.LastPlayingLevel, profileId), -1);

		if (userData.HighestOpenLevel == -1 && userData.LastPlayingLevel == -1) {
			return null;
		}

		userData.LastLetterGroup = PlayerPrefs.GetInt (getPrefsKey_2(Keys_2.LetterGroup, profileId), 1);
		userData.LastMonsterIndex = PlayerPrefs.GetInt(getPrefsKey_2(Keys_2.LastMonsterIndex, profileId), 0);
		userData.LastPettingZoneTutorial = PlayerPrefs.GetInt(getPrefsKey_2(Keys_2.LastPettingZoneTutorial, profileId), -1);
		userData.Levels = convertLevels_2 (profileId);
		userData.Monsters = convertMonsters_2 (profileId);

		return userData;
	}

	UserLevelTO[] convertLevels_2(int profileId) {
		List<UserLevelTO> levels = new List<UserLevelTO> ();

		for (int i = 0; i < GameAssets.Instance.NumOfLevels; i++) {
			UserLevelTO level = new UserLevelTO();
			level.levelId = i;
			level.levelScore = PlayerPrefs.GetInt (getPrefsKey_2(Keys_2.LevelScore, profileId, i.ToString()), 0);
			level.levelStars = PlayerPrefs.GetInt (getPrefsKey_2(Keys_2.LevelStars, profileId, i.ToString()), 0);
			levels.Add (level);
		}
		return levels.ToArray ();
	}

	UserMonsterTO[] convertMonsters_2(int profileId) {
		List<UserMonsterTO> monsters = new List<UserMonsterTO> ();

		foreach (MonsterType type in Enum.GetValues(typeof(MonsterType)))
		{
			if (type != MonsterType.NONE) {
				UserMonsterTO monster = new UserMonsterTO ();

				monster.monsterType = type;

				monster.monsterLevelFaled	= PlayerPrefs.GetInt (getPrefsKey_2 (Keys_2.MonsterLevelFaled,	profileId, ((int)type).ToString ()), 0);
				monster.monsterLastUsed = new DateTime (long.Parse (PlayerPrefs.GetString	(getPrefsKey_2 (Keys_2.MonsterLastUsed, profileId, ((int)type).ToString ()), System.DateTime.Now.Date.Ticks.ToString ())));
				monster.monsterEmotionType	= (MonsterEmotionTypes)Enum.Parse (typeof(MonsterEmotionTypes), (PlayerPrefs.GetInt (getPrefsKey_2 (Keys_2.MonsterEmotionType,	profileId, ((int)type).ToString ()), 0)).ToString ());
				monster.monsterReady = ((PlayerPrefs.GetInt (getPrefsKey_2 (Keys_2.MonsterReady, profileId, ((int)type).ToString ()), 0)) == 1) ? true : false;

				monster.monsterGage = PlayerPrefs.GetInt (getPrefsKey_2 (Keys_2.MonsterGage, profileId, ((int)type).ToString ()), 0);
				monster.monsterGageValue	= PlayerPrefs.GetFloat	(getPrefsKey_2 (Keys_2.MonsterGageValue, profileId, ((int)type).ToString ()), 0f);

				monsters.Add (monster);
			}
		}
		return monsters.ToArray ();
	}


	public enum Keys_2
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
		LastMonsterType,
		LastPettingZoneTutorial,
	}

	public string getPrefsKey_2(Keys_2 key, int profileId, string val)
	{
		string str = getPrefsKey_2(key, profileId);
		if (!string.IsNullOrEmpty (val)) {
			str += "_" + val; 
		}
		return str;
	}

	public string getPrefsKey_2(Keys_2 key, int profileId)
	{
		string str = "U_";
		if (profileId > -1) {
			str += profileId;
		} else {
			str += UsersController.Instance.CurrentProfileId;
		}
		str += "_";

		switch (key) {

		case Keys_2.LevelScore:
			return str + "LevelScore";
		case Keys_2.LevelStars:
			return str + "LevelStars";
		case Keys_2.LevelCount:
			return str + "LevelCount";
		case Keys_2.MonsterLevelFaled:
			return str + "MonsterLevelFaled";
		case Keys_2.MonsterLastUsed:
			return str + "MonsterLastUsed";
		case Keys_2.LetterGroup:
			return str + "LastLetterGroup";
		case Keys_2.MonsterEmotionType:
			return str + "MonsterEmotionType";
		case Keys_2.LevelOpenIndex:
			return str + "LevelOpenIndex";
		case Keys_2.Monster:
			return str + "Monster";
		case Keys_2.MonsterReady:
			return str + "MonsterReady";
		case Keys_2.MonsterGage:
			return str + "MonsterGage";
		case Keys_2.MonsterGageValue:
			return str + "MonsterGageValue";
		case Keys_2.LastPlayingLevel:
			return str + "LastPlayingLevel";
		case Keys_2.LastPettingZoneTutorial:
			return str + "LastPettingZoneTutorial";
		}
		return str;
	}
	#endregion
}
