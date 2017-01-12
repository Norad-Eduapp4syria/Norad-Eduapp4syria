using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;
using System.Collections;

public class CountTo10Letter : MonoBehaviour
,IBeginDragHandler, IDragHandler, IEndDragHandler, IDropHandler
{
	public string value;

	public Vector3 InitPosition;
	public Vector3 NewPos;

	bool isDragable = false;

	public AudioClip SoundAppear;
	public AudioClip SoundSelected;
	public AudioClip SoundUnselected;

	int currentLocation;

	bool isGoToMouth = false;
	float mTimeFromLaunch;
	float Speed = 20000;

	// Use this for initialization
	void Start ()
	{
		Text text = gameObject.GetComponentInChildren<Text> ();
//		text.text = ArabicSupport.ArabicFixer.Fix(value, true, false);
//		text.text = RTL.Fix(value);
		text.text = value;

		text.enabled = true;
		InitPosition = transform.position;
	}

	// Update is called once per frame
	void Update () {


		if (isGoToMouth) {

			Vector3 toPos = getMonsterMouth ();

			transform.position = Vector3.MoveTowards (transform.position, toPos,	Time.deltaTime * Speed * (Time.time - mTimeFromLaunch));
			//			transform.localPosition =  Vector3.MoveTowards (transform.localPosition,	-Vector3.up * 300, 	Time.deltaTime  * Speed * 0.025f - (Time.time - mTimeFromLaunch));

			if (Vector3.Distance (transform.position, toPos) < 5f) {
				CountTo10Game.Instance.ApproveDigit (this);
			}
		} else if (!isDragable) {
			transform.position = Vector3.MoveTowards (transform.position, NewPos, Time.deltaTime * 1000);
		}
	}

	public void Rollback() {
		NewPos = InitPosition;
	}


	void moveToMouse()
	{
		Vector2 WorldObject_ScreenPosition;

		Canvas c = GetComponentInParent<Canvas> ();
		RectTransform CanvasRect = c.GetComponent<RectTransform> ();

		Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Input.mousePosition);

		WorldObject_ScreenPosition = new Vector2 (
			((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
			((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
		);
		transform.position = WorldObject_ScreenPosition;
		NewPos = transform.position;
	}

	public void OnEnable() {

		isGoToMouth = false;

		AudioController.Instance.PlaySound (SoundAppear);
		currentLocation = Random.Range (0, CountTo10Game.Instance.LettersLocations.Length);
		transform.position = CountTo10Game.Instance.LettersLocations [currentLocation].transform.position; //getLocationBySpawnId (LettersLocations).transform.position;
		NewPos = InitPosition = transform.position;
	}

	public void OnBeginDrag(PointerEventData eventData) 
	{
		isDragable = true;
		AudioController.Instance.PlaySound (SoundSelected);
		CountTo10Game.Instance.onStartDragLetter ();
		moveToMouse ();
//		GameplayController.Instance.onBeginDragLetter (this);
	}

	public void OnDrag(PointerEventData eventData)
	{
		if (isDragable == true) {
			moveToMouse ();
//			CountTo10Game.Instance.onDragLetter (this);
		}
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		if (isDragable == true) {
			isDragable = false;
			AudioController.Instance.PlaySound (SoundUnselected);
			NewPos = InitPosition;
			CountTo10Game.Instance.onEndDragLetter (this);
		}
	}

	public void OnDrop(PointerEventData eventData)
	{
		if (isDragable == true) {
			//			Debug.Log ("drop");
		}
	}


	public void gotoMouth()
	{

		mTimeFromLaunch = Time.time;
		isGoToMouth = true;

	}




	public Vector2 getMonsterMouth()
	{
		Transform to = GameObject.Find ("monster").transform.Find ("Mouth");
		Vector2 toPos;
		toPos = new Vector2 (to.position.x * 100f, to.position.y * 100f);

		Canvas c = GetComponentInParent<Canvas> ();
		RectTransform CanvasRect = c.GetComponent<RectTransform> ();
		Vector2 ViewportPosition = Camera.main.ScreenToViewportPoint (Camera.main.WorldToScreenPoint(to.position));

		toPos = new Vector2 (
			((ViewportPosition.x * CanvasRect.sizeDelta.x) - (CanvasRect.sizeDelta.x * 0.5f)),
			((ViewportPosition.y * CanvasRect.sizeDelta.y) - (CanvasRect.sizeDelta.y * 0.5f))
		);

		return toPos;
	}


}
