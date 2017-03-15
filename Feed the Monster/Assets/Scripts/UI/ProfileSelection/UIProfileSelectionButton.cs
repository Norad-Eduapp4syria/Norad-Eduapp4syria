using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIProfileSelectionButton : MonoBehaviour {

	public int ProfileId;

	public Image ImageIcon;
	public Image ImageSelected;

	public Image ImageLevel;
	public Text TextLevel;

	CanvasGroup cg;
	Button btn;
//	bool currentProfile;


	CanvasGroup CG
	{
		get {
			if (cg == null) {
				cg = gameObject.GetComponent<CanvasGroup> ();		
			}
			return cg;
		}
	}


	Button Btn
	{
		get {
			if (btn == null) {
				btn = gameObject.GetComponent<Button> ();		
			}
			return btn;
		}
	}




	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		
	}


	public void MarkSelected ()
	{
		if (ImageSelected != null) {
			ImageSelected.enabled = true;
		}
		UpdateLevel ();

		CG.alpha = 0.5f;
		Btn.interactable = false;


//		currentProfile = true;
	}


	public void MarkUnSelected()
	{
		if (ImageSelected != null) {
			ImageSelected.enabled = false;
		}
		UpdateLevel ();
		CG.alpha = 1.0f;
		Btn.interactable = true;
//		currentProfile = false;
	}

	public void OnClick()
	{
//		if (!currentProfile)
		{
			UIProfileSelectionController.Instance.OnChangeProfile (this);
		}
	}

	void UpdateLevel()
	{
		if (ImageLevel == null) {
			return;
		}
		int highestLevelOpenIndex = UserInfo.Instance.GetHighestOpenLevel (ProfileId);

		if (highestLevelOpenIndex > 0) {
			
			ImageLevel.gameObject.SetActive (true);
			TextLevel.text = highestLevelOpenIndex.ToString ();
		} else {
			ImageLevel.gameObject.SetActive (false);
		}

	}


}
