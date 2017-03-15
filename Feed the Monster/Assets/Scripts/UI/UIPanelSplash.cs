using UnityEngine;
using System.Collections;

public class UIPanelSplash : MonoBehaviour {

	public GameObject background;

	public GameObject nextScreen;

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

/*
		for (int i = 2; i < transform.childCount; i++) {
			transform.GetChild(i).localScale = new Vector3(0,0,0);
		}

		Invoke ("aaaa", 0.5f);
*/
	}

	// Update is called once per frame
	void Update () {

	}

	void OnDisable()
	{
		GameplayController.Instance.DestroyBackground();
	}

	public void OnPlayClick()
	{
		if (UserInfo.Instance.GetLastProfileId() == -1) {
			OnProfileClick ();
		} else {
			if (nextScreen != null) {
				UIController.Instance.ShowPanel(nextScreen);
			} else {
				UIController.Instance.ShowPanel(UIController.Instance.MapPanel);
			}
		}
	}

	public void OnProfileClick()
	{
		UIController.Instance.ShowPopup (UIController.Instance.SelectProfilePopup);

		UIProfileSelectionController.Instance.skipConfirmationPopup = true;
		UIProfileSelectionController.Instance.allowToSelectCurrentProfile  = true;

		if (nextScreen != null) {
			UIProfileSelectionController.Instance.NextScreen = nextScreen;
		} else {
			UIProfileSelectionController.Instance.NextScreen = UIController.Instance.MapPanel;
		}
	}



}
