using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;
using System.Collections;

public class UIMonsterSelection : MonoBehaviour
/*
,IBeginDragHandler, IDragHandler, IEndDragHandler
,IPointerClickHandler
*/
{
	public MonsterBar monsterBar;

	public GameObject ButtonPrevious;
	public GameObject ButtonNext;
	public AudioClip InstructionSound;
	public string VoiceTutorial;

	public MonsterSelectionTouchController TouchController;


	Monster selectedMonster = null;

	bool selected = false;
	bool isDraged = false;

	bool isTutorial;
	float TutorialCurrentTime = 0;
	float TutorialShowTime = 0;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Escape)) {
			BackToMap ();
		}

		if (!isDraged && !isTutorial) {
			TutorialCurrentTime += Time.deltaTime;

			if (TutorialShowTime > 0 && TutorialCurrentTime >= TutorialShowTime) {
				showTutorial ();
			}
		}
	}


	void OnEnable() {
		selectedMonster = null;
//		if(GameplayController.Instance.ReaplaceBackground_SelectMonster == true)
		if(GameplayController.Instance != null)
		{
			GameplayController.Instance.LoadBackground ();
			GameplayController.Instance.ReaplaceBackground_SelectMonster = false;
		}

		monsterBar.ButtonPrevious = ButtonPrevious.GetComponent<Button> ();
		monsterBar.ButtonNext = ButtonNext.GetComponent<Button> ();

//		monsterBar.Init ();
		monsterBar.IsMiniGame = false;

		monsterBar.onMonsterLocated += onMonsterLocated;
//		monsterBar.onMonsterDrag += onMonsterDrag;

		updateButtons ();


		if (GameplayController.Instance.CurrentLevelIndex == 0 && UsersController.Instance.userData().getHighestOpenLevel () == 0) {
			TutorialController.Instance.AddVoiceTutorial (VoiceTutorial, enableTutorialHand);
		} else {
			AudioController.Instance.PlaySoundAfterDelay (InstructionSound, 0.3f);
			enableTutorialHand ();
			//Invoke ("addTutorialHandPosition", 0.8f);
		}

		if (TouchController != null) {
			TouchController.onBeginDrag += OnBeginDrag;
			TouchController.onDrag += OnDrag;
			TouchController.onEndDrag += OnEndDrag;
			TouchController.onPointerClick += OnPointerClick;
		}

		Analitics.TreckScreen ("Monster Select");
	}

	void enableTutorialHand()
	{
		if (GameAssets.CurrentLevelIndex == 0) {
			if (UsersController.Instance.userData().getHighestOpenLevel () == 0) {
				this.TutorialShowTime = 0.01f;
			} else {
				this.TutorialShowTime = 0.8f;
			}
		} else {
			if (UsersController.Instance.userData ().getLastLetterGroup() <= 1) {
				this.TutorialShowTime = 3f;
			} else {
				this.TutorialShowTime = 0f;
			}
		}
	}

	void showTutorial()
	{
		isTutorial = true;
		addTutorialHandPosition ();
	}

	public void addTutorialHandPosition()
	{
		//		if (GameplayController.Instance.CurrentLevelIndex == 0) {
		if(isTutorial) {
			Transform to = monsterBar.currentMonster.Find ("Hand");
			Vector2 toPos = new Vector2 (0, -140);
			if (to == null) {
				GameObject go;
				go = GameObject.Find ("Button - Ok");
				if (go != null) {
					toPos = go.transform.localPosition + new Vector3 (0, 100);
				} else {

				}
			} else {
				toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

				Canvas c = GetComponentInParent<Canvas> ();
				RectTransform CanvasRect = c.GetComponent<RectTransform> ();
				Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint (to.position));

				toPos = new Vector2 (
					((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
					((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
				);
			}
			TutorialController.Instance.PointAt (toPos, null, true);
		}
	}




	public void Done(){
		if (selected)
			return;
		selected = true;
		monsterBar.Select ();

		Invoke ("GotoGame", 1f);
		GetComponent<UIPopupPanel> ().PopOut ();

		if (GameplayController.Instance.CurrentLevelIndex == 0) {
			TutorialController.Instance.EndTutorial ();
		}
		if (selectedMonster != null) {
			Analitics.Instance.treckEvent (
				AnaliticsCategory.GamePlay,
				AnaliticsAction.SelectMonster +
				" " + selectedMonster.name +
				" Evolve_" + (selectedMonster.Gage + 1),
				"Level_" + (GameplayController.Instance.CurrentLevelIndex + 1),
				(long)selectedMonster.MonsterType
			);
		}
	}

	void OnDisable(){
		selected = false;
		CancelInvoke ("setDrag");

		monsterBar.Clean ();
		monsterBar.onMonsterLocated -= onMonsterLocated;
//		monsterBar.onMonsterDrag -= onMonsterDrag;

		if (TouchController != null) {
			TouchController.onBeginDrag -= OnBeginDrag;
			TouchController.onDrag -= OnDrag;
			TouchController.onEndDrag -= OnEndDrag;
			TouchController.onPointerClick -= OnPointerClick;
		}
	}

	void GotoGame(){
		UIController.Instance.ShowPanelWithoutTransitionEffect (UIController.Instance.GamePanel);

		if (GameplayController.Instance.CurrentLevelIndex == 0) {
			TutorialController.Instance.EndTutorial ();
		}


	}

	void updateButtons () {
		if (monsterBar.NumMonsters > 1) {
			if(ButtonNext != null) ButtonNext.SetActive (true);
			if(ButtonPrevious != null) ButtonPrevious.SetActive (true);

//			monsterBar.updateButtons ();
		} else {
			if(ButtonNext != null) ButtonNext.SetActive (false);
			if(ButtonPrevious != null) ButtonPrevious.SetActive (false);
		}
	}

	public void PreviousMonsterClick()
	{
		monsterBar.MoveToPrevious ();
		if (GameplayController.Instance.CurrentLevelIndex == 0) {
			TutorialController.Instance.EndTutorial ();
		}
	}

	public void NextMonsterClick()
	{
		monsterBar.MoveToNext ();
		if (GameplayController.Instance.CurrentLevelIndex == 0) {
			TutorialController.Instance.EndTutorial ();
		}
	}



	float LastX;

//	public void OnBeginDrag(PointerEventData eventData) 
	public void OnBeginDrag() 
	{
		Invoke ("setDrag", 0.025f);
		if (isTutorial) {
			TutorialController.Instance.EndTutorial ();
		}
	}

	void setDrag()
	{
		isDraged = true;
		LastX = convertMousePosition().x;
		monsterBar.OnBeginDrag();
	}


//	public void OnDrag(PointerEventData eventData)
	public void OnDrag()
	{
		if (isDraged) {
			float currX = convertMousePosition ().x;

			float moveX = currX - LastX;
			monsterBar.DragBy (moveX);

			LastX = currX;
		}
//		Debug.Log ("OnDrag");
	}

//	public void OnEndDrag(PointerEventData eventData)
	public void OnEndDrag()
	{
		CancelInvoke ("setDrag");

		isDraged = false;
		monsterBar.OnEndDrag ();

//		Debug.Log ("OnEndDrag");
	}

//	public void OnPointerClick (PointerEventData eventData)
	public void OnPointerClick ()
	{
		if (!isDraged) {
			Done ();
//			Debug.Log ("OnPointerClick");
		}
	}


	Vector2 convertMousePosition()
	{
		return Camera.main.ScreenToWorldPoint(Input.mousePosition);
	}


	void onMonsterLocated(Monster monster)
	{
		selectedMonster = monster;
		addTutorialHandPosition ();
	}

	public void BackToMap() {
		SceneController.Instance.LoadScene("MapScreen");
	}

}
