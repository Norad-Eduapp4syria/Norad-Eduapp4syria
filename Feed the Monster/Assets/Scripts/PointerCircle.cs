using UnityEngine;
using System.Collections;

public class PointerCircle : MonoBehaviour {

	float SizeMultiplier = 2;
	float AlphaMultiplier = 0.75f;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		transform.localScale += new Vector3 (Time.deltaTime*SizeMultiplier, Time.deltaTime*SizeMultiplier, Time.deltaTime*SizeMultiplier);
		GetComponent<CanvasGroup> ().alpha -= Time.deltaTime * AlphaMultiplier;
		if (GetComponent<CanvasGroup> ().alpha == 0)
			gameObject.SetActive (false);
	}

	void OnEnable() {
		transform.localScale = new Vector3 (0.1f, 0.1f, 0.1f);
		GetComponent<CanvasGroup> ().alpha = 100;
	}
}
