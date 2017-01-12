using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;
using MiniJSON;


public class DataLoader : MonoBehaviour {


	public static readonly List<string> readonlyLetters = new List<string> (){"م","ب","ل","ن","ر" };
	public static readonly List<string> readonlyLettersSound = new List<string> (){"Meem","Bay","Lam","Noon","Ray"};
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public Databank LoadData(string _databank){
		Databank dataBank = new Databank ();
		IDictionary databank = Json.Deserialize (_databank) as IDictionary;
		IDictionary databankDictionary = databank ["DataBank"] as IDictionary;
		IDictionary DailougeSystem = databankDictionary ["DailougeSystem"] as IDictionary;
		IDictionary lettersData = databankDictionary ["Letters"] as IDictionary;
//		IList enemyList = databankDictionary ["EnemiesData"] as IList;
		dataBank.LettersData = LoadLettersData (lettersData);
		//dataBank.Foods = LoadFoodData (foodList);
//		dataBank.Enemies = LoadEnemiesData (enemyList);


		return dataBank;



	}

	Dictionary<string,List<mLetter>> LoadLettersData(IDictionary lettersData){

		Dictionary<string,List<mLetter>> totalLettersDictionary = new Dictionary<string,List<mLetter>> ();
		List<mLetter> aSingleLetterList = new List<mLetter>();
		mLetter aLetterObject;
		foreach(string alphabet in readonlyLetters){
			IList aLetterList = lettersData [alphabet] as IList;

		foreach(IDictionary aLetter in aLetterList){
				aLetterObject = new mLetter ();
				aLetterObject.letter = aLetter["Letters"].ToString();
				aLetterObject.letterEnglish = aLetter["English"].ToString();
				aLetterObject.letterWord = aLetter["Words"].ToString();
				aLetterObject.letterSequence =Convert.ToInt32(aLetter["Sequence"]);
			aSingleLetterList.Add (aLetterObject);
			
		}
			Debug.Log ("letter"+aSingleLetterList[0].letter+" "+ aSingleLetterList[0].letterWord);
		totalLettersDictionary.Add (aSingleLetterList[0].letter,aSingleLetterList);

		aLetterList.Clear ();
		aLetterList = null;
			aSingleLetterList.Clear();
			aSingleLetterList = new List<mLetter>();
			 
		}
//		 aLetterList = lettersData ["مَ"];
//
//		foreach(IDictionary aLetter in aLetterList){
//			aLetterObject.letter = aLetter["Letters"].ToString();
//			aLetterObject.letterEnglish = aLetter["English"].ToString();
//			aLetterObject.letterWord = aLetter["Words"].ToString();
//			aLetterObject.letterSequence =Convert.ToInt32(aLetter["Sequence"]);
//			aSingleLetterList.Add (aLetterObject);
//
//		}
//		totalLettersDictionary.Add (aSingleLetterList[0].letter,aSingleLetterList);
		return totalLettersDictionary;	 
	}


 
}
