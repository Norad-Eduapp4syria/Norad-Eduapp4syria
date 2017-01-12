using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using ArabicSupport;
public class teststart : MonoBehaviour {


	public Text t;
	// Use this for initialization
	void Start () {
//		Debug.Log ("Aya");

		t.text = ArabicFixer.Fix (t.text,true,true);
//		StopAllCoroutines ();
//		StartCoroutine ("StartGame");
		//Invoke("StartGame",4);
	}
	void OnEnable () {
		
	}
	// Update is called once per frame
	void Update () {
	
	}

	void StartGame(){
//		Debug.Log ("Aya g");
//		yield return new WaitForSeconds (4);
//		Debug.Log ("Aya l");

		//Application.LoadLevel (1);
	}

	public void InfiniteRunner(){
		Application.LoadLevel (1);
	}

	public void WordFactory(){
		Application.LoadLevel (2);
	}
}
