using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIController : MonoBehaviour {
	public static UIController Instance;


	public GameObject GamePanel;
	public GameObject PausePopup;
	public GameObject MonsterSelectionPanel;

	public GameObject LevelEndPopup;
	public GameObject ScreenTransitionEffect;


	public AudioClip ClickSound;

	GameObject mLastPanel;
	GameObject mCurrentPanel;
	GameObject mNextPanel;
	GameObject mOpenPopup;



	public GameObject LastPanel {
		get { 
			return mLastPanel;
		}
	}

	void Awake()
	{

		Instance = this;

		HideAllPanels();
	}

	// Use this for initialization
	void Start () {
		Init ();
	}

	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Escape)) {
			//			Application.Quit(); 
		}
	}


	void Init()
	{
		if (GameAssets.Instance.ForceMonster == MonsterType.NONE) {
			Invoke ("ShowMonsterSelectionPanel", 0.01f);
		} else {
			Invoke ("ShowGamePanel", 0.01f);
		}
	}

	void HideAllPanels()
	{
		Transform canvas = GameObject.Find ("Canvas").transform;
		for (int i = 0; i < canvas.childCount; i++) {
			canvas.GetChild (i).gameObject.SetActive (false);
		}
	}


	void ShowMonsterSelectionPanel()
	{
		ShowPanel (MonsterSelectionPanel);
	}

	void ShowGamePanel()
	{
		ShowPanel (GamePanel);
	}



	public void ShowPopup(GameObject popup)
	{
		GameObject oldPopup = mOpenPopup;

		if (oldPopup != null)
			oldPopup.SetActive (false);
		
		mOpenPopup = popup;
		popup.SetActive (true);
	}

	public void ShowPanel(GameObject nextPanel)
	{
		//mLoadingScreenRequired =  mCurrentPanel != null && (mCurrentPanel == GamePanel && nextPanel == MapPanel || mCurrentPanel == MapPanel && nextPanel == MonsterSelectionPanel);
		mNextPanel = nextPanel;

		if (mCurrentPanel == null) {
			Transition ();
		} else {
			ScreenTransitionEffect.SetActive (true);
		}
		//Debug.Log ("ShowPanel " + mCurrentPanel);
	}

	public void ShowPanelWithoutTransitionEffect(GameObject panel)
	{
		mNextPanel = panel;
		Transition ();
	}

	public void Transition() 
	{
		if (mOpenPopup != null) {
			ClosePopup (mOpenPopup);
		}

		if (mCurrentPanel != null) {
			mCurrentPanel.SetActive (false);
		}

		mLastPanel = mCurrentPanel;
		mCurrentPanel = mNextPanel;
		mCurrentPanel.SetActive (true);
	}
/*
	public void QuitGameClick()
	{
		ConfirmationPopup.mNextPanelToShow = MapPanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}
*/
	public void SoundButtonClick()
	{
		SaveStatConnector.Instance.SoundState = !SaveStatConnector.Instance.SoundState;
		AudioController.Instance.UpdateVolume ();
	}

	public void MusicButtonClick()
	{
		SaveStatConnector.Instance.MusicState = !SaveStatConnector.Instance.MusicState;
		AudioController.Instance.UpdateVolume ();
	}

	public void ClosePopup(GameObject popup)
	{
		popup.SetActive (false);
		if (popup == mOpenPopup) {
			mOpenPopup = null;
		}
	}

	public void LevelButtonClick(int levelIndex)
	{
		GoToLevel (levelIndex);
	}
/*
	public void RetryLevelClickConfirm()
	{
		ConfirmationPopup.mNextPanelToShow = GamePanel; //UserInfo.Instance.CollectionLength > 0 ? MonsterSelectionPanel : GamePanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}
*/
/*
	public void RetryLevelClick() {

		bool isWin = GameplayController.Instance.CurrentLevelStars > 0;

		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster) ) {
			ShowPanel (DiscoverNewFriendsPanel);
			DiscoverNewFriendsPanel.GetComponent<UIDiscoverNewMonsterController> ().SetNextPanelToShow (GamePanel, GameplayController.Instance.CurrentLevelIndex);
		} else {
			GoToLevel (GameplayController.Instance.CurrentLevelIndex, false);
		}
	}
*/
/*
	public void QuitLevelClick()
	{
		ConfirmationPopup.mNextPanelToShow = MapPanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}
*/
/*
	public void MapClick() // TODO: Resolve Bug - Pausing the game end exiting to map could result in "New Monster Discovered Screen" if enough points were obtained.
	{
		bool isWin = GameplayController.Instance.CurrentLevelStars > 0;

//		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster.name) ) {
		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster) ) {
			ShowPanel (DiscoverNewFriendsPanel);
			DiscoverNewFriendsPanel.GetComponent<UIDiscoverNewMonsterController> ().SetNextPanelToShow (MapPanel,GameplayController.Instance.CurrentLevelIndex + 1);
		} else {
			if(TutorialController.Instance != null)
				TutorialController.Instance.EndTutorial();
			ShowPanel (MapPanel);
		}
	}
*/

/*
	public void NextClick()
	{
		GameAssets.NextLevelIndex = GameplayController.Instance.CurrentLevelIndex + 1;

		bool isWin = GameplayController.Instance.CurrentLevelStars > 0;


		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster) ) {
			ShowPanel (DiscoverNewFriendsPanel);
			DiscoverNewFriendsPanel.GetComponent<UIDiscoverNewMonsterController> ().SetNextPanelToShow (MapPanel, GameplayController.Instance.CurrentLevelIndex + 1);
		} else {
			ShowMapPanel ();
		}
	}
*/
	public void GoToLevel(int levelIndex, bool monsterSelection = true)
	{
		GameplayController.Instance.CurrentLevelIndex = Mathf.Min(levelIndex, GameAssets.Instance.NumOfLevels - 1);

		if (monsterSelection && UsersController.Instance.userData().CollectionLength > 0) {
//			GameplayController.Instance.ReaplaceBackground = false;
			ShowPanel (MonsterSelectionPanel);
		} else {
			if (TutorialController.Instance != null) {
				TutorialController.Instance.EndTutorial ();
			}
			ShowPanel (GamePanel);
		}
	}

	public void SelectFriend(GameObject buttonSender)
	{

	}



/*
	public void OnChangeProfile(GameObject nextScreen)
	{
		if (nextScreen != null) {
			ShowPanel (nextScreen);
		} else if (mCurrentPanel == MapPanel) {
			ShowMapPanel ();
		}
	}
*/

}
