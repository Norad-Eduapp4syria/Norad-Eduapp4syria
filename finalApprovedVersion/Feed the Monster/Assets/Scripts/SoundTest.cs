using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class SoundTest : MonoBehaviour {



	public bool TryLetter = true;
	public bool TryLetterName = true;
	public bool TryLetterInWord = true;
	public bool TryWord = true;



	public bool MoveNotUsed = false;


	Dictionary<string, FileInfo> letters = new Dictionary<string, FileInfo>();
	Dictionary<string, FileInfo> letterName = new Dictionary<string, FileInfo>();
	Dictionary<string, FileInfo> words = new Dictionary<string, FileInfo>();


	string logLetter;
	string logLetterName;
	string logLetterInWord;
	string logWord;

	// Use this for initialization
	void Start () {
		MoveNotUsed = false;
	}
	
	// Update is called once per frame
	void Update () {
		
	}



	public void OnEnable() {

		if (MoveNotUsed) {
			loadAllFiles ();
		}


		logLetter = string.Empty;
		logLetterName = string.Empty;
		logLetterInWord = string.Empty;
		logWord = string.Empty;

		foreach (Level lvl in XMLController.Instance.getLevelList()) {
			if (lvl.Segments != null) {
				for (int sId = 0; sId < lvl.Segments.Length; sId++) {
					PlayCalloutSound (lvl, sId, lvl.Segments [sId]);
				}
			}
		}

		if (TryLetter) {
			Debug.Log (logLetter);
		}
		if (TryLetterName) {
			Debug.Log (logLetterName);
		}
		if (TryLetterInWord) {
			Debug.Log (logLetterInWord);
		}
		if (TryWord) {
			Debug.Log (logWord);
		}

		if (MoveNotUsed) {
			MoveNotUsed = false;
			moveNotRelevantFiles ();
		}
	}

//	List<string> letters = new List<string>();


	void loadAllFiles()
	{
		letters.Clear ();
		words.Clear ();
		letterName.Clear ();

		DirectoryInfo dir = new DirectoryInfo("Assets/Resources/Sounds/Voice/Letters");
		FileInfo[] info = dir.GetFiles("*.mp3");

		foreach (FileInfo file in info) {
			letters.Add (file.Name.Replace (".mp3", ""), file);
		}

		Debug.Log (letters.Count);



		dir = new DirectoryInfo("Assets/Resources/Sounds/Voice/LettersName");
		info = dir.GetFiles("*.mp3");

		foreach (FileInfo file in info) {
			letterName.Add (file.Name.Replace (".mp3", ""), file);
		}
		Debug.Log (letterName.Count);

		dir = new DirectoryInfo("Assets/Resources/Sounds/Voice/Words");
		info = dir.GetFiles("*.mp3");

		foreach (FileInfo file in info) {
			words.Add (file.Name.Replace (".mp3", ""), file);
		}

		Debug.Log (words.Count);


	}

	void moveNotRelevantFiles() {
		foreach (FileInfo file in letters.Values) {
			string destinationFile = "C:\\WorkSpace\\FTM\\FTM-Main\\Assets\\Sounds\\Voice\\Letters\\" + file.Name;
			Debug.Log (file.FullName + " --> " + destinationFile);
//			C:\WorkSpace\FTM\FTM-Main\Assets\Resources\Sounds\Voice\Letters\ـراب.mp3
			System.IO.File.Move(file.FullName, destinationFile);
		}

		foreach (FileInfo file in letterName.Values) {
			string destinationFile = "C:\\WorkSpace\\FTM\\FTM-Main\\Assets\\Sounds\\Voice\\LettersName\\" + file.Name;
			Debug.Log (file.FullName + " --> " + destinationFile);
			//			C:\WorkSpace\FTM\FTM-Main\Assets\Resources\Sounds\Voice\Letters\ـراب.mp3
			System.IO.File.Move(file.FullName, destinationFile);
		}


		foreach (FileInfo file in words.Values) {
			string destinationFile = "C:\\WorkSpace\\FTM\\FTM-Main\\Assets\\Sounds\\Voice\\Words\\" + file.Name;
			Debug.Log (file.FullName + " --> " + destinationFile);
			//			C:\WorkSpace\FTM\FTM-Main\Assets\Resources\Sounds\Voice\Words\ـراب.mp3
			System.IO.File.Move(file.FullName, destinationFile);
		}
	}

	public void PlayCalloutSound(Level lvl, int segmentId, Segment seg){
		string fileName;
		string url;
		AudioClip voice;
		string word = "";

		switch (lvl.monsterInputType) {

		case MonsterInputType.LetterName:
		case MonsterInputType.SoundLetterName:
			if (TryLetterName) {
				fileName = RTL.Clean (seg.MonsterRequiredLetters [0]);
				if(letterName.ContainsKey(fileName)) {
					letterName.Remove(fileName);
				}
				url = "Sounds/Voice/LettersName/" + fileName;
				voice = Resources.Load (url) as AudioClip;
				if (voice == null) {
					logLetterName += "Letter Name - Sound is missing - '" + /*RTL.Fix*/(url) + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1) + "\n";
					//					Debug.Log ("Letter - Sound is missing - '" + url + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1));
				}
			}
			break;

		case MonsterInputType.Letter:
		case MonsterInputType.SoundLetter:
			if (TryLetter) {
				fileName = RTL.Clean (seg.MonsterRequiredLetters [0]);
				if(letters.ContainsKey(fileName)) {
					letters.Remove(fileName);
				}
				url = "Sounds/Voice/Letters/" + fileName;
				voice = Resources.Load (url) as AudioClip;
				if (voice == null) {
					logLetter += "Letter - Sound is missing - '" + /*RTL.Fix*/(url) + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1) + "\n";
//					Debug.Log ("Letter - Sound is missing - '" + url + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1));
				}
			}
			break;
		case MonsterInputType.LetterInWord:
			if (TryLetterInWord) {
				fileName = ArabicBaseForm.Extract (RTL.Clean (seg.MonsterRequiredLetters [0]));
//				fileName = RTL.Fix(seg.MonsterRequiredLetters [0]);
				
				if(letters.ContainsKey(fileName)) {
					letters.Remove(fileName);
				}

				url = "Sounds/Voice/Letters/" + fileName;
				voice = Resources.Load (url) as AudioClip;
				if (voice == null) {
					logLetterInWord += "Letter In Word - Sound is missing - '" + /*RTL.Fix*/(url) + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1) +  " ( " + url + " )" +"\n";
//					Debug.Log ("Letter In Word - Sound is missing - '" + url + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1));
				}
			}
			break;
		case MonsterInputType.Word:
		case MonsterInputType.SoundWord:
			if (TryWord) {
				word = "";
				foreach (string letter in seg.MonsterRequiredLetters) {
					word += letter;
				}
				fileName = ArabicBaseForm.Extract (RTL.Clean (word));
				if(words.ContainsKey(fileName)) {
					words.Remove(fileName);
				}
				url = "Sounds/Voice/Words/" + fileName;

				voice = Resources.Load (url) as AudioClip;
				if (voice == null) {
					logWord += "Word - Sound is missing - '" + /*RTL.Fix*/(url) + "'" + " Level: " + (lvl.levelId - 1) + " Segment Id: " + (segmentId + 1) + "\n";
				}	
			}
			break;
		}
	}




}
