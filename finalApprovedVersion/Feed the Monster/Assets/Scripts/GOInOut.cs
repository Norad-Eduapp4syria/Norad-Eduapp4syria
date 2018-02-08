using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GOInOut : MonoBehaviour {

	static float speed=5f;


	public float delay = 0f;
	public bool  destroyOnDone = true;

	Vector3 initScale = Vector3.one;

	void Awake() {
		initScale = transform.localScale;

		transform.localScale = Vector3.zero;
	}

	// Use this for initialization
	void Start () {
	

	}

	void OnEnable(){
		PopIn ();
	}


	// Update is called once per frame
	void Update () {
			
	}





	public void PopIn()
	{
		StartCoroutine (PopInElement ());
	}

	public void PopOut()
	{
		StartCoroutine (PopOutElement ());
	}



	IEnumerator PopInElement(){

		transform.localScale = Vector3.zero;
		if (delay > 0) {
			yield return new WaitForSeconds (delay);
		}

		Vector3[] scales = new Vector3[] { Vector3.zero, initScale * 1.1f, initScale * 0.9f, initScale * 1f };

		foreach (Vector3 destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = destScale;
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}

		yield return true;
	}



	IEnumerator PopOutElement(){

		transform.localScale = initScale;

		Vector3[] scales = new Vector3[] { initScale * 0.9f, initScale * 1.1f, Vector3.zero }; 

		foreach (Vector3 destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = destScale;
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t*t);
				yield return null;
			}
			transform.localScale = endScale;
		}
		if (destroyOnDone) {
			Destroy (gameObject);
		}

		yield return true;
	}

}
