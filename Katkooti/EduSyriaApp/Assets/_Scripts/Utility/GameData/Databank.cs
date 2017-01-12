using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Databank {

	public Dictionary<string,List<mLetter>> LettersData;
	//public Dictionary<string,Dictionary<int,Dialogue>> dialougeData;



	public List<string> getWordsForLetter(string letter){

		List<mLetter> letters = LettersData [letter];

		List<string> wordList = new List<string> (); 

		foreach(mLetter l in letters){
			wordList.Add (l.letterWord);
		}

		return wordList;
	}

	public List<string> getDicricticsForLetter(string letter){
		int index = DataLoader.readonlyLetters.FindIndex (x => x == letter);
		List<string> dicritics = new List<string> ();
		for(int i =0;i<4;i++){
			dicritics.Add (DataLoader.readonlyLetters [i]);
		}        
		return dicritics;
	}

}
