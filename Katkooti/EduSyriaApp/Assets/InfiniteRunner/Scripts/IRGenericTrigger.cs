using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class IRGenericTrigger : MonoBehaviour {

	// Use this for initialization
	public string []texts;
	public Text tex;
	void Start () {
		tex.text=texts[Random.Range(0,texts.Length)];
	}
	
	// Update is called once per frame
	void Update () {
	
	}

}
