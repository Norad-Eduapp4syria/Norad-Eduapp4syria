using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class XMLTool {

	public static IEnumerator LoadLettersXML()
	{
		XMLLetters xmlLetters = new XMLLetters ();

		yield return xmlLetters.LoadFromResources ("Gameplay/letters");

		XMLController.Instance.isLetterLoaded = true;
		yield return true;
	}

	public static IEnumerator LoadDressingXML()
	{
		XMLDressing xmlLetters = new XMLDressing ();

		yield return xmlLetters.LoadFromResources ("Gameplay/dressing");

		XMLController.Instance.isDressingLoaded = true;
		yield return true;
	}


	public static IEnumerator LoadLevelsXML()
	{
		Level[] levels = XMLController.Instance.getLevelList();

		float t = Time.time;

		for (int i = 0; i < levels.Length; i++) {
			//string url = "http://storage.cet.ac.il/feedthemonster/level" + i + ".xml";
			levels [i] = ScriptableObject.CreateInstance<Level>();
			XMLLevel xmlLevel = new XMLLevel ();

			yield return xmlLevel.LoadFromResources (i + 1, "Gameplay/Levels/level" + i.ToString(), levels [i]);

//			yield return xmlLevel.LoadFromResources (i + 1, path.Replace("${ID}", i.ToString()), levels [i]);
			if (TutorialSettings.TutorialLetterInWordLevel == 0 && levels [i].monsterInputType == MonsterInputType.LetterInWord) {
				TutorialSettings.TutorialLetterInWordLevel = i;
			}

			if (TutorialSettings.TutorialWordLevel == 0 && levels [i].monsterInputType == MonsterInputType.Word) {
				TutorialSettings.TutorialWordLevel = i;
			}

			yield return new WaitForSeconds(0.01f);

//			Debug.Log ("level " + i + " loaded");
		}

		Debug.Log (XMLLevel.LevelMaxScore);

		XMLController.Instance.isLevelLoaded = true;
//		Debug.Log ("Loaded Time: " + (Time.time - t).ToString ());

		yield return true;
	}

	public static Level LoadLevelXML(int LevelId)
	{
		Level level;

		level = ScriptableObject.CreateInstance<Level>();
		XMLLevel xmlLevel = new XMLLevel ();
		Debug.Log ("Reading: " + LevelId);

		xmlLevel.LoadFromResources2 (LevelId + 1, "Gameplay/Levels/level" + LevelId.ToString(), level);

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
