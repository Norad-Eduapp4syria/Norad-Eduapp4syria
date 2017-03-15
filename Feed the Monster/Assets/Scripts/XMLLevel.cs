using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;
using System.IO;
using System;

[XmlRoot("XMLLevel")]
public class XMLLevel {
	[XmlAttribute("monsterInputType")]
	public MonsterInputType monsterInputType;

	[XmlAttribute("CollectableMonster")]
	public string CollectableMonster;

	[XmlAttribute("HideCallout")]
	public int HideCallout;

	[XmlAttribute("ShuffleSegment")]
	public bool ShuffleSegment;


	[XmlAttribute("LevelTemplete")]
	public string LevelTemplete;

	[XmlAttribute("SegmentTime")]
	public float SegmentTime;

	[XmlAttribute("StoneType")]
	public int StoneType;

	[XmlArray("Segments")]
	[XmlArrayItem("Segment")]
	public Segment[] Segments;

/*
	[XmlArray("Recognitions")]
	[XmlArrayItem("Recognition")]
	public Recognition[] Recognitions;
*/


	[XmlAttribute("LettersGroup")]
	public int LettersGroup;



	public static string LevelMaxScore = string.Empty;

//	public void Save()
//	{
//		var serializer = new XmlSerializer(typeof(XMLLevel));
//
//		var memoryStream = new MemoryStream();
//		var streamWriter = new StreamWriter(Application.dataPath + "/level" + LevelIndex + ".xml", false, System.Text.Encoding.UTF8);
//
//		using(streamWriter)
//		{
//			serializer.Serialize(streamWriter, this);
//		}
//	}

	public IEnumerator LoadFromWebResponse(int levelId, string levelUrl, Level level)
	{
		Debug.Log ("begin xml: " + levelUrl);

		WWW froma;
		yield return froma = new WWW(levelUrl);

		MemoryStream ms = new MemoryStream (froma.bytes);

		XmlTextReader reader;
		yield return reader = new XmlTextReader  (ms);


		SerializeLevelFromXML (levelId, levelUrl, reader, level);

		yield return true;
	}

	public IEnumerator LoadFromResources(int levelId, string levelPath, Level level){
		TextAsset xmlDataFile = new TextAsset ();
		xmlDataFile = (TextAsset)Resources.Load (levelPath, typeof(TextAsset));
		MemoryStream ms = new MemoryStream (xmlDataFile.bytes);

		XmlTextReader reader;
		yield return reader = new XmlTextReader  (ms);

		SerializeLevelFromXML (levelId, levelPath ,reader, level);

		yield return true;
	}



	public void LoadFromResources2(int levelId, string levelPath, Level level) {
		TextAsset xmlDataFile = new TextAsset ();
		xmlDataFile = (TextAsset)Resources.Load (levelPath, typeof(TextAsset));
		MemoryStream ms = new MemoryStream (xmlDataFile.bytes);

		XmlTextReader reader;
		reader = new XmlTextReader  (ms);

		SerializeLevelFromXML (levelId, levelPath ,reader, level);
	}



	private void SerializeLevelFromXML(int levelId, string levelPath, XmlReader reader, Level level) {
		var serializer = new XmlSerializer(typeof(XMLLevel));

		if (level == null) {
			level = new Level ();
		}

		XMLLevel xmlLevel = serializer.Deserialize(reader) as XMLLevel;

		level.levelId = levelId;
		level.lettersGroup = xmlLevel.LettersGroup;
		level.monsterInputType = xmlLevel.monsterInputType;
		level.hideCallout = xmlLevel.HideCallout;
		level.shuffleSegment = xmlLevel.ShuffleSegment;
		level.SegmentTime = (xmlLevel.SegmentTime > 0f) ? xmlLevel.SegmentTime : GameplaySettings.CountdownDefault;
		level.StoneType = xmlLevel.StoneType;

		if (!string.IsNullOrEmpty (xmlLevel.CollectableMonster)) {

			if (Enum.IsDefined (typeof(MonsterType), xmlLevel.CollectableMonster)) {
				MonsterType type = (MonsterType)Enum.Parse (typeof(MonsterType), xmlLevel.CollectableMonster, true);
				level.CollectableMonster = Resources.Load ("Gameplay/Monsters/" + type.ToString ()) as Monster;
			}
		}
		level.Segments = xmlLevel.Segments;

		int maxPointsInLevel = 0;

		if(level.monsterInputType == MonsterInputType.Letter || level.monsterInputType == MonsterInputType.LetterInWord || level.monsterInputType == MonsterInputType.SoundLetter) {
			maxPointsInLevel = calcLetterMaxScore(level);
		} else {
			maxPointsInLevel = calcWordMaxScore(level);
		}

		LevelMaxScore += "Level: " + levelId + ",  FileName: " + levelPath + ",  Max Points: " + maxPointsInLevel.ToString () + "\n";
/*
 		if ( xmlLevel.Recognitions != null) {
			GameplayController.Instance.Recognitions = xmlLevel.Recognitions;
		}
*/
//		Level templete = Resources.Load ("Gameplay/LevelTempletes/LevelTempleteBlueSky") as Level;
//		if (templete != null) {
			level.LoadTemplete (GameplayController.Instance.DefaultLevelTempletes);
//		}
		Debug.Log ("LoadLevel" + levelPath);
	}

	int calcWordMaxScore(Level level) {
		int maxPointsInLevel = 0;

		foreach (Segment segment in level.Segments) {
			int p = 0;
			float toAdd = 0;

			GameplaySettings.PuzzleSuccessScore.TryGetValue (level.monsterInputType, out p);
			toAdd += p;

			toAdd += GameplaySettings.ShuterButtonAddScore_1;
			toAdd += ((int)((segment.SegmentTime > 0) ? segment.SegmentTime : level.SegmentTime)) * GameplaySettings.PuzzleLeftTimeScore;

			int v = segment.MonsterRequiredLetters.Length;
			toAdd += GameplaySettings.LetterComboScore * (v - 1);
			toAdd += v * GameplaySettings.LetterInWordComboScore;

			toAdd += (((float)toAdd) * (GameplaySettings.LevelScoreFactor * ((float)level.levelId)));
			maxPointsInLevel += (int)toAdd;
		}
		return maxPointsInLevel;
	}

	int calcLetterMaxScore(Level level)
	{
		int maxPointsInLevel = 0;

		foreach (Segment segment in level.Segments) {
			int p = 0;
			GameplaySettings.PuzzleSuccessScore.TryGetValue (level.monsterInputType, out p);
			maxPointsInLevel += p;

			maxPointsInLevel += GameplaySettings.ShuterButtonAddScore_1;
			maxPointsInLevel += ((int)((segment.SegmentTime > 0) ? segment.SegmentTime : level.SegmentTime)) * GameplaySettings.PuzzleLeftTimeScore;

			Dictionary<string, int> ltrs = new Dictionary<string, int>();
			foreach (Stone stone in segment.Stones) {
				if(!stone.isBooster()) {
					if(ltrs.ContainsKey(stone.value)) {
						ltrs[stone.value]++;
					} else {
						ltrs.Add(stone.value, 1);
					}
				}
			}

			foreach(string key in ltrs.Keys)
			{
				int v = ltrs[key];

				maxPointsInLevel += GameplaySettings.LetterComboScore * (v - 1);

				if(key.Equals(segment.MonsterRequiredLetters[0])) {
					if(v == 1) {
						maxPointsInLevel+= GameplaySettings.LetterScore;
					} else {
						maxPointsInLevel+= v * GameplaySettings.LetterInComboScore;
					}
				}
			}
		}
		float toAdd = maxPointsInLevel;
		toAdd += (((float)toAdd) * (GameplaySettings.LevelScoreFactor * ((float)level.levelId)));
		maxPointsInLevel = (int)toAdd;

		return maxPointsInLevel;
	}


}
