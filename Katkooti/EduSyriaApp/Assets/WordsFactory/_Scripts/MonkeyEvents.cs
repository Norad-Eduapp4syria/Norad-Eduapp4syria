using UnityEngine;
using System.Collections;

public class MonkeyEvents : MonoBehaviour {

	GameObject temp;
	// Use this for initialization
	void Start () {
	
	}
	
	public void Fetch()
	{
	 	temp = GameObject.FindGameObjectWithTag ("Selected");
		temp.tag = "Letter";
		temp.GetComponent<TapLetter> ().movetomonkeyhand = true;
	}

	public void Throw()
	{ 
		temp.GetComponent<TapLetter> ().movetomonkeyhand = false;
		temp.GetComponent<TapLetter> ().movetobucket = true;

	}
		
}
