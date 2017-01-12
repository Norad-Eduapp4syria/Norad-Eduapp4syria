using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class UIMapController : MonoBehaviour {
	public Text ScoreText;
	public Button btnCollection;
	public ScrollRect mapScroll;

	bool isStatusPopupShow = false;

	void Awake() {

	}

	// Use this for initialization
	/*void Start () {
	
	}*/
	
	// Update is called once per frame
	void Update () {

	}

	void OnEnable()
	{

		int sumAllLevelsScore = 0;
		int highestLevelOpenIndex;
		int lastPlayingLevelIndex;

		highestLevelOpenIndex = UserInfo.Instance.GetHighestOpenLevel ();
		lastPlayingLevelIndex = UserInfo.Instance.GetLastPlayingLevel ();
		TutorialController.Instance.EndTutorial (); //Jonathan??

/*
		if (UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS) {
//			highestLevelOpenIndex = GameplayController.Instance.Levels.Length - 1;
			highestLevelOpenIndex = GameplayController.Instance.NumOfLevels - 1;
		}
*/

		SnapTo (GameObject.Find ("Pin - Level " + lastPlayingLevelIndex).transform);

		for (int i = highestLevelOpenIndex; i >= 0; i--) {
			sumAllLevelsScore += UserInfo.Instance.GetLevelScore (i);
		}

		if (highestLevelOpenIndex == 0) {
			var curPin = GameObject.Find ("Pin - Level 0").transform;
			TutorialController.Instance.PointAt (curPin.localPosition + new Vector3 (0, 30, 0), curPin.parent);
		}

		ScoreText.text = sumAllLevelsScore.ToString ();
		btnCollection.interactable = UserInfo.Instance.CollectionLength > 0;

		Invoke("ShowStatusPopup", 0.8f);

		Analitics.Instance.treckScreen ("Map");
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



	void ShowStatusPopup()
	{
		if(!isStatusPopupShow)
		{
			Monster monster = MiniGameController.Instance.getEmotionMonster ();
			if (monster != null) {
				UIController.Instance.ShowPopup (UIController.Instance.MonsterStatusPopup);
				UIStatusController StatusController = UIController.Instance.MonsterStatusPopup.GetComponent<UIStatusController> ();

				StatusController.init (monster);

				isStatusPopupShow = true;
			}
		}

		if (TutorialController.Instance.GetIsInMinigameTutorial ()) {
			Button[] stations = GameObject.Find ("Stations").GetComponentsInChildren<Button> ();
			foreach (Monster friend in UserInfo.Instance.CollectedFriends) {
				friend.EmotionType = MonsterEmotionTypes.Afraid;
			}
			TutorialController.Instance.PointAt (btnCollection.transform.position, this.transform);
		}
	}
}
