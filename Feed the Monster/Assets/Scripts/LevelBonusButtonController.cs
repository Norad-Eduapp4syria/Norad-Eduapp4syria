using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class LevelBonusButtonController : LevelButtonController {


	public Image DoneImage;
	public int RequiredLevel = -1;


	// Use this for initialization
	void Start () {

	}

	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		disableElements ();

		highestOpenLevelIndex = UserInfo.Instance.GetHighestOpenLevel ();

		levelIndex = int.Parse (gameObject.name.Replace ("Pin - Level ", ""));


		if (levelIndex >= highestOpenLevelIndex) {
			transform.localScale = new Vector3 (0.01f, 0.01f, 0.01f);
		}

		int levelOpen = UserInfo.Instance.GetHighestOpenLevel ();

		if (levelOpen >= levelIndex) {
			Appear ();	
		} else {
			Invoke ("Appear", .5f + (levelIndex - levelOpen) * .2f);
		}

		if (UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS) {
			//	levelOpen = GameplayController.Instance.Levels.Length - 1;
			levelOpen = GameplayController.Instance.NumOfLevels - 1;
		}


//		if (levelIndex <= levelOpen) {
		if (RequiredLevel > -1 && RequiredLevel <= levelOpen) {
			int levelScore = UserInfo.Instance.GetLevelScore (levelIndex);

			if (levelScore == 0) {
				GetComponent<Button> ().interactable = true;
				if (DoneImage != null) {
					DoneImage.enabled = false;
				}
			} else {
				GetComponent<Button> ().interactable = false;
				if (DoneImage != null) {
					DoneImage.enabled = true;
					DoneImage.gameObject.SetActive (true);
				}
			}
			LockImage.enabled = false;
		} else {
			GetComponent<Button> ().interactable = false;

			LockImage.enabled = true;
		}
	}





	void disableElements()
	{
		if(StarImage1 != null) {
			StarImage1.gameObject.SetActive (false);
		}
		if(StarImage2 != null) {
			StarImage2.gameObject.SetActive (false);
		}
		if(StarImage3 != null) {
			StarImage3.gameObject.SetActive (false);
		}
		if (LevelNumberText != null) {
			LevelNumberText.gameObject.SetActive(false);
		}


	}


}
