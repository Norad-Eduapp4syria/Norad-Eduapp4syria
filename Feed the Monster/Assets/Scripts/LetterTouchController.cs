using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;

public class LetterTouchController : MonoBehaviour
,IPointerDownHandler, IPointerEnterHandler
,IBeginDragHandler, IDragHandler, IEndDragHandler, IDropHandler
{
	LetterController letterController
	{
		get { 
			return gameObject.GetComponentInChildren<LetterController> ();
		}

	}

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}



	public void OnPointerDown (PointerEventData eventData)
	{
		letterController.OnPointerDown (eventData);
	}


	public void OnPointerEnter (PointerEventData eventData)
	{
		letterController.OnPointerEnter (eventData);
	}


	public void OnBeginDrag(PointerEventData eventData) 
	{
		letterController.OnBeginDrag (eventData);
	}

	public void OnDrag(PointerEventData eventData)
	{
		letterController.OnDrag (eventData);
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		letterController.OnEndDrag (eventData);
	}

	public void OnDrop(PointerEventData eventData)
	{
		letterController.OnDrop (eventData);

	}


}
