using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;

public class MiniGameBubble : MonoBehaviour
,IPointerClickHandler
{

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}


	public void OnPointerClick (PointerEventData eventData)
	{
		if (! UIMiniGame.Instance.IsDraged) {
			UIMiniGame.Instance.Done ();
//			Debug.Log ("OnPointerClick");
		}
	}

}
