using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class MonsterBar : MonoBehaviour {

	public static MonsterBar Instance;

	public delegate void onMonsterChangeDelegate(Monster monster);
	public onMonsterChangeDelegate onMonsterLocated;
	public onMonsterChangeDelegate onMonsterDrag;

	[HideInInspector]
	public int NumMonsters;

	public Button ButtonPrevious;
	public Button ButtonNext;

	public Slider MonsterGageSlider;
	public Image Icon_gage_1;
	public Image Icon_gage_2;
	public Image Icon_gage_3;


	public MonsterDressingBar DressingBar;

	[HideInInspector]
	public Transform Content;

	float spacing;
	//int currentIndex = 0;

	Transform selectedMonster = null;

	float toX = 0;
	bool isDrag = false;
	bool isLocated = true;
	bool isTouchAllow = false;

	public void JumpToMonsterIndex(int newIndex)
	{
		currentMonsterIndex = newIndex;
		Invoke("jumpToNewPosition", 0.001f);
	}

	public int currentMonsterIndex
	{
		get {
			return UsersController.Instance.userData().getLastMonsterIndex ();
//			return currentIndex;
		}

		set { 
			UsersController.Instance.userData().setLastMonsterIndex (value);
//			currentIndex = value;
		}
	}

	public Transform currentMonster
	{
		get { 
			try {
				return Content.GetChild (currentMonsterIndex);
			} catch {
				return null;
			}
		}
	}

	void jumpToNewPosition()
	{
		Transform t = Content.GetChild (currentMonsterIndex);
		toX = Content.transform.position.x - t.position.x;

		Vector2 newPos = new Vector2 (toX, Content.position.y);
		Content.position = newPos;

		isDrag = false;
		updateButtons (false);
	}


	void Awake()
	{
		Instance = this;
	}

	// Use this for initialization
	void Start () {
		Content = transform.GetChild (0);
//		startPos = Content.position;
		if (GameAssets.Instance.ForceMonster == MonsterType.NONE) {
			Init ();
		}
	}


	// Update is called once per frame
	void Update () {

		if (selectedMonster != null) {
			if (isLocated == false) {
				selectedMonster.localScale = Vector3.Lerp (selectedMonster.localScale, transform.localScale, Time.deltaTime * 5);
//				selectedMonster.position = Vector3.Lerp (selectedMonster.position, transform.position, Time.deltaTime * 5);
				if (!IsMiniGame) {
					selectedMonster.position = Vector3.Lerp (selectedMonster.position, selectedMonster.GetComponent<MonsterPosition> ().GameScreen, Time.deltaTime * 5);
				}

				float dis1 = Vector2.Distance (selectedMonster.localScale, transform.localScale);
				if (IsMiniGame) {
					if (dis1 < 0.001f) {
						isLocated = true;
						selectedMonster = null;
					}
				} else {
					float dis2 = Vector2.Distance (selectedMonster.position, selectedMonster.GetComponent<MonsterPosition> ().GameScreen);

					if (dis1 < 0.001f && dis2 < 0.001f) {
						isLocated = true;
						selectedMonster = null;
					}
				}
			}
			return;
		} else if (Content.childCount == 0) {
			return;
		}

		if (isDrag == false && Content.transform.position.x != toX) {
			Vector2 newPos = new Vector2 (toX, Content.position.y);
			Content.position = Vector3.MoveTowards (Content.position, newPos, Time.deltaTime * 20);
			float dis = Vector2.Distance (Content.position, newPos);
			if (dis < 0.001f) {
				Content.position = newPos;

				if (isLocatedCalled == false) {
					isLocatedCalled = true;
					callMonsterLocatedDelegate ();
				}
			}
		}
	}

	bool isLocatedCalled = false;

	[HideInInspector]
	public bool IsMiniGame = false;


	void Init()
	{
//		IsMiniGame = isMiniGame;
		selectedMonster = null;
		isLocated = true;
		isTouchAllow = true;
//		currentIndex = 0;

		Destroy (GameObject.Find ("monster"));

		Clean ();

		hideGageIcons ();

		//spacing = Screen.width * 1.45f;
		spacing = Screen.width * 2.0f;
		spacing = Camera.main.ScreenToWorldPoint(new Vector3(spacing,0,0)).x;

		var friends = UsersController.Instance.userData().getCollectedMonsters;

		int numReady = 0;
		if (DressingBar != null) {
			DressingBar.clean ();
			DressingBar.gameObject.SetActive (IsMiniGame);
		}

		for (int monsterIndex = 0; monsterIndex < friends.Length; monsterIndex++) {
			Monster monster = friends [monsterIndex];
			if (monster != null) {
				//GameObject newMonster = Instantiate (protoMonster, new Vector3 (), Quaternion.identity) as GameObject;
				GameObject newMonster = Instantiate (monster.currentPlayGO, new Vector3 (), Quaternion.identity) as GameObject;

				newMonster.transform.parent = Content;

				if (IsMiniGame) {
					newMonster.GetComponent<MonsterPosition> ().setMiniGamePosition ();
					if (DressingBar != null) {
						StartCoroutine (DressingBar.addMonster (monster, new Vector3 (spacing * numReady, 0, 0)));
					}

				} else {
					newMonster.GetComponent<MonsterPosition> ().setGamePosition ();
				}

				newMonster.transform.localPosition += new Vector3 (spacing * numReady, 0, 0);

				newMonster.transform.localScale = new Vector3 (.8f, .8f, .8f);
				newMonster.AddComponent<MonsterSpritesController> ().monster = monster;

				updateMonsterEmotion (IsMiniGame, newMonster, monster);

				numReady++;

				if (GameAssets.Instance.DefaultMonster != MonsterType.NONE && GameAssets.Instance.DefaultMonster == monster.MonsterType) {
					GameAssets.Instance.DefaultMonster = MonsterType.NONE;
					currentMonsterIndex = monsterIndex;
				}

			}
		}
		NumMonsters = numReady;
		callMonsterLocatedDelegate();


		Invoke("jumpToNewPosition", 0.01f);
		Invoke("showCurrentMonsterItems", 0.1f);

//		Invoke("updateButtons", 0.011f);
	}

	void updateMonsterEmotion (bool isMiniGame, GameObject monsterGO, Monster monster)
	{
		Animator animController = null;
		if (monsterGO) {
			var obj = monsterGO.GetComponentInChildren<MonsterAnimation> ();
			if (obj != null) {
				animController = obj.gameObject.GetComponent<Animator> ();
			}

			if (animController != null) {
				if (isMiniGame == false) {
					animController.SetBool ("IsMiniGame", false);
					animController.SetBool ("IsSad", false);
				} else {
					animController.SetBool ("IsMiniGame", true);

					if (monster.EmotionType == MonsterEmotionTypes.Happy || monster.EmotionType == MonsterEmotionTypes.NONE || monster.IsReady == false) {
						animController.SetBool ("IsSad", false);
					} else {
						animController.SetBool ("IsSad", true);
					}
				}
			}
		}
	}


	public void Select() {
		selectedMonster = Content.GetChild (currentMonsterIndex);
		selectedMonster.transform.parent = null;
		for (int i = 0; i < Content.childCount; i++) {
			Destroy (Content.GetChild (i).gameObject);
		}
		selectedMonster.gameObject.name = "monster";
		isLocated = false;
		isTouchAllow = false;
		//selectedMonster.gameObject.tag = "CurrentMonster";
	}


	public void Clean() {
		if (Content == null) {
			return;
		}
		for (int i = 0; i < Content.childCount; i++) {
			Destroy (Content.GetChild (i).gameObject);
		}
	}

	public void MoveToPrevious()
	{
		if(currentMonsterIndex - 1 >= 0)
		{
			callMonsterDragDelegate ();

			currentMonsterIndex--;

			setNewIndexPosition ();
		}
		isLocatedCalled = false;
	}

	public void MoveToNext()
	{
		if(currentMonsterIndex + 1 < Content.childCount)
		{
			callMonsterDragDelegate ();
			currentMonsterIndex++;
			setNewIndexPosition ();
		}
		isLocatedCalled = false;
	}

	void setNewIndexPosition()
	{
		Transform t = Content.GetChild (currentMonsterIndex);
		toX = Content.transform.position.x - t.position.x;
		isDrag = false;
		updateButtons (false);
	}

	public void updateButtons(bool immediately )
	{

		if (immediately == true) {
			updateButtons ();
		} else {
			Invoke ("updateButtons", 0.05f);
		}
	}

	public void updateButtons()
	{
		if (ButtonNext != null) {
			if (currentMonsterIndex < (Content.childCount - 1)) {
				ButtonNext.interactable = true;
			} else {
				ButtonNext.interactable = false;
			}

/*
			if (currentIndex == 0) {
				ButtonNext.interactable  = true;	
			} else {
				ButtonNext.interactable  = false;	
			}
*/
		}

		if (ButtonPrevious != null) {

			if (currentMonsterIndex > 0) {
				ButtonPrevious.interactable  = true;
			} else {
				ButtonPrevious.interactable  = false;
			}
/*
			if (currentIndex == Content.childCount - 1) {
				ButtonPrevious.interactable  = true;
			} else {
				ButtonPrevious.interactable  = false;
			}
*/
		}
		updateMonsterSlider ();
	}

	void updateMonsterSlider()
	{
		if (MonsterGageSlider != null) {
			Monster monster = getCurrentMonster();

			if (monster != null) {
		
				if (monster.IsReady) {
					MonsterGageSlider.gameObject.SetActive (false);
				} else {
					MonsterGageSlider.gameObject.SetActive (true);
					MonsterGageSlider.value = (monster.GageValue > 98f ) ? 98f : monster.GageValue;
					UpdateGageSprite (monster);
				}
			} else {
				MonsterGageSlider.gameObject.SetActive (false);
			}
		}
	}



	public Monster getCurrentMonster()
	{
		Monster monster = null;
		try {
			monster = Content.GetChild (currentMonsterIndex).GetComponent<MonsterSpritesController> ().monster;
		} catch {
			monster = null;
		}
		return monster;
	}


	public void DragBy(float moveX)
	{
		Vector2 newPos = new Vector2 (Content.transform.position.x + moveX, Content.transform.position.y);

		Content.transform.position = newPos;
	}

	public void OnBeginDrag()
	{
		if (isTouchAllow) {
			isDrag = true;
			isLocatedCalled = false;
			callMonsterDragDelegate ();
		}

	}

	public void OnEndDrag()
	{
		if (isTouchAllow) {

			isDrag = false;

			float minDistance = float.MaxValue;
			int minIndex = 0;
			for (int i = 0; i < Content.childCount; i++) {
				float dist = Vector3.Distance (Content.GetChild (i).transform.position, transform.position);

				if (i == currentMonsterIndex) {
					dist = dist * 1.5f;
				}

//				if (i != currentIndex && (minDistance == float.MaxValue || dist < minDistance)) {
				if (minDistance == float.MaxValue || dist < minDistance) {
					minDistance = dist;
					minIndex = i;
				}
			}

			float currDist = Vector3.Distance (Content.GetChild (currentMonsterIndex).transform.position, transform.position);

			if (minDistance < currDist * 4.0f) {

				Transform t = Content.GetChild (minIndex);
				toX = Content.transform.position.x - t.position.x;

				currentMonsterIndex = minIndex;

				updateButtons (false);
			}
		}
	}

	public void addBackMonster(GameObject newMonster)
	{
		newMonster.transform.parent = Content;
		newMonster.GetComponent<MonsterPosition> ().setGamePosition ();

//		newMonster.transform.localPosition += new Vector3 (spacing * numReady, 0, 0);
//		newMonster.transform.localScale = new Vector3 (.8f, .8f, .8f);
	}

	void hideGageIcons ()
	{
		if (Icon_gage_1) {
			Icon_gage_1.gameObject.SetActive (false);
		}
		if (Icon_gage_2) {
			Icon_gage_2.gameObject.SetActive (false);
		}
		if (Icon_gage_3) {
			Icon_gage_3.gameObject.SetActive (false);
		}
	}

	void UpdateGageSprite(Monster monster)
	{
		hideGageIcons ();
		if (monster.Gage == 0) {
			Icon_gage_1.gameObject.SetActive (true);
		} else if (monster.Gage == 1) {
			Icon_gage_2.gameObject.SetActive (true);
		} else if (monster.Gage == 2) {
			Icon_gage_3.gameObject.SetActive (true);
		}

	}


	void callMonsterDragDelegate () {
		if (onMonsterDrag != null) {
			onMonsterDrag (null);
		}
		if (DressingBar != null) {
			DressingBar.hideAllItems ();
		}
	}


	void callMonsterLocatedDelegate () {
		Monster m = getCurrentMonster();
		if (m != null) {
			if (onMonsterLocated != null) {
				onMonsterLocated (m);
			}
			showCurrentMonsterItems (m.MonsterType);
		}
	}

	public void showCurrentMonsterItems () {

		if (Content.childCount > currentMonsterIndex) {
			Transform t = Content.GetChild (currentMonsterIndex);
			if (t != null) {
				Monster m = t.GetComponent<MonsterSpritesController> ().monster;
				if (m != null) {
					showCurrentMonsterItems (m.MonsterType);
				}
			}
		}
	}

	void showCurrentMonsterItems (MonsterType type) {
		if (DressingBar != null) {
			DressingBar.showCurrentMonsterItems (type);
		}
	}


}
