using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class MonsterPettingZone : MonoBehaviour,
IBeginDragHandler, IDragHandler, IEndDragHandler {

	private bool isPetting = false;

	public float pettingValue = 1;


	Vector3 StartTouch;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {

	}

	void OnEnable() {
		isPetting = false;
	}

	public void OnBeginDrag(PointerEventData eventData)
	{
		StartTouch = Input.mousePosition;
		isPetting = true;
	}
	public void OnDrag(PointerEventData eventData)
	{
		if (isPetting == true && !Vector3.Equals(StartTouch, Vector3.zero)) {
			float diff = Mathf.Abs (Vector3.Distance (StartTouch, Input.mousePosition));

			if (diff > 50f) {
				OnEndDrag (null);
				GetComponentInParent<MonsterPettingGame> ().StartPetting();
//				Debug.Log (diff.ToString() + " - I m happy");
			} else {
//				Debug.Log (diff.ToString() + " - I m sad");
			}
		}
	}

	public void OnEndDrag(PointerEventData eventData)
	{
		StartTouch = Vector3.zero;
		isPetting = false;
	}

	public bool IsInObject (PointerEventData eventData) {
		return RectTransformUtility.RectangleContainsScreenPoint ((RectTransform)transform, eventData.position, GameplayController.Instance.canvasCamera);
	}
}
