using UnityEngine;
using System.Collections;
using System;

public class ActivityTransitionFinished : MonoBehaviour {

    public Action OnTransitionAreaShown;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

    public void ActivityShowEvent()
    {
        OnTransitionAreaShown.Raise();
    }
}
