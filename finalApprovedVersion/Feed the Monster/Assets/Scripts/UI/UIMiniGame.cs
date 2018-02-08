using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;


public class UIMiniGame : MonoBehaviour
,IBeginDragHandler, IDragHandler, IEndDragHandler
//,IPointerClickHandler

{
	public static UIMiniGame Instance;

	public GameObject CheatButton;
	public MonsterBar monsterBar;


	public GameObject ButtonBack;
	public GameObject ButtonPrevious;
	public GameObject ButtonNext;

	public Button ButtonItems1;
	public Button ButtonItems2;
	public Button ButtonPlay;

	public GameObject StatusBubble;

	public Image StatusIcon;

	public Sprite Icon_Angry;
	public Sprite Icon_Bored;
	public Sprite Icon_Sad;

	public GameObject PanelEndGame;
	public string background = "BG_Collection";


	bool selected = false;
	bool isDraged = false;
	float LastX;
	float noSelectedMonsterTime = 0f;



	Monster _currentMonster;

	public Monster CurrentMonster
	{
		get { 
			return _currentMonster;
		}
	}


	void Awake()
	{
		Instance = this;
	}


	// Use this for initialization
	void Start ()
	{
		if (CheatButton != null) {
			if (GameAssets.Instance.DEBUG_ACTIVE == true) {
				CheatButton.SetActive (true);
			} else {
				CheatButton.SetActive (false);
			}
		}

	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Input.GetKeyDown (KeyCode.Escape) && MiniGameController.Instance.CurrentGame == null) {
			BackToMap ();
		}


		/*
		 * this fix an bug
		 * on fast taping there is no selected monster 
		 */
		if (_currentMonster == null && !isDraged) {
			noSelectedMonsterTime += Time.deltaTime;
//			LogConntroller.Instance.Log("No Monster: "+ aaa);

			if (noSelectedMonsterTime >= 1f) {
				noSelectedMonsterTime = 0f;
				monsterBar.showCurrentMonsterItems ();
				onMonsterLocated (monsterBar.getCurrentMonster ());
			}
		}
	}

	void  OnDisable()
	{
//		GameplayController.Instance.DestroyBackground();
		MiniGameController.Instance.hideAllGames ();

		monsterBar.onMonsterLocated -= onMonsterLocated;
		monsterBar.onMonsterDrag -= onMonsterDrag;
	}

	void OnEnable()
	{
		if(PanelEndGame != null) {
			PanelEndGame.SetActive (false);
		}
		lastMonsterIndex = -1;
		init ();
	}

	public Vector2 getMonsterMouth()
	{
		Transform to = GameObject.Find ("monster").transform.Find ("Mouth");
		Vector2 toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

			Canvas c = GetComponentInParent<Canvas> ();
			RectTransform CanvasRect = c.GetComponent<RectTransform> ();
			Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

			toPos = new Vector2 (
				((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
				((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
			);
			
		return toPos;
	}

	public bool IsDraged
	{
		get { 
			return isDraged;
		}
	}

	public void init(bool initBackground = true)
	{
		selected = false;
		isDraged = false;
		if (MiniGameController.Instance) {
			MiniGameController.Instance.hideAllGames ();
		}
		if (StatusBubble != null) {
			StatusBubble.SetActive (false);
		}

		monsterBar.ButtonPrevious = ButtonPrevious.GetComponent<Button> ();
		monsterBar.ButtonNext = ButtonNext.GetComponent<Button> ();

		monsterBar.onMonsterLocated += onMonsterLocated;
		monsterBar.onMonsterDrag += onMonsterDrag;

//		monsterBar.Init (true);
		monsterBar.IsMiniGame = true;

		if (lastMonsterIndex > -1) {
			monsterBar.JumpToMonsterIndex(lastMonsterIndex);
		}
		Invoke("updateButtons", 0.05f);


		if (GameAssets.Instance != null && GameAssets.Instance.ForceMiniGame != MiniGameController.GameType.None) {


			removeButtons ();

			Invoke ("GoToMiniGame", 0.03f);
		} else if (GameAssets.Instance != null && GameAssets.Instance.AutoStartMiniGame == true) {
			GameAssets.Instance.AutoStartMiniGame = false;

			Invoke ("Done", 0.03f);
		}
	}

	void GoToMiniGame() {
//		UIDressing.Instance.closePopup ();

		selected = true;
		monsterBar.Select ();

		removeButtons ();
		MiniGameController.Instance.StartRandomGame (null);
	}

	public void SetMonsterReady()
	{
		if (GameAssets.Instance.DEBUG_ACTIVE) {
			_currentMonster.IsReady = true;
		}
	}

	public void Done() {
//		if (selected || _currentMonster == null || !_currentMonster.IsReady || _currentMonster.MiniGame == MiniGameController.GameType.None) {
		if (selected || _currentMonster == null || _currentMonster.MiniGame == MiniGameController.GameType.None) {
			return;
		}

		selected = true;
		monsterBar.Select ();

		Invoke ("GotoMiniGame", 1f);

		if(ButtonNext != null) ButtonNext.SetActive (false);
		if(ButtonPrevious != null) ButtonPrevious.SetActive (false);

		if (ButtonItems1 != null)	ButtonItems1.interactable = false;
		if (ButtonItems2 != null)	ButtonItems2.interactable = false;
		if (ButtonPlay != null)		ButtonPlay.interactable = false;

		StatusBubble.SetActive (false);

		hideButtons ();






	}

	void hideButtons() {
		UIPopupPanel pop = gameObject.GetComponent<UIPopupPanel> ();

		if (pop != null) {
			if (ButtonItems1 != null) {
				pop.PopOutAny (ButtonItems1.transform);
			}
			if (ButtonItems2 != null) {
				pop.PopOutAny (ButtonItems2.transform);
			}
			if (ButtonPlay != null) {
				pop.PopOutAny (ButtonPlay.transform);
			}
			if (ButtonNext != null) {
				pop.PopOutAny (ButtonNext.transform);
			}
			if (ButtonPrevious != null) {
				pop.PopOutAny (ButtonPrevious.transform);
			}
			UIDressing.Instance.DressingPopupClick(-1);

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
	}

	public void NextMonsterClick()
	{
		monsterBar.MoveToNext ();
	}

	public void OnBeginDrag(PointerEventData eventData) 
	{
		if (selected || isDraged) {
			return;
		}

		isDraged = true;
		noSelectedMonsterTime = 0f;
		LastX = convertMousePosition().x;

		monsterBar.OnBeginDrag();
	}

	public void OnDrag(PointerEventData eventData)
	{
		if (!isDraged) {
			return;
		}

		float currX = convertMousePosition().x;

		float moveX = currX - LastX;
		monsterBar.DragBy (moveX);

		LastX = currX;
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		if (!isDraged) {
			return;
		}
		monsterBar.OnEndDrag ();
		isDraged = false;
	}

	void onMonsterDrag(Monster monster)
	{
		_currentMonster = null;
		ButtonPlay.interactable = false;
		StatusBubble.SetActive (false);
	}

	void onMonsterLocated(Monster monster)
	{
		_currentMonster = monster;

		if (monster.IsReady) {
			showStatusIcon (monster);
		}

		ButtonPlay.interactable = (monster.MonsterType == MonsterType.Magnet && monster.IsReady || monster.MonsterType != MonsterType.Magnet);
		UIDressing.Instance.onMonsterChange ();
	}




/*
	public void OnPointerClick (PointerEventData eventData)
	{

		if (!isDraged && !UIDressing.Instance.isPopuoOpen) {
			Done ();
		}
	}
*/


	Vector2 convertMousePosition()
	{
		return Camera.main.ScreenToWorldPoint(Input.mousePosition);
	}



	int lastMonsterIndex = -1;

	void GotoMiniGame() {
		//		UIDressing.Instance.closePopup ();

		removeButtons ();
		MiniGameController.Instance.StartRandomGame (_currentMonster);
		lastMonsterIndex = monsterBar.currentMonsterIndex;
		// UIController.Instance.ShowPanelWithoutTransitionEffect (UIController.Instance.GamePanel);
	}


	void removeButtons () {
		if (ButtonItems1 != null) {
			ButtonItems1.gameObject.SetActive (false);
		}
		if (ButtonItems2 != null) {
			ButtonItems2.gameObject.SetActive (false);
		}
		if (ButtonPlay != null) {
			ButtonPlay.gameObject.SetActive (false);
		}
		if (ButtonNext != null) {
			ButtonNext.gameObject.SetActive (false);
		}
		if (ButtonPrevious != null) {
			ButtonPrevious.gameObject.SetActive (false);
		}
	}




	public void showStatusIcon(Monster monster)
	{
		
		switch (monster.EmotionType) {

		case MonsterEmotionTypes.Happy:
		case MonsterEmotionTypes.NONE:
			StatusBubble.SetActive (false);
//			StatusBubble.GetComponent<UIPopupPanel> ().PopOut ();
			break;
		case MonsterEmotionTypes.Angry:
			StatusBubble.SetActive (true);
			StatusIcon.sprite = Icon_Angry;
			break;
		case MonsterEmotionTypes.Bored:
			StatusBubble.SetActive (true);
			StatusIcon.sprite = Icon_Bored;
			break;
		case MonsterEmotionTypes.Sad:
			StatusBubble.SetActive (true);
			StatusIcon.sprite = Icon_Sad;
			break;
//		case MonsterEmotionTypes.Hungry:
//			StatusBubble.SetActive (true);
//			StatusIcon.sprite = Icon_Hungry;
//			break;
//		case MonsterEmotionTypes.Afraid:
//			StatusBubble.SetActive (true);
//			StatusIcon.sprite = Icon_Afraid;
//			break;
		}
	}

	public void ShowEndGamePanel()
	{
		if(PanelEndGame != null) {
			PanelEndGame.SetActive (true);
		}

		if (ButtonBack != null) {
			UIPopupPanel popupPanel = this.gameObject.GetComponent<UIPopupPanel> ();
			if (popupPanel != null) {
				popupPanel.PopOutAny (ButtonBack.transform);
			}
		}
	}

//	MonsterType CenterMonsterType;
	public void setCurrentMonster (MonsterType monsterType)
	{
//		CenterMonsterType = monsterType;
	}

	public void BackToMap() {
		SceneController.Instance.LoadScene("MapScreen");
		GameAssets.Instance.MiniGameAsLevel = false;
	}

	public void NextLevel() {
		GameAssets.NextLevelIndex = GameAssets.CurrentLevelIndex + 1;

		BackToMap ();
	}

	public void onGameCompleteClick()
	{
		SceneController.Instance.LoadScene("GameCompleteScreen");
	}


}