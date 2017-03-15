using UnityEngine;
using System.Collections;
using System.Xml;
using System.Xml.Serialization;

[System.Serializable]
public class Segment {

	[XmlAttribute("spawnIds")]
	public string SpawnIds;

	[XmlAttribute("SegmentTime")]
	public float SegmentTime;

	[XmlArray("Stones")]
	[XmlArrayItem("string")]
	public Stone[] Stones;


	[XmlArray("MonsterRequiredLetters")]
	[XmlArrayItem("string")]
	public string[] MonsterRequiredLetters;

	[XmlArray("MonsterAllLetters")]
	[XmlArrayItem("string")]
	public string[] MonsterAllLetters;



	string[] _fixRequiredLetters;
	string[] _fixAllLetters;


	public string GetFixRequiredLetters(int index)
	{
		if (_fixRequiredLetters == null) {
			_fixRequiredLetters = new string[MonsterRequiredLetters.Length];
		}
		if (string.IsNullOrEmpty (_fixRequiredLetters [index])) {
			_fixRequiredLetters [index] = RTL.Fix (MonsterRequiredLetters [index]);
		}
		return _fixRequiredLetters [index];
	}

	public string GetFixAllLetters(int index)
	{
		if (_fixAllLetters == null) {
			_fixAllLetters = new string[MonsterAllLetters.Length];
		}
		if (string.IsNullOrEmpty (_fixAllLetters [index])) {
			_fixAllLetters [index] = RTL.Fix (MonsterAllLetters [index]);
		}
		return _fixAllLetters [index];
	}



	public string valueForAnalitics
	{
		get {
			string s = string.Empty;

			switch (GameplayController.Instance.CurrentLevel.monsterInputType) {
			case MonsterInputType.Letter:
				s += "Letter: ";
				break;
			case MonsterInputType.LetterInWord:
				s += "Letter In Word: ";
				break;
			case MonsterInputType.Word:
				s += "Word: ";
				break;
			case MonsterInputType.SoundLetter:
				s += "Sound Letter: ";
				break;
			case MonsterInputType.SoundWord:
				s += "Sound Word: ";
				break;
			}


			for (int i = 0; i < MonsterRequiredLetters.Length; i++) {
				s += MonsterRequiredLetters [i];
			}
			return s;
		}

	}


}
