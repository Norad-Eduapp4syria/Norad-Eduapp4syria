using UnityEngine;
using System.Collections;

public class MapComponentActivate : MonoBehaviour {

	// Use this for initialization
	public GameManager.GameSate ActiveState;
	public GameObject target;
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (GameManager.Instance.getCurrentGameState () == ActiveState) {
			target.gameObject.SetActive (true);
		} else {
			target.gameObject.SetActive (false);
		}
	}
}
