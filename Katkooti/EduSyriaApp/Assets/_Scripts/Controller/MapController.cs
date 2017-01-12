using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class MapController : MonoBehaviour {


	public float CurrentPositionYValue,TargetPositionYValue, YOffset,MovementFactor;
	// Use this for initialization
	public Button [] Buttons;

	void Awake()
	{
	//	CurrentPositionYValue = this.transform.GetComponent<RectTransform>().anchoredPosition.y;
//		Debug.Log (CurrentPositionYValue );
	}

	void Start () {
		//NextPosition ();
	}

	public void  NextPosition()
	{
		Debug.Log (CurrentPositionYValue);
		Debug.Log (TargetPositionYValue);
	//	TargetPositionYValue = CurrentPositionYValue - YOffset;

	}
	// Update is called once per frame
	void Update () {

//		//Debug.Log (TargetPositionYValue);
//		if (this.transform.GetComponent<RectTransform>().anchoredPosition.y <= TargetPositionYValue) {
//			Sprite pressed = Buttons [(int)(GameManager.Instance.getCurrentGameState())].spriteState.disabledSprite;
//			Buttons [(int)(GameManager.Instance.getCurrentGameState())].gameObject.GetComponent<Image> ().sprite = pressed;
//			CurrentPositionYValue =  this.transform.GetComponent<RectTransform>().anchoredPosition.y;;
//		} else {
//			this.transform.GetComponent<RectTransform>().Translate (Vector3.down * MovementFactor * Time.deltaTime) ;
//		}
	
	}







}
