using UnityEngine;
using System.Collections;
using ArabicSupport;
using UnityEngine.UI;
public class arabicgenerator : MonoBehaviour {

	public InputField field;
	public Text text;
	// Use this for initialization
	void Start () {
		// ArabicFixer.Fix ("a", true, true);
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void AddText(){
		string tempText = text.text;
		text.text = "";
		tempText = tempText + field.text;
//		char [] array=tempText.ToCharArray ();
//		tempText = "";
//		for (int i = 0; i < array.Length; i++) {
//			tempText += array [i];
//		}
		field.text = "";
		tempText= ArabicFixer.Fix (tempText, true, true);
		text.text = tempText;
	}
}
