using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class Feedback : MonoBehaviour
{
	void Awake()
	{
		this.transform.localScale = Vector3.zero;
	}		


	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
//		init (null);
	}

	public void init(string fileName)
	{
		string path = "Gameplay/Feedbacks/Positive/" + fileName;

		GameObject go = Resources.Load<GameObject> (path);
		if (go != null) {
			go = Instantiate (go, transform, false) as GameObject;
			if (go != null) {
				StartCoroutine (PopIn (transform));
				return;
			}
		}
		Destroy (gameObject);
	}

	IEnumerator PopIn(Transform transform, float speed=2.0f){

		/*

		transform.localScale = new Vector3 (0, 0, 0);

		float[] scales = new float[] { 1.1f, 0.9f, 1f, 1f, 1f, 1.2f, 0f }; 

		foreach (float destScale in scales)
		{
			Vector3 startScale = transform.localScale;
			Vector3 endScale = new Vector3(destScale, destScale, destScale);
			for(float t=0; t<=1; t += speed * Time.deltaTime)
			{
				transform.localScale = Vector3.Lerp(startScale, endScale, t * t);
				yield return null;
			}
			transform.localScale = endScale;
		}
*/
		yield return new WaitForSeconds(2f);

		Destroy (gameObject);
	}


}
