using UnityEngine;
using System.Collections;

public class LoadingScreenController : MonoBehaviour {


	public GameObject LoadingScreen, LogQuestLoadingScreen,HareRunQuestLoadingScreen,SwingingVinesLoadingScreen;

	public void Activate()
	{
//		if (LevelName.Equals ("2dInfiniteRunner")) {
//			LogQuestLoadingScreen.SetActive (true);
//		}
//		else if(LevelName.Equals ("MainScene"))
//		{
//			LoadingScreen.SetActive (true);
//		}

		LoadingScreen.SetActive (true);
	}

	public void ActivateLogQuest()
	{
		LogQuestLoadingScreen.SetActive (true);
	}

	public void ActivateHareRunQuest()
	{
		HareRunQuestLoadingScreen.SetActive (true);
	}

	public void ActivateSwingingWineQuest()
	{
		SwingingVinesLoadingScreen.SetActive (true);
	}
	public void DeActivate()
	{
		LoadingScreen.SetActive (false);
		SwingingVinesLoadingScreen.SetActive (false);
		HareRunQuestLoadingScreen.SetActive (false);
		LogQuestLoadingScreen.SetActive (false);
	}
}
