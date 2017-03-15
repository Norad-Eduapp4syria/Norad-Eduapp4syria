using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using UnityEngine.EventSystems;

public class InteractiveButton : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler, IPointerUpHandler, IPointerDownHandler, IPointerClickHandler {


	Button btn;

	// Use this for initialization
	void Start () {
		btn = gameObject.GetComponent<Button> ();
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	#region IPointerEnterHandler implementation
	public delegate void PointerEventDataDelegate(PointerEventData eventData);
	public event PointerEventDataDelegate onPointerEnter;
	public void OnPointerEnter (PointerEventData eventData)
	{
	}

	#endregion

	#region IPointerDownHandler implementation
	public event PointerEventDataDelegate onPointerDown;
	public void OnPointerDown (PointerEventData eventData)
	{
		if (btn.interactable) {
			transform.localScale = new Vector3 (.9f, .9f, .9f);
		}
	}

	#endregion

	#region IPointerExitHandler implementation
	public event PointerEventDataDelegate onPointerExit;
	public void OnPointerExit (PointerEventData eventData)
	{
		
	}

	#endregion

	#region IPointerUpHandler implementation
	public event PointerEventDataDelegate onPointerUp;
	public void OnPointerUp (PointerEventData eventData)
	{
		transform.localScale = new Vector3 (1f, 1f, 1f);
	}

	#endregion

	#region IPointerClickHandler implementation

	public void OnPointerClick (PointerEventData eventData)
	{
		if (btn.IsInteractable()) {
			AudioController.Instance.PlaySound (UIController.Instance.ClickSound);
		}
	}

	#endregion

}
