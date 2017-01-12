using UnityEngine;
using UnityEngine.UI;
using System.Collections;


public class LetterSpawn : MonoBehaviour {

	public int id;


	// Use this for initialization
	void Start () {
		Image img = gameObject.GetComponent<Image> ();

		if (img != null) {
			img.enabled = false;
		}

		Text t = gameObject.GetComponentInChildren<Text>();
		if(t != null) 
		{
			Destroy(t.gameObject);
		}
	}

}
