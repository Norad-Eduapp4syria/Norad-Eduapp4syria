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

	public MonsterSelectionTouchController TouchController;


	bool selected = false;
	bool isDraged = false;

	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Escape)) {
			UIController.Instance.MapClick ();
		}

/*
		if(timer >= 0)
			timer += Time.deltaTime;
		
		if (Input.GetMouseButtonDown (0)) {
			print (Input.mousePosition.y);
			if (Input.mousePosition.y < 500) {
				lastX = Input.mousePosition.x;
				timer = 0;
			} 
		}
		if (Input.GetMouseButtonUp (0)) {
			if (Mathf.Abs (lastX - Input.mousePosition.x) < 1 && 0 <= timer && timer <= 1)
				Done ();
			timer = -1;
		}*/
	}


	void OnEnable(){
		GameplayController.Instance.LoadBackground ();

		monsterBar.ButtonPrevious = ButtonPrevious.GetComponent<Button> ();
		monsterBar.ButtonNext = ButtonNext.GetComponent<Button> ();

		monsterBar.Init ();
		monsterBar.onMonsterLocated += onMonsterLocated;
//		monsterBar.onMonsterDrag += onMonsterDrag;



		updateButtons ();
		AudioController.Instance.PlaySound (InstructionSound);

		//Jonathan
		if (GameplayController.Instance.CurrentLevelIndex == 0) {

			GameObject go;
			Vector2 point = new Vector2(0, -140);
			go = GameObject.Find ("Button - Ok");
			if (go != null) {
				point = go.transform.localPosition + new Vector3 (0, 100, 0);
			} else {
			
			}
			TutorialController.Instance.PointAt (point);
		}
		//End Jonathan


		if (TouchController != null) {
			TouchController.onBeginDrag += OnBeginDrag;
			TouchController.onDrag += OnDrag;
			TouchController.onEndDrag += OnEndDrag;
			TouchController.onPointerClick += OnPointerClick;
		}

		Analitics.Instance.treckScreen ("Monster Select");
	}

	public void Done(){
		if (selected)
			return;
		selected = true;
		monsterBar.Select ();

		Invoke ("GotoGame", 1f);
		GetComponent<UIPopupPanel> ().PopOut ();
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



	float LastX;

//	public void OnBeginDrag(PointerEventData eventData) 
	public void OnBeginDrag() 
	{
/*
		isDraged = true;
		LastX = convertMousePosition().x;
		monsterBar.OnBeginDrag();
*/
		Invoke ("setDrag", 0.025f);
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
		Analitics.Instance.treckEvent (AnaliticsCategory.GamePlay, AnaliticsAction.SelectMonster, monster.name, (long)monster.MonsterType);
	}


}
