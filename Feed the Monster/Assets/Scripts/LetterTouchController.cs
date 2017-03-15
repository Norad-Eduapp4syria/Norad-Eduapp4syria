using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;

public class LetterTouchController : MonoBehaviour
,IPointerDownHandler, IPointerEnterHandler
,IBeginDragHandler, IDragHandler, IEndDragHandler, IDropHandler
{
	bool isDragBegin;
	bool isPointerDown;


	LetterController _letterController;

	LetterController letterController
	{
		get { 
			if (_letterController == null) {
				_letterController = gameObject.GetComponentInChildren<LetterController> ();
			}
			return _letterController;
		}
	}


	public void OnPointerDown (PointerEventData eventData)
	{
		isPointerDown = true;

		letterController.OnPointerDown (eventData);
		letterController.OnBeginDrag (eventData);
	}


	public void OnPointerEnter (PointerEventData eventData)
	{
//		letterController.OnPointerEnter (eventData);

		if (!isDragBegin && isPointerDown) {
			letterController.OnDrag (eventData);
		}
	}


	public void OnBeginDrag(PointerEventData eventData) 
	{
		isDragBegin = true;
//		letterController.OnBeginDrag (eventData);
	}

	public void OnDrag(PointerEventData eventData)
	{
		letterController.OnDrag (eventData);
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		isDragBegin = false;
		isPointerDown = false;
		letterController.OnEndDrag (eventData);
	}

	public void OnDrop(PointerEventData eventData)
	{
		letterController.OnDrop (eventData);
	}


}
