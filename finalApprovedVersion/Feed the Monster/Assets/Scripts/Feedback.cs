using UnityEngine;
using UnityEngine.UI;
using System;
using System.Collections;
using System.Collections.Generic;

public class Feedback : MonoBehaviour
{
	public Action onDone; 
	public Image FeedbackImage;
	public Image MaskImage;


	public List<FeedbackAsset> Feedbacks;
	static Dictionary<string , FeedbackAsset> feedbacks_d;


	void Awake()
	{
		if(feedbacks_d == null) {
			feedbacks_d = new Dictionary<string, FeedbackAsset> ();
			foreach(FeedbackAsset f in Feedbacks) {
				if (!feedbacks_d.ContainsKey (f.name)) {
					feedbacks_d.Add (f.name, f);
				}
			}
		}
	}		


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
	
	}

	void OnEnable()
	{
//		init ("Feedback_v01");
	}

	public void init(string fileName)
	{
		FeedbackAsset fa = null;

		if (feedbacks_d.ContainsKey (fileName)) {
			fa = feedbacks_d [fileName];
		}


		if (fa != null) {
			FeedbackImage.sprite = fa.feedback;
			MaskImage.sprite = fa.mask;
			StartCoroutine (PopOut ());
			return;
		}
		Destroy (gameObject);
	}

	IEnumerator PopOut(float time=3.0f){
		yield return new WaitForSeconds(time);

		if (onDone != null) {
			onDone ();
		}
		Destroy (gameObject);
	}


}
