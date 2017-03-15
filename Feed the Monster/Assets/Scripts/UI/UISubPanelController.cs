using UnityEngine;
using System.Collections;

public class UISubPanelController : MonoBehaviour {
	public GameObject[] SubPanels;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
		foreach (GameObject sub in SubPanels) {
			sub.SetActive (true);
		}
	}

	void OnDisable()
	{
		foreach (GameObject sub in SubPanels) {
			sub.SetActive (false);
		}
	}
}
