using UnityEngine;
using UnityEngine.UI;
using System.Collections;
using System.Collections.Generic;

public class Feedback : MonoBehaviour
{
	
	public List<GameObject> Feedbacks;
	static Dictionary<string , GameObject> feedbacks_d;


	void Awake()
	{
		this.transform.localScale = Vector3.zero;


		if(feedbacks_d == null) {
			feedbacks_d = new Dictionary<string, GameObject> ();
			foreach(GameObject f in Feedbacks) {
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
//		init (null);
	}

	public void init(string fileName)
	{
//		string path = "Gameplay/Feedbacks/Positive/" + fileName;
//		GameObject go = Resources.Load<GameObject> (path);

		GameObject go = null;


		if (feedbacks_d.ContainsKey (fileName)) {
			go = feedbacks_d [fileName];
		}

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
		yield return new WaitForSeconds(2f);
		Destroy (gameObject);
	}


}
