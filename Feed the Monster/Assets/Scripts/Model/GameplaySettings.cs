using UnityEngine;
using System.Collections;
using System.Collections.Generic;



public static class GameplaySettings {
	
	public const float CountdownDefault = 10f;

	public const float ShowTimeupSeconds = 1.6f;

//	public const float CountdownWarningMonsterRatio = .5f;

	public const float CountdownWarningLetterRatio = .5f;

	public const float	BoosterFreezeDuration = 5f;
	public const float	BoosterSlowMovementDuration = 5f;
	public const int	BoosterShowCalloutTimes = 4;


	public static int 		ShuterButtonAddScore_4		= 0;
	public static int 		ShuterButtonAddScore_3		= 25;
	public static int 		ShuterButtonAddScore_2		= 75;
	public static int 		ShuterButtonAddScore_1		= 100;

	public static float		ShuterButtonShowTime_4		=  1.5f;
	public static float		ShuterButtonShowTime_3		=  1.5f;
	public static float		ShuterButtonShowTime_2		=  1.5f;
	public static float		ShuterButtonShowTime_1		=  1.5f;

/*
	public static float		ShuterButtonDecreaseTime_4	=  0.0f;
	public static float		ShuterButtonDecreaseTime_3	=  2.5f;
	public static float		ShuterButtonDecreaseTime_2	=  7.5f;
	public static float		ShuterButtonDecreaseTime_1	= 10.0f;
*/

	public static int 		LetterScore				= 100;
	public static int 		LetterInComboScore		= 150;
//  public static int 		LetterCollectScore		= 150;
	public static int 		LetterInWordComboScore	= 200;


	public static int	 	LetterComboScore	= 10;
	public static float[] 	LetterComboScale	= { 1.2f,1.1f,1.05f,1.05f,1.04f,1.04f,1.04f,1.03f,1.03f,1.03f,1.02f,1.02f,1.02f,1.02f };
	public static float	 	LetterComboMaxScale	= 1.5f;

	public static float	 	LevelScoreFactor	= 0.01f;

	public static int	 							PuzzleLeftTimeScore = 10;
	public static Dictionary<MonsterInputType, int> PuzzleSuccessScore = new Dictionary<MonsterInputType, int> {
		{MonsterInputType.Letter,		100},
		{MonsterInputType.LetterInWord,	100},
		{MonsterInputType.SoundLetter,	300},
		{MonsterInputType.Word,			200},
		{MonsterInputType.SoundWord,	300}
	};

	public static int		BonusLetterBoosterScore = 200;


	public static float	 	LetterLauncherPointStartScale	= 0.01f;

	public static int 		LetterStationingSpeed	= 1000;
	public static int 		LetterMovementSpeed		= 250;

	public static int MonsterAngryLevelFaledValue			=	2;
	public static int MonsterBoredDaysValue					=	3;

	public static int MonsterSadLevelFaledValue				=	3;
	public static int MonsterSadDaysValue					=	3;

	public static int HungryAfraidCompliteLevels =	10;


	public static int TreasureChest_ClicksToOpen = 1;

	public static int TreasureChest_ScoreMin = 500;
	public static int TreasureChest_ScoreMax = 1500;

	public static float TreasureChest_ChanceToShow = 0.15f;



	public static int MiniGame_SuccessScore = 500;

	public static Vector2 DragSpacious = new Vector2 (-30f, 30f);

}