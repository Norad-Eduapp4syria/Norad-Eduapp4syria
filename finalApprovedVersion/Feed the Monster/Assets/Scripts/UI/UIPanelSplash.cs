using UnityEngine;
using System.Collections;

public class UIPanelSplash : MonoBehaviour {

//	public GameObject background;
	public Transform popupsHolder;
	public GameObject profileSelectionGO = null;

	public string nextScene;


	// Use this for initialization
	void Start () {
//		GameplayController.Instance.LoadBackground (background);
		Analitics.TreckScreen ("Splash Screen");
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

	void Update () {

	}

	void OnDisable()
	{

	}

	public void OnPlayClick()
	{
		if (string.IsNullOrEmpty(nextScene)) {
			nextScene = "MapScreen";
		}

		if (SaveStatConnector.Instance.ProfileId == -1) {
			OnProfileClick ();
		} else {
			loadNextScene ();
		}
	}

	public void OnProfileClick()
	{
		if (string.IsNullOrEmpty(nextScene)) {
			nextScene = "MapScreen";
		}

		#if UNITY_WEBGL
		nextScene = "MapScreen";
		#endif

		showConfirmaction ();
	}




	void showConfirmaction ()
	{
		GameObject popup;

		if (profileSelectionGO != null) {
			popup = Instantiate (profileSelectionGO, popupsHolder);
		} else {
			popup = Instantiate (Resources.Load ("Gameplay/Popups/Popup Panel - Profile Selection") as GameObject, popupsHolder);
		}

		UIProfileSelectionController psc = popup.GetComponent<UIProfileSelectionController> ();
		psc.NextScene = nextScene;
		psc.skipConfirmationPopup = true;
		psc.popupsHolder = popupsHolder;
	}

	void loadNextScene () {
		SceneController.Instance.LoadScene (nextScene);
	}


}
