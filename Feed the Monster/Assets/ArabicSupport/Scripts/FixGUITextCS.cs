using UnityEngine;
using System.Collections;
using ArabicSupport;

public class FixGUITextCS : MonoBehaviour {
	
	public string text;
	public bool tashkeel = true;
	public bool hinduNumbers = true;
	
	// Use this for initialization
	void Start () {
		gameObject.GetComponent<GUIText>().text = ArabicFixer.Fix(text, tashkeel, hinduNumbers);
	}
	
	// Update is called once per frame
	void Update () {
	
	}
}
