using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UIPopInOut : MonoBehaviour
{
	public bool doActiveOnDone = true;


	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	}


	void OnEnable(){
		StartCoroutine (PopInElement (transform));
	}


	void OnDisable(){

	}


	public void PopOut()
	{
		StartCoroutine (PopOutElement (transform));
	}


	public void PopIn()
	{
		StartCoroutine (PopInElement (transform));
	}



	IEnumerator PopInElement(Transform transform, float speed=5f){

		transform.localScale = new Vector3 (0, 0, 0);

		yield return new WaitForSeconds (0);

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
		yield return true;
	}

	IEnumerator PopOutElement(Transform transform, float speed=5.0f){

		transform.localScale = new Vector3 (1, 1, 1);

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
		if (doActiveOnDone) {
			gameObject.SetActive (false);
		}

		yield return true;
	}




}
