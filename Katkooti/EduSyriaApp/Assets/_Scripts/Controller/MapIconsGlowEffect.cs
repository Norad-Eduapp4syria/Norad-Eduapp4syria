using UnityEngine;
using System.Collections;

public class MapIconsGlowEffect : MonoBehaviour {

	public GameObject Target,Icons,ScrollablePanel;
	public GameManager.GameSate TargetState;
	public float yMinValue;
	public float yMaxValue;
	public bool isLastPos = false;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		//Debug.Log (GameManager.Instance.getCurrentGameState ());
		if (GameManager.Instance.getCurrentGameState ()  == TargetState) {

			Target.SetActive (true);
		} else {
			Target.SetActive (false);
		}
		if (!isLastPos) {
			if (ScrollablePanel.GetComponent<RectTransform> ().localPosition.y >= yMinValue && ScrollablePanel.GetComponent<RectTransform> ().localPosition.y <= yMaxValue) {
				Icons.SetActive (true);
			} else {
				Icons.SetActive (false);
			}
		}

		else if (isLastPos) {
			if (ScrollablePanel.GetComponent<RectTransform> ().localPosition.y < yMinValue) {
				Icons.SetActive (true);
			}
			else {
				Icons.SetActive (false);
			}
		}
		
		
		

	
	}
}
