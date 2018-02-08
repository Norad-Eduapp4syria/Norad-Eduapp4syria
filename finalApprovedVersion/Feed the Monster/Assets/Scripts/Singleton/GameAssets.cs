using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameAssets : MonoBehaviour {

	public static GameAssets Instance;


	public static int CurrentLevelIndex = 0;
	public static int NextLevelIndex = -1;

	public GameObject tutorialHend;

	public int NumOfLevels = 76;


	public Sprite[] ProfileSprites;
	public AudioClip ClickSound;
	public Level DefaultLevelTempletes;


	public bool DEBUG_ACTIVE;

	[HideInInspector]
	public Monster NewMonster = null;

	[HideInInspector]
	public string NextScene = string.Empty;

	[HideInInspector]
	public MiniGameController.GameType ForceMiniGame =  MiniGameController.GameType.None;

	[HideInInspector]
	public bool MiniGameAsLevel = false;


	[HideInInspector]
	public MonsterType ForceMonster = MonsterType.NONE;

	[HideInInspector]
	public MonsterType DefaultMonster = MonsterType.NONE;


	[HideInInspector]
	public bool AutoStartMiniGame = false;

	[HideInInspector]
	public GameObject BonusPazzleGO = null;

	void Awake () {
		if (Instance == null) {
			Instance = this;
			DontDestroyOnLoad (gameObject);
			SingletonLoader.CheckSingleton();
		} else if (Instance != this) {
			Destroy (gameObject);
		}

	}


	public void init()
	{

	}


}
