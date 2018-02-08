using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIGameCompleteScreen : MonoBehaviour {

	[Range(3f, 20f)]
	public float showFeedBackAfter;
	public string FeedBackFile;
	public GameObject FeedBackGO;

	// Use this for initialization
	void Start () {
		if (FeedBackGO != null) {
			FeedBackGO.SetActive (false);
			Invoke ("addFeedBack", showFeedBackAfter);
		}
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void onMapClick() {
		SceneController.Instance.LoadScene("MapScreen");
	}

	void addFeedBack()
	{
		if(FeedBackGO != null && !string.IsNullOrEmpty(FeedBackFile)) {
			Feedback fb = FeedBackGO.GetComponentInChildren<Feedback> ();
			if (fb != null) {
				string fileName = AudioController.Instance.PlayFeedback (FeedBackFile);
				FeedBackGO.SetActive (true);
				fb.onDone = onFeedBackDone;
				fb.init (fileName);
			}
		}
	}

	void onFeedBackDone()
	{
		Invoke ("onMapClick", 1f);
	}

}
