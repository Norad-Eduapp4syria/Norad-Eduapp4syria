using UnityEngine;
using System.Collections;

public class CloudAppearingEnter : MonoBehaviour {

	Vector3 dest;
	bool arrived = false;
	// Use this for initialization
	void Start () {
		dest = transform.localPosition;
		transform.localPosition = dest - new Vector3(Screen.width * 2, 0, 0);
	}
	float counter = 0;
	// Update is called once per frame
	void Update () {
		counter += Time.deltaTime;
		counter = counter % 180;
		transform.localPosition += new Vector3(0, Mathf.Sin (counter) / 10, 0);

		if (!arrived) {
			transform.localPosition = Vector3.Lerp (transform.localPosition, dest, 0.05f);
			if (Vector3.Distance (transform.localPosition, dest) < 0.02f) {
				arrived = true;
				//GetComponent<Animator> ().enabled = true;
			}
		} else {
			
		}
	}
}
