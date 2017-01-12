using UnityEngine;
using System.Collections;

public class OnDisableChildDisabler : MonoBehaviour {
	public GameObject [] childToDisable;
	void OnDisable(){
		foreach (GameObject g in childToDisable) {
			g.SetActive (false);
		}
	}
}
