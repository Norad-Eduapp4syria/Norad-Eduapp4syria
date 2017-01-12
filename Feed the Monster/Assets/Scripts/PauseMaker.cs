using UnityEngine;
using System.Collections;

public class PauseMaker : MonoBehaviour {

	// Use this for initialization
	void Awake () {
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		//GameplayController.Instance.IsPause = true;
		GameplayController.Instance.IsPausePopup = true;
	}

	void OnDisable()
	{
//		GameplayController.Instance.IsPause = false;
		GameplayController.Instance.IsPausePopup = false;
	}
}
