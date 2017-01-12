using UnityEngine;
using System.Collections;

public class SmoothFollow : MonoBehaviour {

	// Use this for initialization
	public Transform target;
	public float offset;
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		this.transform.position = Vector3.Lerp(this.transform.position,new Vector3(target.position.x-offset,target.position.y,this.transform.position.z),1*Time.deltaTime);
	}
}
