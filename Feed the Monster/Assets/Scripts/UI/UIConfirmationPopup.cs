using UnityEngine;
using System.Collections;

public class UIConfirmationPopup : MonoBehaviour {

	public GameObject mNextPanelToShow;
	// Use this for initialization


	public delegate void ConfirmDelegate();
	public ConfirmDelegate onConfirm;

	public AudioClip sndRUShure;

	void OnEnable(){
		GameplayController.Instance.IsPausePopup = true;	

		AudioController.Instance.PlaySound ( sndRUShure );
	}


	void Update () {
		if (Input.GetKeyDown (KeyCode.Escape)) {
			Cancel ();
		}
	}


	public void Confirm(){
		UIController.Instance.ClosePopup (gameObject);
		if (mNextPanelToShow != null) {
			UIController.Instance.ShowPanel (mNextPanelToShow);
		}
		if (onConfirm != null) {
			onConfirm();
			onConfirm = null;
		}

	}
	public void Cancel() {
		UIController.Instance.ClosePopup (gameObject);
	}
}
