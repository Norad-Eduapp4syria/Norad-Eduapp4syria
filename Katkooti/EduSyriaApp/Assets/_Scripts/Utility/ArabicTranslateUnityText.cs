using UnityEngine;
using System.Collections;
using ArabicSupport;
using UnityEngine.UI;
public class ArabicTranslateUnityText : MonoBehaviour {

	// Use this for initialization
	Text data;
	void Start () {
		data = this.GetComponent<Text> ();
		data.text = ArabicFixer.Fix (data.text);
	}
	
	// Update is called once per frame
	void Update () {
//		data.text = ArabicFixer.Fix (data.text, true, true);
	}
}
