using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[Serializable]
public class UserLevelTO {

	public int levelId;
	public int levelScore;
	public int levelStars;




	public static UserLevelTO create(int levelId, int score, int stars)
	{
		UserLevelTO level = new UserLevelTO ();
		level.levelId = levelId;
		level.levelScore = score;
		level.levelStars = stars;

		return level;
	}

}
