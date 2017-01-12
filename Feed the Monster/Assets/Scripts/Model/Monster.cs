using UnityEngine;
using System.Collections;
using System.Collections.Generic;


[System.Serializable]
public class Monster : ScriptableObject {
//	public Sprite Icon;
//	public Sprite Name;
	public Booster.BoosterType booster = Booster.BoosterType.NONE;
//	public string SpritesheetName;
	public MonsterType MonsterType;



	// Start Tzahi

	public GameObject MonsterPrefab;

	static int NumGages = 4;
	public int[] GageCost = new int[NumGages];
	public GameObject[] PlayGameObjects = new GameObject[NumGages];
//	public GameObject[] UIGameObject = new GameObject[NumGages];

	public List<int> IdleStates;
	public List<int> EatStates;
	public List<int> NoEatStates;

	public List<int> HappyStates;
	public List<int> SadStates;
	public List<int> ImpatientStates;

	public float Pitch = 1;

	bool _isReady = false;
	int _gage;
	float _gageValue;

	int _lastUse;
	int _levelFaled;
	MonsterEmotionTypes _emotionType;


	public bool AddGageValue(float addedCost)
	{
		bool isGageChanged = false;

		float costToValue = (100f / currentGageCost);
		float valueToCost = (currentGageCost / 100f);
		float neededValue = (100f - _gageValue);
		float neededCost = neededValue * valueToCost;

		if (addedCost < neededCost) {
			_gageValue += costToValue * addedCost;
		} else {
			_gage++;
			_gageValue = 0;
			isGageChanged = true;

//			if (addedCost > neededCost) {
//				float balance = addedCost - neededCost;
//				AddGageValue ((int)balance);
//				return isGageChanged;
//			}
		}

		UserInfo.Instance.SetMonsterGage (this);
		UserInfo.Instance.SetMonsterGageValue (this);
		if (_gage >= NumGages - 1) {
			IsReady = true;
		}

		return isGageChanged;
	}

	public bool IsReady
	{
		get { 
			if (_gage >= NumGages - 1) {
				return true;
			}
			return _isReady;
		}
		set { 
			_isReady = value;
			UserInfo.Instance.SetMonsterStatus (this);
		}
	}



	public int Gage
	{
		get { 
			if (_gage < 0) {
				return 0;
			} else if(_gage > TotalGages){
				return TotalGages;			
			}
			return _gage;
		}
		set { 
			_gage = value;
			UserInfo.Instance.SetMonsterGage (this);
		}
	}

	public float GageValue
	{
		get { 
			if (_gageValue < 0) {
				return 0;
			} else if(_gageValue > 100){
				return 100;
			}
			return _gageValue;
		}
		set { 
			_gageValue = value;
			UserInfo.Instance.SetMonsterGageValue (this);
		}
	}

	public int LastUse
	{
		set { 
			_lastUse = value;
		}
		get { 
			return _lastUse;
		}
	}

	public int LevelFaled
	{
		set { 
			_levelFaled = value;
		}
		get { 
			return _levelFaled;
		}
	}


	public int TotalGages
	{
		get {
			//return Mathf.Min(new int[3]{GageCost.Length, UIGameObject.Length, PlayGameObjects.Length});
			return Mathf.Min(new int[2]{GageCost.Length, PlayGameObjects.Length});
		}
	}



	public int currentGageCost
	{
		get {
			if (GageCost.Length > Gage) {
				return GageCost [Gage];
			} else {
				return GageCost [GageCost.Length - 1];
			}
		}
	}

	public GameObject currentPlayGO
	{
		get {

			if (IsReady == false && PlayGameObjects.Length > Gage) {
				return PlayGameObjects [Gage];
			} else {
				return PlayGameObjects [PlayGameObjects.Length - 1];
			}
		}
	}



	public void ResetEmotion()
	{
		EmotionType = MonsterEmotionTypes.Happy;
		_lastUse = UserInfo.Instance.SetMonsterLastUsed (this);
		UserInfo.Instance.SetMonsterLevelFaled (this, 0);
		_levelFaled = 0;
	}



	public MonsterEmotionTypes EmotionType
	{
		get {
			return _emotionType;
		}
		set {
			_emotionType = value;
			UserInfo.Instance.SetEmotionType (this, _emotionType);
		}
	}



	public void setLevelComplite (int stars) {
		_lastUse = UserInfo.Instance.SetMonsterLastUsed (this);
		if (stars == 0) {
			_levelFaled = UserInfo.Instance.SetMonsterLevelFaled (this);
		}
		updateEmotionType ();
	}


	void updateEmotionType()
	{
		if (_levelFaled == GameplaySettings.MonsterAngryLevelFaledValue && _emotionType == MonsterEmotionTypes.Happy) {
			_emotionType = MonsterEmotionTypes.Angry;
		} else if (_lastUse == GameplaySettings.MonsterBoredDaysValue && _emotionType == MonsterEmotionTypes.Happy) {
			_emotionType = MonsterEmotionTypes.Bored;
		}
		if(
			_levelFaled > GameplaySettings.MonsterAngryLevelFaledValue + GameplaySettings.MonsterSadLevelFaledValue
			||
			_lastUse > GameplaySettings.MonsterBoredDaysValue + GameplaySettings.MonsterSadDaysValue
			&& 
			(
				_emotionType == MonsterEmotionTypes.Happy
				||
				_emotionType == MonsterEmotionTypes.Angry
				||
				_emotionType == MonsterEmotionTypes.Bored
			)
		) {
			_emotionType = MonsterEmotionTypes.Sad;
		}
		UserInfo.Instance.SetEmotionType (this, _emotionType);
	}


	// End Tzahi

}
