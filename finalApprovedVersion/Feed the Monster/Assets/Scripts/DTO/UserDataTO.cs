using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class UserDataTO
{
	public string UserId;
	public int HighestOpenLevel;
	public int LastPlayingLevel;
	public int LastLetterGroup;
	public int LastMonsterIndex;

	public int LastPettingZoneTutorial;

	public bool HasReadyMonster;
	public int MiniGameTutorialCount;
	public int NewAvailableAccessorie;

	public UserLevelTO[] Levels;
	public UserMonsterTO[] Monsters;


	Dictionary<int, UserLevelTO> mLevels = null;
	Dictionary<MonsterType, UserMonsterTO> mMonsters = null;

//	public bool isChanged { get; set; }

	public void MarkToSave() {
		UsersController.Instance.save (this);
	}

	public int getHighestOpenLevel() {
		if (HighestOpenLevel < 0) {
			HighestOpenLevel = 0;
		}
		return HighestOpenLevel;
	}
	public bool setHighestOpenLevel(int levelId) {
		if (levelId > HighestOpenLevel) {
			HighestOpenLevel = levelId;
			MarkToSave ();
			return true;
		}
		return false;
	}

	public int getLastPlayingLevel() {
		if (LastPlayingLevel < 0) {
			LastPlayingLevel = 0;
		}
		return LastPlayingLevel;
	}
	public void setLastPlayingLevel(int levelId) {
		if (LastPlayingLevel != levelId) {
			LastPlayingLevel = levelId;
			MarkToSave ();
		}
	}

	public int getLastLetterGroup () {
		if (LastLetterGroup == 0) {
			setLastLetterGroup (1);
		}

		return LastLetterGroup;
	}
	public void setLastLetterGroup (int letterGroup) {
		int newLetterGroup = Mathf.Max (LastLetterGroup, letterGroup);
		if(newLetterGroup > LastLetterGroup) {
			LastLetterGroup = newLetterGroup;
			MarkToSave ();
		}
	}

	public int getLastMonsterIndex () {
		return LastMonsterIndex;
	}
	public void setLastMonsterIndex (int monsterIndex) {
		if (LastMonsterIndex != monsterIndex) {
			LastMonsterIndex = monsterIndex;
			MarkToSave ();
		}
	}

	public int getLastPettingZoneTutorial () {
		return LastPettingZoneTutorial;
	}
	public void setLastPettingZoneTutorial (int lastPettingZoneTutorial) {
		if (LastPettingZoneTutorial != lastPettingZoneTutorial) {
			LastPettingZoneTutorial = lastPettingZoneTutorial;
			MarkToSave ();
		}
	}


	public bool getHasReadyMonster () {
		return HasReadyMonster;
	}
	public void setReadyMonster () {
		if (!HasReadyMonster) {
			HasReadyMonster = true;
			MarkToSave ();
		}
	}

	public int getMiniGameTutorialCount () {
		return MiniGameTutorialCount;
	}
	public void addToMiniGameTutorialCount () {
		MiniGameTutorialCount++;
		MarkToSave ();
	}


	#region Levels
		void OrganizeLevel() {
			if (mLevels == null) {
				mLevels = new Dictionary<int, UserLevelTO> ();
				if (Levels != null) {
					foreach (UserLevelTO l in Levels) {
						if (l != null) {
							mLevels.Add (l.levelId, l);
						}
					}
				} else {
					Levels = new UserLevelTO[0];
				}
			}
		}
		void updateLevelArray() {
			List<UserLevelTO> l = new List<UserLevelTO> (mLevels.Values);
			Levels = l.ToArray ();
		}

		UserLevelTO getLevel(int levelId) {
			UserLevelTO level = null;
			if (mLevels != null) {
				if (!mLevels.ContainsKey (levelId)) {
					mLevels.Add (levelId, UserLevelTO.create (levelId, 0, 0));	
				}
				level = mLevels [levelId];
			}
			return level;
		}


	public void setLevelStars (int levelId, int stars) {
		UserLevelTO level = getLevel(levelId);
		
		int max = Mathf.Max (level.levelStars, stars);
		if(level.levelStars < max) {
			level.levelStars = max;	
			MarkToSave ();
		}
	}
	public int getLevelStars(int levelId) {
		UserLevelTO level = getLevel(levelId);
		return level.levelStars;
	}

	public int getLevelScore(int levelId) {
		UserLevelTO level = getLevel(levelId);
		return level.levelScore;
	}
	public void setLevelScore (int levelId, int score) {
		UserLevelTO level = getLevel(levelId);
		int max = Mathf.Max (level.levelScore, score);
		if (level.levelScore < max) {
			level.levelScore = max;
		MarkToSave ();
		}
	}
	#endregion

	#region Monsters
	void OrganizeMonsters()
	{
		if (mMonsters == null) {
			mMonsters = new Dictionary<MonsterType, UserMonsterTO> ();
			if (Monsters != null) {
				foreach (UserMonsterTO m in Monsters) {
					if (m != null) {
						mMonsters.Add (m.monsterType, m);
					}
				}
			} else {
				Monsters = new UserMonsterTO[0];
			}
		}
	}

	void updateMonsterArray() {
		List<UserMonsterTO> m = new List<UserMonsterTO> (mMonsters.Values);
		Monsters = m.ToArray ();
	}

	UserMonsterTO getMonster(MonsterType monsterType) {
		UserMonsterTO monster = null;

		if (mMonsters != null && mMonsters.ContainsKey (monsterType)) {
			monster = mMonsters [monsterType];
		}
		return monster;
	}

	public int CollectionLength {
		get {
			int num = 0;

			if (mMonsters != null) {
				num = mMonsters.Count;
			}
			return num;
		}
	}

	public int setMonsterLevelFaled(Monster monster) {
		int num = getMonsterLevelFaled (monster) + 1;
		setMonsterLevelFaled (monster, num);
		return num;
	}
	public void setMonsterLevelFaled(Monster monster, int num) {
		if (monster.MiniGame == MiniGameController.GameType.None) {
			return;
		}
		UserMonsterTO userMonster = getMonster(monster.MonsterType); 
		userMonster.monsterLevelFaled = num;
	MarkToSave ();
	}
	public int getMonsterLevelFaled(Monster monster) {
		UserMonsterTO userMonster = getMonster(monster.MonsterType); 
		return userMonster.monsterLevelFaled;
	}

	public int setMonsterLastUsed(Monster monster) {
		UserMonsterTO userMonster = getMonster(monster.MonsterType); 
		userMonster.monsterLastUsed = DateTime.Now;

		MarkToSave ();

		return getMonsterLastUsed (monster.MonsterType);
	}

	public int getMonsterLastUsed(MonsterType monsterType) {
		UserMonsterTO userMonster = getMonster(monsterType); 
		DateTime now = DateTime.Now.Date;
		return (int)((now - userMonster.monsterLastUsed).TotalDays);
	}

	public MonsterEmotionTypes getMonsterEmotionType (Monster monster)
	{
		UserMonsterTO userMonster = getMonster(monster.MonsterType); 
		return userMonster.monsterEmotionType;
	}
	public void setMonsterEmotionType (Monster monster, MonsterEmotionTypes emotionType)
	{
		if (emotionType == MonsterEmotionTypes.NONE) {
			return;
		}
		UserMonsterTO userMonster = getMonster(monster.MonsterType); 
		userMonster.monsterEmotionType = emotionType;
	MarkToSave ();
	}

	public void addFirstFriendsToCollection() {
		addFriendToCollection (MonsterType.Magnet);
	}

	public void addFriendToCollection(MonsterType monsterType) {
		UserMonsterTO userMonster = getMonster (monsterType);
		
		if (userMonster == null) {
			mMonsters.Add(monsterType, UserMonsterTO.create (monsterType));
		MarkToSave ();
		}
	}

	public bool getMonsterStatus(Monster monster) {
		UserMonsterTO um = getMonster (monster.MonsterType);
		bool status = false;
		if (um != null) {
			status = um.monsterReady;
		}
		return status;
	}

	public void setMonsterStatus(Monster monster) {
		UserMonsterTO um = getMonster (monster.MonsterType);
		um.monsterReady = monster.IsReady;
		MarkToSave ();
	}

	public void setMonsterStatus(MonsterType monsterType, bool isReady) {
		UserMonsterTO um = getMonster (monsterType);
		um.monsterReady = isReady;
		MarkToSave ();
	}

	public int getMonsterGage(Monster monster) {
		UserMonsterTO um = getMonster (monster.MonsterType);
		return um.monsterGage;
	}
	public void setMonsterGage(Monster monster)	{
		UserMonsterTO um = getMonster (monster.MonsterType);
		um.monsterGage = monster.Gage;
		MarkToSave ();
	}

	public float getMonsterGageValue(Monster monster) {
		UserMonsterTO um = getMonster (monster.MonsterType);
		return um.monsterGageValue;
	}
	public void setMonsterGageValue(Monster monster) {
		UserMonsterTO um = getMonster (monster.MonsterType);
		um.monsterGageValue = monster.GageValue;
		MarkToSave ();
	}

	public int getNewAvailableAccessorie() {
		return NewAvailableAccessorie;
	}

	public void setNewAvailableAccessorie(int itemId) {
		NewAvailableAccessorie = itemId;
		MarkToSave ();
	}

	public void resetNewAvailableAccessories() {
		NewAvailableAccessorie = -1;
		MarkToSave ();
	}

	public MonsterAccessoryTO getMonsterAccessory(Monster monster, int categoryId) {
		return getMonsterAccessory (monster.MonsterType, categoryId);
	}

	public MonsterAccessoryTO getMonsterAccessory(MonsterType monsterType, int categoryId) {
		UserMonsterTO um = getMonster (monsterType);
		
		if (um.monsterAccessories == null) {
			um.monsterAccessories = new  MonsterAccessoryTO[5];
		}
		if (um.monsterAccessories.Length < categoryId) {
			Array.Resize<MonsterAccessoryTO>(ref  um.monsterAccessories, 5);
		}
		if (um.monsterAccessories [categoryId] != null) {
			return um.monsterAccessories [categoryId];
		}
		return null;
	}

	public void updateMonsterAccessory(Monster monster, int categoryId, MonsterAccessoryTO monsterItem) {
		UserMonsterTO um = getMonster (monster.MonsterType);

		if (um.monsterAccessories == null) {
			um.monsterAccessories = new MonsterAccessoryTO[5];
		}
		if (um.monsterAccessories.Length < categoryId) {
			Array.Resize<MonsterAccessoryTO>(ref  um.monsterAccessories, 5);
		}
		um.monsterAccessories [categoryId] = monsterItem;

		MarkToSave ();
	}


	public bool HasMonster(Monster monster) {
		return HasMonster (monster.MonsterType);
	}
	public bool HasMonster(MonsterType monsterType) {
		return mMonsters.ContainsKey (monsterType);
	}

	public Monster[] getCollectedMonsters { 
		get {
			List<Monster> monsters = new List<Monster>();
			addFirstFriendsToCollection ();
			foreach (UserMonsterTO m in mMonsters.Values) {
				string collectedMonsterType = m.monsterType.ToString ();
				if (!string.IsNullOrEmpty(collectedMonsterType)) {
					Monster monster = Resources.Load ("Gameplay/Monsters/" + collectedMonsterType) as Monster;
					if (monster != null) {
						monster.reset ();
						monster.IsReady = m.monsterReady;
						monster.Gage = m.monsterGage;
						monster.GageValue = m.monsterGageValue;
						monster.LastUse = getMonsterLastUsed(m.monsterType);
						monster.LevelFaled = m.monsterLevelFaled;
						//monster.EmotionType = m.monsterEmotionType;
						monster.updateEmotionType ();
						monsters.Add (monster);
					}
				}
			}
		return monsters.ToArray();
		}
	}

	#endregion

	public void Organize()
	{
		OrganizeLevel ();
		OrganizeMonsters ();
	}


	public string toJson()
	{
		updateLevelArray ();
		updateMonsterArray ();

		string json = JsonUtility.ToJson (this);
		return json;
	}

	public static UserDataTO create(string json, string userId)
	{
		UserDataTO userData = JsonUtility.FromJson<UserDataTO> (json);
//		Debug.Log (json);
		userData.UserId = userId;
		userData.OrganizeLevel ();
		userData.OrganizeMonsters ();

		return userData;
	}
}
