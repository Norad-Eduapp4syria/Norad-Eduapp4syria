using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class UIPopupPanel : MonoBehaviour {

	private Image windowImage;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable(){
		if (windowImage == null)
			windowImage = transform.GetChild (1).GetComponent<Image> ();

		if(windowImage != null)
			StartCoroutine (PopInElement (windowImage.transform, 0, 10f));
		
		int buttonCounter = 0;
		float rate = 10.0f;

		for (int i = 2; i < transform.childCount; i++) {
			Transform child = transform.GetChild (i);

			if (isObjectAllow(child.gameObject)) {
				StartCoroutine (PopInElement (child, (buttonCounter++) / rate++));
			}
		}
		Popup ();
	}


	bool isObjectAllow(GameObject go)
	{
		string name = go.name.ToLower ();
		if (name.Contains ("background")) {
			return false;
		} else {
			UIPopInOut p1 = go.GetComponent<UIPopInOut>();
			if (p1 != null) {
				return false;
			} else {
				UIPopupPanel p2 = go.GetComponent<UIPopupPanel>();
				if (p2 != null) {
					return false;
				}
			}
		}
		return true;
	}

	void OnDisable(){
		
	}

	public void Popup(){
	}

	public void PopOut(){
		int buttonCounter = 0;
		float rate = 5.0f;

		for (int i = transform.childCount - 1; i >= 0; i--) {

			Transform child = transform.GetChild (i);

			if (isObjectAllow(child.gameObject)) {
				StartCoroutine (PopOutElement (child, (buttonCounter++) / rate++));
			}
		}
	}

	IEnumerator PopInElement(Transform transform, float delay = 0, float speed=5f){

		transform.localScale = new Vector3 (0, 0, 0);

		yield return new WaitForSeconds (delay);

		float[] scales = new float[] { 0f, 1.1f, 0.9f, 1f };

		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
	}

	IEnumerator PopOutElement(Transform transform, float delay = 0, float speed=5.0f){

		transform.localScale = new Vector3 (1, 1, 1);

		yield return new WaitForSeconds (delay);

		//float[] scales = new float[] { 1f, 0.9f, 1f, 0f }; 
		float[] scales = new float[] { 0.9f, 1.1f, 0f }; 
		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
		gameObject.SetActive (false);
	}



	//Jonathan
	public void PopInAny(Transform _transform, float delay = 0, float speed = 5f) {
		if (_transform == null) {
			return;
		}

		StartCoroutine (PopInElement (_transform, delay, speed));
	}

	public void PopOutAny(Transform _transform, float delay = 0, float speed = 5f) {
		if (_transform == null) {
			return;
		}

		StartCoroutine (PopOutElementAny (_transform, delay, speed));
	}

	IEnumerator PopOutElementAny(Transform transform, float delay = 0, float speed=5.0f){

		transform.localScale = new Vector3 (1, 1, 1);

		yield return new WaitForSeconds (delay);

		//float[] scales = new float[] { 1f, 0.9f, 1f, 0f }; 
		float[] scales = new float[] { 0.9f, 1.1f, 0f }; 


		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
	}
}
