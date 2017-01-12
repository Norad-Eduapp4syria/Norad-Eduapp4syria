using UnityEngine;
using System.Collections;

public class UIPanelSplash : MonoBehaviour {

	public GameObject background;


	// Use this for initialization
	void Start () {
		GameplayController.Instance.LoadBackground (background);
		Analitics.Instance.treckScreen ("Splash Screen");
	}

	void OnEnable() {
//		string s;
//		s = "لا";
//		s = "يَصْـ";
//		string ss = RTL.Fix (s);
//		Debug.Log ("text: '" + s + "' == '" + ss + "'");
	}

	// Update is called once per frame
	void Update () {

	}

	void OnDisable()
	{
		GameplayController.Instance.DestroyBackground();
	}



}
