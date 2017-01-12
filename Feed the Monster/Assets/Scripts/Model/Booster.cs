using UnityEngine;
using System.Collections;
using System;

[System.Serializable]
public class Booster : ScriptableObject {
	public enum BoosterType
	{
		NONE				= 100,
		FreezeTime			= 0,
		FireWrongLetter 	= 1,
		LoseSegment			= 2,
		MagnetLetter		= 3,
		SlowMovment			= 4,
		ShowCallout			= 5,
        BonusLetter         = 6,
		Shield		        = 7
	}

	public static string[] BoosterNames = {
		"BoosterFrost",
		"BoosterFire",
		"BoosterBlock",
		"BoosterMagnet",
		"BoosterSlowMovment",
		"BoosterShowCallout",
		"BoosterBonus",
		"BoosterShield"
	};


	public AudioClip Sound;

	public Sprite Icon;
	public Sprite SelectedIcon;
	public BoosterType Type;

	public GameObject EffectOnLetterPrefab;




	public static BoosterType toEnum(string strValue)
	{
		if(!Enum.IsDefined(typeof(BoosterType), strValue ))
		{
			return BoosterType.NONE;
		}
		return (BoosterType)Enum.Parse(typeof(BoosterType), strValue);

	}
}
