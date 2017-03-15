using UnityEngine;
using System.Collections;

public class UIGamePanelController : MonoBehaviour {


	void Awake() {

	}



	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable(){
		Screen.sleepTimeout = SleepTimeout.NeverSleep;
		if (GameplayController.Instance != null) {
			GameplayController.Instance.LoadLevel (GameplayController.Instance.CurrentLevelIndex);
		}
	}

	void OnDisable()
	{
		Screen.sleepTimeout = SleepTimeout.SystemSetting;
		GameplayController.Instance.ClearGameplay ();


	}

}
