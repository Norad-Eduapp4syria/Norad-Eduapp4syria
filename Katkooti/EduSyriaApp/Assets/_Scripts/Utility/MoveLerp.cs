using UnityEngine;
using System.Collections;

public class MoveLerp : MonoBehaviour {

	// Use this for initialization
	public float time;
	public Transform target = null;
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		if (target != null) {
			this.transform.position = Vector3.Lerp (this.transform.position, target.transform.position, time * Time.deltaTime);
		}
	}
}
