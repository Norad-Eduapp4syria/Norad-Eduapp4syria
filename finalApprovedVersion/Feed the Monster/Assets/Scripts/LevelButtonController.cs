using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class LevelButtonController : MonoBehaviour {
	public Image StarImage1;
	public Image StarImage2;
	public Image StarImage3;
	public Text LevelNumberText;
	public Image LockImage;

	public int ColliderPointId = -1;


	public MiniGameController.GameType ForceMiniGame = MiniGameController.GameType.None;

	protected bool isInited = false;
	protected int highestOpenLevelIndex;
	public int levelIndex;


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
		UpdateView ();
	}

	void OnDisable() {
		if (levelIndex >= highestOpenLevelIndex && isInited == false) {
			stopAnimator ();
		}
	}

	protected void Appear(){
//		if (levelIndex >= highestOpenLevelIndex && isInited == false)
		{
			isInited = true;
			startAnimator ();
			Invoke ("stopAnimator", 0.5f);
		}
	}

	void stopAnimator()
	{
		GetComponent<Animator> ().enabled = false;
	}

	void startAnimator()
	{
		GetComponent<Animator> ().enabled = true;
	}

	public void UpdateView()
	{
		highestOpenLevelIndex = UsersController.Instance.userData().getHighestOpenLevel ();

		levelIndex = int.Parse (gameObject.name.Replace ("Pin - Level ", ""));

		if (levelIndex >= highestOpenLevelIndex) {
			transform.localScale = new Vector3 (0.01f, 0.01f, 0.01f);
		}

		if (highestOpenLevelIndex >= levelIndex) {
			Appear ();
		} else {
			Invoke ("Appear", .5f + (levelIndex - highestOpenLevelIndex) * .2f);
		}

		if (GameAssets.Instance.DEBUG_ACTIVE) {
			//	levelOpen = GameplayController.Instance.Levels.Length - 1;
			highestOpenLevelIndex = GameAssets.Instance.NumOfLevels - 1;
		}
		if (levelIndex <= highestOpenLevelIndex || levelIndex == 0) {
			GetComponent<Button> ().interactable = true;
			string levelNumber = (levelIndex  +1).ToString();

			Color fullColor = new Color (1, 1, 1, 1);
//			Color emptyColor = new Color (0.0f, 0.0f, 0.0f, 0.7f);

			// Added by Tzahi
			int levelStars = UsersController.Instance.userData().getLevelStars (levelIndex);

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
			GetComponent<Button> ().interactable = true;
		} else {
			GetComponent<Button> ().interactable = false;

			LockImage.enabled = true;
			StarImage1.enabled = false;
			StarImage2.enabled = false;
			StarImage3.enabled = false;
			LevelNumberText.enabled = false;
		}
	
	}


	public void onClick()
	{
		GameAssets.CurrentLevelIndex = levelIndex;

		if (ForceMiniGame == MiniGameController.GameType.None) {
			goToGame ();
		} else {
			goToMiniGame ();
		}
	}

	public void setNotActive() {
		GetComponent<Button> ().interactable = false;
	}



	public void goToGame() {
		SceneController.Instance.LoadScene("GameScreen");
	}


	public void goToMiniGame () {

		GameAssets.Instance.ForceMiniGame = ForceMiniGame;
		GameAssets.Instance.MiniGameAsLevel = true;
		SceneController.Instance.LoadScene("MiniGamesScreen");

		UsersController.Instance.userData ().setLastPlayingLevel (GameAssets.CurrentLevelIndex);
	}

}
