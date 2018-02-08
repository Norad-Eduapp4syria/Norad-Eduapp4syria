using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class UserMonsterTO
{
	public MonsterType monsterType;

	public int monsterLevelFaled;
	public long LastUsed;
	public MonsterEmotionTypes monsterEmotionType;
	public bool monsterReady;
	public int monsterGage;
	public float monsterGageValue;

	public MonsterAccessoryTO[] monsterAccessories;

	public static UserMonsterTO create(MonsterType type)
	{
		UserMonsterTO monster = new UserMonsterTO ();
		monster.monsterType = type;
		monster.monsterLevelFaled = 0;
		monster.monsterLastUsed = DateTime.Now;
		monster.monsterEmotionType = MonsterEmotionTypes.Happy;
		monster.monsterReady = false;
		monster.monsterGage = 0;
		monster.monsterGageValue = 0;
		monster.monsterAccessories = new MonsterAccessoryTO[5];
		return monster;
	}


	public DateTime monsterLastUsed
	{
		get { 
			return new DateTime (LastUsed);
		}
		set {
			LastUsed = value.Ticks;
		}
	}





}