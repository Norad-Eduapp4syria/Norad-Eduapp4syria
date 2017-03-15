using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MonsterPettingZone : MonoBehaviour,
IBeginDragHandler, IDragHandler, IEndDragHandler,
IPointerDownHandler, IPointerUpHandler
{

	public enum TutorialType {
		None,
		Swipe,
		Tap,
	}


	public bool isTapEnable;
	public int tapValue = 1;

	public bool isSwipeEnable;
	public int swipeValue = 1;

	public TutorialType tutorialType = TutorialType.Swipe;


	[HideInInspector]
	public bool isTutorial = false;


//	bool isTap;
	bool isSwipe;




	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

	}

	void OnEnable() {
		isSwipe = false;
		isTutorial = false;
	}

	void OnDisable() {
		CancelInvoke ();
	}

	public void OnPointerDown (PointerEventData data)
	{
		if (!isTapEnable) {
			return;
		}
	}

	public void OnPointerUp (PointerEventData data)
	{
		if (!isTapEnable) {
			return;
		}
		if (!isSwipe) {
			MonsterPettingGame.Instance.SetEmotion (this, tapValue);
			Invoke ("StopSwipe", 0.2f);

			if (isTutorial) {
				TutorialController.Instance.EndTutorial ();
				isTutorial = false;
			}
		}
	}

	public void StopSwipe()
	{
		MonsterPettingGame.Instance.SetEmotion (this, 0);
	}

	public void OnBeginDrag(PointerEventData eventData)
	{

	}

	public void OnDrag(PointerEventData eventData)
	{
		if (isSwipe) {
			return;
		}

		if (isSwipeEnable) {
			isSwipe = true;
			MonsterPettingGame.Instance.SetEmotion (this, swipeValue);
			if (isTutorial) {
				TutorialController.Instance.EndTutorial ();
				isTutorial = false;
			}
		}
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		if (isSwipe) {
			if (isSwipeEnable) {
				StopSwipe ();
			}
			isSwipe = false;
		}
	}

	public void startTutorial()
	{
		isTutorial = true;


		if (tutorialType == TutorialType.Swipe) {
			TutorialController.Instance.StartTutorial (gameObject);
		} else if (tutorialType == TutorialType.Tap) {
			TutorialController.Instance.PointAt (transform.localPosition, transform.parent, true);
		}
	}

/*
	public bool IsInObject (PointerEventData eventData) {
		return RectTransformUtility.RectangleContainsScreenPoint ((RectTransform)transform, eventData.position, GameplayController.Instance.canvasCamera);
	}
*/
}
