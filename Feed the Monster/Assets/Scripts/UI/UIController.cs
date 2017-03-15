using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIController : MonoBehaviour {
	public static UIController Instance;



	public GameObject SplashPanel;
	public Button SplashScreenStartButton;
	public GameObject MapPanel;
	public GameObject GamePanel;
	public GameObject SettingsPopup;
	public GameObject SelectProfilePopup;

	public GameObject MiniGamePopup;
	public GameObject MonsterStatusPopup;

	public GameObject DiscoverNewFriendsPanel;
	public GameObject PausePopup;
	public UIConfirmationPopup ConfirmationPopup;
	public GameObject LoadingPopup;
	public GameObject MonsterSelectionPanel;
	public GameObject ParentsReportPanel;

	public Text PuzzleCountdown;

	public GameObject LevelEndPopup;
	public GameObject ScreenTransitionEffect;

	public bool DEBUG_ADD_ALL_MONSTERS;
	public bool DEBUG_CLEAR_PLAYERPREFS;
	public bool DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS;
	public bool DEBUG_USU_ONLINE_XMLS;

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
		if (DEBUG_CLEAR_PLAYERPREFS) {
			PlayerPrefs.DeleteAll ();
		}

		Instance = this;
		Application.runInBackground = false;
		Input.multiTouchEnabled = false;

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
		ShowPanel (SplashPanel);
		AudioController.Instance.PlayMusic (AudioController.Instance.Music);
//		Invoke ("ShowMapPanel", 2);
	}

	void HideAllPanels()
	{
		Transform canvas = GameObject.Find ("Canvas").transform;
		for (int i = 0; i < canvas.childCount; i++) {
			canvas.GetChild (i).gameObject.SetActive (false);
		}
	}

	void ShowMapPanel()
	{
		ShowPanel (MapPanel);
	}
	

	public void ShowPopup(GameObject popup)
	{
		GameObject oldPopup = mOpenPopup;

		if (oldPopup != null)
			oldPopup.SetActive (false);
		
		mOpenPopup = popup;
		popup.SetActive (true);
	}

	bool mLoadingScreenRequired = false; 

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

		if (mLoadingScreenRequired) {
			mLoadingScreenRequired = false;
			ShowPopup (LoadingPopup);
		}

		mLastPanel = mCurrentPanel;
		mCurrentPanel = mNextPanel;
		mCurrentPanel.SetActive (true);
	}

	public void QuitGameClick()
	{
		ConfirmationPopup.mNextPanelToShow = MapPanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}

	public void SoundButtonClick()
	{
		UserInfo.Instance.SetSound(!(UserInfo.Instance.IsSoundEnable() ? true : false));
		AudioController.Instance.UpdateVolume ();
	}

	public void MusicButtonClick()
	{
		UserInfo.Instance.SetMusic(!(UserInfo.Instance.IsMusicEnable() ? true : false));
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

	public void RetryLevelClickConfirm()
	{
		ConfirmationPopup.mNextPanelToShow = GamePanel; //UserInfo.Instance.CollectionLength > 0 ? MonsterSelectionPanel : GamePanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}

	public void RetryLevelClick() {

		bool isWin = GameplayController.Instance.CurrentLevelStars > 0;


//		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster.name) ) {
		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster) ) {
			ShowPanel (DiscoverNewFriendsPanel);
			DiscoverNewFriendsPanel.GetComponent<UIDiscoverNewMonsterController> ().SetNextPanelToShow (GamePanel, GameplayController.Instance.CurrentLevelIndex);
		} else {
			GoToLevel (GameplayController.Instance.CurrentLevelIndex, false);
		}

	}

	public void QuitLevelClick()
	{
		ConfirmationPopup.mNextPanelToShow = MapPanel;
		ShowPopup (ConfirmationPopup.gameObject);
	}


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


	public void NextClick()
	{
		bool isWin = GameplayController.Instance.CurrentLevelStars > 0;

//		GameplayController.Instance.ReaplaceBackground = true;

//		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster.name) ) {
		if (isWin && GameplayController.Instance.CurrentLevel.CollectableMonster != null && !UserInfo.Instance.HasCollectedFriend(GameplayController.Instance.CurrentLevel.CollectableMonster) ) {
			ShowPanel (DiscoverNewFriendsPanel);
			DiscoverNewFriendsPanel.GetComponent<UIDiscoverNewMonsterController> ().SetNextPanelToShow (GamePanel, GameplayController.Instance.CurrentLevelIndex + 1);
		} else {
			GoToLevel (GameplayController.Instance.CurrentLevelIndex + 1, false);
		}

	}

	public void GoToLevel(int levelIndex, bool monsterSelection = true)
	{
		GameplayController.Instance.CurrentLevelIndex = Mathf.Min(levelIndex, GameplayController.Instance.NumOfLevels - 1);

		if (monsterSelection && UserInfo.Instance.CollectionLength > 0) {
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




	public void OnChangeProfile(GameObject nextScreen)
	{
		/*
		if (mCurrentPanel == MapPanel) {
			UIMapController c = mCurrentPanel.GetComponent<UIMapController> ();
			if(c != null) {
				c.updatePosition (true);
			}
		}
*/

		if (nextScreen != null) {
			ShowPanel (nextScreen);
		} else if (mCurrentPanel == MapPanel) {
			ShowMapPanel ();
		}
	}

}
