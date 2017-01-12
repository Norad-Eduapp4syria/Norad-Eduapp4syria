using UnityEngine;
using System.Collections;

public class UIScreenTransitionEffect : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}

	// function start() { }
	// Update is called once per frame
	void Update () {
	}



	public void ChangeScreen(){
		UIController.Instance.Transition ();
	}

	public void End(){
		gameObject.SetActive (false);
	}
}
