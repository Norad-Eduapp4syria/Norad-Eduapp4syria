using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class UIPopInOut : MonoBehaviour
{
	public bool startOnEnable = true;
	public bool doActiveOnDone = true;
	public float delay = 0f;



	float mInitScale;

	public float InitScale {
		set {
			mInitScale = value;
		}
	}


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	}


	void OnEnable(){
		if (startOnEnable) {
			PopIn ();
		}
	}


	void OnDisable(){
		transform.localScale = new Vector3(mInitScale, mInitScale, mInitScale);
	}


	public void PopOut()
	{
		mInitScale = transform.localScale.x;
		StartCoroutine (PopOutElement (transform));
	}


	public void PopIn()
	{
		mInitScale = transform.localScale.x;
		StartCoroutine (PopInElement (transform));
	}



	IEnumerator PopInElement(Transform transform, float speed=5f){

		transform.localScale = new Vector3 (0, 0, 0);
		if (delay > 0) {
			yield return new WaitForSeconds (delay);
		}

		float[] scales = new float[] { 0f, mInitScale * 1.1f, mInitScale * 0.9f, mInitScale * 1f };

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

		transform.localScale = new Vector3 (mInitScale * 1, mInitScale * 1, mInitScale * 1);

		float[] scales = new float[] { mInitScale * 0.9f, mInitScale * 1.1f, 0f }; 

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
			transform.localScale = new Vector3(mInitScale, mInitScale, mInitScale);
		}

		yield return true;
	}




}
