using UnityEngine;
using System.Collections;
using UnityEngine.EventSystems;

public class HoleButtonController : MonoBehaviour,IPointerEnterHandler, IPointerExitHandler, IPointerUpHandler, IPointerDownHandler, IPointerClickHandler {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	#region IPointerEnterHandler implementation
	public delegate void PointerEventDataDelegate(PointerEventData eventData);
	public event PointerEventDataDelegate onPointerEnter;
	public void OnPointerEnter (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable)
			return;
		
		if (Input.GetMouseButton (0)) {
			Debug.Log ("OnPointerEnter");
			if (onPointerEnter != null)
				onPointerEnter (eventData);
		}
	}

	#endregion

	#region IPointerDownHandler implementation
	public event PointerEventDataDelegate onPointerDown;
	public void OnPointerDown (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable)
			return;
		
		if (Input.GetMouseButton (0)) {
			if (onPointerDown != null)
				onPointerDown (eventData);
		}
	}

	#endregion

	#region IPointerExitHandler implementation
	public event PointerEventDataDelegate onPointerExit;
	public void OnPointerExit (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable)
			return;
		
		if (!Input.GetMouseButtonUp (0)) {
			if (onPointerExit != null)
				onPointerExit (eventData);
		}
	}

	#endregion

	#region IPointerUpHandler implementation
	public event PointerEventDataDelegate onPointerUp;
	public void OnPointerUp (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable)
			return;
		
		if (onPointerUp != null)
			onPointerUp (eventData);
	}

	#endregion

	#region IPointerClickHandler implementation
	public event PointerEventDataDelegate onPointerClick;
	public void OnPointerClick (PointerEventData eventData)
	{
		if (!GameplayController.Instance.IsInteractable)
			return;

		if (onPointerClick != null)
			onPointerClick (eventData);	
	}
	#endregion
}
