using UnityEngine;
using System.Collections;
using System;

[System.Serializable]
public class GameBackground : ScriptableObject
{
	public Sprite PlaygroundSprite;
	public Sprite BackgroundCloud1;
	public Sprite BackgroundCloud2;
	public Sprite ForegroundCloud1;
	public Sprite ForegroundCloud2;
	public Sprite ForegroundCloud3;
	public Sprite Hill;

	public static GameBackground create(
//		Sprite playgroundSprite,
//		Sprite backgroundCloud1,
//		Sprite backgroundCloud2,
//		Sprite foregroundCloud1,
//		Sprite foregroundCloud2,
//		Sprite foregroundCloud3,
//		Sprite hill
	)
	{
		//GameBackground gameBackground = new GameBackground ();
		GameBackground gameBackground = ScriptableObject.CreateInstance<GameBackground>();
		/*
		gameBackground.PlaygroundSprite = playgroundSprite;
		gameBackground.BackgroundCloud1 = backgroundCloud1;
		gameBackground.BackgroundCloud2 = backgroundCloud2;
		gameBackground.ForegroundCloud1 = foregroundCloud1;
		gameBackground.ForegroundCloud2 = foregroundCloud2;
		gameBackground.ForegroundCloud3 = foregroundCloud3;
		gameBackground.Hill = hill;
*/
		return gameBackground;
	}

}
