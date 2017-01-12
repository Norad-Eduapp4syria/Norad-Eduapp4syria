using UnityEngine;
using System.Collections;
[System.Serializable]
public class Habitat : MonoBehaviour {


	public GameManager.GameSate unlockState;
	public Exterior exterior;
	public Interior interior;
	public GameObject FadeINOUTImage;
	public GameObject HouseBuildEffect;

	public GameObject mapPostion;


	void Awake(){
		
	}

	void Start(){
		if (GameManager.Instance.getCurrentGameState () > unlockState) {
			exterior.Level = 2;
		} else if (GameManager.Instance.tutorialController.getCurrentState () == TutorialController.TutorialStates.MORE_GOODS_REQUIRED) {
			exterior.Level = 1;
		}else if (GameManager.Instance.tutorialController.getCurrentState () > TutorialController.TutorialStates.MORE_GOODS_REQUIRED) {
			exterior.Level = 1;
		}
		else {
			exterior.Level = 0;
		}
	}

	void Update(){
		if (GameManager.Instance.tutorialController.getCurrentState () >= TutorialController.TutorialStates.RETURN_TO_HABITAT) {
			exterior.Level = 2;
		} else if (GameManager.Instance.tutorialController.getCurrentState () >= TutorialController.TutorialStates.PLAYER_TAP_TO_BUILD_HOME) {
			exterior.Level = 1;
		} else {
			exterior.Level = 0;
		}
	}


//	void OnApplicationFocus(bool focus){
//		AudioSource[] s = GameObject.FindObjectsOfType<AudioSource> ();
//		foreach (AudioSource a in s) {
//			a.mute = false;
//			a.volume = 1;
//			a.UnPause ();
//			a.enabled = true;
//		}
//	}
//
//	void OnApplicationPause(bool paused){
//		AudioSource[] s = GameObject.FindObjectsOfType<AudioSource> ();
//		foreach (AudioSource a in s) {
//			a.mute = false;
//			a.volume = 1;
//			a.UnPause ();
//			a.enabled = true;
//		
//		}
//	}
	public void FadeIn()
	{
		FadeINOUTImage.GetComponent<Animator> ().SetBool ("IsFadeIn", true);
	}

	public void FadeOut()
	{
		FadeINOUTImage.GetComponent<Animator> ().SetBool ("IsFadeIn", false);
	}


	void FixedUpdate()
	{
//		Debug.Log ("Chal raha bawa");
	}

}
