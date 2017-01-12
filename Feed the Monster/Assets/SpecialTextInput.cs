using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SpecialTextInput : MonoBehaviour {
	public string OriginalText;

    Text textView;
    string value = "";
	// Use this for initialization
	void Start () {
        textView = GetComponent<Text>();
    }
	
	// Update is called once per frame
	void Update () {
	
	}

    public void Parse(string letter)
    {
		OriginalText = letter;
		textView = GetComponent<Text>();
        value += letter;
		//textView.text = ArabicSupport.ArabicFixer.Fix(value,true,false);
		textView.text = RTL.Fix(value);
    }

    public void Clear()
    {
        value = "";
        textView.text = "-";
    }

	public string text {
		get {
			return textView.text;
		}
	}
}
