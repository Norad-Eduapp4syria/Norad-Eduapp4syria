using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIMapController : MonoBehaviour {
	static bool isStatusPopupShow = false;


	//	public Text ScoreText;
	public Button btnCollection;
	public Button btnPreferences;

	public Transform popupsHolder;
	public GameObject mSettingsPopup;

	public ScrollRect mapScroll;

	public MapAvatarController avatar;
	public EdgeCollider2D trackCollider;



	void Awake() {
		avatar.ColliderPoints = trackCollider.points;
	}

	// Use this for initialization
	/*void Start () {
	
	}*/
	
	// Update is called once per frame
	void Update () {

	}

	void OnEnable()
	{
		mSettingsPopup.SetActive (false);
		Invoke ("initMap", 0.02f);
	}

	void initMap()
	{
		updatePosition ();
		updateAvatarPosition ();

		if (GameAssets.NextLevelIndex == -1) {
			Invoke ("ShowPopups", 2f);
		}

		if (!StartTutorial ()) {
			Invoke ("moveAvatarToNextPosition", 0.1f);
			if (GameAssets.NextLevelIndex == -1 && UsersController.Instance.userData().HasReadyMonster && UsersController.Instance.userData().getMiniGameTutorialCount() <= GameplaySettings.TutorialShowTimes) {
				TutorialController.Instance.PointAt (btnCollection.transform.localPosition + new Vector3 (0, 0, 0), btnCollection.transform.parent, true);
			}
		}


		Analitics.TreckScreen ("Map");
	}



	void OnDisable() {
		if (TutorialController.Instance != null) {
			TutorialController.Instance.EndTutorial ();
		}
		CancelInvoke ();
	}

	public void updatePosition()
	{
		int lastPlayingLevelIndex;

		lastPlayingLevelIndex = UsersController.Instance.userData().getLastPlayingLevel ();
		TutorialController.Instance.EndTutorial (); //Jonathan??

		SnapTo (GameObject.Find ("Pin - Level " + lastPlayingLevelIndex).transform);

	}

	void updateAvatarPosition()
	{
		try 
		{
			int lastPlayingLevelIndex = UsersController.Instance.userData().getLastPlayingLevel ();

			GameObject stationGO = GameObject.Find("Pin - Level " + lastPlayingLevelIndex);
			LevelButtonController stationController = stationGO.GetComponent<LevelButtonController>();

			avatar.jumpToPointId(stationController.ColliderPointId);

			btnCollection.interactable = false;
			btnPreferences.interactable = false;
		} catch {
			btnCollection.interactable = true;
			btnPreferences.interactable = true;
			Debug.Log ("Error to locate avatar");
		}
	}

	void moveAvatarToNextPosition()
	{
		if(GameAssets.NextLevelIndex != -1) {
			int NextLevelIndex = GameAssets.NextLevelIndex;
			int highestOpenLevel = UsersController.Instance.userData().getHighestOpenLevel ();
			int lastPlayingLevelIndex = UsersController.Instance.userData().getLastPlayingLevel ();

			if (NextLevelIndex > highestOpenLevel) {
				NextLevelIndex = highestOpenLevel;
			}

			GameObject stationGO = GameObject.Find("Pin - Level " + lastPlayingLevelIndex);
			LevelButtonController stationController = stationGO.GetComponent<LevelButtonController>();

			LevelButtonController[] allStations = GetComponentsInChildren<LevelButtonController>(); 

			btnCollection.interactable = false;
			btnPreferences.interactable = false;

			foreach(LevelButtonController st in allStations) {
				st.setNotActive();
			}

			stationGO = GameObject.Find("Pin - Level " + NextLevelIndex);
			stationController = stationGO.GetComponent<LevelButtonController>();
			avatar.goToPointId(stationController.ColliderPointId, stationController, 0.5f);

			GameAssets.NextLevelIndex = -1;
		} else {
			btnCollection.interactable = true;
			btnPreferences.interactable = true;
		}
	}


	private void SnapTo(Transform target)
	{
		Canvas.ForceUpdateCanvases();
		RectTransform contentPanel = mapScroll.content;

		var d = (target.localPosition.y - 200) / (contentPanel.sizeDelta.y - 400);
		d = Mathf.Min (d, 1);
		d = Mathf.Max (d, 0);
		mapScroll.normalizedPosition = new Vector2(0, d);

		/*contentPanel.anchoredPosition =
			(Vector2)mapScroll.transform.InverseTransformPoint(contentPanel.position)
			- (Vector2)mapScroll.transform.InverseTransformPoint(target.position);*/
	}

	void ShowPopups()
	{
		if(ShowNewAccessoriesPopup()) {
			
		}
	}

	bool ShowNewAccessoriesPopup() {
		bool isShow = false;

		if (UsersController.Instance.userData ().NewAvailableAccessorie > 0 && GameAssets.NextLevelIndex == -1) {
			Instantiate(Resources.Load ("Gameplay/Popups/Popup Panel - New Accessories") as GameObject, popupsHolder);
			isShow = true;
		}
		return isShow;
	}


	public void OnSELClick()
	{
		Analitics.Instance.treckEvent (AnaliticsCategory.Sel, AnaliticsAction.Open, "Map");
		SceneController.Instance.LoadScene("MiniGamesScreen");
	}

	public void OpenSettingsPopup()
	{
		mSettingsPopup.SetActive (true);
	}

	bool StartTutorial()
	{
		int highestLevelOpenIndex = UsersController.Instance.userData().getHighestOpenLevel ();

		if (highestLevelOpenIndex == 0) {
			TutorialController.Instance.AddVoiceTutorial ("Text_01", addTutorialHand_1);
			return true;
		} else if (highestLevelOpenIndex == 1) {
			TutorialController.Instance.AddVoiceTutorial ("Text_15", addTutorialHand_2);
			return true;
		} 
		return false;
	}

	void addTutorialHand_1()
	{
		if (GameAssets.NextLevelIndex == -1) {
			var curPin = GameObject.Find ("Pin - Level 0").transform;
			TutorialController.Instance.PointAt (curPin.localPosition + new Vector3 (0, 30, 0), curPin.parent, true);
		}
		Invoke ("moveAvatarToNextPosition", 0.1f);
	}

	void addTutorialHand_2()
	{
		if (GameAssets.NextLevelIndex == -1) {
			var curPin = GameObject.Find ("Pin - Level 1").transform;
			TutorialController.Instance.PointAt (curPin.localPosition + new Vector3 (0, 30, 0), curPin.parent, true);
		}
		Invoke ("moveAvatarToNextPosition", 0.1f);
	}

}
