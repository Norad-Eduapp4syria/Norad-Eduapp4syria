using UnityEngine;
using System.Collections;

public class MoveTapToTarget : MonoBehaviour {

	public Transform target;
	public GameObject Image;
	void Update(){
		if(target!=null)
			Image.transform.position = Camera.main.WorldToScreenPoint(target.transform.position);
	}
}
