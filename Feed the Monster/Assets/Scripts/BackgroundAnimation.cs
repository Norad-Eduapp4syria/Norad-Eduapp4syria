using UnityEngine;
using System.Collections;

public class BackgroundAnimation : MonoBehaviour {


	public GameObject ElementsGO;


	Vector3 currentRotate;



	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	}


	void OnEnable()
	{
		setRotate (new Vector3 (0f, 0f, 90f));
		Invoke ("init", 0.5f);
	}

	void init()
	{
		StartCoroutine (MoveInElements ());
	}

	IEnumerator MoveInElements()
	{
		float[] angels = new float[] { -10f, 3.3f, 0f }; 
		float[] speeds = new float[] {   3f,  6f, 6f }; 

		for (int i = 0; i < angels.Length; i++)
		//foreach (float destAngel in angels)
		{
			float destAngel = angels [i];
			float destSpeed = speeds [i];

			Vector3 startScale = currentRotate;
			Vector3 endScale = new Vector3(0f, 0f, destAngel);
			for(float t=0; t<=1; t += destSpeed * Time.deltaTime)
			{
				setRotate (Vector3.Lerp (startScale, endScale, t * t));
				yield return null;
			}
			setRotate(endScale);
		}
	}


	void setRotate(Vector3 v)
	{
		currentRotate = v;
		ElementsGO.transform.rotation = Quaternion.Euler(v);
	}




}
