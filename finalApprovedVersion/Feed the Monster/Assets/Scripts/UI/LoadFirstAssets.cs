using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoadFirstAssets : MonoBehaviour {

	public GameObject baseBackground;


	// Use this for initialization
	void Start () {
		Monster[] monsters = UsersController.Instance.userData().getCollectedMonsters;
//		GameObject go = Resources.Load ("Gameplay/Background/BG_2") as GameObject;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
