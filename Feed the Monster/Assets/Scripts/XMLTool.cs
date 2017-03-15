using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class XMLTool {
//	static string NetPath = "http://storage.cet.ac.il/feedthemonster";
	static string NetPath = "http://192.168.36.186:8081";



	static bool isLevelsFromNetwork
	{
		get { 
			if (UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS && UIController.Instance.DEBUG_USU_ONLINE_XMLS) {
				return true;
			} else {
				return false;
			}
		}
	}


	public static IEnumerator LoadLettersXML()
	{
		XMLLetters xmlLetters = new XMLLetters ();

		yield return xmlLetters.LoadFromResources ("Gameplay/letters");

		yield return true;
	}

	public static IEnumerator LoadLevelsXML()
	{
		Level[] levels = GameplayController.Instance.getLevelList();

		float t = Time.time;

		for (int i = 0; i < levels.Length; i++) {
			//string url = "http://storage.cet.ac.il/feedthemonster/level" + i + ".xml";
			levels [i] = ScriptableObject.CreateInstance<Level>();
			XMLLevel xmlLevel = new XMLLevel ();

			if(isLevelsFromNetwork) {

				yield return xmlLevel.LoadFromWebResponse (i + 1, NetPath + "/level" + i.ToString () + ".xml", levels [i]);
//				yield return xmlLevel.LoadFromWebResponse (i + 1, "http://storage.cet.ac.il/feedthemonster/level" + i.ToString () + ".xml", levels [i]);
			} else {
				yield return xmlLevel.LoadFromResources (i + 1, "Gameplay/Levels/level" + i.ToString(), levels [i]);
			}
//			yield return xmlLevel.LoadFromResources (i + 1, path.Replace("${ID}", i.ToString()), levels [i]);
			if (TutorialSettings.TutorialLetterInWordLevel == 0 && levels [i].monsterInputType == MonsterInputType.LetterInWord) {
				TutorialSettings.TutorialLetterInWordLevel = i;
			}

			if (TutorialSettings.TutorialWordLevel == 0 && levels [i].monsterInputType == MonsterInputType.Word) {
				TutorialSettings.TutorialWordLevel = i;
			}
//			Debug.Log ("level " + i + " loaded");
		}

		Debug.Log (XMLLevel.LevelMaxScore);

		UIController.Instance.SplashScreenStartButton.gameObject.SetActive(true);

		Debug.Log ("Loaded Time: " + (Time.time - t).ToString ());

		yield return true;
	}

	public static Level LoadLevelXML(int LevelId)
	{
		Level level;

		level = ScriptableObject.CreateInstance<Level>();
		XMLLevel xmlLevel = new XMLLevel ();
		Debug.Log ("Reading: " + LevelId);

		if(isLevelsFromNetwork) {
			xmlLevel.LoadFromWebResponse (LevelId + 1, NetPath +  "/level" + LevelId.ToString () + ".xml", level);
		} else {
			xmlLevel.LoadFromResources2 (LevelId + 1, "Gameplay/Levels/level" + LevelId.ToString(), level);
		}

		if (TutorialSettings.TutorialLetterInWordLevel == 0 && level.monsterInputType == MonsterInputType.LetterInWord)
			TutorialSettings.TutorialLetterInWordLevel = LevelId;

		if (TutorialSettings.TutorialWordLevel == 0 && level.monsterInputType == MonsterInputType.Word)
			TutorialSettings.TutorialWordLevel = LevelId;

		return  level;
	}


//	public static IEnumerator LoadRecognitionsXML()
//	{
//		XMLRecognition xmlRecognition = new XMLRecognition ();
//		yield return xmlRecognition.LoadFromWebResponse ();
//
////		GameplayController.Instance.Recognitions = xmlRecognition.ToRecognitions();
//		yield return true;
//	}
}
