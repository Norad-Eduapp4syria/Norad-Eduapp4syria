using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VoiceTutorialEvent : MonoBehaviour {
	

	public delegate void EventDelegate();
	public EventDelegate onOut;
	public EventDelegate onIn;

	public void OnTutorialOut()
	{
		if (onOut != null) {
			onOut ();
		}
	}

	public void OnTutorialIn()
	{
		if (onIn != null) {
			onIn ();
		}

	}

}
