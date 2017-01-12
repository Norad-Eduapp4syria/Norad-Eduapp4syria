using UnityEngine;
using System.Collections;

public class FadeIn : MonoBehaviour {

	// Use this for initialization
	Color32 newColor;
	void Start () {
		newColor = this.GetComponent<SpriteRenderer> ().color;
		newColor = new Color32 (newColor.r, newColor.g, newColor.b, 255);
	}

	// Update is called once per frame
	void Update () {
		this.GetComponent<SpriteRenderer>().color = Color32.Lerp ( this.GetComponent<SpriteRenderer>().color, newColor, 2f*Time.deltaTime);
	}
}
