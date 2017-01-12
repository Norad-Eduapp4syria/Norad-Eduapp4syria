using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class DebugController : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	public void ChangeSegment(int segmentIndex)
	{
		//GameplayController.Instance.LoadSegment (segmentIndex);
	}

	void OnEnable() {
		Application.logMessageReceived += HandleLog;
	}
	void OnDisable() {
		Application.logMessageReceived -= HandleLog;
	}
	void HandleLog(string logString, string stackTrace, LogType type) {
		GameObject newLog = Instantiate(GameObject.Find("Text Log Prefab"));
		newLog.transform.SetParent (GameObject.Find ("Text Log Prefab").transform.parent);
		newLog.GetComponent<Text> ().text = logString;
		Destroy (newLog, 20);
	}
}
