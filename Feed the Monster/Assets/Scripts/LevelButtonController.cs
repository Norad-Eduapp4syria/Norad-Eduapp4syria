using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class LevelButtonController : MonoBehaviour {
	public Image StarImage1;
	public Image StarImage2;
	public Image StarImage3;
	public Sprite StarEmpty;
	public Sprite StarFill;
	public Text LevelNumberText;
	public Image LockImage;

	protected bool isInited = false;
	protected int highestOpenLevelIndex;
	protected int levelIndex;


	// Use this for initialization
	void Awake () {
		if (LevelNumberText != null) {
			LevelNumberText.transform.localScale /= 2;
			LevelNumberText.fontSize *= 2;
		}
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		highestOpenLevelIndex = UserInfo.Instance.GetHighestOpenLevel ();

		levelIndex = int.Parse (gameObject.name.Replace ("Pin - Level ", ""));


		if (levelIndex >= highestOpenLevelIndex) {
			transform.localScale = new Vector3 (0.01f, 0.01f, 0.01f);
		}

		int levelOpen = UserInfo.Instance.GetHighestOpenLevel ();

		if (levelOpen >= levelIndex)
			Appear ();	
		else
			Invoke ("Appear", .5f + (levelIndex - levelOpen) * .2f);
		
		if (UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS) {
		//	levelOpen = GameplayController.Instance.Levels.Length - 1;
			levelOpen = GameplayController.Instance.NumOfLevels - 1;
		}
		if (levelIndex <= levelOpen) {
			GetComponent<Button> ().interactable = true;
			string levelNumber = (levelIndex  +1).ToString();


			Color fullColor = new Color (1, 1, 1, 1);
			Color emptyColor = new Color (0.0f, 0.0f, 0.0f, 0.7f);

			// Added by Tzahi
			int levelStars = UserInfo.Instance.GetLevelStars (levelIndex);
/*
			StarImage1.color = levelStars >= 1 ? fullColor : emptyColor;
			StarImage3.color = levelStars >= 2 ? fullColor : emptyColor;
			StarImage2.color = levelStars >= 3 ? fullColor : emptyColor;
*/


			if (levelStars >= 1) {
				StarImage1.color = fullColor;
				StarImage1.gameObject.SetActive (true);
			} else {
				StarImage1.gameObject.SetActive (false);
			}

			if (levelStars >= 2) {
				StarImage3.color = fullColor;
				StarImage3.gameObject.SetActive (true);
			} else {
				StarImage3.gameObject.SetActive (false);
			}

			if (levelStars >= 3) {
				StarImage2.color = fullColor;
				StarImage2.gameObject.SetActive (true);
			} else {
				StarImage2.gameObject.SetActive (false);
			}

			LevelNumberText.text = levelNumber;

			LockImage.enabled = false;
			StarImage1.enabled = true;
			StarImage2.enabled = true;
			StarImage3.enabled = true;
			LevelNumberText.enabled = true;
		} else {
			GetComponent<Button> ().interactable = false;

			LockImage.enabled = true;
			StarImage1.enabled = false;
			StarImage2.enabled = false;
			StarImage3.enabled = false;
			LevelNumberText.enabled = false;
		}
	}

	void OnDisable() {
		if (levelIndex >= highestOpenLevelIndex && isInited == false) {
			GetComponent<Animator> ().enabled = false;
		}
	}

	protected void Appear(){
		if (levelIndex >= highestOpenLevelIndex && isInited == false) {
			isInited = true;
			GetComponent<Animator> ().enabled = true;
		}
	}


	public void onClick()
	{
		UIController.Instance.LevelButtonClick(levelIndex);
	}

}
