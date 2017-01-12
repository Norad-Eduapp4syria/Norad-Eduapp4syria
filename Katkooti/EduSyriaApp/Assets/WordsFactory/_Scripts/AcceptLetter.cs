using UnityEngine;
using System.Collections;

public class AcceptLetter : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	void OnTriggerEnter2D(Collider2D other)
	{
		//UIManager.Instance.Word = other.gameObject.GetComponent<TextMesh> ().text;
	}
}
