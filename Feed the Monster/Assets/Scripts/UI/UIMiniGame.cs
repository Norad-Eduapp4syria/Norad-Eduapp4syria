using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;


public class UIMiniGame : MonoBehaviour
,IBeginDragHandler, IDragHandler, IEndDragHandler

{
	public static UIMiniGame Instance;

	public GameObject CheatButton;
	public MonsterBar monsterBar;
	public GameObject ButtonPrevious;
	public GameObject ButtonNext;

	public GameObject StatusBubble;

	public Image StatusIcon;

	public Sprite Icon_Angry;
	public Sprite Icon_Bored;
	public Sprite Icon_Sad;
	public Sprite Icon_Hungry;
	public Sprite Icon_Afraid;

	public GameObject PanelEndGame;
	public GameObject background;


	bool selected = false;
	bool isDraged = false;
	float LastX;


	void Awake()
	{
		Instance = this;
	}


	// Use this for initialization
	void Start ()
	{
		if (CheatButton != null) {
			if (UIController.Instance.DEBUG_OPEN_ALL_LEVELS_PLAYERPREFS == true) {
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
			UIController.Instance.MapClick();
		}
	}

	void  OnDisable()
	{
		GameplayController.Instance.DestroyBackground();
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
		if (TutorialController.Instance.GetIsInMinigameTutorial ()) {
			Invoke ("PointAtCallout", 0.7f);
		}
	}
	public void PointAtCallout() {
		TutorialController.Instance.PointAt (StatusBubble.transform.position + new Vector3(0, 180, 0), this.transform);
		//TutorialController.Instance.PointAt (getMonsterMouth (), this.transform);
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
		if (initBackground) {
			GameplayController.Instance.LoadBackground (background);
		}
		if (MiniGameController.Instance) {
			MiniGameController.Instance.hideAllGames ();
		}

		monsterBar.ButtonPrevious = ButtonPrevious.GetComponent<Button> ();
		monsterBar.ButtonNext = ButtonNext.GetComponent<Button> ();

		monsterBar.onMonsterLocated += onMonsterLocated;
		monsterBar.onMonsterDrag += onMonsterDrag;

		monsterBar.Init (true);
		if (lastMonsterIndex > -1) {
			monsterBar.CurrentMonsterIndex = lastMonsterIndex;
		}
		updateButtons ();
	}


	public void Done() {
		if (selected) {
			return;
		}
		selected = true;
		monsterBar.Select ();

		Invoke ("GotoMiniGame", 1f);

		if(ButtonNext != null) ButtonNext.SetActive (false);
		if(ButtonPrevious != null) ButtonPrevious.SetActive (false);

		StatusBubble.SetActive (false);
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
		isDraged = true;
		LastX = convertMousePosition().x;

		monsterBar.OnBeginDrag();
	}

	public void OnDrag(PointerEventData eventData)
	{
		float currX = convertMousePosition().x;

		float moveX = currX - LastX;
		monsterBar.DragBy (moveX);

		LastX = currX;
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		isDraged = false;
		monsterBar.OnEndDrag ();
	}


	Vector2 convertMousePosition()
	{
		return Camera.main.ScreenToWorldPoint(Input.mousePosition);
	}



	int lastMonsterIndex = -1;

	void GotoMiniGame() {
		MiniGameController.Instance.StartRandomGame (currentMonster);
		lastMonsterIndex = monsterBar.CurrentMonsterIndex;
		// UIController.Instance.ShowPanelWithoutTransitionEffect (UIController.Instance.GamePanel);
	}





	void onMonsterDrag(Monster monster)
	{
		currentMonster = null;
		StatusBubble.SetActive (false);
	}


	Monster currentMonster;
	void onMonsterLocated(Monster monster)
	{
		currentMonster = monster;
		showStatusIcon (monster);
	}


	public void showStatusIcon(Monster monster)
	{
		switch (monster.EmotionType) {

		case MonsterEmotionTypes.Happy:
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
		case MonsterEmotionTypes.Hungry:
			StatusBubble.SetActive (true);
			StatusIcon.sprite = Icon_Hungry;
			break;
		case MonsterEmotionTypes.Afraid:
			StatusBubble.SetActive (true);
			StatusIcon.sprite = Icon_Afraid;
			break;
		}
	}

	public void ShowEndGamePanel()
	{
		if(PanelEndGame != null) {
			PanelEndGame.SetActive (true);
		}
	}


	MonsterType CenterMonsterType;
	public void setCurrentMonster (MonsterType monsterType)
	{
		CenterMonsterType = monsterType;
	}


}
