using UnityEngine;
using System.Collections;

public class UIZoomOut : MonoBehaviour {
	public delegate void onDoneDelegate();
	public onDoneDelegate onDone;


	bool isZoomDone = false;
	bool isCircleDone = false;


	float startSize;
	float targetSize;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (isZoomDone && isCircleDone) {
			if (onDone != null) {
				onDone ();
			}
			Destroy (this);
		}

	}

	public void init(float size = 5f)
	{
		startSize = Camera.main.orthographicSize;
		targetSize = size;


		StartCoroutine (ZoomIn ());
		StartCoroutine (Circle ());
	}




	IEnumerator ZoomIn(){
		for (float t = 0; t <= 1; t += Time.deltaTime*1.8f) {
			Camera.main.orthographicSize = Mathf.Lerp (startSize, targetSize, t*t*t);
			Camera.main.transform.position = new Vector3(
				Camera.main.transform.position.x,
				Mathf.Lerp (-1.3f, 0f, t*t*t),
				Camera.main.transform.position.z
			);
			yield return null;
		}
		Camera.main.orthographicSize = targetSize;
		Camera.main.transform.position = new Vector3(Camera.main.transform.position.x, 0, Camera.main.transform.position.z);

		isZoomDone = true;
	}

	IEnumerator Circle(){
		//var tran = transform.GetChild (0).gameObject.GetComponent<RectTransform> ();
		var tran = (RectTransform)transform;

		var startScale = new Vector3 (1f, 1f, 1f);
		var endScale = new Vector3 (3.1f, 3.1f, 3.1f);
		tran.localScale = startScale;
		yield return new WaitForSeconds (.2f);
		for (float t = 0; t <= 1; t += Time.deltaTime * 4) {
			tran.localScale = Vector3.Lerp(startScale, endScale, t*t*t);
			yield return null;
		}
		tran.localScale = endScale;

		isCircleDone = true;
	}


}
